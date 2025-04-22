#include "Hermes/ProxyServer.h"
#include "Hermes/Logger.h"
#include <boost/beast.hpp>
#include <thread>

namespace Hermes {
    ProxyServer::ProxyServer(boost::asio::io_context& io_context, 
                           const boost::asio::ip::tcp::endpoint& endpoint, 
                           const std::string& proxy_host)
        : io_context_(io_context), endpoint_(endpoint), proxy_host_(proxy_host),
          acceptor_(io_context_, endpoint_) {
        LOG_INFO("Proxy server initialized for " + proxy_host_);
    }

    void ProxyServer::start() {
        LOG_INFO("Proxy server started on port " + std::to_string(endpoint_.port()));
        accept_connections();
    }

    void ProxyServer::accept_connections() {
        acceptor_.async_accept(
            [this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket) {
                if (!ec) {
                    LOG_INFO("New proxy connection from " + 
                            socket.remote_endpoint().address().to_string());
                    std::thread(&ProxyServer::proxy_request, this, std::move(socket)).detach();
                } else {
                    LOG_WARNING("Accept error: " + ec.message());
                }
                accept_connections();
            });
    }

    void ProxyServer::proxy_request(boost::asio::ip::tcp::socket client_socket) {
        try {
            // 1. Чтение запроса
            boost::beast::flat_buffer buffer;
            boost::beast::http::request<boost::beast::http::string_body> request;
            boost::beast::http::read(client_socket, buffer, request);

            LOG_INFO("Proxy request: " + std::string(request.method_string()) + 
                    " " + std::string(request.target()));

            // 2. Разбор proxy_host
            size_t colon_pos = proxy_host_.find(':');
            std::string host = proxy_host_.substr(0, colon_pos);
            std::string port = colon_pos != std::string::npos ? 
                             proxy_host_.substr(colon_pos + 1) : "80";

            // 3. Подключение к целевому серверу
            boost::asio::ip::tcp::resolver resolver(io_context_);
            auto const results = resolver.resolve(host, port);
            boost::asio::ip::tcp::socket server_socket(io_context_);
            boost::asio::connect(server_socket, results.begin(), results.end());

            // 4. Отправка запроса
            request.set(boost::beast::http::field::host, host);
            boost::beast::http::write(server_socket, request);

            // 5. Получение и передача ответа
            boost::beast::flat_buffer response_buffer;
            boost::beast::http::response<boost::beast::http::dynamic_body> response;
            boost::beast::http::read(server_socket, response_buffer, response);
            boost::beast::http::write(client_socket, response);

            LOG_INFO("Proxy completed: " + std::to_string(response.result_int()));

        } catch (const std::exception& e) {
            LOG_WARNING("Proxy error: " + std::string(e.what()));
            try {
                boost::beast::http::response<boost::beast::http::string_body> res;
                res.result(boost::beast::http::status::bad_gateway);
                res.body() = "502 Bad Gateway";
                res.prepare_payload();
                boost::beast::http::write(client_socket, res);
            } catch (...) {
                LOG_WARNING("Failed to send error response");
            }
        }
    }
}
#include "Hermes/ProxyServer.h"
#include "Hermes/Logger.h"
#include <boost/beast.hpp>
#include <thread>

namespace Hermes {
    ProxyServer::ProxyServer(boost::asio::io_context& io_context, 
                           const boost::asio::ip::tcp::endpoint& endpoint, 
                           const std::string& proxy_host)
        : io_context_(io_context), acceptor_(io_context, endpoint), proxy_host_(proxy_host),
          endpoint_(endpoint) {
        LOG_INFO("Proxy server initialized on port " + std::to_string(endpoint.port()));
    }

    void ProxyServer::start() {
        LOG_INFO("Proxy server started");
        acceptConnections();
    }

    void ProxyServer::stop() {
        acceptor_.close();
    }

    void ProxyServer::acceptConnections() {
        acceptor_.async_accept(
            [this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket) {
                if (!ec) {
                    LOG_INFO("New proxy connection from " + 
                            socket.remote_endpoint().address().to_string());
                    std::thread(&ProxyServer::proxyRequest, this, std::move(socket)).detach();
                } else {
                    LOG_WARNING("Accept error: " + ec.message());
                }
                acceptConnections();
            });
    }

    void ProxyServer::proxyRequest(boost::asio::ip::tcp::socket client_socket) {
        try {
            std::string host = proxy_host_;
            std::string port = "80"; 
            
            size_t colon_pos = proxy_host_.find(':');
            if (colon_pos != std::string::npos) {
                host = proxy_host_.substr(0, colon_pos);
                port = proxy_host_.substr(colon_pos + 1);
            }

            boost::asio::ip::tcp::resolver resolver(io_context_);
            auto endpoints = resolver.resolve(host, port);

            boost::asio::ip::tcp::socket server_socket(io_context_);
            boost::asio::connect(server_socket, endpoints);

            boost::beast::flat_buffer buffer;
            boost::beast::http::request<boost::beast::http::string_body> req;
            boost::beast::http::read(client_socket, buffer, req);

            LOG_INFO("Proxying request: " + std::string(req.method_string()) + 
                    " " + std::string(req.target()));

            boost::beast::http::write(server_socket, req);

            boost::beast::flat_buffer server_buffer;
            boost::beast::http::response<boost::beast::http::string_body> res;
            boost::beast::http::read(server_socket, server_buffer, res);

            boost::beast::http::write(client_socket, res);

            client_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_send);
            server_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_send);

        } catch (const std::exception& e) {
            LOG_WARNING("Proxy error: " + std::string(e.what()));
            client_socket.close();
        }
    }
}
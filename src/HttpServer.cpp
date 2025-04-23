#include "Hermes/HttpServer.h"
#include "Hermes/Logger.h"
#include <boost/beast.hpp>
#include <thread>
#include <iostream>

namespace Hermes {
    HttpServer::HttpServer(boost::asio::io_context& io_context, 
                         const boost::asio::ip::tcp::endpoint& endpoint, 
                         Router& router)
        : io_context_(io_context)
        , acceptor_(io_context, endpoint)
        , router_(router) {
        LOG_INFO("HTTP server initialized on port " + std::to_string(endpoint.port()));
    }

    void HttpServer::start() {
        LOG_INFO("HTTP server started");
        acceptConnections();
    }

    void HttpServer::stop() {
        acceptor_.close();
    }

    void HttpServer::acceptConnections() {
        acceptor_.async_accept(
            [this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket) {
                if (!ec) {
                    LOG_INFO("New HTTP connection from " + 
                            socket.remote_endpoint().address().to_string());
                    std::thread(&HttpServer::handleRequest, this, std::move(socket)).detach();
                } else {
                    LOG_WARNING("Accept error: " + ec.message());
                }
                acceptConnections();
            });
    }

    void HttpServer::handleRequest(boost::asio::ip::tcp::socket socket) {
        try {
            boost::beast::flat_buffer buffer;
            boost::beast::http::request<boost::beast::http::string_body> req;
            
            // 1. Чтение запроса с обработкой ошибок
            boost::system::error_code ec;
            boost::beast::http::read(socket, buffer, req, ec);
            
            if (ec == boost::beast::http::error::end_of_stream) {
                
                LOG_INFO("Client closed connection prematurely");
                socket.shutdown(boost::asio::ip::tcp::socket::shutdown_send, ec);
                return;
            }
            else if (ec) {
                throw boost::system::system_error(ec);
            }
    
            // 2. Обработка запроса
            LOG_INFO("HTTP request: " + std::string(req.method_string()) + 
                               " " + std::string(req.target()));
            
            boost::beast::http::response<boost::beast::http::string_body> res;
            router_.handleRequest(std::string(req.target()), req, res);
    
            // 3. Отправка ответа с обработкой ошибок
            boost::beast::http::write(socket, res, ec);
            if (ec) {
                LOG_WARNING("Failed to send response: " + ec.message());
            }
            else {
                LOG_INFO("HTTP response: " + std::to_string(res.result_int()));
            }
    
        } catch (const std::exception& e) {
            LOG_WARNING("HTTP handler error: " + std::string(e.what()));
            
            try {
                // Попытка отправить ошибку клиенту
                boost::beast::http::response<boost::beast::http::string_body> res;
                res.result(boost::beast::http::status::internal_server_error);
                res.body() = "500 Internal Server Error";
                res.prepare_payload();
                boost::beast::http::write(socket, res);
            } catch (...) {
                // Игнорируем ошибки при отправке error response
            }
        }
        
        // Корректное закрытие сокета
        boost::system::error_code ec;
        socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
        if (ec && ec != boost::asio::error::not_connected) {
            LOG_WARNING("Socket shutdown error: " + ec.message());
        }
    }
}
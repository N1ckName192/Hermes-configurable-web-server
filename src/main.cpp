#include "Hermes/Router.h"
#include "Hermes/HttpServer.h"
#include "Hermes/ProxyServer.h"
#include "Hermes/Logger.h"
#include "Hermes/StaticFileHandler.h"
#include "Hermes/Config.h"
#include "Hermes/Test/TestFramework.h"
#include <boost/asio.hpp>
#include <memory>
#include <vector>
#include <iostream>
#include <filesystem>

namespace Hermes {
    namespace Test {
        bool runTests() {
            bool allPassed = true;
            
            // Тест 1: Проверка маршрутизатора
            try {
                Router router("static");
                router.addRoute("/test", [](auto& req, auto& res) {
                    res.result(boost::beast::http::status::ok);
                    res.body() = "OK";
                });
                
                boost::beast::http::request<boost::beast::http::string_body> req;
                req.target("/test");
                boost::beast::http::response<boost::beast::http::string_body> res;
                
                router.handleRequest(std::string(req.target()), req, res);
                
                if (res.result() != boost::beast::http::status::ok || res.body() != "OK") {
                    throw std::runtime_error("Router test failed");
                }
                
                LOG_INFO("[TEST] Router test passed");
            } catch (const std::exception& e) {
                LOG_WARNING("[TEST] Router test failed: " + std::string(e.what()));
                allPassed = false;
            }
            
            // Тест 3: Проверка прокси
            try {
                boost::asio::io_context io;
                ProxyServer proxy(io, 
                    boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 9090),
                    "localhost:8080");
                
                LOG_INFO("[TEST] Proxy initialization test passed");
            } catch (const std::exception& e) {
                LOG_WARNING("[TEST] Proxy test failed: " + std::string(e.what()));
                allPassed = false;
            }
            
            return allPassed;
        }
    }

    class TcpServer {
    public:
        TcpServer(boost::asio::io_context& io_context, const boost::asio::ip::tcp::endpoint& endpoint)
            : io_context_(io_context), acceptor_(io_context, endpoint) {
            LOG_INFO("TCP server initialized on port " + std::to_string(endpoint.port()));
        }

        void start() {
            acceptConnections();
        }

    private:
        void acceptConnections() {
            acceptor_.async_accept(
                [this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket) {
                    if (!ec) {
                        LOG_INFO("New TCP connection from " + 
                                socket.remote_endpoint().address().to_string());
                        std::thread(&TcpServer::handleConnection, this, std::move(socket)).detach();
                    }
                    acceptConnections();
                });
        }

        void handleConnection(boost::asio::ip::tcp::socket socket) {
            try {
                LOG_INFO("TCP connection established");
                std::array<char, 1024> buffer;
                boost::system::error_code ec;

                while (!ec) {
                    LOG_INFO("Waiting for data...");
                    size_t bytes = socket.read_some(boost::asio::buffer(buffer), ec);
                    if (ec) {
                        LOG_WARNING("Read error: " + ec.message());
                        break;
                    }

                    std::string message(buffer.data(), bytes);
                    LOG_INFO("Received " + std::to_string(bytes) + " bytes: '" + message + "'");

                    if (message == "PING") {
                        LOG_INFO("Sending PONG response");
                        const char* pong = "PONG";
                        boost::asio::write(socket, boost::asio::buffer(pong, 4), ec);
                        if (ec) {
                            LOG_WARNING("Write error: " + ec.message());
                            break;
                        }
                        LOG_INFO("PONG sent successfully");
                    }
                }
            } catch (const std::exception& e) {
                LOG_WARNING("TCP error: " + std::string(e.what()));
            }
            LOG_INFO("TCP connection closed");
        }

        boost::asio::io_context& io_context_;
        boost::asio::ip::tcp::acceptor acceptor_;
    };
}

int main() {
    std::cout << "Run tests before starting server? (y/n): ";
    std::string choice;
    std::getline(std::cin, choice);
    
    if (choice == "y" || choice == "Y") {
        if (!Hermes::Test::TestRunner::getInstance().runAllTests()) {
            LOG_WARNING("Tests failed! Aborting startup.");
            return 1;
        }
        LOG_INFO("All tests passed successfully!");
        LOG_INFO("-----------------------------------");
        LOG_INFO("-----------------------------------");
    }

    try {
        LOG_INFO("Starting HTTP server...");
        boost::asio::io_context io_context;

        std::filesystem::path project_root = std::filesystem::current_path().parent_path();
        std::string static_root = (project_root / "Debug" / "static").lexically_normal().string();
        LOG_INFO("Static root path: " + static_root);
        
        Hermes::Router router(static_root);

        router.addRoute("/", [](auto& req, auto& res) {
            res.result(boost::beast::http::status::ok);
            res.set(boost::beast::http::field::content_type, "text/html");
            res.set(boost::beast::http::field::server, "Hermes/1.0");
            res.body() = 
                "<html>"
                "<head><title>Hermes Server</title></head>"
                "<body>"
                "<h1>Welcome to Hermes HTTP Server</h1>"
                "<p>This is a custom C++ HTTP server implementation</p>"
                "</body>"
                "</html>";
            res.prepare_payload();
        });

        router.addRoute("/test", [](auto& req, auto& res) {
            res.result(boost::beast::http::status::ok);
            res.set(boost::beast::http::field::content_type, "application/json");
            res.set(boost::beast::http::field::server, "Hermes/1.0");
            res.body() = "{\"status\":\"success\",\"message\":\"Server is working\"}";
            res.prepare_payload();
        });

        router.addRoute("/work", [](auto& req, auto& res) {
            res.result(boost::beast::http::status::ok);
            res.set(boost::beast::http::field::content_type, "text/plain");
            res.set(boost::beast::http::field::server, "Hermes/1.0");
            res.body() = "The server is working correctly!";
            res.prepare_payload();
        });

        const unsigned short http_port = 8080;
        const unsigned short proxy_port = 9090;
        const unsigned short tcp_port = 7070;
        const std::string proxy_target = "localhost:" + std::to_string(http_port);

        Hermes::HttpServer http_server(
            io_context,
            boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), http_port),
            router
        );
        http_server.start();
        LOG_INFO("HTTP server started on port " + std::to_string(http_port));

        Hermes::ProxyServer proxy_server(
            io_context,
            boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), proxy_port),
            proxy_target
        );
        proxy_server.start();
        LOG_INFO("Proxy server started on port " + std::to_string(proxy_port) + 
                " forwarding to " + proxy_target);

        Hermes::TcpServer tcp_server(
            io_context,
            boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), tcp_port)
        );
        tcp_server.start();
        LOG_INFO("TCP server started on port " + std::to_string(tcp_port));

        LOG_INFO("All services initialized successfully. Starting event loop...");
        io_context.run();
        LOG_INFO("Server shutdown gracefully");

    } catch (const std::exception& e) {
        LOG_WARNING("Fatal error: " + std::string(e.what()));
        return 1;
    } catch (...) {
        LOG_WARNING("Fatal error: Unknown exception occurred");
        return 1;
    }

    return 0;
}
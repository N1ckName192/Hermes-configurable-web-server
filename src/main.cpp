#include "Hermes/Router.h"
#include "Hermes/HttpServer.h"
#include "Hermes/ProxyServer.h"
#include "Hermes/Logger.h"
#include "Hermes/StaticFileHandler.h"
#include "Hermes/Config.h"
#include <boost/asio.hpp>
#include <memory>
#include <vector>


namespace Hermes {
    namespace Test {
        bool runTests() {
            bool allPassed = true;
            
            // Тест 1: Проверка маршрутизатора
            try {
                Router router("static");
                router.add_route("/test", [](auto& req, auto& res) {
                    res.result(boost::beast::http::status::ok);
                    res.body() = "OK";
                });
                
                boost::beast::http::request<boost::beast::http::string_body> req;
                req.target("/test");
                boost::beast::http::response<boost::beast::http::string_body> res;
                
                router.handle_request(std::string(req.target()), req, res);
                
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
}

int main() {
    std::cout << "Run tests before starting server? (y/n): ";
    std::string choice;
    std::getline(std::cin, choice);
    
    if (choice == "y" || choice == "Y") {
        LOG_INFO("Starting self-tests...");
        if (!Hermes::Test::runTests()) {
            LOG_WARNING("Tests failed! Aborting startup.");
            return 1;
        }
        LOG_INFO("All tests passed successfully!");
        LOG_INFO("-----------------------------------");
        LOG_INFO("-----------------------------------");
    }

    try {
        LOG_INFO("Starting HTTP server...");
        // Инициализация контекста ввода-вывода
        boost::asio::io_context io_context;

        // Инициализация маршрутизатора с корневой директорией для статических файлов
        Hermes::Router router("static");

        // Добавление обработчиков маршрутов
        // 1. Главная страница
        router.add_route("/", 
            [](boost::beast::http::request<boost::beast::http::string_body>& req,
               boost::beast::http::response<boost::beast::http::string_body>& res) {
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

        // 2. Тестовый маршрут
        router.add_route("/test", 
            [](boost::beast::http::request<boost::beast::http::string_body>& req,
               boost::beast::http::response<boost::beast::http::string_body>& res) {
                res.result(boost::beast::http::status::ok);
                res.set(boost::beast::http::field::content_type, "application/json");
                res.set(boost::beast::http::field::server, "Hermes/1.0");
                res.body() = "{\"status\":\"success\",\"message\":\"Server is working\"}";
                res.prepare_payload();
            });

        // 3. Маршрут для проверки работы сервера
        router.add_route("/work", 
            [](boost::beast::http::request<boost::beast::http::string_body>& req,
               boost::beast::http::response<boost::beast::http::string_body>& res) {
                res.result(boost::beast::http::status::ok);
                res.set(boost::beast::http::field::content_type, "text/plain");
                res.set(boost::beast::http::field::server, "Hermes/1.0");
                res.body() = "The server is working correctly!";
                res.prepare_payload();
            });

        // Параметры серверов
        const unsigned short http_port = 8080;
        const unsigned short proxy_port = 9090;
        const std::string proxy_target = "localhost:" + std::to_string(http_port);

        // Создание и запуск HTTP сервера
        Hermes::HttpServer http_server(
            io_context,
            boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), http_port),
            router
        );
        http_server.start();
        LOG_INFO("HTTP server started on port " + std::to_string(http_port));

        // Создание и запуск прокси-сервера
        Hermes::ProxyServer proxy_server(
            io_context,
            boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), proxy_port),
            proxy_target
        );
        proxy_server.start();
        LOG_INFO("Proxy server started on port " + std::to_string(proxy_port) + 
                " forwarding to " + proxy_target);

        LOG_INFO("All services initialized successfully. Starting event loop...");

        // Запуск основного цикла обработки событий
        io_context.run();

        LOG_INFO("Server shutdown gracefully");

    } catch (const std::exception& e) {
        // Обработка критических ошибок
        LOG_WARNING("Fatal error: " + std::string(e.what()));
        return 1; // Возвращаем код ошибки
    } catch (...) {
        // Обработка неизвестных исключений
        LOG_WARNING("Fatal error: Unknown exception occurred");
        return 1;
    }

    return 0;
}
#include "Hermes/Router.h"
#include "Hermes/HttpServer.h"
#include "Hermes/ProxyServer.h"
#include "Hermes/Logger.h"
#include <boost/asio.hpp>

int main() {
    try {
        boost::asio::io_context io_context;

        // Инициализация маршрутизатора
        Hermes::Router router("");
        router.add_route("/", [](auto& req, auto& res) {
            res.result(boost::beast::http::status::ok);
            res.body() = "Welcome to Hermes server!";
            res.set(boost::beast::http::field::server, "Hermes/1.0");
        });

        router.add_route("/work", [](auto& req, auto& res) {
            res.result(boost::beast::http::status::ok);
            res.body() = "Вроде как работает!)";
            res.set(boost::beast::http::field::server, "Hermes/1.0");
        });

        // Запуск серверов
        Hermes::HttpServer http_server(io_context, 
                                     boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8080), 
                                     router);
        http_server.start();

        Hermes::ProxyServer proxy_server(io_context, 
                                       boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 9090), 
                                       "localhost:8080");
        proxy_server.start();

        LOG_INFO("All services started");
        io_context.run();

    } catch (const std::exception& e) {
        LOG_WARNING("Fatal error: " + std::string(e.what()));
        return 1;
    }
    return 0;
}
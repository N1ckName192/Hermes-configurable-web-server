#ifndef HERMES_ROUTER_H
#define HERMES_ROUTER_H

#include <boost/beast/http.hpp>
#include <unordered_map>
#include <functional>
#include <memory>
#include <string>

namespace Hermes {
    class Router {
    public:
        using HttpHandler = std::function<void(
            boost::beast::http::request<boost::beast::http::string_body>&,
            boost::beast::http::response<boost::beast::http::string_body>&)>;

        explicit Router(const std::string& static_root = "");
        
        void add_route(const std::string& path, HttpHandler handler);
        void handle_request(
            const std::string& path,
            boost::beast::http::request<boost::beast::http::string_body>& req,
            boost::beast::http::response<boost::beast::http::string_body>& res);

    private:
        std::unordered_map<std::string, HttpHandler> routes_;
        std::string static_root_;
    };
}

#endif
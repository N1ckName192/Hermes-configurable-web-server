#include "Hermes/Router.h"

namespace Hermes {

    Router::Router(const std::string& static_root) 
        : static_root_(static_root) {
    }

    void Router::add_route(const std::string& path, HttpHandler handler) {
        routes_[path] = handler;
    }

    void Router::handle_request(
            const std::string& path,
            boost::beast::http::request<boost::beast::http::string_body>& req,
            boost::beast::http::response<boost::beast::http::string_body>& res) {
        if (routes_.find(path) != routes_.end()) {
            routes_[path](req, res);
        } else {
            res.result(boost::beast::http::status::not_found);
            res.body() = "404 Not Found";
        }
    }
}
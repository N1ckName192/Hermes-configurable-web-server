#include "Hermes/Router.h"
#include "Hermes/StaticFileHandler.h"
#include <boost/beast/http.hpp>

namespace Hermes {

    Router::Router(const std::string& static_root) {
        static_handler_ = std::make_unique<StaticFileHandler>(static_root);
    }

    void Router::addRoute(const std::string& path, 
                         std::function<void(boost::beast::http::request<boost::beast::http::string_body>&,
                                          boost::beast::http::response<boost::beast::http::string_body>&)> handler) {
        routes_[path] = std::move(handler);
    }

    void Router::addHandler(std::unique_ptr<IRequestHandler> handler) {
        handlers_.push_back(std::move(handler));
    }

    void Router::handleRequest(const std::string& path,
                             boost::beast::http::request<boost::beast::http::string_body>& req,
                             boost::beast::http::response<boost::beast::http::string_body>& res) {

        auto it = routes_.find(path);
        if (it != routes_.end()) {
            it->second(req, res);
            return;
        }
        
        for (const auto& handler : handlers_) {
            if (handler->canHandle(path)) {
                handler->handleRequest(req, res);
                return;
            }
        }
        
        if (static_handler_ && static_handler_->canHandle(path)) {
            static_handler_->handleRequest(req, res);
            return;
        }
        
        res.result(boost::beast::http::status::not_found);
        res.body() = "404 Not Found";
        res.prepare_payload();
    }
}
#pragma once

#include "Hermes/IRequestHandler.h"
#include <boost/beast/http.hpp>
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <unordered_map>

namespace Hermes {

class StaticFileHandler;

class Router {
public:
    explicit Router(const std::string& static_root);
    
    void addRoute(const std::string& path, 
                 std::function<void(boost::beast::http::request<boost::beast::http::string_body>&,
                                  boost::beast::http::response<boost::beast::http::string_body>&)> handler);
    
    void addHandler(std::unique_ptr<IRequestHandler> handler);
    
    void handleRequest(const std::string& path,
                      boost::beast::http::request<boost::beast::http::string_body>& req,
                      boost::beast::http::response<boost::beast::http::string_body>& res);
    
private:
    std::unordered_map<std::string, 
        std::function<void(boost::beast::http::request<boost::beast::http::string_body>&,
                         boost::beast::http::response<boost::beast::http::string_body>&)>> routes_;
    
    std::vector<std::unique_ptr<IRequestHandler>> handlers_;
    std::unique_ptr<StaticFileHandler> static_handler_;
};

} // namespace Hermes
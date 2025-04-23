#pragma once

#include <boost/beast/http.hpp>
#include <string>

namespace Hermes {

class IRequestHandler {
public:
    virtual ~IRequestHandler() = default;
    
    virtual bool canHandle(const std::string& path) const = 0;
    virtual void handleRequest(
        boost::beast::http::request<boost::beast::http::string_body>& req,
        boost::beast::http::response<boost::beast::http::string_body>& res) = 0;
};

} // namespace Hermes 
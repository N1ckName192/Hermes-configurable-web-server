#ifndef HERMES_STATICFILEHANDLER_H
#define HERMES_STATICFILEHANDLER_H

#include <boost/beast/http.hpp>
#include <string>

namespace Hermes {
    class StaticFileHandler {
    public:
        StaticFileHandler(const std::string& root_dir);
        
        bool handle_request(
            const boost::beast::http::request<boost::beast::http::string_body>& req,
            boost::beast::http::response<boost::beast::http::string_body>& res);
            
    private:
        std::string root_dir_;
        
        std::string get_mime_type(const std::string& path);
    };
}

#endif
#pragma once

#include "Hermes/IRequestHandler.h"
#include <boost/beast/http.hpp>
#include <string>
#include <filesystem>

namespace Hermes {

class StaticFileHandler : public IRequestHandler {
public:
    explicit StaticFileHandler(const std::string& root_dir);
    
    bool canHandle(const std::string& path) const override;
    void handleRequest(
        boost::beast::http::request<boost::beast::http::string_body>& req,
        boost::beast::http::response<boost::beast::http::string_body>& res) override;
    
private:
    std::filesystem::path root_dir_;
    
    std::string getMimeType(const std::string& path) const;
    bool isFileAccessible(const std::filesystem::path& file_path) const;

    std::string getContentType(const std::filesystem::path& path) const;
};

} // namespace Hermes
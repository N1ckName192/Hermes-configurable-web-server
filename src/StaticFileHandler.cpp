#include "Hermes/StaticFileHandler.h"
#include "Hermes/Logger.h"
#include <boost/beast/http.hpp>
#include <filesystem>
#include <fstream>

namespace Hermes {

StaticFileHandler::StaticFileHandler(const std::string& root_dir)
    : root_dir_(root_dir) {
    LOG_INFO("StaticFileHandler initialized with root: " + root_dir);
    if (!std::filesystem::exists(root_dir_)) {
        LOG_WARNING("Static directory does not exist: " + root_dir);
        std::filesystem::create_directories(root_dir_);
        LOG_INFO("Created static directory: " + root_dir);
    } else {
        LOG_INFO("Static directory exists: " + root_dir);
        LOG_INFO("Directory contents:");
        for (const auto& entry : std::filesystem::directory_iterator(root_dir_)) {
            LOG_INFO("  " + entry.path().string());
        }
    }
}

bool StaticFileHandler::canHandle(const std::string& path) const {
    LOG_INFO("canHandle called with path: " + path);
    
    if (path.empty() || path[0] != '/') {
        LOG_INFO("Invalid path format: " + path);
        return false;
    }
    
    std::string clean_path = path;
    if (clean_path.find("/static") == 0) {
        clean_path = clean_path.substr(7);
    }
    
    if (clean_path.empty() || clean_path.back() == '/') {
        clean_path += "index.html";
    }
    
    if (!clean_path.empty() && clean_path[0] == '/') {
        clean_path = clean_path.substr(1);
    }
    
    std::filesystem::path file_path = std::filesystem::path(root_dir_) / clean_path;
    LOG_INFO("Checking file: " + file_path.string());
    LOG_INFO("File exists: " + std::string(std::filesystem::exists(file_path) ? "yes" : "no"));
    LOG_INFO("Is regular file: " + std::string(std::filesystem::is_regular_file(file_path) ? "yes" : "no"));
    
    bool accessible = isFileAccessible(file_path);
    LOG_INFO("File accessible: " + std::string(accessible ? "yes" : "no"));
    return accessible;
}

void StaticFileHandler::handleRequest(
    boost::beast::http::request<boost::beast::http::string_body>& req,
    boost::beast::http::response<boost::beast::http::string_body>& res) {
    
    try {
        std::string target = std::string(req.target());
        LOG_INFO("Handling request for: " + target);
        
        if (target.empty() || target[0] != '/') {
            target = "/" + target;
        }

        if (target.find("/static") == 0) {
            target = target.substr(7);
        }

        if (target.empty() || target.back() == '/') {
            target += "index.html";
        }

        if (!target.empty() && target[0] == '/') {
            target = target.substr(1);
        }

        std::filesystem::path file_path = std::filesystem::path(root_dir_) / target;
        LOG_INFO("Full file path: " + file_path.string());
        LOG_INFO("File exists: " + std::string(std::filesystem::exists(file_path) ? "yes" : "no"));
        LOG_INFO("Is regular file: " + std::string(std::filesystem::is_regular_file(file_path) ? "yes" : "no"));

        if (!std::filesystem::exists(file_path)) {
            LOG_WARNING("File not found: " + file_path.string());
            res.result(boost::beast::http::status::not_found);
            res.body() = "404 Not Found";
            res.prepare_payload();
            return;
        }
        
        if (!std::filesystem::is_regular_file(file_path)) {
            LOG_WARNING("Not a regular file: " + file_path.string());
            res.result(boost::beast::http::status::not_found);
            res.body() = "404 Not Found";
            res.prepare_payload();
            return;
        }

        std::ifstream file(file_path, std::ios::binary);
        if (!file) {
            LOG_WARNING("Failed to open file: " + file_path.string());
            res.result(boost::beast::http::status::internal_server_error);
            res.body() = "500 Internal Server Error";
            res.prepare_payload();
            return;
        }

        std::string content((std::istreambuf_iterator<char>(file)),
                          std::istreambuf_iterator<char>());

        res.result(boost::beast::http::status::ok);
        res.set(boost::beast::http::field::content_type, 
                boost::beast::string_view(getContentType(file_path)));
        res.body() = content;
        res.prepare_payload();
        LOG_INFO("Successfully served file: " + file_path.string());

    } catch (const std::exception& e) {
        LOG_WARNING("Static file handler error: " + std::string(e.what()));
        res.result(boost::beast::http::status::internal_server_error);
        res.body() = "500 Internal Server Error";
        res.prepare_payload();
    }
}

std::string StaticFileHandler::getContentType(const std::filesystem::path& path) const {
    std::string ext = path.extension().string();
    if (ext == ".html") return "text/html";
    if (ext == ".css") return "text/css";
    if (ext == ".js") return "application/javascript";
    if (ext == ".json") return "application/json";
    if (ext == ".png") return "image/png";
    if (ext == ".jpg" || ext == ".jpeg") return "image/jpeg";
    if (ext == ".gif") return "image/gif";
    if (ext == ".svg") return "image/svg+xml";
    return "application/octet-stream";
}

bool StaticFileHandler::isFileAccessible(const std::filesystem::path& file_path) const {
    try {
        return std::filesystem::exists(file_path) && 
               std::filesystem::is_regular_file(file_path) &&
               file_path.string().find("..") == std::string::npos;
    } catch (...) {
        return false;
    }
}

} // namespace Hermes
#include "Hermes/StaticFileHandler.h"
#include <fstream>
#include <boost/filesystem.hpp>

namespace Hermes {
    StaticFileHandler::StaticFileHandler(const std::string& root_dir) 
        : root_dir_(boost::filesystem::canonical(root_dir).string()) {}
    
    bool StaticFileHandler::handle_request(const auto& req, auto& res) {
        std::string path = (boost::filesystem::path(root_dir_) / req.target().to_string()).lexically_normal();
        
        // Проверка на выход за пределы root_dir
        if (path.find(root_dir_) != 0) {
            return false;
        }
        
        if (boost::filesystem::is_regular_file(path)) {
            std::ifstream file(path, std::ios::binary);
            if (file) {
                res.result(boost::beast::http::status::ok);
                res.body() = std::string(std::istreambuf_iterator<char>(file), {});
                res.set(boost::beast::http::field::content_type, get_mime_type(path));
                return true;
            }
        }
        return false;
    }
    
    std::string StaticFileHandler::get_mime_type(const std::string& path) {
        // ... реализация определения MIME-типа по расширению
    }
}
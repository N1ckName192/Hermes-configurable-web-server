#include "Hermes/Config.h"
#include <fstream>
#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace Hermes {
    ServerConfig ConfigLoader::loadFromFile(const std::string& filename) {
        namespace pt = boost::property_tree;
        pt::ptree tree;
        std::ifstream config_file(filename);
        
        if (!config_file.is_open()) {
            throw std::runtime_error("Could not open config file: " + filename);
        }

        pt::read_json(config_file, tree);
        
        ServerConfig config;
        config.port = tree.get<int>("http_port", 8080);
        config.static_root = tree.get<std::string>("static_root", "./public");
        
        // Загрузка маршрутов
        for (const auto& route : tree.get_child("routes")) {
            RouteConfig rconfig;
            rconfig.path = route.second.get<std::string>("path");
            rconfig.handler_type = route.second.get<std::string>("type");
            rconfig.target = route.second.get<std::string>("target", "");
            config.routes.push_back(rconfig);
        }
        
        return config;
    }
}
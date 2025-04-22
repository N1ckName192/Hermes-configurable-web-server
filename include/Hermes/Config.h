#ifndef HERMES_CONFIG_H
#define HERMES_CONFIG_H

#include <string>
#include <vector>
#include <map>

namespace Hermes {
    struct RouteConfig {
        std::string path;
        std::string handler_type; // "static", "proxy", "custom"
        std::string target;
    };

    struct ServerConfig {
        int port;
        std::vector<RouteConfig> routes;
        std::string static_root;
    };

    class ConfigLoader {
    public:
        static ServerConfig loadFromFile(const std::string& filename);
    };
}

#endif
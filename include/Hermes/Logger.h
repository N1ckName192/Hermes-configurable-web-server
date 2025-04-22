#ifndef HERMES_LOGGER_H
#define HERMES_LOGGER_H

#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>

namespace Hermes {
    class Logger {
    public:
        enum class Level { INFO, WARNING};

        static void log(Level level, const std::string& message) {
            auto now = std::chrono::system_clock::now();
            auto time = std::chrono::system_clock::to_time_t(now);
            
            std::cerr << "\033[1;37m["
                      << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S")
                      << "]\033[0m \033[1;34m[Hermes]\033[0m ";
            
            switch(level) {
                case Level::INFO: std::cerr << "\033[1;32m[info]\033[0m "; break;
                case Level::WARNING: std::cerr << "\033[1;33m[warning]\033[0m "; break;
            }
            
            std::cerr << message << std::endl;
        }
    };
}

#define LOG_INFO(msg) Hermes::Logger::log(Hermes::Logger::Level::INFO, msg)
#define LOG_WARNING(msg) Hermes::Logger::log(Hermes::Logger::Level::WARNING, msg)

#endif
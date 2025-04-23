# Hermes - Configurable Web Server

## Overview
Hermes is a high-performance, configurable web server written in modern C++20. Built on top of Boost.Beast and Boost.Asio, it provides a robust foundation for handling HTTP, routing, proxying, and raw TCP connections. The server follows SOLID principles and implements a clean, modular architecture.

## Key Features
- **HTTP/1.1 Support**: Full implementation of HTTP/1.1 protocol
- **Flexible Routing**: Dynamic route configuration with pattern matching
- **Proxy Support**: Built-in reverse proxy capabilities
- **Raw TCP**: Low-level TCP socket handling
- **Asynchronous I/O**: Non-blocking operations using Boost.Asio
- **Thread Pool**: Efficient request handling with configurable thread pool
- **Configuration**: JSON-based configuration system
- **Logging**: Comprehensive logging system with multiple levels
- **Metrics**: Built-in performance monitoring

## Architecture
The server follows a layered architecture:
- **Network Layer**: Handles low-level socket operations
- **Protocol Layer**: Implements HTTP and TCP protocols
- **Routing Layer**: Manages request routing and handlers
- **Application Layer**: Business logic and custom handlers

## Design Patterns
- Factory Method for handler creation
- Strategy for different protocol implementations
- Observer for event handling
- Singleton for configuration management
- Command for request processing
- Chain of Responsibility for middleware

## Requirements
- C++20 compatible compiler
- CMake 3.15+
- Boost 1.75+
- OpenSSL (optional, for HTTPS support)

## Building
```bash
mkdir build && cd build
cmake ..
cmake --build .
```

## Configuration
```json
{
    "server": {
        "port": 8080,
        "threads": 4,
        "timeout": 30
    },
    "routes": [
        {
            "path": "/api/*",
            "handler": "api_handler"
        }
    ]
}
```

## Usage Example
```cpp
#include <hermes/server.hpp>

int main() {
    hermes::Server server;
    server.configure("config.json");
    server.start();
    return 0;
}
```

## Performance
- Handles 10,000+ concurrent connections
- Sub-millisecond response times
- Memory-efficient connection handling

## Contributing
1. Fork the repository
2. Create a feature branch
3. Submit a pull request

## License
MIT License

## Author
[Your Name]

## Acknowledgments
- Boost.Beast
- Boost.Asio
- OpenSSL

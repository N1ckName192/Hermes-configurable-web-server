#pragma once

#include <boost/asio.hpp>
#include <string>

namespace Hermes {

class ProxyServer {
public:
    ProxyServer(boost::asio::io_context& io_context,
                const boost::asio::ip::tcp::endpoint& endpoint,
                const std::string& proxy_host);

    void start();
    void stop();

private:
    void acceptConnections();
    void handleRequest(boost::asio::ip::tcp::socket socket);
    void proxyRequest(boost::asio::ip::tcp::socket client_socket);

    boost::asio::io_context& io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
    std::string proxy_host_;
    boost::asio::ip::tcp::endpoint endpoint_;
};

} // namespace Hermes
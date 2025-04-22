#ifndef HERMES_PROXYSERVER_H
#define HERMES_PROXYSERVER_H

#include <boost/asio.hpp>
#include <string>

namespace Hermes {
    class ProxyServer {
    public:
        ProxyServer(boost::asio::io_context& io_context, 
                   const boost::asio::ip::tcp::endpoint& endpoint, 
                   const std::string& proxy_host);
        void start();
    private:
        void accept_connections();
        void proxy_request(boost::asio::ip::tcp::socket client_socket);

        boost::asio::io_context& io_context_;
        boost::asio::ip::tcp::endpoint endpoint_;
        std::string proxy_host_;
        boost::asio::ip::tcp::acceptor acceptor_;
    };
}

#endif
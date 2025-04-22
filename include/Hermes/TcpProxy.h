#ifndef HERMES_TCPPROXY_H
#define HERMES_TCPPROXY_H

#include <boost/asio.hpp>
#include "Hermes/Logger.h"

namespace Hermes {
    class TcpProxy {
    public:
        TcpProxy(boost::asio::io_context& io_context,
                const boost::asio::ip::tcp::endpoint& listen_endpoint,
                const boost::asio::ip::tcp::endpoint& target_endpoint);
        void start();

    private:
        void accept_connections();
        void handle_connection(boost::asio::ip::tcp::socket client_socket);

        boost::asio::io_context& io_context_;
        boost::asio::ip::tcp::acceptor acceptor_;
        boost::asio::ip::tcp::endpoint target_endpoint_;
    };
}

#endif
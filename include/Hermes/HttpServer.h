#ifndef HERMES_HTTPSERVER_H
#define HERMES_HTTPSERVER_H

#include "Router.h"
#include <boost/beast.hpp>
#include <boost/asio.hpp>

namespace Hermes {
    class HttpServer {
    public:
        HttpServer(boost::asio::io_context& io_context, 
                  const boost::asio::ip::tcp::endpoint& endpoint, 
                  Router& router);
        void start();
    private:
        void accept_connections();
        void handle_request(boost::asio::ip::tcp::socket socket);

        boost::asio::ip::tcp::acceptor acceptor_;
        Router& router_;
    };
}

#endif
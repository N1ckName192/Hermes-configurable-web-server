#pragma once

#include "Hermes/Router.h"
#include <boost/asio.hpp>
#include <memory>

namespace Hermes {

class HttpServer {
public:
    HttpServer(boost::asio::io_context& io_context,
              const boost::asio::ip::tcp::endpoint& endpoint,
              Router& router);
    
    void start();
    void stop();

private:
    void acceptConnections();
    void handleRequest(boost::asio::ip::tcp::socket socket);

    boost::asio::io_context& io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
    Router& router_;
};

} // namespace Hermes
#include "Hermes/TcpProxy.h"

namespace Hermes {
    TcpProxy::TcpProxy(boost::asio::io_context& io_context,
                      const boost::asio::ip::tcp::endpoint& listen_endpoint,
                      const boost::asio::ip::tcp::endpoint& target_endpoint)
        : io_context_(io_context),
          acceptor_(io_context, listen_endpoint),
          target_endpoint_(target_endpoint) {
        LOG_INFO("TCP Proxy initialized: " + listen_endpoint.address().to_string() + 
                ":" + std::to_string(listen_endpoint.port()) + " -> " +
                target_endpoint.address().to_string() + ":" + 
                std::to_string(target_endpoint.port()));
    }

    void TcpProxy::start() {
        accept_connections();
    }

    void TcpProxy::accept_connections() {
        acceptor_.async_accept(
            [this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket) {
                if (!ec) {
                    LOG_INFO("New TCP connection from " + 
                            socket.remote_endpoint().address().to_string());
                    std::thread(&TcpProxy::handle_connection, this, std::move(socket)).detach();
                }
                accept_connections();
            });
    }

    void TcpProxy::handle_connection(boost::asio::ip::tcp::socket client_socket) {
        try {
            boost::asio::ip::tcp::socket server_socket(io_context_);
            server_socket.connect(target_endpoint_);

            boost::asio::thread_pool pool(2);
            boost::asio::post(pool, [&] {
                boost::asio::streambuf buf;
                boost::system::error_code ec;
                while (!ec) {
                    boost::asio::read(client_socket, buf, ec);
                    if (!ec) boost::asio::write(server_socket, buf);
                }
            });
            boost::asio::post(pool, [&] {
                boost::asio::streambuf buf;
                boost::system::error_code ec;
                while (!ec) {
                    boost::asio::read(server_socket, buf, ec);
                    if (!ec) boost::asio::write(client_socket, buf);
                }
            });
            pool.join();
        } catch (const std::exception& e) {
            LOG_WARNING("TCP Proxy error: " + std::string(e.what()));
        }
    }
}
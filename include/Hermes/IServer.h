#pragma once

#include <boost/asio.hpp>

namespace Hermes {

class IServer {
public:
    virtual ~IServer() = default;
    
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual bool isRunning() const = 0;
    
protected:
    virtual void handleAccept(const boost::system::error_code& error) = 0;
};

} // namespace Hermes 
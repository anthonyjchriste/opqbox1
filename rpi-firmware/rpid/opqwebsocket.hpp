#ifndef OPQWEBSOCKET_HPP
#define OPQWEBSOCKET_HPP

#include "contrib/easywsclient.hpp"

#include <string>

class OpqWebsocket
{
public:
    OpqWebsocket();
    void listen();
private:
    std::string wsUrl_;
    easywsclient::WebSocket::pointer ws_;
    void handleMessage(std::string & message);
};

#endif // OPQWEBSOCKET_HPP

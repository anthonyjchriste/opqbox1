#ifndef OPQWEBSOCKET_HPP
#define OPQWEBSOCKET_HPP

#include "contrib/easywsclient.hpp"

#include <string>
#include <queue>

class OpqWebsocket
{
public:
    OpqWebsocket();
    void listen();
    std::queue<std::string> messages;

private:
    std::string wsUrl_;
    easywsclient::WebSocket::pointer ws_;

};

#endif // OPQWEBSOCKET_HPP

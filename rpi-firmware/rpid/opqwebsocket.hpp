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
    void operator () (std::string message);
    std::queue<std::string> messages;
private:
    std::string wsUrl_;
    easywsclient::WebSocket::pointer ws_;
    void handleMessage(std::string &message);
};

#endif // OPQWEBSOCKET_HPP

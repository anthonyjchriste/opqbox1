#include "coresettings.hpp"
#include "opqwebsocket.hpp"
#include "contrib/easywsclient.hpp"
#include <assert.h>
#include <stdio.h>

OpqWebsocket::OpqWebsocket()
{
    OpqSettings* opqSettings = OpqSettings::Instance();
    wsUrl_ = boost::get<std::string>(opqSettings->getSetting("ws.url"));
    ws_ = easywsclient::WebSocket::from_url(wsUrl_);
}

void OpqWebsocket::handleMessage(std:string & message) {
    printf("%s\n", message.c_str());
}

void OpqWebsocket::listen() {
    while(ws_->getReadyState() != easywsclient::WebSocket::CLOSED) {
        ws_->poll();
        ws_->dispatch(handleMessage);
    }
}


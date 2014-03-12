#include <eleo_socket.hpp>
#include <algorithm>
#include <assert.h>
#include <websocketpp/base64/base64.hpp>
#include <string>
#include <algorithm>    // find
#include <boost/lexical_cast.hpp>

#include <sys/ioctl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdexcept>

using namespace opq::eleo;
using namespace std;

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>

int input_timeout (int filedes, unsigned int seconds)
{
  fd_set set;
  struct timeval timeout;

  /* Initialize the file descriptor set. */
  FD_ZERO (&set);
  FD_SET (filedes, &set);

  /* Initialize the timeout data structure. */
  timeout.tv_sec = seconds;
  timeout.tv_usec = 0;

  /* select returns 0 if timeout, 1 if input available, -1 if error. */
  return TEMP_FAILURE_RETRY (select (FD_SETSIZE,
                                     &set, NULL, NULL,
                                     &timeout));
}


struct Uri
{
public:
    std::string QueryString, Path, Protocol, Host, Port;

    static Uri Parse(const std::string &uri)
    {
        Uri result;

        typedef std::string::const_iterator iterator_t;

        if (uri.length() == 0)
            return result;

        iterator_t uriEnd = uri.end();

        // get query start
        iterator_t queryStart = std::find(uri.begin(), uriEnd, '?');

        // protocol
        iterator_t protocolStart = uri.begin();
        iterator_t protocolEnd = std::find(protocolStart, uriEnd, ':');            //"://");

        if (protocolEnd != uriEnd)
        {
            std::string prot = &*(protocolEnd);
            if ((prot.length() > 3) && (prot.substr(0, 3) == "://"))
            {
                result.Protocol = std::string(protocolStart, protocolEnd);
                protocolEnd += 3;   //      ://
            }
            else
                protocolEnd = uri.begin();  // no protocol
        }
        else
            protocolEnd = uri.begin();  // no protocol

        // host
        iterator_t hostStart = protocolEnd;
        iterator_t pathStart = std::find(hostStart, uriEnd, '/');  // get pathStart

        iterator_t hostEnd = std::find(protocolEnd,
                                       (pathStart != uriEnd) ? pathStart : queryStart,
                                       ':');  // check for port

        result.Host = std::string(hostStart, hostEnd);

        // port
        if ((hostEnd != uriEnd) && ((&*(hostEnd))[0] == ':'))  // we have a port
        {
            hostEnd++;
            iterator_t portEnd = (pathStart != uriEnd) ? pathStart : queryStart;
            result.Port = std::string(hostEnd, portEnd);
        }

        // path
        if (pathStart != uriEnd)
            result.Path = std::string(pathStart, queryStart);

        // query
        if (queryStart != uriEnd)
            result.QueryString = std::string(queryStart, uri.end());

        return result;

    }   // Parse
};  // uri

void searchAndReplace(std::string& str, const std::string& oldStr, const std::string& newStr)
{
    size_t pos = 0;
    while((pos = str.find(oldStr, pos)) != std::string::npos)
    {
        str.replace(pos, oldStr.length(), newStr);
        pos += newStr.length();
    }
}

Socket::Socket(std::string url)
{
    _url = url;
    struct Uri uri = Uri::Parse(url);
    _host = uri.Host;
    _path = uri.Path;
    if(_path.length() == 0)
        _path = "/";
    if(uri.Port.length() != 0)
        _port = boost::lexical_cast<int>(uri.Port);
    else
        _port = 80;
    string header = UPGRADE_HEADER;
    searchAndReplace(header, "[PATH]",_path);
    searchAndReplace(header, "[HOST]",_host);

    struct hostent *he;
    struct sockaddr_in server;
    if((he=gethostbyname(_host.c_str())) == NULL)
        throw runtime_error("Could not find host " + _host);
    if((_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        throw runtime_error("Socket error");
    server.sin_family = AF_INET;
    server.sin_port = htons(_port);
    server.sin_addr = *((struct in_addr *)he->h_addr);
    memset(&(server.sin_zero), '\0', 8);

    if(connect(_sock, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1)
        throw runtime_error("Could not connect to host " + _host);

    long on = 1L;
    ioctl(_sock, (int)FIONBIO, (char *)&on);
    ::write(_sock,header.c_str(), header.length());

    input_timeout(_sock,1);
    int data = 1;
    while(data >0)
    {
        char buff[2];
        data = ::read(_sock, buff ,1);

        buff[data] = '\0';
    }
}

Socket::~Socket()
{
}


void Socket::send(const unsigned char* data, int len)
{
    PacketHeader h;
    h.magic = 1;
    int packetLen = sizeof(PacketHeader) + len;
    unsigned char buffer[packetLen];
    for(size_t i = 0; i< sizeof(PacketHeader); i++)
    {
        buffer[i] = ((char*)(&h))[i];
    }

    for(size_t i = 0; i< len; i++)
    {
        buffer[i + sizeof(PacketHeader)] = data[i];
    }

    std::string packet = websocketpp::base64_encode(buffer, packetLen);

    char next;
    next = 0x80 | (0x1 & 0x0f);
    ::write(_sock, &next, sizeof(char));
    uint64_t size = packet.length();

    cout <<  size << endl;
    if (size < 126)
    {
        next = size | (1<<7);
        ::write(_sock, &next, sizeof(char));
    }
    else if (size < 0xFFFF)
    {
        next = 126 | (1<<7);
        ::write(_sock, &next, sizeof(char));
        next = (size >> 8) & 0xff;
        ::write(_sock, &next, sizeof(char));
        next = size & 0xff;
        ::write(_sock, &next, sizeof(char));
    }
    else
    {
        next = 127 | (1<<7);
        ::write(_sock, &next, sizeof(char));
        for (int i = 0; i < 8; i++)
        {
            next = (size >> (7-i)*8) & 0xff;
            ::write(_sock, &next, sizeof(char));
        }
    }

    next = 0;
    for(int i = 0; i< 4; i++)
        ::write(_sock, &next, sizeof(char));
    ::write(_sock, packet.c_str(), packet.length());
    //Get the responce hack.
    input_timeout(_sock,1);
    int da = 1;
    while(da >0)
    {
        char buff[2];
        da = ::read(_sock, buff ,1);
        buff[da] = '\0';
        cout << buff;
    }
}

void Socket::send(const std::vector<unsigned char> data)
{
    const unsigned char* buffer = data.data();
    int len = data.size();
    this->send(buffer, len);
}


Socket& Socket::operator << (const std::vector<unsigned char> data)
{
    const unsigned char* buffer = data.data();
    int len = data.size();
    this->send(buffer, len);
    return *this;
}

Socket& Socket::operator << (const std::string data)
{
    std::vector<unsigned char> buf;
    for(size_t i = 0; i< data.length(); i++)
    {
        buf.push_back(data.at(i));
    }
    this->send(buf);
    return *this;
}

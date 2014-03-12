#include <eleo_socket.hpp>
#include <unistd.h>
#include <cstring>

using namespace opq::eleo;

int main()
{
    Socket s("ws://128.171.10.84:9000/private/ws");
    char * a = new char[65400];
    memset(a,'b',65400);
    a[65400 -1] = '\0';
    s << a;
    sleep(10);
    return 0;
}

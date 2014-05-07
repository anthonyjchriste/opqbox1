#ifndef UARTREAD_HPP
#define UARTREAD_HPP
#include "datastructures.hpp"
#include <string>
#include <termios.h>

using std::string;

struct Msp430Uart
{
    int fd;
    std::string path;
    uint baudrate;
    struct termios settings;
};

bool uartInit(Msp430Uart &uart);

OpqFrame* uartRead(Msp430Uart &uart, size_t len);

#endif // UARTREAD_HPP

#ifndef UARTREAD_HPP
#define UARTREAD_HPP
#include "datastructures.hpp"
#include <string>
#include <termios.h>

using std::string;

/**
 * @brief The Msp430Uart struct serial port representation.
 */
struct Msp430Uart
{
    /**
     * @brief fd file descriptor to the port.
     */
    int fd;

    /**
     * @brief path file system path to the device.
     */
    std::string path;
    uint baudrate;
    struct termios settings;
};

/**
 * @brief uartInit initialize uart.
 * @param uart  uart struct.
 * @return  true on success, otherwise, false.
 */
bool uartInit(Msp430Uart &uart);

/**
 * @brief uartRead read an opq frame.
 * @param uart  uart descriptor.
 * @param len   length of the record in samples.
 * @return pointer to a frame or NULL on failier.
 */
OpqFrame* uartRead(Msp430Uart &uart, size_t len);

/**
 * @brief uartClear clear the uart buffer.
 * @param uart  Uart descriptor.
 */
void uartClear(Msp430Uart &uart);

#endif // UARTREAD_HPP

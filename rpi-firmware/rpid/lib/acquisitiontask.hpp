#ifndef ACQUISITIONTASK_HPP
#define ACQUISITIONTASK_HPP
#include "uartread.hpp"
#include "datastructures.hpp"
#include <stdexcept>
class AcquisitionTask
{
public:
    AcquisitionTask(FrameQueuePointer oq) throw(std::runtime_error&);
    void run();
private:
    FrameQueuePointer oq_;
    Msp430Uart uart_;
};

#endif // ACQUISITIONTASK_HPP

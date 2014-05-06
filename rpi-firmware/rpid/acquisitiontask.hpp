#ifndef ACQUISITIONTASK_HPP
#define ACQUISITIONTASK_HPP
#include "uartread.hpp"
#include "datastructures.hpp"
#include "boost/thread.hpp"

class AcquisitionTask
{
public:
    AcquisitionTask(FrameQueuePointer oq);
    bool initialize();
    void run();
private:
    FrameQueuePointer oq_;
};

#endif // ACQUISITIONTASK_HPP

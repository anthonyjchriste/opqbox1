#ifndef POWERTRANSFORMTASK_HPP
#define POWERTRANSFORMTASK_HPP

#include "datastructures.hpp"

class PowerTransformTask
{
public:
    PowerTransformTask(FrameQueuePointer iq, FrameQueuePointer oq);
    void run();
private:
    FrameQueuePointer oq_;
    FrameQueuePointer iq_;
};

#endif // POWERTRANSFORMTASK_HPP

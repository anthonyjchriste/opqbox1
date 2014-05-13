#ifndef FILTERTASK_HPP
#define FILTERTASK_HPP

#include "datastructures.hpp"

class FilterTask
{
public:
    FilterTask(FrameQueuePointer iq, FrameQueuePointer oq);
    void run();
private:
    FrameQueuePointer oq_;
    FrameQueuePointer iq_;
};

#endif // FILTERTASK_HPP

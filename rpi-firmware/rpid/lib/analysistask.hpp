#ifndef ANALYSISTASK_HPP
#define ANALYSISTASK_HPP
#include "datastructures.hpp"

class AnalysisTask
{
public:
    AnalysisTask(FrameQueuePointer iq, FrameQueuePointer oq);
    void run();
private:
    FrameQueuePointer oq_;
    FrameQueuePointer iq_;
};

#endif // ANALYSISTASK_HPP

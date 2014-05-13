#include "../lib/filtertask.hpp"

FilterTask::FilterTask(FrameQueuePointer iq, FrameQueuePointer oq)
{
    oq_ = oq;
    iq_ = iq;
}

void FilterTask::run()
{
    try
    {
        while(true)
        {
            OpqFrame* next = iq_->pop();

            oq_->push(next);
            boost::this_thread::interruption_point();
        }
    }
    catch(boost::thread_interrupted &e)
    {
        return;
    }
}

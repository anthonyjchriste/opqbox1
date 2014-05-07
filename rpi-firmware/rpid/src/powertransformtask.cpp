#include "powertransformtask.hpp"
#include "powerSpectrum.hpp"

PowerTransformTask::PowerTransformTask(FrameQueuePointer iq, FrameQueuePointer oq)
{
    oq_ = oq;
    iq_ = iq;
}

void PowerTransformTask::run()
{
    try
    {
        while(true)
        {
            OpqFrame* next = iq_->pop();
            next->fft = powerSpectrum(next->data);
            oq_->push(next);
            boost::this_thread::interruption_point();
        }
    }
    catch(boost::thread_interrupted &e)
    {
        return;
    }

}

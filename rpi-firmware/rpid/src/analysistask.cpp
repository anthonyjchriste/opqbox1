#include "analysistask.hpp"
#include "gausianpeak.hpp"

AnalysisTask::AnalysisTask(FrameQueuePointer iq, FrameQueuePointer oq)
{
    iq_ = iq;
    oq_ = oq;
}

void AnalysisTask::run()
{
    try
    {
        while(true)
        {
            OpqFrame* next = iq_->pop();
            OpqSetting frequency = OpqSetting((float)(4000.0*gausianPeak(next)/(next->fft.size())));
            next->parameters["f"] = frequency;
            oq_->push(next);
            boost::this_thread::interruption_point();
        }
    }
    catch(boost::thread_interrupted &e)
    {
        return;
    }
}

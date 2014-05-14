#include "../lib/filtertask.hpp"
#include "coresettings.hpp"
#include "opqpacket.hpp"
FilterTask::FilterTask(FrameQueuePointer iq, FrameQueuePointer oq)
{
    oq_ = oq;
    iq_ = iq;
}

void FilterTask::run()
{
    try
    {
        OpqSettings* set = OpqSettings::Instance();

        float Fexp = boost::get<float>(set->getSetting("filter.expected.f"));
        float Vexp = boost::get<float>(set->getSetting("filter.expected.vrms"));
        while(true)
        {
            OpqFrame* next = iq_->pop();
            float Fthresh = boost::get<float>(set->getSetting("filter.thresh.f"));
            float Vthresh = boost::get<float>(set->getSetting("filter.thresh.vrms"));
            float Fmeas = boost::get<float>(next->parameters["f"]);
            float Vmeas = boost::get<float>(next->parameters["vrms"]);
            if(fabs(Fexp - Fmeas) >= Fthresh)
            {
                next->parameters["event.type"] = EVENT_FREQUENCY;
                oq_->push(next);
            }
            else if(fabs(Vexp - Vmeas) >= Vthresh)
            {
                next->parameters["event.type"] = EVENT_VOLTAGE;
                oq_->push(next);
            }
            boost::this_thread::interruption_point();
        }
    }
    catch(boost::thread_interrupted &e)
    {
        return;
    }
}

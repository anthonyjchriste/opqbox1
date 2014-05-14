#include "../lib/filtertask.hpp"
#include "coresettings.hpp"
#include "opqpacket.hpp"
#include "pinctl.hpp"
FilterTask::FilterTask(FrameQueuePointer iq, FrameQueuePointer oq)
{
    oq_ = oq;
    iq_ = iq;
    exportPin(LED2);
    setPinDirection(LED2, OUT);
    setPinValue(LED2, HIGH);
}

void FilterTask::run()
{
    try
    {
        OpqSettings* set = OpqSettings::Instance();

        double Fexp = boost::get<double>(set->getSetting("filter.expected.f"));
        double Vexp = boost::get<double>(set->getSetting("filter.expected.vrms"));
        bool ledState = false;
        while(true)
        {
            OpqFrame* next = iq_->pop();
            double Fthresh = boost::get<double>(set->getSetting("filter.thresh.f"));
            double Vthresh = boost::get<double>(set->getSetting("filter.thresh.vrms"));
            double Fmeas = boost::get<double>(next->parameters["f"]);
            double Vmeas = boost::get<double>(next->parameters["vrms"]);
            if(fabs(Fexp - Fmeas) >= Fthresh)
            {
                next->parameters["event.type"] = EVENT_FREQUENCY;
                oq_->push(next);
                if(ledState)
                    setPinValue(LED2, LOW);
                else
                    setPinValue(LED2, HIGH);
                ledState = !ledState;
            }
            else if(fabs(Vexp - Vmeas) >= Vthresh)
            {
                next->parameters["event.type"] = EVENT_VOLTAGE;
                oq_->push(next);
                if(ledState)
                    setPinValue(LED2, LOW);
                else
                    setPinValue(LED2, HIGH);
                ledState = !ledState;
            }
            else
                delete next;
            boost::this_thread::interruption_point();
        }
    }
    catch(boost::thread_interrupted &e)
    {
        setPinValue(LED2, HIGH);
        return;
    }
}

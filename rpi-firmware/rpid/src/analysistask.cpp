#include "analysistask.hpp"
#include "gausianpeak.hpp"
#include "rmsvoltage.hpp"
#include "coresettings.hpp"
AnalysisTask::AnalysisTask(FrameQueuePointer iq, FrameQueuePointer oq)
{
    iq_ = iq;
    oq_ = oq;
}

void AnalysisTask::run()
{
    try
    {
        OpqSettings* set = OpqSettings::Instance();
        float SAMPLING_RATE = boost::get<float>(set->getSetting("cal.sampling_rate"));
        float VOLTAGE_SCALING = boost::get<float>(set->getSetting("cal.voltageScaling"));
        while(true)
        {
            OpqFrame* next = iq_->pop();
            OpqSetting frequency = OpqSetting((float)(SAMPLING_RATE*gausianPeak(next)/(next->fft.size())));

            next->parameters["f"] = frequency;
            std::vector<double> data;
            int start = 0;
            int end = 0;
            for(int i = 0; i< next->data.size() -1; i++)
            {
                if(start == 0)
                {
                    if(data[i]*data[i-1] < 0)
                        start = i;
                }
                else if(data[i]*data[i-1] < 0)
                        end = i;
            }
            data.assign(end - start, 0);
            std::copy(next->data.begin() + start, next->data.begin() + end, data.begin());
            next->parameters["vrms"] = (float)(VOLTAGE_SCALING*rmsVoltage(data));

            next->parameters["thd"] = "TO DO";
            oq_->push(next);
            boost::this_thread::interruption_point();
        }
    }
    catch(boost::thread_interrupted &e)
    {
        return;
    }
}

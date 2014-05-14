#include <iostream>
#include <cmath>
#include <vector>

#include "powerSpectrum.hpp"
#include "coresettings.hpp"
#include <string>
#include "acquisitiontask.hpp"
#include "powertransformtask.hpp"
#include "analysistask.hpp"
#include "opqwebsocket.hpp"
#include "opqpacket.hpp"

#include <boost/thread/thread.hpp>
#include <boost/date_time.hpp>

#include <endian.h>

using namespace std;


int main(int argc, char** argv)
{
    OpqSettings *set = OpqSettings::Instance();
    set->loadFromFile(std::string("settings.set"));
#ifdef ANTHONY_MAIN
    FrameQueuePointer wsQ(new FrameQueue);
    OpqWebsocket *ws = new OpqWebsocket(wsQ);
    boost::thread wsT = boost::thread(&OpqWebsocket::run, ws);

    sleep(100);
#else
    FrameQueuePointer acqQ(new FrameQueue);
    FrameQueuePointer fftQ(new FrameQueue);
    FrameQueuePointer anaQ(new FrameQueue);

    AcquisitionTask *acq = new AcquisitionTask(acqQ);
    PowerTransformTask *fft = new PowerTransformTask(acqQ, fftQ);
    AnalysisTask * ana = new AnalysisTask(fftQ, anaQ);

    boost::this_thread::sleep(boost::posix_time::millisec(1000));
    boost::thread acqT = boost::thread(&AcquisitionTask::run, acq);
    boost::thread fftT = boost::thread(&PowerTransformTask::run, fft);
    boost::thread anaT = boost::thread(&AnalysisTask::run, ana);
    int index = 0;
    while(true)
    {
        if (index <100)
        {
            OpqFrame* frame  = anaQ->pop();

            //for(int i = 0; i< frame->fft.size(); i++)
            //    cout << frame->fft[i] << endl;
//            for(int i = 0; i< frame->fft.size(); i++)
//                cout << frame->data[i] << endl;

            cout << boost::get<float>(frame->parameters["f"]) << " " << boost::get<float>(frame->parameters["vrms"]) << endl;

            delete frame;
            index++;
        }
        else
        {
            exit(0);
        }
    }
#endif
}

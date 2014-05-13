#include <iostream>
#include <cmath>
#include <vector>

#include "powerSpectrum.hpp"
#include "rmsVoltage.hpp"
#include "uartread.hpp"
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

void fftRmsTest()
{
    std::vector<double> test;
    for(int i = 0; i < 1000; i++)
    {
        test.push_back(sin(i*0.1 *M_PI) + 0.5*sin(i*0.2 *M_PI));
    }
    std::vector<double> out = powerSpectrum(test);
    for(int i = 0; i < 1000; i++)
    {
        cout << i/1000.0 << " " << out[i] << endl;
    }
    cout << "RMS: " << rmsVoltage(test) << endl;
}

void uartTest()
{
    Msp430Uart urt;
    urt.path = "/dev/ttyAMA0";
    cout << "Openning uart " << (int)uartInit(urt) << endl;
    OpqFrame *next = uartRead(urt, 1000);
    for(int i = 0; i< next->size; i++)
    {
        cout << next->data[i] << endl;
    }
    delete next;
}


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

            cout << boost::get<float>(frame->parameters["f"]) << endl;
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

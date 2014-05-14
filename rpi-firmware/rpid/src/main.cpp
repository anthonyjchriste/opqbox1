#include <iostream>
#include <cmath>
#include <vector>
#include <stdlib.h>

#include "coresettings.hpp"
#include <string>
#include "acquisitiontask.hpp"
#include "powertransformtask.hpp"
#include "analysistask.hpp"
#include "filtertask.hpp"
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
    FrameQueuePointer acqQ(new FrameQueue);
    FrameQueuePointer fftQ(new FrameQueue);
    FrameQueuePointer anaQ(new FrameQueue);
    FrameQueuePointer fltrQ(new FrameQueue);

    AcquisitionTask *acq = new AcquisitionTask(acqQ);
    PowerTransformTask *fft = new PowerTransformTask(acqQ, fftQ);
    AnalysisTask * ana = new AnalysisTask(fftQ, anaQ);
    FilterTask * fltr = new FilterTask(anaQ, fltrQ);
    OpqWebsocket *ws = new OpqWebsocket(fltrQ);

    boost::this_thread::sleep(boost::posix_time::millisec(1000));
    boost::thread acqT = boost::thread(&AcquisitionTask::run, acq);
    boost::thread fftT = boost::thread(&PowerTransformTask::run, fft);
    boost::thread anaT = boost::thread(&AnalysisTask::run, ana);
    boost::thread fltrT = boost::thread(&FilterTask::run, fltr);
    boost::thread wsT = boost::thread(&OpqWebsocket::run, ws);
    getchar();
}

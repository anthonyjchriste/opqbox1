#include <iostream>
#include <cmath>
#include <vector>

#include "powerSpectrum.hpp"
#include "rmsVoltage.hpp"
#include "uartread.hpp"
#include "coresettings.hpp"
#include <string>
#include "acquisitiontask.hpp"
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
    cout << set->loadFromFile(std::string("settings.set")) << endl;
    FrameQueuePointer acqQ(new FrameQueue);
    AcquisitionTask *acq = new AcquisitionTask(acqQ);
    boost::thread acqT = boost::thread(&AcquisitionTask::run, acq);
    while(true)
    {
        delete acqQ->pop();
        cout << "Poped" << endl;
    }
}

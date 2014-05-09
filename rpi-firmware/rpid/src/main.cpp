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
#include "opqwebsocket.hpp"
#include "opqpacket.hpp"

#include <boost/thread/thread.hpp>
#include <boost/date_time.hpp>

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

    struct OpqPacketHeader packetHeader;
    packetHeader.magic = 0x00C0FFEE;
    packetHeader.type = 4;
    packetHeader.sequenceNumber = 0;
    packetHeader.deviceId = 2;
    packetHeader.timestamp = 1096906472L;
    packetHeader.bitfield = 0;
    for(int i = 0; i < 4; i++) packetHeader.reserved[i] = 0;
    packetHeader.checksum = 0;

    std::vector<uint8_t> payload;
    payload.push_back(1);
    packetHeader.payloadSize = payload.size();

    OpqPacket opqPacket = std::make_pair(packetHeader, payload);
    opqPacket.first.checksum = computeChecksum(opqPacket);

    printHeader(opqPacket.first);

    OpqWebsocket opqWebsocket;
    opqWebsocket.messages.push(encodeOpqPacket(opqPacket));
    opqWebsocket.listen();



    /*
    FrameQueuePointer acqQ(new FrameQueue);
    FrameQueuePointer fftQ(new FrameQueue);

    AcquisitionTask *acq = new AcquisitionTask(acqQ);
    PowerTransformTask *fft = new PowerTransformTask(acqQ, fftQ);
    boost::this_thread::sleep(boost::posix_time::millisec(1000));
    boost::thread acqT = boost::thread(&AcquisitionTask::run, acq);
    boost::thread fftT = boost::thread(&PowerTransformTask::run, fft);
    int index = 0;
    while(true)
    {
        if (index <100)
        {
            OpqFrame* frame  = fftQ->pop();
            for(int i = 0; i< frame->fft.size(); i++)
                cout << frame->fft[i] << endl;
            for(int i = 0; i< frame->fft.size(); i++)
                cout << frame->data[i] << endl;
            delete frame;
            index++;
        }
        else
        {
            exit(0);
        }
    }
    */

}

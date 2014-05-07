#include "acquisitiontask.hpp"
#include "coresettings.hpp"

AcquisitionTask::AcquisitionTask(FrameQueuePointer oq) throw(std::runtime_error&)
{
    oq_ = oq;
    OpqSettings* set = OpqSettings::Instance();
    uart_.path = boost::get<std::string> (set->getSetting("uart.port"));
    if(uartInit(uart_) < 0)
        throw std::runtime_error("could not initialize UART.");
}

void AcquisitionTask::run()
{
    try
    {
        while(true)
        {

        }
    }
    catch(boost::thread_interrupted &e)
    {

    }
}

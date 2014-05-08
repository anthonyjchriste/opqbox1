#include "acquisitiontask.hpp"
#include "coresettings.hpp"
#include <boost/thread/exceptions.hpp>
#include "pinctl.hpp"

AcquisitionTask::AcquisitionTask(FrameQueuePointer oq) throw(std::runtime_error&)
{
    oq_ = oq;
    OpqSettings* set = OpqSettings::Instance();
    uart_.path = boost::get<std::string> (set->getSetting("uart.port"));
    if(uartInit(uart_) < 0)
        throw std::runtime_error("could not initialize UART.");
    exportPin("18");
    setPinDirection("18", OUT);
    setPinValue("18", HIGH);
}

AcquisitionTask::~AcquisitionTask()
{
    unExportPin("18");
}

void AcquisitionTask::run()
{
    OpqSettings* set = OpqSettings::Instance();
    try
    {
        while(true)
        {
            int blockSize = boost::get<int>(set->getSetting("uart.block_size"));
            //uartClear(uart_);
            setPinValue("18", LOW);
            OpqFrame* next = uartRead(uart_, blockSize);
            setPinValue("18", HIGH);
            oq_->push(next);
            boost::this_thread::interruption_point();
        }
    }
    catch(boost::thread_interrupted &e)
    {
        return;
    }
}

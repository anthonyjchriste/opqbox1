#ifndef ACQUISITIONTASK_HPP
#define ACQUISITIONTASK_HPP
#include "uartread.hpp"
#include "datastructures.hpp"
#include <stdexcept>

/**
 * @brief The AcquisitionTask class aquires data from the serial port and pushes in on a queue.
 */
class AcquisitionTask
{
public:
    /**
     * @brief AcquisitionTask default constructor.
     * @param oq    output queue.
     */
    AcquisitionTask(FrameQueuePointer oq) throw(std::runtime_error&);
    ~AcquisitionTask();

    /**
     * @brief run starts the acquisition loop.
     */
    void run();
private:
    /**
     * @brief oq_ output queue.
     */
    FrameQueuePointer oq_;

    /**
     * @brief uart_ uart parameters.
     */
    Msp430Uart uart_;
};

#endif // ACQUISITIONTASK_HPP

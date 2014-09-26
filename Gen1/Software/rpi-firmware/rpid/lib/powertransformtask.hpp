#ifndef POWERTRANSFORMTASK_HPP
#define POWERTRANSFORMTASK_HPP

#include "datastructures.hpp"

/**
 * @brief The PowerTransformTask class task responsible for computing the power spectrum
 */
class PowerTransformTask
{
public:

    /**
     * @brief PowerTransformTask default constructor.
     * @param iq    //Input queue.
     * @param oq    //Output queue.
     */
    PowerTransformTask(FrameQueuePointer iq, FrameQueuePointer oq);
    /**
     * @brief run start the power transform loop.
     */
    void run();
private:
    FrameQueuePointer oq_;
    FrameQueuePointer iq_;
};

#endif // POWERTRANSFORMTASK_HPP

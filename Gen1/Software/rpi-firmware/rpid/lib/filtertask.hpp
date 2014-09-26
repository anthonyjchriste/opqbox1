#ifndef FILTERTASK_HPP
#define FILTERTASK_HPP

#include "datastructures.hpp"

/**
 * @brief The FilterTask class  desides if an event is present in the data.
 */
class FilterTask
{
public:
    /**
     * @brief FilterTask Default constructor
     * @param iq    Input queue
     * @param oq    Output queue
     */
    FilterTask(FrameQueuePointer iq, FrameQueuePointer oq);
    ~FilterTask();

    /**
     * @brief run run the filter thread.
     */
    void run();
private:
    /**
     * @brief oq_ output queue
     */
    FrameQueuePointer oq_;

    /**
     * @brief iq_ input queue.
     */
    FrameQueuePointer iq_;
};

#endif // FILTERTASK_HPP

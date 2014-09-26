#ifndef ANALYSISTASK_HPP
#define ANALYSISTASK_HPP
#include "datastructures.hpp"

/**
 * @brief The AnalysisTask class performs feature extraction and analisys.
 */
class AnalysisTask
{
public:
    /**
     * @brief AnalysisTask default constructor.
     * @param iq    Input queue.
     * @param oq    Output queue.
     */
    AnalysisTask(FrameQueuePointer iq, FrameQueuePointer oq);

    /**
     * @brief run Starts the analisys loop.
     */
    void run();

private:

    /**
     * @brief oq_ output queue.
     */
    FrameQueuePointer oq_;

    /**
     * @brief iq_ input queue.
     */
    FrameQueuePointer iq_;
};

#endif // ANALYSISTASK_HPP

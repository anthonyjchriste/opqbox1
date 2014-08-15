#ifndef DATASTRUCTURES_HPP
#define DATASTRUCTURES_HPP
#include <stdint.h>
#include <sys/types.h>
#include <boost/variant.hpp>
#include <boost/shared_ptr.hpp>
#include <map>
#include <string>
#include <vector>
#include "coredataqueue.hpp"

using std::string;
using std::map;
using std::vector;

/**
 * @brief OpqSetting a generic setting.
 */
typedef boost::variant<uint64_t, double, int, string, bool> OpqSetting;

/**
 * @brief OpqParameters a key value pair used to store arbitrary type.
 */
typedef map<string, OpqSetting> OpqParameters;


/**
 * @brief The OpqFrame struct Individual data frame.
 */
struct OpqFrame
{
    uint32_t timeSec;               ///Time of acquisition sec.
    uint32_t timeUsec;              ///Time of acquisition in usec.
    uint32_t duration;
    std::vector<double>  data;      ///Voltages.
    std::vector<double>  fft;       ///Power spectrum of the voltage.
    OpqParameters parameters;       ///Feature extraction and analisys parameters.
};

/**
 * @brief FrameQueue queue of opq frames.
 */
typedef pland::Data_Queue<OpqFrame*> FrameQueue;

/**
 * @brief FrameQueuePointer reference counted version of FrameQueue.
 */
typedef boost::shared_ptr<FrameQueue> FrameQueuePointer;

#endif // DATASTRUCTURES_HPP

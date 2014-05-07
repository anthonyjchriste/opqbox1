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

typedef boost::variant<uint64_t, float, int, string, bool> OpqSetting;

typedef map<string, OpqSetting> OpqParameters;

struct OpqFrame
{
    uint32_t timeSec;
    uint32_t timeUsec;
    std::vector<double>  data;
    std::vector<double>  fft;
    size_t size;
    OpqParameters parameters;
};

typedef pland::Data_Queue<OpqFrame*> FrameQueue;

typedef boost::shared_ptr<FrameQueue> FrameQueuePointer;

#endif // DATASTRUCTURES_HPP

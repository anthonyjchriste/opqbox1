#ifndef DATASTRUCTURES_HPP
#define DATASTRUCTURES_HPP
#include <stdint.h>
#include <sys/types.h>
#include <map>
#include <boost/variant.hpp>
#include <string>
#include <vector>

using std::string;
using std::map;
using std::vector;

enum OpqFrameType {ADC, FFT};

typedef boost::variant<uint64_t, OpqFrameType, float, int, string, bool> OpqSetting;

typedef map<string, OpqSetting> OpqParameters;

struct OpqFrame
{
    uint32_t timeSec;
    uint32_t timeUsec;
    uint16_t*  data;
    size_t size;
    OpqParameters parameters;
};

#endif // DATASTRUCTURES_HPP

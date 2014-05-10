#include "gausianpeak.hpp"
#include <algorithm>
using namespace std;

float gausianPeak(OpqFrame* frame)
{
    std::vector<double> fft = frame->fft;
    return distance(fft.begin(), max_element(fft.begin(), fft.end()));
}

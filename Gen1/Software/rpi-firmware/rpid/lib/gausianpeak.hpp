#ifndef GAUSIANPEAK_HPP
#define GAUSIANPEAK_HPP
#include "datastructures.hpp"

/**
 * @brief gausianPeak computes the peak of the power spectrum.
 * @param frame Data frame with a precomputed power spectrum.
 * @return gausian peak position.
 */
float gausianPeak(OpqFrame* frame);

#endif // GAUSIANPEAK_HPP

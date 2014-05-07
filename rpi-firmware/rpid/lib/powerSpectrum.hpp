#ifndef POWER_SPECTRUM_H
#define POWER_SPECTRUM_H
#include <gsl/gsl_errno.h>
#include <gsl/gsl_fft_real.h>
#include <gsl/gsl_fft_halfcomplex.h>
#include <vector>

using std::vector;

vector<double> powerSpectrum(vector<double> input);

#endif

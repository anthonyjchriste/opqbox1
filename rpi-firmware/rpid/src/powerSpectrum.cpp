#include "powerSpectrum.hpp"
//#include <gsl/gsl_errno.h>
#include <gsl/gsl_fft_real.h>
#include <gsl/gsl_fft_complex.h>
//#include <gsl/gsl_fft_halfcomplex.h>

#include <vector>

vector<double> powerSpectrum(vector<double> input)
{
    size_t length = input.size();
    double reals[length*2];
    for(size_t i = 0; i <length; i++)
    {
        reals[i*2] = input[i];
        reals[i*2+1] = 0;
    }
    gsl_fft_complex_wavetable * complex;
    gsl_fft_complex_workspace * work;

    work = gsl_fft_complex_workspace_alloc(length);
    complex = gsl_fft_complex_wavetable_alloc(length);
    gsl_fft_complex_transform (reals, 1, length, complex, work, gsl_fft_forward);

    gsl_fft_complex_wavetable_free (complex);
    gsl_fft_complex_workspace_free (work);
    for(int i = 0; i< length; i++)
    {
        input[i] = sqrt(reals[i*2]*reals[i*2] + reals[i*2+1]*reals[i*2+1])/length;
    }
    return input;
}

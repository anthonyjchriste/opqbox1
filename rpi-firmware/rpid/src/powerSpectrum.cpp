#include "powerSpectrum.hpp"

vector<double> powerSpectrum(vector<double> input)
{
    size_t length = input.size();
    gsl_fft_real_wavetable * real;
    gsl_fft_halfcomplex_wavetable * hc;
    gsl_fft_real_workspace * work;

    work = gsl_fft_real_workspace_alloc(length);
    real = gsl_fft_real_wavetable_alloc(length);
    gsl_fft_real_transform (input.data(), 1, length,
                            real, work);

    gsl_fft_real_wavetable_free (real);
    gsl_fft_real_workspace_free (work);
    for(int i = 0; i< length; i++)
    {
        input[i] = fabs(input[i]);
    }
    return input;
}

/*
    Amplitude class for scalar phi^3 theory to compute
    n leg scattering amplitudes with Berends-Giele recurrence relations.
*/

#ifndef SCALAR_AMPLITUDE
#define SCALAR_AMPLITUDE

#include <iostream>
#include <complex>
#include <vector>

#include "definitions.h"
#include "fourvector.h"

class ScalarTreeAmplitude
{
public:
    //Constructor: default
    ScalarTreeAmplitude ();
    //Constructor: massless
    ScalarTreeAmplitude (const int& numberOfLegs, const real_t& coupling);
    //Constructor: massive
    ScalarTreeAmplitude (const int& numberOfLegs, const real_t& coupling,
                         const real_t& mass);

    //Amplitude
    complex_t amplitude (const std::vector <FourVector <real_t>>& momenta);

private:
    //Amputated off-shell currents
    complex_t masslessCurrentAmputated
        (const std::vector <FourVector <real_t>>& momenta,
         const std::vector <unsigned int>& idList);
    complex_t massiveCurrentAmputated
        (const std::vector <FourVector <real_t>>& momenta);

    //Off-shell currents
    complex_t masslessCurrent
        (const std::vector <FourVector <real_t>>& momenta,
         const std::vector <unsigned int>& idList);
    complex_t massiveCurrent
        (const std::vector <FourVector <real_t>>& momenta);

    //Feynman-rules
    complex_t vertex ();
    complex_t masslessPropagator
        (const FourVector <real_t>& momenta);
    complex_t massivePropagator
        (const FourVector <real_t>& momenta);

    //Containers
    std::vector <LabeledContainer>* currentStorage_;

    //Parameters
    const unsigned int numberOfLegs_;
    const real_t coupling_;
    const real_t mass_;
    const bool massless_;

};

#endif

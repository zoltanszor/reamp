/*
    Amplitude class for scalar phi^3 theory to compute
    n leg scattering amplitudes with Berends-Giele recurrence relations.
*/
#include <iostream>
#include <complex>
#include <vector>

#include "definitions.h"
#include "fourvector.h"
#include "scalaramplitude.h"

//Constructor: default
ScalarTreeAmplitude::ScalarTreeAmplitude ()
    : numberOfLegs_ (1), coupling_(1), mass_ (0), massless_(true) {}

//Constructor: massless
ScalarTreeAmplitude::ScalarTreeAmplitude
    (const int& numberOfLegs, const real_t& coupling)
    : numberOfLegs_ (numberOfLegs), coupling_(coupling), mass_ (0),
      massless_(true) {}

//Constructor: massive
ScalarTreeAmplitude::ScalarTreeAmplitude
    (const int& numberOfLegs, const real_t& coupling, const real_t& mass)
    : numberOfLegs_ (numberOfLegs), coupling_(coupling), mass_ (mass),
      massless_(false) {}

//Amputated massless recursive current
complex_t ScalarTreeAmplitude::masslessCurrentAmputated
    (const std::vector <FourVector <real_t>>& momenta,
     const std::vector <unsigned int>& idList)
{
    //n bits to store
    unsigned int n = momenta.size () - 1;
    //Result container
    complex_t result = 0;

    //Generate all set combinations except the last one via bit representation
    for (unsigned int i = 0; i < pow(2, n) - 1; i++)
    {
        //Initialize two sets of current momenta and idList
        std::vector <FourVector <real_t>> currentMomenta1;
        std::vector <FourVector <real_t>> currentMomenta2;

        std::vector <unsigned int> idList1;
        std::vector <unsigned int> idList2;

        //The first set always contains the first element of set 'momenta'
        currentMomenta1.push_back (momenta.at (0));
        idList1.push_back (idList.at (0));

        //Read off bits of 'i' and fill current momenta sets accordingly
        for (unsigned int j = 0; j < n; j++)
        {
            unsigned int readoff = pow (2, j);

            //Element is in the first set
            if ((i & readoff) == readoff)
            {
                currentMomenta1.push_back (momenta.at (j + 1));
                idList1.push_back (idList.at (j + 1));
            }
            //Element is in the second set
            else
            {
                currentMomenta2.push_back (momenta.at (j + 1));
                idList2.push_back (idList.at (j + 1));
            }

        }

        //Momenta generation complete, calculate contribution
        result += vertex() * masslessCurrent(currentMomenta1, idList1)
                        * masslessCurrent(currentMomenta2, idList2);
    }

    return result;
}

//Amputated massive recursive current
complex_t ScalarTreeAmplitude::massiveCurrentAmputated
    (const std::vector <FourVector <real_t>>& momenta)
{
    //n bits to store
    unsigned int n = momenta.size () - 1;
    //Result container
    complex_t result = 0;

    //Generate all set combinations except the last one via bit representation
    for (unsigned int i = 0; i < pow(2, n) - 1; i++)
    {
        //Initialize two sets of current momenta
        std::vector <FourVector <real_t>> currentMomenta1;
        std::vector <FourVector <real_t>> currentMomenta2;

        //The first set always contains the first element of set 'momenta'
        currentMomenta1.push_back (momenta.at (0));


        //Read off bits of 'i' and fill current momenta sets accordingly
        for (unsigned int j = 0; j < n; j++)
        {
            unsigned int readoff = pow (2, j);

            //Element is in the first set
            if ((i & readoff) == readoff)
            {
                currentMomenta1.push_back (momenta.at (j + 1));
            }
            //Element is in the second set
            else
            {
                currentMomenta2.push_back (momenta.at (j + 1));
            }

        }

        //Momenta generation complete, calculate contribution
        result += vertex() * massiveCurrent(currentMomenta1)
                        * massiveCurrent(currentMomenta2);
    }

    return result;
}

//Massless recursive current
complex_t ScalarTreeAmplitude::masslessCurrent
    (const std::vector <FourVector <real_t>>& momenta,
     const std::vector <unsigned int>& idList)
{
    //Check if recursion terminates
    if (momenta.size () == 1)
    {
        return 1;
    }
    //Continue recursion
    else
    {
        //Calculate current ID
        unsigned int currentID = 0;
        for (auto i : idList)
        {
            currentID += pow (2,i);
        }

        //std::cout << "currentID: " << currentID << "\n";

        //Check if current was already computed
        unsigned int level = momenta.size() - 2;

        for (auto i : currentStorage_ [level])
        {
            if (i.ID_ == currentID)
            {
                //std::cout << "Current was already calculated!\n";
                //std::cout << "Value: " << i.value_ << "\n\n";

                return i.value_;
            }
        }

        //Calculate current, store it and return it
        complex_t result = masslessPropagator (sum (momenta))
                         * masslessCurrentAmputated (momenta, idList);

        //std::cout << "Value: " << result << "\n\n";


        LabeledContainer container_t;
        container_t.ID_ = currentID;
        container_t.value_ = result;

        currentStorage_ [level].push_back (container_t);

        return result;

    }
}

//Massive recursive current
complex_t ScalarTreeAmplitude::massiveCurrent
    (const std::vector <FourVector <real_t>>& momenta)
{
    //Check if recursion terminates
    if (momenta.size () == 1)
    {
        return 1;
    }
    else
    {
        return massivePropagator (sum (momenta))
               * massiveCurrentAmputated (momenta);
    }
}

//Amplitude
complex_t ScalarTreeAmplitude::amplitude
    (const std::vector <FourVector <real_t>>& momenta)
{
    if (momenta.size() == numberOfLegs_)
    {
        //Initialize current momenta
        std::vector <FourVector <real_t>> currentMomenta = momenta;
        //We start recursion on the last leg
        currentMomenta.pop_back();

        //Prepare idList
        std::vector <unsigned int> idList;
        for (unsigned int i = 0; i < numberOfLegs_ - 1; i++)
        {
            idList.push_back (i);
        }

        //Initialize container for calculated currents
        currentStorage_ = new std::vector <LabeledContainer> [numberOfLegs_ - 2];

        //Initialize container for result
        complex_t result = 0;

        if (massless_)
        {
            result = masslessCurrentAmputated (currentMomenta, idList);
        }
        else
        {
            result = massiveCurrentAmputated (currentMomenta);
        }

        //Multiply with overall coupling factor
        result *= pow(coupling_, numberOfLegs_ - 2);

        //Clean current storage
        delete [] currentStorage_;

        return result;
    }

    else
    {
        std::cout << "Error: number of legs and "
            << "number of external momenta do not match\n";
        return 0;
    }
}

complex_t ScalarTreeAmplitude::vertex ()
{
    //Coupling is factored out
    return imaginaryUnit;
}

complex_t ScalarTreeAmplitude::masslessPropagator
    (const FourVector <real_t>& momenta)
{
    return imaginaryUnit / (momenta * momenta);
}

complex_t ScalarTreeAmplitude::massivePropagator
    (const FourVector <real_t>& momenta)
{
    return imaginaryUnit / (momenta * momenta - mass_ * mass_);
}

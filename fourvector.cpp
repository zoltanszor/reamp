/*
    Fourvector template class including arithmetic operator overloads
    between real and complex types.
*/
#include <array>
#include <complex>
#include <iostream>

#include "definitions.h"
#include "fourvector.h"

//---NON-MEMBER DEFINITIONS AND OPERATOR OVERLOADS---

//Addition: real + complex
FourVector <complex_t> operator + (const FourVector <real_t>& fourvector1,
                                   const FourVector <complex_t>& fourvector2)
{
    FourVector <complex_t> sum;

    for (unsigned int i = 0; i < 4; i++)
    {
        sum.setComponent(i, fourvector1(i) + fourvector2(i));
    }

    return sum;
}

//Addition: complex + real
FourVector <complex_t> operator + (const FourVector <complex_t>& fourvector1,
                                   const FourVector <real_t>& fourvector2)
{
    FourVector <complex_t> sum;

    for (unsigned int i = 0; i < 4; i++)
    {
        sum.setComponent(i, fourvector1(i) + fourvector2(i));
    }

    return sum;
}

//Subtraction: real - complex
FourVector <complex_t> operator - (const FourVector <real_t>& fourvector1,
                                   const FourVector <complex_t>& fourvector2)
{
    FourVector <complex_t> difference;

    for (unsigned int i = 0; i < 4; i++)
    {
        difference.setComponent(i, fourvector1(i) - fourvector2(i));
    }

    return difference;
}

//Subtraction: complex - real
FourVector <complex_t> operator - (const FourVector <complex_t>& fourvector1,
                                   const FourVector <real_t>& fourvector2)
{
    FourVector <complex_t> difference;

    for (unsigned int i = 0; i < 4; i++)
    {
        difference.setComponent(i, fourvector1(i) - fourvector2(i));
    }

    return difference;
}

//Scalar product: real * complex
complex_t operator * (const FourVector <real_t>& fourvector1,
                      const FourVector <complex_t>& fourvector2)
{
    complex_t product = fourvector1 (0) * fourvector2 (0);

    for (unsigned int i = 1; i < 4; i++)
    {
        product -= fourvector1 (i) * fourvector2 (i);
    }

    return product;
}

//Scalar product: complex * real
complex_t operator * (const FourVector <complex_t>& fourvector1,
                      const FourVector <real_t>& fourvector2)
{
    complex_t product = fourvector1 (0) * fourvector2 (0);

    for (unsigned int i = 1; i < 4; i++)
    {
        product -= fourvector1 (i) * fourvector2 (i);
    }

    return product;
}

//Scalar product of spatial components: real * real
real_t spatialProduct (const FourVector <real_t>& fourvector1,
                       const FourVector <real_t>& fourvector2)
{
    real_t sum = 0;

    for (unsigned int i = 1; i < 4; i++)
    {
        sum += fourvector1(i) * fourvector2(i);
    }

    return sum;
}

//Scalar product of spatial components: real * complex
complex_t spatialProduct (const FourVector <real_t>& fourvector1,
                          const FourVector <complex_t>& fourvector2)
{
    complex_t sum = 0;

    for (unsigned int i = 1; i < 4; i++)
    {
        sum += fourvector1(i) * fourvector2(i);
    }

    return sum;
}

//Scalar product of spatial components: complex * real
complex_t spatialProduct (const FourVector <complex_t>& fourvector1,
                          const FourVector <real_t>& fourvector2)
{
    complex_t sum = 0;

    for (unsigned int i = 1; i < 4; i++)
    {
        sum += fourvector1(i) * fourvector2(i);
    }

    return sum;
}

//Scalar product of spatial components: complex * complex
complex_t spatialProduct (const FourVector <complex_t>& fourvector1,
                          const FourVector <complex_t>& fourvector2)
{
    complex_t sum = 0;

    for (unsigned int i = 1; i < 4; i++)
    {
        sum += fourvector1(i) * fourvector2(i);
    }

    return sum;
}

/*
    Fourvector template class including arithmetic operator overloads
    between real and complex types.
*/

#ifndef FOURVECTOR
#define FOURVECTOR

#include <array>
#include <complex>
#include <cmath>
#include <iostream>
#include <vector>

#include "definitions.h"

template <class T>
class FourVector
{
public:

    //CONSTRUCTORS
    FourVector ();
    FourVector (const T& component0,
                const T& component1,
                const T& component2,
                const T& component3);
    FourVector (const std::array <T, 4>& components);
    template <class K>
    FourVector (const FourVector <K>& fourvector);

    //OPERATORS
    //Assigment with double -> complex included
    template <class K>
    FourVector <T>& operator = (const FourVector <K>& fourvector);
    //Addition of same type
    FourVector <T> operator + (const FourVector <T>& fourvector) const;
    //Subtraction of same  type
    FourVector <T> operator - (const FourVector <T>& fourvector) const;
    //Negation
    FourVector <T> operator - () const;
    //Lorentz-scalar product of same type
    T operator * (const FourVector <T>& fourvector) const;
    //Getting element at index
    T operator () (const int& index) const;

    //FUNCTIONS
    //Setting element at index
    void setComponent(const unsigned int& index, const T& value);
    //Square as vector*vector
    T square() const;
    //Length as \sqrt{vector*\bar{vector}}
    real_t length() const;
    //Spatial part
    std::array <T, 3> spatial() const;

    //I/O operations
    template <class K>
    friend std::ostream& operator << (std::ostream & out,
                                      const FourVector <K>& fourvector);
private:
    //Components
    std::array <T, 4> components_;

};


//---CLASS MEMBER DEFINITONS---

//Constructor: default
template <class T>
FourVector <T>::FourVector ()
    : components_({0, 0, 0, 0}) {}

//Constructor: via 4 arguments
template <class T>
FourVector <T>::FourVector (const T& component0,
                            const T& component1,
                            const T& component2,
                            const T& component3)
    : components_({component0, component1, component2, component3}) {}

//Constructor: via array
template <class T>
FourVector <T>::FourVector (const std::array <T, 4>& components)
    : components_(components) {}

//Copy constructor
template <class T> template <class K>
FourVector <T>::FourVector (const FourVector <K>& fourvector)
    : components_({fourvector(0), fourvector(1), fourvector(2), fourvector(3)})
{}

//Assignment
template <class T> template <class K>
FourVector<T>& FourVector <T>::operator = (const FourVector <K>& fourvector)
{
    for (unsigned int i = 0; i < 4; i++)
    {
        components_[i] = fourvector(i);
    }

    return *this;
}

//Addition of same type
template <class T>
FourVector<T> FourVector <T>::operator + (const FourVector <T>& fourvector) const
{
    FourVector<T> sum;

    for (unsigned int i = 0; i < 4; i++)
    {
        sum.components_[i] = components_[i] + fourvector.components_[i];
    }

    return sum;
}

//Subraction of same type
template <class T>
FourVector<T> FourVector <T>::operator - (const FourVector <T>& fourvector) const
{
    FourVector<T> difference;

    for (unsigned int i = 0; i < 4; i++)
    {
        difference.components_[i] = components_[i] - fourvector(i);
    }

    return difference;
}

//Negation
template <class T>
FourVector<T> FourVector <T>::operator - () const
{
    FourVector<T> negative;

    for (unsigned int i = 0; i < 4; i++)
    {
        negative.components_[i] = - components_[i];
    }

    return negative;
}

//Getting element at index
template <class T>
T FourVector <T>::operator () (const int& index) const
{
    return components_.at(index);
}

//Scalar product with same type
template <class T>
T FourVector <T>::operator * (const FourVector <T>& fourvector) const
{
    T product = components_[0] * fourvector.components_[0];
    for (unsigned int i = 1; i < 4; i++)
    {
        product -= components_[i] * fourvector.components_[i];
    }

    return product;
}

//Setting element at index
template <class T>
void FourVector <T>::setComponent(const unsigned int& index, const T& value)
{
    components_.at(index) = value;
}

//Square of the vector
template <class T>
T FourVector <T>::square () const
{
    T squaredSum = components_[0] * components_[0];

    for (unsigned int i = 1; i < 4; i++)
    {
        squaredSum -= components_[i] * components_[i];
    }

    return squaredSum;
}

//Length of the vector as \sqrt{|vector*\bar{vector}|}
template <class T>
real_t FourVector<T>::length () const
{
    //Cast type to complex
    std::array <complex_t, 4> casted;
    for (unsigned int i = 0; i < 4; i++)
    {
        casted[i] = components_[i];
    }

    complex_t squaredSum = std::norm (casted[0]);
    for (unsigned int i = 1; i < 4; i++)
    {
        squaredSum -= std::norm (casted[i]);
    }

    return sqrt ( abs (squaredSum.real () ) );

}

//Spatial part
template <class T>
std::array <T, 3> FourVector <T>::spatial () const
{
    std::array <T, 3> spatialVector;

    for (unsigned int i = 0; i < 3; i++)
    {
        spatialVector[i] = components_[i + 1];
    }

    return spatialVector;
}

//Printing
template <class K>
std::ostream& operator << (std::ostream& out,
                           const FourVector <K>& fourvector)
{
    out << "( ";

    for (unsigned int i = 0; i < 4; i++)
    {
        out << fourvector.components_[i];

        if (i < 3)
        {
            out << ", ";
        }
    }

    out << " )";

    return out;
}

//---NON-MEMBER DEFINITIONS AND OPERATOR OVERLOADS---

//Addition: real + complex
FourVector <complex_t> operator + (const FourVector <real_t>& fourvector1,
                                   const FourVector <complex_t>& fourvector2);

//Addition: complex + real
FourVector <complex_t> operator + (const FourVector <complex_t>& fourvector1,
                                   const FourVector <real_t>& fourvector2);

//Subtraction: real - complex
FourVector <complex_t> operator - (const FourVector <real_t>& fourvector1,
                                   const FourVector <complex_t>& fourvector2);

//Subtraction: complex - real
FourVector <complex_t> operator - (const FourVector <complex_t>& fourvector1,
                                   const FourVector <real_t>& fourvector2);

//Scalar product: real * complex
complex_t operator * (const FourVector <real_t>& fourvector1,
                      const FourVector <complex_t>& fourvector2);

//Scalar product: complex * real
complex_t operator * (const FourVector <complex_t>& fourvector1,
                      const FourVector <real_t>& fourvector2);

//Multiplication with number: real * any
template <class T>
FourVector <T> operator * (const real_t& number,
                           const FourVector <T>& fourvector)
{
    FourVector <T> multiple;

    for (unsigned int i = 0; i < 4; i++)
    {
        multiple.setComponent (i, number * fourvector(i));
    }

    return multiple;
}

//Multiplication with number: complex * any
template <class T>
FourVector <complex_t> operator * (const complex_t& number,
                                   const FourVector <T>& fourvector)
{
    FourVector <complex_t> multiple;

    for (unsigned int i = 0; i < 4; i++)
    {
        multiple.setComponent (i, number * fourvector(i));
    }

    return multiple;
}

//Multiplication with number: any * real
template <class T>
FourVector <T> operator * (const FourVector <T>& fourvector,
                           const real_t& number)
{
    FourVector <T> multiple;

    for (unsigned int i = 0; i < 4; i++)
    {
        multiple.setComponent (i, number * fourvector(i));
    }

    return multiple;
}

//Multiplication with number: any * complex
template <class T>
FourVector <complex_t> operator * (const FourVector <T>& fourvector,
                                   const complex_t& number)
{
    FourVector <complex_t> multiple;

    for (unsigned int i = 0; i < 4; i++)
    {
        multiple.setComponent (i, number * fourvector(i));
    }

    return multiple;
}

//Division by number: any / real
template <class T>
FourVector<T> operator / (const FourVector <T>& fourvector,
                          const real_t& number)
{
    FourVector<T> divided;

    for (unsigned int i = 0; i < 4; i++)
    {
        divided.setComponent (i, fourvector(i) / number);
    }

    return divided;
}

//Division by number: any / complex
template <class T>
FourVector<complex_t> operator / (const FourVector <T>& fourvector,
                                  const complex_t& number)
{
    FourVector<complex_t> divided;

    for (unsigned int i = 0; i < 4; i++)
    {
        divided.setComponent (i, fourvector(i) / number);
    }

    return divided;
}

//Scalar product of spatial components: real * real
real_t spatialProduct (const FourVector <real_t>& fourvector1,
                       const FourVector <real_t>& fourvector2);

//Scalar product of spatial components: real * complex
complex_t spatialProduct (const FourVector <real_t>& fourvector1,
                          const FourVector <complex_t>& fourvector2);

//Scalar product of spatial components: complex * real
complex_t spatialProduct (const FourVector <complex_t>& fourvector1,
                          const FourVector <real_t>& fourvector2);

//Scalar product of spatial components: complex * complex
complex_t spatialProduct (const FourVector <complex_t>& fourvector1,
                          const FourVector <complex_t>& fourvector2);

//Sum of all fourvectors in a list
template <class T>
FourVector <T> sum (const std::vector <FourVector <T>>& momenta)
{
    FourVector <T> result;

    for (auto element : momenta)
    {
        result = result + element;
    }

    return result;
}
//template FourVector <real_t> sum (const std::vector <FourVector <real_t>>&);
//template FourVector <complex_t> sum (const std::vector <FourVector <complex_t>>&);

#endif

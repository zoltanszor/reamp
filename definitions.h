#ifndef DEFINITIONS
#define DEFINITIONS

//Macros
//Sets accuracy within two float numbers will be considered equal
#define IS_CLOSE_ACCURACY 1e-16

//Types
typedef double real_t;
typedef std::complex <double> complex_t;

const complex_t imaginaryUnit (0,1);

struct LabeledContainer
{
    unsigned int ID_;
    complex_t value_;
};

//Functions
//Test closeness of two float number
inline bool isClose (real_t a, real_t b)
{
    return (std::abs (a - b) < IS_CLOSE_ACCURACY) ? true : false;
}

//Test closeness of two complex float number
inline bool isClose (complex_t a, complex_t b)
{
    return isClose (a.real (), b.real ()) && isClose (a.imag (), b.imag ());
}

#endif

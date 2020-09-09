#ifndef DEFINITIONS
#define DEFINITIONS

//Types
typedef double real_t;
typedef std::complex <double> complex_t;

const complex_t imaginaryUnit (0,1);

struct LabeledContainer
{
    unsigned int ID_;
    complex_t value_;
};

#endif

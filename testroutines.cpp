//Testroutines
#include <array>
#include <complex>

#include "definitions.h"
#include "fourvector.h"
#include "scalaramplitude.h"

void testFourVector ()
{
    std::cout << "\n*** Testing FourVector functionality ***\n" ;

    //Constructors
    FourVector <real_t> testVec1;
    FourVector <real_t> testVec2 (1, 2, 3, 4);

    std::array <complex_t, 4> components =
        { { {3, 4}, {5, 6}, {7, 8}, {9, 10} } };
    FourVector <complex_t> testVec3 (components);

    const real_t c1 = 5;
    const complex_t c2 = {5, 6};

    std::cout << "v1: " << testVec1 << "\n";
    std::cout << "v2: " << testVec2 << "\n";
    std::cout << "v3: " << testVec3 << "\n";

    //Operators
    testVec1 = testVec2;
    std::cout << "v1 = v2: " << testVec1 << "\n";

    std::cout << "v1 + v2: " << testVec1 + testVec2 << "\n";
    std::cout << "v1 - v2: " << testVec1 - testVec2 << "\n";

    std::cout << "v1 + v3: " << testVec1 + testVec2 << "\n";
    std::cout << "v3 + v1: " << testVec3 + testVec1 << "\n";

    std::cout << "v1 - v3: " << testVec1 - testVec3 << "\n";
    std::cout << "v3 - v1: " << testVec3 - testVec1 << "\n";

    std::cout << "-v1: " << - testVec1 << "\n";
    std::cout << "-v3: " << - testVec3 << "\n";

    std::cout << "v1 * v2: " << testVec1 * testVec2 << "\n";
    std::cout << "v1 * v3: " << testVec1 * testVec3 << "\n";
    std::cout << "v3 * v1: " << testVec3 * testVec1 << "\n";

    std::cout << "c1 * v1: " << c1 * testVec1 << "\n";
    std::cout << "c2 * v1: " << c2 * testVec1 << "\n";

    std::cout << "c1 * v3: " << c1 * testVec3 << "\n";
    std::cout << "c2 * v3: " << c2 * testVec3 << "\n";

    std::cout << "v1 * c1: " << testVec1 * c1 << "\n";
    std::cout << "v1 * c2: " << testVec1 * c2 << "\n";

    std::cout << "v3 * c1: " << testVec3 * c1 << "\n";
    std::cout << "v3 * c2: " << testVec1 * c2 << "\n";

    std::cout << "v1 / c1: " << testVec1 / c1 << "\n";
    std::cout << "v1 / c2: " << testVec1 / c2 << "\n";

    std::cout << "v3 / c1: " << testVec3 / c1 << "\n";
    std::cout << "v3 / c2: " << testVec3 / c2 << "\n";

    std::cout << "v1(2): " << testVec1 (2) << "\n";

    std::cout << "v3**2: " << testVec3.square () << "\n";
    std::cout << "v3 length: " << testVec3.length () << "\n";

    std::array <complex_t, 3> threeVec = testVec3.spatial ();
    std::cout << "v3 spatial part: "
        << threeVec[0] << ", " << threeVec[1] << ", " << threeVec[2] << "\n";

    std::cout << "Spatial product v1 * v2: "
              << spatialProduct (testVec1, testVec2) << "\n";
    std::cout << "Spatial product v1 * v3: "
              << spatialProduct (testVec1, testVec3) << "\n";
    std::cout << "Spatial product v3 * v1: "
              << spatialProduct (testVec3, testVec1) << "\n";
    std::cout << "Spatial product v3 * v3: "
              << spatialProduct (testVec3, testVec3) << "\n";


    testVec3 = testVec1;
    std::cout << "v3 = v1: " << testVec3 << "\n";

    FourVector <complex_t> testVec4 = testVec3;
    std::cout << "v4 = v3: " << testVec4 << "\n";

    FourVector <complex_t> testVec5 = testVec1;
    std::cout << "v5 = v1: " << testVec5 << "\n";
}

void testScalarTreeAmplitude ()
{
    ScalarTreeAmplitude dummyAmplitude;
    ScalarTreeAmplitude masslessAmplitude (6, 1);
    ScalarTreeAmplitude massiveAmplitude (6, 1, 500);

    FourVector <real_t> p1(1, 22, 3, 44);
    FourVector <real_t> p2(11, 2, 33, 4);
    FourVector <real_t> p3 (-1, 22, -4, 55);
    FourVector <real_t> p4 (-2, 32, -5, 5);
    FourVector <real_t> p5 (8, 11, 21, 7);
    FourVector <real_t> p6 = - p1 - p2 - p3 - p4 - p5;

    std::vector <FourVector <real_t>> momenta = {p1, p2, p3, p4, p5, p6};
    std::vector <FourVector <real_t>> momentaPermutated = {p3, p4, p5, p6, p1, p2};

    std::vector <FourVector <real_t>> momenta3 = {p1, p2, -p1 - p2};

    //std::cout << "sum: " << sum (momenta) << "\n";

    ScalarTreeAmplitude amplitude6 (6, 1);
    std::cout << "6 leg amplitude: " << amplitude6.amplitude (momenta) << "\n";
    std::cout << "6 leg amplitude (perm): " << amplitude6.amplitude (momentaPermutated) << "\n";

    ScalarTreeAmplitude amplitude6_2 (6, 1, 0);
    std::cout << "6 leg amplitude (mass): " << amplitude6_2.amplitude (momenta) << "\n";

    ScalarTreeAmplitude amplitude3 (3, 1);
    std::cout << "3 leg amplitude: " << amplitude3.amplitude (momenta3) << "\n";

    p4 = - p1 - p2 - p3;
    std::vector <FourVector <real_t>> momenta4 = {p1, p2, p3, p4};

    //If scalar amplitudes would be colour ordered
    ScalarTreeAmplitude amplitude4 (4, 1);
    std::cout << "4 leg amplitude: numerical: "
        << amplitude4.amplitude (momenta4) << "\n";

    complex_t analytical;
    analytical = imaginaryUnit * imaginaryUnit
               * (amplitude4.masslessPropagator (p1 + p4)
               + amplitude4.masslessPropagator (p1 + p2)
               + amplitude4.masslessPropagator (p1 + p3));
    std::cout << "4 leg amplitude: analytical: " << analytical << "\n";
}

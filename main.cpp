// Main file

#include <iostream>

#include "fourvector_real.h"
#include "testroutines.h"


// LEVEL macro to switch between different functionality
// 0: test
#define LEVEL 0

int main()
{

    //Testing environment
    #if LEVEL == 0
        std::cout << "\n*** Testing environment ***\n\n";

        testUtilities ();
        //testFourVector ();
        //testScalarTreeAmplitude ();

    //Running environment
    #else
        std::cout << "\nThis part is not implemented yet\n";
    #endif

    return 0;
}

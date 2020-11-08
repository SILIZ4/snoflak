#include <math.h>
#include "lattice.h"
#include <iostream>


int main(){
    std::map<std::string, double> parameters { 
        {"rho", 0.64},
        {"beta", 1.6},
        {"alpha", 0.21},
        {"theta", 0.0205},
        {"kappa", 0.07},
        {"mu", 0.07},
        {"gamma", 0.00005},
        {"sigma", 0.0000}
    };
    size_t iterations = 1000;
    size_t size = 100;

    Lattice lattice(size, parameters);

    lattice.saveTo("frames/snowflake_init");

    for (size_t i=0; i<iterations; i++) {
        std::cout << "iterations " + std::to_string(i) << std::endl;
        lattice.diffuse();
        lattice.freeze();
        lattice.attach();
        lattice.melt();
        //lattice.addNoise();


        if (i % 10 == 0)
            lattice.saveTo("frames/snowflake_"+std::to_string(i/10));
    }

    return 0;
}

#include <math.h>
#include "lattice.h"
#include <iostream>


int main(){
    std::map<std::string, double> parameters { 
        {"rho", 0.8},
        {"beta", 2.9},
        {"alpha", 0.006},
        {"theta", 0.004},
        {"kappa", 0.05},
        {"mu", 0.015},
        {"gamma", 0.0001},
        {"sigma", 0.00002}
    };
    size_t iterations = 1000;
    size_t size = 50;

    Lattice lattice(size, parameters);


    for (size_t i=0; i<iterations; i++) {
        std::cout << "iterations " + std::to_string(i) << std::endl;
        lattice.diffuse();
        lattice.freeze();
        lattice.attach();
        lattice.melt();
        //lattice.addNoise();
    }
    lattice.saveTo("snowflake_bin");

    return 0;
}

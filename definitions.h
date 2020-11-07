#ifndef DEFINITIONS_H
#define DEFINITIONS_H


#include <vector>


struct Cell{
    double inSnowflake;
    double vaporMass;
    double superliquidMass;
    double solidMass;
};


typedef std::vector<std::vector<Cell>> Lattice;


#endif

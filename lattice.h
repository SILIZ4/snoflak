#ifndef LATTICE_H
#define LATTICE_H


#include <vector>

struct Cell {
    bool inSnowflake = false;
    double vaporMass = 0;
    double solidMass = 0;
    double liquidMass = 0;
};


class Lattice: public std::vector<std::vector<Cell>>{
    size_t latticeSize;
    double density;

    public:
        Lattice(size_t size, double density);

    private:
        void freezeCenter();
        void setDensity();

        void diffuse();
        void freeze();
        void attach();
        void melt();
        void addNoise();
};

#endif

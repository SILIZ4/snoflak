#ifndef LATTICE_H
#define LATTICE_H


#include <vector>
#include <list>


struct Cell {
    bool inSnowflake = false;
    double vaporMass = 0;
    double solidMass = 0;
    double liquidMass = 0;
};


class Lattice: public std::vector<std::vector<Cell>>{
    size_t latticeSize;
    double density;


    std::list<std::pair<size_t, size_t>> boundary;
    std::list<std::pair<size_t, size_t>> complementOfClosure;

    public:
        Lattice(size_t size, double density);

        void updateBoundaryAndComplementOfClosure();

        void diffuse();
        void freeze();
        void attach();
        void melt();
        void addNoise();


    private:
        void freezeCenter();
        void setDensityOutsideSnowflake();

        std::list<std::pair<long int, long int>> getNeighboursIndicesOf(long int i, long int j) const;
        void filterInvalidIndices(std::list<std::pair<long int, long int>> &indexList) const;

};

#endif

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
    

    public:
        Lattice(size_t size, double density);

    private:
        void freezeCenter();
        void setDensityOutsideSnowflake();

        std::list<std::pair<long int, long int>> getNeighboursIndicesOf(long int i, long int j) const;
        void filterInvalidIndices(std::list<std::pair<long int, long int>> &indexList) const;

        std::list<Cell> getSnowflakeBoundary() const;
        std::list<Cell> getClosureComplement() const;

        void diffuse();
        void freeze();
        void attach();
        void melt();
        void addNoise();
};

#endif

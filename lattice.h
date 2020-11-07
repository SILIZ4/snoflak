#ifndef LATTICE_H
#define LATTICE_H


#include <vector>
#include <list>
#include <map>
#include <string>


struct Cell {
    bool inSnowflake_before= false;
    double vaporMass_before = 0;
    double solidMass_before = 0;
    double liquidMass_before = 0;

    bool inSnowflake_after = false;
    double vaporMass_after = 0;
    double solidMass_after = 0;
    double liquidMass_after = 0;
};


class Lattice: public std::vector<std::vector<Cell>>{
    size_t latticeSize;
    double density;
    std::map<std::string, double> parameters;

    std::list<std::pair<size_t, size_t>> boundary;
    std::list<std::pair<size_t, size_t>> complementOfClosure;

    public:
        Lattice(size_t size, double density, std::map<std::string, double> parameters);

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

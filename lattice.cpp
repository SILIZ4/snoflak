#include <stdexcept>
#include <math.h>
#include <algorithm>

#include "lattice.h"


using namespace std;


Lattice::Lattice(size_t size, double density): latticeSize(size) {
    if (density < 0)
        throw logic_error("The density must be positive");
    density = density;

    resize(size, vector<Cell>(size));
    freezeCenter();
    setDensityOutsideSnowflake();
}

void Lattice::freezeCenter(){
    size_t middle = ceil(latticeSize/2);
    
    (*this)[middle][middle].inSnowflake = true;
    (*this)[middle][middle].solidMass = 1;
}

void Lattice::setDensityOutsideSnowflake() {
    size_t middle = ceil(latticeSize/2);

    for (size_t i=0; i<latticeSize; i++){
        for (size_t j=i+1; j<latticeSize; j++){

            if (i != middle && j != middle) {
                (*this)[i][j].vaporMass = density;
                (*this)[j][i].vaporMass = density;
            }
        }
    }
}


list<pair<long int, long int>> Lattice::getNeighboursIndicesOf(long int i, long int j) const{
    int parity = i % 2;

    list<pair<long int, long int>> neighbours {
        {i, j}, {i-1, j+parity}, {i-1, j+1+parity}, {i, j-1}, {i, j+1}, {i+1, j+parity}, {i+1, j+1+parity}
    };

    filterInvalidIndices(neighbours);
    return neighbours;
}

void Lattice::filterInvalidIndices(std::list<std::pair<long int, long int>> &indexList) const{
    indexList.remove_if( [&](const std::pair<long int, long int> indices) -> bool {
                            auto i = indices.first;
                            auto j = indices.second;
                            return (i < 0) || (j < 0) || (i > latticeSize-1) || (j > latticeSize-1);
                        } );
}


void Lattice::updateBoundaryAndComplementOfClosure() {
    boundary.clear();
    complementOfClosure.clear();


    std::list<std::pair<long int, long int>> neighbours;
    bool inBoundary;

    for (size_t i=0; i<latticeSize; i++) {
        for (size_t j=0; j<latticeSize; j++) {
            if ( (*this)[i][j].inSnowflake == true )
                continue;


            neighbours = getNeighboursIndicesOf(i, j);
            // possiblity of using any_of and lambda function
            for (auto& neighbour: neighbours){
                if ( (*this)[neighbour.first][neighbour.second].inSnowflake == true ) {
                    inBoundary = true;
                    break;
                }
            }

            if(inBoundary)
                boundary.push_back({i, j});
            else
                complementOfClosure.push_back({i, j});

        }
    }
}

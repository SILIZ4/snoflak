#include <stdexcept>
#include <math.h>
#include <algorithm>

#include "lattice.h"


using namespace std;


Lattice::Lattice(size_t size, double density, std::map<std::string, double> parameters): latticeSize(size), parameters(parameters) {
    if (density < 0)
        throw logic_error("The density must be positive");
    density = density;

    resize(size, vector<Cell>(size));
    freezeCenter();
    setDensityOutsideSnowflake();
}

void Lattice::freezeCenter(){
    size_t middle = ceil(latticeSize/2);
    
    (*this)[middle][middle].inSnowflake_before = true;
    (*this)[middle][middle].solidMass_before = 1;
}

void Lattice::setDensityOutsideSnowflake() {
    size_t middle = ceil(latticeSize/2);

    for (size_t i=0; i<latticeSize; i++){
        for (size_t j=i+1; j<latticeSize; j++){

            if (i != middle && j != middle) {
                (*this)[i][j].vaporMass_before = density;
                (*this)[j][i].vaporMass_before = density;
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
            if ( (*this)[i][j].inSnowflake_before == true )
                continue;


            neighbours = getNeighboursIndicesOf(i, j);
            // possiblity of using any_of and lambda function
            for (auto& neighbour: neighbours){
                if ( (*this)[neighbour.first][neighbour.second].inSnowflake_before ) {
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

void Lattice::diffuse() {
    list<pair<long int, long int>> neighbours;
    double sum;


    for (auto indices=complementOfClosure.begin(); indices!=boundary.end(); indices++) {
        if (indices == complementOfClosure.end())
            indices = boundary.begin();

        neighbours = getNeighboursIndicesOf(indices->first, indices->second);

        for (auto& neighbour: neighbours){
            if ( (*this)[neighbour.first][neighbour.second].inSnowflake_before )
                sum += (*this)[indices->first][indices->second].vaporMass_before;
            else
                sum += (*this)[neighbour.first][neighbour.second].vaporMass_before;
        }
        sum += (7-neighbours.size()) * (*this)[indices->first][indices->second].vaporMass_before;

        (*this)[indices->first][indices->second].vaporMass_after = sum/7;
    }
}

void Lattice::freeze() {

    for (auto& indices: boundary) {
        Cell& cell = (*this)[indices.first][indices.second];

        cell.liquidMass_after = cell.liquidMass_before + (1-parameters["kappa"]) * cell.vaporMass_before;
        cell.solidMass_after = cell.solidMass_before + parameters["kappa"] * cell.vaporMass_before;
        cell.vaporMass_after = 0;
    }

}

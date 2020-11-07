#include <stdexcept>
#include <math.h>
#include <algorithm>
#include <random>

#include "lattice.h"


using namespace std;


static std::mt19937 generator;


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

    updateValuesOnBoundary();
    updateValuesOnComplementOfClosure();
    updateBoundaryAndComplementOfClosure();
}

void Lattice::freeze() {

    for (auto& indices: boundary) {
        Cell& cell = (*this)[indices.first][indices.second];

        cell.liquidMass_after = cell.liquidMass_before + (1-parameters["kappa"]) * cell.vaporMass_before;
        cell.solidMass_after = cell.solidMass_before + parameters["kappa"] * cell.vaporMass_before;
        cell.vaporMass_after = 0;
    }

    updateValuesOnBoundary();
    updateBoundaryAndComplementOfClosure();
}

void Lattice::attach() {
    list<pair<long int, long int>> neighbours;
    size_t numberOfNeighboursInSnowflake;
    double sumOfVaporMass;

    bool condition1, condition2, condition3;

    for (auto& indices: boundary) {
        Cell& cell = (*this)[indices.first][indices.second];

        neighbours = getNeighboursIndicesOf(indices.first, indices.second);
        neighbours.pop_front(); // we exclude the cell itself

        numberOfNeighboursInSnowflake = 0;
        sumOfVaporMass = cell.vaporMass_before;
        for (auto& neighbour : neighbours) {
            if ((*this)[neighbour.first][neighbour.second].inSnowflake_before)
                numberOfNeighboursInSnowflake++;
            sumOfVaporMass += (*this)[neighbour.first][neighbour.second].vaporMass_before;
        }

        condition1 = (numberOfNeighboursInSnowflake == 1 || numberOfNeighboursInSnowflake == 2) && cell.liquidMass_before >= parameters["beta"];
        condition2 = numberOfNeighboursInSnowflake >= 3 && (cell.liquidMass_before >= 1 || (sumOfVaporMass < parameters["theta"] && cell.liquidMass_before >= parameters["alpha"]));
        condition3 = numberOfNeighboursInSnowflake >= 4;
        if (condition1 || condition2 || condition3) {
            cell.inSnowflake_after = true;
            cell.solidMass_after = cell.solidMass_before + cell.liquidMass_before;
            cell.liquidMass_after = 0;
        }

    }
    
    updateValuesOnBoundary();
    updateBoundaryAndComplementOfClosure();
}

void Lattice::melt() {

    for (auto& indices: boundary) {
        Cell& cell = (*this)[indices.first][indices.second];

        cell.liquidMass_after = (1-parameters["mu"])*cell.liquidMass_before;
        cell.solidMass_after = (1-parameters["gamma"])*cell.solidMass_before;
        cell.vaporMass_after = cell.vaporMass_before + parameters["mu"]*cell.liquidMass_before + parameters["gamma"] * cell.solidMass_before;
    }

    updateValuesOnBoundary();
    updateBoundaryAndComplementOfClosure();
}

void Lattice::addNoise() {
    std::bernoulli_distribution bernoulliDistribution(0.5);
    double perturbation;

    for (auto indices=complementOfClosure.begin(); indices!=boundary.end(); indices++) {
        if (indices == complementOfClosure.end())
            indices = boundary.begin();

        Cell& cell = (*this)[indices.first][indices.second];


        perturbation = (2*bernoulliDistribution(generator)-1) * parameters["sigma"];
        cell.vaporMass_after = (1-perturbation)*cell.vaporMass_before;
    }
    updateValuesOnBoundary();
    updateValuesOnComplementOfClosure();
    updateBoundaryAndComplementOfClosure();
}

void Lattice::updateValuesOnBoundary() {
    for (auto& indices: boundary) {
        Cell& cell = (*this)[indices.first][indices.second];

        cell.inSnowflake_before = cell.inSnowflake_after;
        cell.liquidMass_before = cell.liquidMass_after;
        cell.solidMass_before = cell.solidMass_after;
        cell.vaporMass_before = cell.vaporMass_after;
    }
}

void Lattice::updateValuesOnComplementOfClosure() {
    for (auto& indices: complementOfClosure) {
        Cell& cell = (*this)[indices.first][indices.second];

        cell.inSnowflake_before = cell.inSnowflake_after;
        cell.liquidMass_before = cell.liquidMass_after;
        cell.solidMass_before = cell.solidMass_after;
        cell.vaporMass_before = cell.vaporMass_after;
    }
}

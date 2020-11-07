#include <stdexcept>
#include <math.h>

#include "lattice.h"


using namespace std;


Lattice::Lattice(size_t size, double density): latticeSize(size) {
    if (density < 0)
        throw logic_error("The density must be positive");
    density = density;

    resize(size, vector<Cell>(size));
    freezeCenter();
    setDensity();
}

void Lattice::freezeCenter(){
    size_t middle = ceil(latticeSize/2);
    
    (*this)[middle][middle].inSnowflake = true;
    (*this)[middle][middle].solidMass = 1;
}

void Lattice::setDensity(){
    for (size_t i=0; i<latticeSize; i++){
        for (size_t j=i+1; j<latticeSize; j++){
            
            (*this)[i][j].vaporMass = density;
            (*this)[j][i].vaporMass = density;
        }
    }
}

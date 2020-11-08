#include <math.h>
#include <fstream>
#include <iostream>

#include "rapidjson/document.h"
#include "lattice.h"


using namespace std;


static char* getCharFromString(const string& str){
    char *charPtr = new char [str.length()+1];
    strcpy(charPtr, str.c_str());
    return charPtr;
}

static rapidjson::Document getJsonDocumentFromFile(const string& fileName){
    ifstream fileStream(fileName);
    if (!fileStream.is_open()) throw runtime_error("Could not open config file");
    std::string tmp((istreambuf_iterator<char>(fileStream)),
                     istreambuf_iterator<char>());
    const char* fileContent = getCharFromString(tmp);

    rapidjson::Document document;
    document.Parse(fileContent);
    delete[] fileContent;
    return document;
}

static std::map<std::string, double> getMapFromJsonDocument(rapidjson::Document& document) {
    std::map<std::string, double> parametersMap;

    std::list<std::string> parameters {"rho", "beta", "alpha", "theta", "kappa", "mu", "gamma", "sigma" };


    for (auto& parameter: parameters) {
        const char* parameterName = getCharFromString(parameter);
        parametersMap.emplace(parameter, document[parameterName].GetDouble());
        delete[] parameterName;
    }
    return parametersMap;
}

int main(int argc, char* argv[]){
    if (argc == 1) {
        std::cout << "You must enter the json file containing the parameters" << std::endl;   
        return 1;
    } 

    bool skipFrames = false;

    auto document = getJsonDocumentFromFile(argv[1]);
    auto parameters = getMapFromJsonDocument(document);


    size_t iterations = document["iterations"].GetInt();
    size_t size = document["size"].GetInt();
    if (document.HasMember("frameskips"))
        skipFrames = true;


    Lattice lattice(size, parameters);


    for (size_t i=0; i<iterations; i++) {
        std::cout << "iterations " + std::to_string(i) + "/" + std::to_string(iterations) << "\r";
        lattice.diffuse();
        lattice.freeze();
        lattice.attach();
        lattice.melt();
        //lattice.addNoise();


        if (skipFrames) {
            if (i % document["frameskips"].GetInt() == 0)
                lattice.saveTo("frames/snowflake_"+std::to_string(i));
        }
    }

    return 0;
}

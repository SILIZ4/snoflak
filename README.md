# snoflak

*It's christmas let's go home!* The main goal of our project is to reproduce the results of [this paper on snowflake growth simulation](http://psoup.math.wisc.edu/papers/h2l.pdf) in an object-oriented `C++` code. We also implemented a box-counting algorithm to calculate the fractal dimension of snowflakes boundaries in Python.

## Installation
You must first clone the repository (**recursively**, to include the JSON parsing submodule [RapidJSON](http://rapidjson.org/)):

`git clone --recursive`

You must then run our compilation script ([CMake](https://cmake.org/) and g++ are required):

`./compile.sh`

This will create the `snowflake` executable in the repo you cloned. 

## Usage
Once the code is compiled, you can input the parameters of the snowflake in a JSON configuration file (you can see an example in [parameters.json](https://github.com/SILIZ4/snoflak/blob/master/parameters.json)). Simply run:

`./snowflake parameters.json`

This will create data frames for vapour, solid and liquid mass, and a binary mask of the snowflake's interior at the location you specified in the configuration file. 

## Generating figures



# snoflak

*It's Christmas let's go home!* The main goal of our project is to reproduce the results of [this paper on snowflake growth simulation](http://psoup.math.wisc.edu/papers/h2l.pdf) in an object-oriented `C++` code. We also implemented a box-counting algorithm to calculate the fractal dimension of snowflakes boundaries in Python. [CMake](https://cmake.org/) and a C++ compiler (e.g. g++) are required to compile and produce snowflakes.

## Installation
You must first clone the repository **recursively** to include the JSON parsing submodule [RapidJSON](http://rapidjson.org/):

`git clone --recursive`

For Unix-like and Mac users, the bash script ``compile.sh`` can be ran to compile the project and move the binary executable into the root of the project. For Windows, the following commands will do the same
```
mkdir build
cd build
cmake ..
make
mv ./snowflake ../snowflake
cd ..
```

## Usage
Once the code is compiled, you can input the parameters of the snowflake in a JSON configuration file (you can see an example in [parameters.json](https://github.com/SILIZ4/snoflak/blob/master/parameters.json)). Simply run:

`./snowflake parameters.json`

The program saves the snowflake into four binary matrices: vapor mass (double), solid mass(double), liquid mass(double) and the snowflake's interior(boolean). If specified in the configuration file, the attribute `frameskips` allows for animated gifs: a frame (i.e. the snowflake) is saved at every number of frames skipped. Every frame is named ``filepath_prefix``\_\<iteration\>\_\<snowflake atttribute\> and the final file is named ``filepath_prefix``\_\<snowflake atttribute\>.

## Generating figures

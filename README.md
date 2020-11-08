# snoflak

![Zoom on our snowflake](zoom.jpg)

*It's Christmas let's go home!* The main goal of our project is to reproduce the results of [this paper on snowflake growth simulation](http://psoup.math.wisc.edu/papers/h2l.pdf) in an object-oriented `C++` code. We also implemented a box-counting algorithm to calculate the fractal dimension of snowflakes boundaries in Python. [CMake](https://cmake.org/) and a C++ compiler (e.g. g++) are required to compile and produce snowflakes.

## Installation
You must first clone the repository **recursively** to include the JSON parsing submodule [RapidJSON](http://rapidjson.org/):

`git clone --recursive`

For Unix-like and Mac users, the bash script ``compile.sh`` can be run to compile the project and move the binary executable into the root of the project. For Windows, the following commands will do the same
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

The program saves the snowflake into four binary matrices: vapor mass (double), solid mass (double), liquid mass (double) and the snowflake's interior (boolean). If specified in the configuration file, the attribute `frameskips` allows for animated gifs: a frame (i.e. the snowflake) is saved at every number of frames skipped. Every frame is named ``filepath_prefix``\_\<iteration\>\_\<snowflake atttribute\> and the final file is named ``filepath_prefix``\_\<snowflake atttribute\>.

## Generating figures
The Python file `hex_grid.py`contains a function to plot/export the different masses on the domain. A hexagonal grid is used to represent the underlying crystalline structure. A snapshot of the snowflake can also be exported.

## Fractal Dimension
Using the script `fractal_dimension.py`, you can get the box-counting dimension of a curve in 2D space. We recommend using a liquid mass file to compute the fractal dimension of a snowflake, since liquid is located only at the boundary, i.e. the liquid mass curve is a good approximation of the snowflake's boundary. Some of the parameters of the script have to be modified according to the size of the data frame.

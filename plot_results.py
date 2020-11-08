import numpy
from matplotlib import pyplot
from hex_grid import hex_grid


with open("frames10000/snowflake_913_vapor", "rb") as file_stream:
    data = numpy.fromfile(file_stream, dtype=numpy.double).reshape(100, 100)

#hex_grid(data.T)
pyplot.imshow(data, cmap="Blues")
pyplot.colorbar()
pyplot.show()

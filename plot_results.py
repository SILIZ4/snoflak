import numpy
from matplotlib import pyplot
from hex_grid import hex_grid


with open("frames/snowflake_49_solid", "rb") as file_stream:
    data = numpy.fromfile(file_stream, dtype=numpy.double).reshape(100, 100)

# hex_grid(data.T)
pyplot.imshow(data)
pyplot.colorbar()
pyplot.show()

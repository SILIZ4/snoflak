import numpy
from matplotlib import pyplot
from hex_grid import hex_grid


with open("frames/snowflake_2300_vapor", "rb") as file_stream:
    data1 = numpy.fromfile(file_stream, dtype=numpy.double).reshape(500, 500)
with open("frames/snowflake_2300_solid", "rb") as file_stream:
    data2 = numpy.fromfile(file_stream, dtype=numpy.double).reshape(500, 500)
with open("frames/snowflake_2300_liquid", "rb") as file_stream:
    data3 = numpy.fromfile(file_stream, dtype=numpy.double).reshape(500, 500)

hex_grid(data1+data2+data3, cmap="Blues")
#pyplot.imshow(data, cmap="Blues")
#pyplot.colorbar()
#pyplot.show()

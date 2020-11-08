import numpy
from matplotlib import pyplot
from hex_grid import hex_grid


with open("snowflake_5000_vapor", "rb") as file_stream:
    data1 = numpy.fromfile(file_stream, dtype=numpy.double).reshape(600, 600)
with open("snowflake_5000_solid", "rb") as file_stream:
    data2 = numpy.fromfile(file_stream, dtype=numpy.double).reshape(600, 600)
with open("snowflake_5000_liquid", "rb") as file_stream:
    data3 = numpy.fromfile(file_stream, dtype=numpy.double).reshape(500, 500)

hex_grid(data3, cmap="Blues")


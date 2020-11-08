import numpy
import matplotlib.pyplot as plt
from hex_grid import hex_grid
import PIL.Image
import os


#with open("frames/snowflake_49_solid", "rb") as file_stream:
#    data = numpy.fromfile(file_stream, dtype=numpy.double).reshape(100, 100)

# hex_grid(data.T)
# pyplot.imshow(data)
# pyplot.colorbar()
# pyplot.show()


def view_snoflak_gif(number_iter):
    frame = []
    for i in range(0, number_iter) :
        with open("frames/snowflake_" + str(i) + "_solid", "rb") as file_stream:
            data = numpy.fromfile(file_stream, dtype=numpy.double).reshape(50, 50)
        plt.imshow(data.T)
        plt.colorbar()
        plt.savefig(str(i+1))
        plt.clf()

        frame.append(PIL.Image.open(str(i+1) + ".png"))
        os.remove(str(i+1) + ".png")

    frame[0].save("gifs/snoflak.gif", save_all=True, append_images=frame[1:], optimize=False, duration=150, loop=0)


view_snoflak_gif(99)
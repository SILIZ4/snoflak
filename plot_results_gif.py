import numpy as np
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
    dataframes = []
    frame = []
    max_val = -float("inf")
    for i in range(0, number_iter-1) :
        with open("frames/snowflake_" + str(i) + "_solid", "rb") as file_stream:
            data = np.fromfile(file_stream, dtype=np.double).reshape(100, 100)
            dataframes.append(data)
            tmp_max = np.max(data)
            if(tmp_max > max_val):
                max_val = tmp_max


    for i in range(0, number_iter-1) :
        #with open("frames/snowflake_" + str(i) + "_solid", "rb") as file_stream:
        #   data = numpy.fromfile(file_stream, dtype=numpy.double).reshape(100, 100)
        plt.imshow(dataframes[i].T, cmap="Blues", vmin=0, vmax=max_val)
        plt.colorbar()
        plt.savefig(str(i+1))
        plt.clf()

        frame.append(PIL.Image.open(str(i+1) + ".png"))
        os.remove(str(i+1) + ".png")

    frame[0].save("gifs/snoflak_theta_alpha.gif", save_all=True, append_images=frame[1:], optimize=False, duration=100, loop=0)


view_snoflak_gif(99)
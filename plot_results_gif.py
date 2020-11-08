import numpy as np
import matplotlib.pyplot as plt
from hex_grid import hex_grid
import PIL.Image
import os


def view_snoflak_gif(frames_number, dataprefix, output_name):
    dataframes = []
    frame = []
    max_val = -float("inf")
    for i in range(0, frames_number) :
        with open(dataprefix + str(i) + "_solid", "rb") as file_stream:
            data = np.fromfile(file_stream, dtype=np.double)
            data = data.reshape(np.sqrt(len(data)), -1)
            dataframes.append(data)

            tmp_max = np.max(data)
            if(tmp_max > max_val):
                max_val = tmp_max


    for i in range(0, frames_number) :
        plt.imshow(dataframes[i].T, cmap="Blues", vmin=0, vmax=max_val)
        plt.colorbar()
        plt.savefig(str(i+1))

        plt.clf()

        frame.append(PIL.Image.open(str(i+1) + ".png"))
        os.remove(str(i+1) + ".png")

    frame[0].save(output_name, save_all=True, append_images=frame[1:], optimize=False, duration=100, loop=0)


view_snoflak_gif(99, "frames/snowflake_", output_name="gifs/snoflak_theta_alpha.gif")
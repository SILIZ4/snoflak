import numpy as np
import matplotlib.pyplot as plt
from matplotlib.collections import PolyCollection
from matplotlib.patches import RegularPolygon


def hex_grid(mat, cmap=None, file_name=None):
    shape = mat.shape
    i, j = np.meshgrid(range(shape[0]), range(shape[1]))
    i, j = i.flatten(), j.flatten()
    x, y = i + (j+1) % 2 / 2, j * np.sqrt(3) / 2
    centers = np.array([x, y]).T
    offsets = np.zeros((6, shape[0] * shape[1], 2))

    for i in range(6):
        offsets[i, :, 0] = np.sin(2 * np.pi * i / 6) / np.sqrt(3) * 1.01
        offsets[i, :, 1] = np.cos(2 * np.pi * i / 6) / np.sqrt(3) * 1.01
    verts = centers + offsets
    verts = np.swapaxes(verts, 0, 1)

    z = mat.flatten()

    fig, ax = plt.subplots()

    coll = PolyCollection(verts, array=z, cmap=cmap)
    ax.add_collection(coll)

    plt.axis('off')
    plt.autoscale(enable = True)
    fig.subplots_adjust(bottom=-0.06, top=1.06, left=-0.06, right=1.06)

    if file_name:
        plt.savefig(file_name)
    plt.show()


if __name__ == "__main__":
    folders = ["figure11a/", "figure11b/", "figure11c/", "figure11d/", "figure11e/"]
    frame_number = 4000

    for folder in folders:
        with open(folder+"snowflake_{}_vapor".format(frame_number), "rb") as file_stream:
            data1 = np.fromfile(file_stream, dtype=np.double).reshape(600, 600)
        with open(folder+"snowflake_{}_solid".format(frame_number), "rb") as file_stream:
            data2 = np.fromfile(file_stream, dtype=np.double).reshape(600, 600)
        with open(folder+"snowflake_{}_liquid".format(frame_number), "rb") as file_stream:
            data3 = np.fromfile(file_stream, dtype=np.double).reshape(600, 600)

        hex_grid(data1+data2+data3, cmap="Blues", file_name="figures/"+folder[:-1]+".png")

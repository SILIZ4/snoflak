import numpy as np
import matplotlib.pyplot as plt
from matplotlib.collections import PolyCollection


def hex_grid(mat, cmap=None, vmin=0, vmax=1):
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
    ax.autoscale_view()

    fig.colorbar(coll, ax=ax)

    plt.show()
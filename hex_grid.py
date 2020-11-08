import numpy as np
import matplotlib.pyplot as plt
from matplotlib.patches import RegularPolygon


def hex_grid(mat):
    _, ax = plt.subplots(1)
    ax.set_aspect('equal')

    for i in range(mat.shape[0]):
        for j in range(mat.shape[1]):
            plot_hex(ax, i, j, mat[i, j])

    plt.axis('off')
    plt.autoscale(enable = True)
    plt.show()


def plot_hex(ax, i, j, value):
    x, y = i + (j+1) % 2 / 2, j * np.sqrt(3) / 2
    hex = RegularPolygon((x, y), numVertices=6, radius=1/np.sqrt(3), color=(value, value, value))
    ax.add_patch(hex)


if __name__ == "__main__":
    x = np.arange(0, 10)
    X, Y = np.meshgrid(x, x)
    mat = (Y + X % 2) / 3 % 1

    hex_grid(mat)

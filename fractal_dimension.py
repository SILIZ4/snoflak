import numpy as np
import math as mt
from matplotlib import pyplot
from hex_grid import hex_grid


with open("test_fractal/snowflake_5000_liquid", "rb") as file_stream:
    data3 = np.fromfile(file_stream, dtype=np.double).reshape(500, 500)
hex_grid(data3, cmap="Greys")
# Box-counting dimension: lim eps->0 [log N(eps) / log(1/eps)]

# dividers of 500
divisions = [5,10,20,25,50,100,250,500]
EPS = np.zeros((len(divisions),1))
NEPS = np.zeros((len(divisions),1))


for k in range(0,len(divisions)):
    i = divisions[k]
    dx = mt.floor(500/i)
    doesCover = np.zeros((i*i,1))
    for j in range(0,i*i):
        xi_1 = (dx*j)%500
        xi_2 = (dx*j)%500 + dx
        yi_1 = dx*mt.floor(float(j)/float(i))
        yi_2 = dx*mt.floor(float(j)/float(i)) + dx
        for a in range(xi_1,xi_2):
            for b in range(yi_1,yi_2):
                if(data3[a,b]>0):
                    doesCover[j] = 1
    NEPS[k] =  np.sum(doesCover)
    EPS[k] = dx

dim, _ = np.polyfit(np.log(np.reciprocal(EPS)).flatten(),np.log(NEPS).flatten(),1)

print(dim)
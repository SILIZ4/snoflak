import numpy as np
import math as mt
from matplotlib import pyplot
from hex_grid import hex_grid


snowflake_file = "test_fractal/snowflake_5000_liquid"

# Since liquid mass is present almost everywhere along the boundary,
# it's a good approximation of it, so we can use the liquid mass map
# to compute fractal dimension of the snowflake's boundary
with open(snowflake_file, "rb") as file_stream:
    data = np.fromfile(file_stream, dtype=np.double).reshape(500, 500)
data[data>0]=1


# dividers of 500 (if the frame is n x n, choose dividers of n)
divisions = [5,10,20,25,50,100,250,500]
EPS = np.zeros((len(divisions),1))
NEPS = np.zeros((len(divisions),1))


# covering of the boundary with div x div boxes
for k in range(0,len(divisions)):
    i = divisions[k]
    eps = mt.floor(500 / i)
    isCovering = np.zeros((i * i, 1))
    for j in range(0,i*i):
        x_1 = (eps * j) % 500
        x_2 = (eps * j) % 500 + eps
        y_1 = eps * mt.floor(float(j) / float(i))
        y_2 = eps * mt.floor(float(j) / float(i)) + eps
        for a in range(x_1,x_2):
            for b in range(y_1,y_2):
                if(data[a,b] == 1):
                    isCovering[j] = 1
    NEPS[k] = np.sum(isCovering)
    EPS[k] = eps

# Box-counting dimension: lim eps->0 [log N(eps) / log(1/eps)]
dim, _ = np.polyfit(np.log(np.reciprocal(EPS)).flatten(),np.log(NEPS).flatten(),1)

print("Fractal dimension: ", dim)
hex_grid(data, cmap="binary")

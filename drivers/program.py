import numpy as np
import method
from strlearn import streams
from sklearn.decomposition import PCA
import sys

# Configure your program
n = 100000
reg_width = int(sys.argv[1])
inertion_level = 100
buffer_length = 100

# Initialize controller and barf the configuration
archer = method.Archer(
    frameskip=reg_width-1,
    E=1,
    M=3,
    W=256,
    H=256,
    U=31,
    R=3.14,
    G=3.18,
    B=3.22
    )
archer.barf()
archer.white(10000)

# Calculate the signal parameters
n_components = 4
n_features = 16

stream = streams.StreamGenerator(
    n_chunks=200, chunk_size=200,
    n_drifts=3,
    n_features=n_features, n_informative=4, n_redundant=0, n_repeated=0,
    n_classes=5,
)
buffer = np.zeros((buffer_length, n_features))

# Prepare inertion array
nara = np.zeros((reg_width, inertion_level))
i, j = 0, 0
while chunk := stream.get_chunk():
    X, y = chunk
    for x in X:
        j += 1
        buffer[j%buffer_length] = x

        if j%4 == 0:
            pca = PCA(n_components=n_components)
            pca.fit(buffer)

            a = pca.components_.T.ravel()

            for v in a:
                i += 1
                nara[i%reg_width, (i//reg_width)%inertion_level] = v
                val = np.mean(nara[i%reg_width,:])
                print('V', np.power(val,2))

# End the flight
archer.white(10000)
archer.escape()

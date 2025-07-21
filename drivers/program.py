import numpy as np
import method
from strlearn import streams

# Configure your program
n = 100000
periods = 2

# Initialize controller and barf the configuration
archer = method.Archer(frameskip=128)
archer.barf()

# Calculate the signal parameters
stream = streams.StreamGenerator(
    n_chunks=1000, chunk_size=100, 
    n_drifts=1, 
    n_features=3, n_informative=3, n_redundant=0, n_repeated=0,
    class_sep = 32)

while chunk := stream.get_chunk():
    X, y = chunk

    for x in X:
        for v in x:
            print('V', v)

# signal += np.random.normal(0,.0001,size=signal.shape)
# signal = signal*0

# Scream the values
# for i, v in enumerate(signal):
#     print('V', v)

# End the flight
archer.escape()
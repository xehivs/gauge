"""
Exemplary python driver for arche.

Windmill infered on principal components of buffered synthetic strlearn data stream.
"""
import method
import sys
import numpy as np
from sklearn.decomposition import PCA
from strlearn import streams

# Configure your program
inertion_level = 100
buffer_length = 100
interval = 4

# Initialize controller and barf the configuration
reg_width = int(sys.argv[1])
archer = method.Archer(
    frameskip=reg_width-1,
    E=.5,
    M=2,
    W=256,
    H=256,
    U=254,
    R=3.14,
    G=3.18,
    B=3.22
    )
archer.barf()

# Sanitize with white noise
archer.white(20000)

"""
Do the processing
"""
# Calculate the signal parameters
n_components = 4
n_features = 16
stream = streams.StreamGenerator(
    n_chunks=200, chunk_size=200,
    n_drifts=3,
    n_features=n_features, n_informative=8, n_redundant=0, n_repeated=0,
    n_classes=5,
)

# Prepare buffers
b_buffer = np.zeros((buffer_length, n_features))
i_buffer = np.zeros((reg_width, inertion_level))

# Iterate chunks of a stream
i_head, b_head = 0, 0
while chunk := stream.get_chunk():
    X, y = chunk
    
    # For every object
    for x in X:
        
        # Update the buffer
        b_head += 1
        b_buffer[b_head % buffer_length] = x

        # At every n-th [interval] state of the buffer
        if b_head % interval == 0:
            
            # Calculate principal components of a buffer
            pca = PCA(n_components=n_components)
            pca.fit(b_buffer)

            # Unravel the components into signal (n_features * n_components)
            components = pca.components_.T.ravel()

            # For every value in components signal
            for v in components:
                
                # Update inertion buffer
                i_head += 1
                i_buffer[i_head % reg_width, (i_head // reg_width) % inertion_level] = v
                
                # Calculate and tell the value
                val = np.mean(i_buffer[i_head % reg_width, :])
                print('V', np.power(val,2))

# Sanitize the end and end the flight
archer.white(20000)
archer.escape()

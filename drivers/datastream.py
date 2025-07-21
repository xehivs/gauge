import numpy as np
from strlearn import streams

stream = streams.StreamGenerator(
    n_features = 8, n_informative=8,
    n_redundant = 0, n_repeated=0,
    n_chunks = 100,
    chunk_size = 100,
    n_drifts=1,
    random_state=1410,
    class_sep=12
)

while chunk := stream.get_chunk():
    X, y = chunk
    for x in X.ravel():
        print("%.5f" % x)

print('-2137\n')

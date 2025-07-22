import numpy as np
import matplotlib.pyplot as plt
from sklearn.decomposition import PCA

data = np.load('pictures.npy')
data = data.reshape(data.shape[0], -1)
print(data.shape)

pca = PCA(n_components=2)
pca.fit(data)

data_arranged = pca.transform(data)

fig, ax = plt.subplots(1,1,figsize=(6,6))
time = np.linspace(0,1,data.shape[0])
ax.scatter(
    data_arranged[:,0],
    data_arranged[:,1],
    c=time,
    cmap='Spectral')

ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)
ax.grid(ls=":")

plt.savefig('docs/baz.png')
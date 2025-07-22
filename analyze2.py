import numpy as np
import matplotlib.pyplot as plt
from sklearn.decomposition import PCA
from scipy.signal import medfilt

data = np.load('pictures.npy')
data = data.reshape(data.shape[0], -1)
print(data.shape)

pca = PCA(n_components=3)
pca.fit(data)

data_arranged = pca.transform(data)
data_arranged = data_arranged/np.max(np.abs(data_arranged))

fig, ax = plt.subplots(2,2,figsize=(6,6))
time = np.linspace(0,1,data.shape[0])

ax[0,0].scatter(
    data_arranged[:,0],
    data_arranged[:,1],
    c=time,
    cmap='Spectral')

ax[0,1].scatter(
    data_arranged[:,0],
    data_arranged[:,2],
    c=time,
    cmap='Spectral')

ax[1,0].scatter(
    data_arranged[:,1],
    data_arranged[:,2],
    c=time,
    cmap='Spectral')

rgb = ((data_arranged+1)/2)[:, None]

ax[1,1].imshow(rgb.swapaxes(0,1), aspect=rgb.shape[0])

for aa in ax.ravel()[:3]:
    aa.spines['top'].set_visible(False)
    aa.spines['right'].set_visible(False)
    aa.grid(ls=":")

    aa.set_xlim(-1,1)
    aa.set_ylim(-1,1)

    aa.set_xticks(np.linspace(-1,1,5))
    aa.set_yticks(np.linspace(-1,1,5))

plt.tight_layout()
plt.savefig('docs/baz.png')
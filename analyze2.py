import numpy as np
import matplotlib.pyplot as plt
from sklearn.decomposition import PCA
from scipy.signal import medfilt

data = np.load('pictures.npy')
data = data.reshape(data.shape[0], -1)
print(data.shape)

data = data[24:]

pca = PCA(n_components=3)
pca.fit(data)


data_arranged = pca.transform(data)
data_arranged = data_arranged/np.max(np.abs(data_arranged))


bw = 8

fig, ax = plt.subplots(2,4,figsize=(bw,bw/1.618))


rgb = ((data_arranged+1)/2)[:, None]

time = np.linspace(0,1,rgb.shape[0])

pairs = [
    [0,1],
    [1,0],
    [0,2],
    [1,2]
]

for i, pair in enumerate(pairs):
    a, b = pair
    ax.ravel()[i].scatter(
        data_arranged[:,a],
        data_arranged[:,b],
        s=500,
        alpha=.1,
        c=rgb)

    ax.ravel()[i].plot(
        data_arranged[:,a], data_arranged[:,b],
        lw=1,
        c='white',
        alpha=.5
    )

    ax.ravel()[i].scatter(
        [data_arranged[0,a]], [data_arranged[0,b]],
        marker='o',
        c='white',
        s=50
    )

    ax.ravel()[i].scatter(
        [data_arranged[-1,a]], [data_arranged[-1,b]],
        marker='o',
        c='white',
        s=400
    )

    ax.ravel()[i].scatter(
        [data_arranged[-1,a]], [data_arranged[-1,b]],
        marker='o',
        c='black',
        s=50,
        zorder=1000
    )

for aa in ax.ravel():
    aa.spines['top'].set_visible(False)
    aa.spines['right'].set_visible(False)
    aa.spines['left'].set_visible(False)
    aa.spines['bottom'].set_visible(False)
    aa.grid(ls=":")

    m = 1.5

    aa.set_xlim(-m,m)
    aa.set_ylim(-m,m)

    aa.set_xticks([])
    aa.set_yticks([])

pax = plt.subplot(212)
pax.imshow(rgb.swapaxes(0,1), aspect=rgb.shape[0]/4)
pax.set_xticks([])
pax.set_yticks([])
pax.spines['top'].set_visible(False)
pax.spines['right'].set_visible(False)
pax.spines['left'].set_visible(False)
pax.spines['bottom'].set_visible(False)

plt.tight_layout()
plt.savefig('docs/baz.png')
import numpy as np
import matplotlib.pyplot as plt
from tqdm import tqdm

zzz = np.load('concept-track.npz')

data_arranged = zzz['arr_0']
rgb = zzz['arr_1']

bw = 8


time = np.linspace(0,1,rgb.shape[0])

pairs = [
    [0,1],
    [1,0],
    [0,2],
    [1,2]
]

fig, ax = plt.subplots(2,4,figsize=(bw,bw/1.618))
for i, pair in enumerate(pairs):
    a, b = pair
    ax.ravel()[i].scatter(
        data_arranged[:,a],
        data_arranged[:,b],
        s=500,
        alpha=.01,
        c='black')


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

j = 0
head, tail = 0, 0
l = 50
tail += l
for k in tqdm(range(data_arranged.shape[0])):
        # ax.ravel()[i].plot(
        #     data_arranged[:,a], data_arranged[:,b],
        #     lw=1,
        #     c='white',
        #     alpha=.5
        # )

        # ax.ravel()[i].scatter(
        #     [data_arranged[0,a]], [data_arranged[0,b]],
        #     marker='o',
        #     c='white',
        #     s=50
        # )

        # ax.ravel()[i].scatter(
        #     [data_arranged[-1,a]], [data_arranged[-1,b]],
        #     marker='o',
        #     c='white',
        #     s=400
        # )

        # ax.ravel()[i].scatter(
        #     [data_arranged[-1,a]], [data_arranged[-1,b]],
        #     marker='o',
        #     c='black',
        #     s=50,
        #     zorder=1000
        # )


    if k % l == 0:
        plt.savefig('gear/%05i.png' % j)
        # plt.savefig('docs/baz.png')

        for i, pair in enumerate(pairs):
            a, b = pair
            ax.ravel()[i].plot(
                [data_arranged[head:tail,a]],
                [data_arranged[head:tail,b]],
                lw=1,
                c='black')
            ax.ravel()[i].scatter(
                [data_arranged[head:tail,a]],
                [data_arranged[head:tail,b]],
                s=400,
                alpha=1,
                c=rgb[head:tail])

            ax.ravel()[i].scatter(
                [data_arranged[tail-1,a]], [data_arranged[tail-1,b]],
                marker='o',
                c='white',
                s=200
            )

            ax.ravel()[i].scatter(
                [data_arranged[tail-1,a]], [data_arranged[tail-1,b]],
                marker='o',
                c='black',
                s=50
            )

        head += l
        tail += l
        j += 1
    # plt.close()

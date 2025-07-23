from PIL import Image
import numpy as np
import matplotlib.pyplot as plt
import glob
from tqdm import tqdm
from sklearn.decomposition import PCA

# Count bitmaps
count = len(glob.glob('cache/*.bmp'))
print(count, 'bitmaps acquired')

# Prepare figure
res = (256, 256, 3)

# Prepare buffer
b_length = 24
buffer = np.zeros((b_length, *res))
stack = []

i = 0
for j in tqdm(range(count)):
    image = Image.open('cache/%06i.bmp' % j)
    image_array = np.array(image)

    buffer[j%b_length] = image_array
    picture = np.mean(buffer, axis=0)

    stack.append(np.copy(picture).astype(np.uint8))

    # plt.imsave(
    #     'smooth/%06i.png' % j, 
    #     picture.astype(np.uint8))

    # if j in idxs:
    #     ax[i].imshow(picture.astype(np.uint8))

    #     i += 1
    #     print(i, j)

    # last_picture = picture

print("Establishing stack")
stack = np.array(stack)

print("Flattening stack to data")
data = stack.reshape(stack.shape[0], -1)
# data = data[b_length:]

print("Decomposing to three primary components")
pca = PCA(n_components=3)
pca.fit(data[b_length:])

print("Retransforming color")
data_arranged = pca.transform(data)
data_arranged = data_arranged/np.max(np.abs(data_arranged[b_length:]))
rgb = ((data_arranged+1)/2)[:, None]
rgb = np.clip(rgb, 0, 1)

print("Colouring image")
for idx, _ in tqdm(enumerate(stack)):
    image = stack[idx]
    # print(idx, np.mean(image))
    signature = rgb[idx][0]
    image = image * signature[None,None,:]
    image = image.astype(np.uint8)

    plt.imsave(
        'smooth/%06i.png' % idx, 
        image.astype(np.uint8))

print("Presenting baz")
np.savez('concept-track.npz',
    data_arranged, rgb)
bw = 8

fig, ax = plt.subplots(2,4,figsize=(bw,bw/1.618))

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


# for aa in ax:
#     aa.set_xticks([])
#     aa.set_yticks([])

# plt.tight_layout()
# plt.savefig('docs/foo.png')

# fig, ax = plt.subplots(1,1,figsize=(6,6/1.618))

# print(vs.shape)

# ax.plot(vs[b_length:,0], c='r')
# ax.plot(vs[b_length:,1], c='g')
# ax.plot(vs[b_length:,2], c='b')

# ax.spines['top'].set_visible(False)
# ax.spines['right'].set_visible(False)
# ax.grid(ls=":")

# ax.set_xlabel('time')
# ax.set_ylabel('mean channel value')

# plt.savefig('docs/bar.png')
# plt.tight_layout()

# np.save('pictures.npy', np.array(stack))
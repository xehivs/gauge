from PIL import Image
import numpy as np
import matplotlib.pyplot as plt
import glob

# Count bitmaps
count = len(glob.glob('cache/*.bmp'))
print(count, 'bitmaps')

# Prepare figure
bw = 16
rows = 12
cols = 7
res = (256, 256, 3)
fig, ax = plt.subplots(rows,cols,figsize=(bw, bw*1.618))
ax = ax.ravel()
fig.patch.set_facecolor('black')

# Select bitmaps
idxs = np.linspace(0,count-1,rows*cols).astype(np.int32)

# Prepare buffer
b_length = 12
buffer = np.zeros((b_length, *res))
last_picture = np.zeros(res)
vs = []
stack = []

i = 0
for j in range(count):
    image = Image.open('cache/%06i.bmp' % j)
    image_array = np.array(image)

    buffer[j%b_length] = image_array
    picture = np.mean(buffer, axis=0)

    v = [
        np.mean(picture[:,:,0]),
        np.mean(picture[:,:,1]),
        np.mean(picture[:,:,2]),
    ]
    vs.append(v)
    stack.append(np.copy(picture))

    plt.imsave(
        'smooth/%06i.png' % j, 
        picture.astype(np.uint8))

    if j in idxs:
        ax[i].imshow(picture.astype(np.uint8))

        i += 1
        print(i, j)

    last_picture = picture

vs = np.array(vs)

for aa in ax:
    aa.set_xticks([])
    aa.set_yticks([])

plt.tight_layout()
plt.savefig('docs/foo.png')

fig, ax = plt.subplots(1,1,figsize=(6,6/1.618))

print(vs.shape)

ax.plot(vs[b_length:,0], c='r')
ax.plot(vs[b_length:,1], c='g')
ax.plot(vs[b_length:,2], c='b')

ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)
ax.grid(ls=":")

ax.set_xlabel('time')
ax.set_ylabel('mean channel value')

plt.savefig('docs/bar.png')
plt.tight_layout()

np.save('pictures.npy', np.array(stack))
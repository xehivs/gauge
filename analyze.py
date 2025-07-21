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
b_length = 32
buffer = np.zeros((b_length, *res))

i = 0
for j in range(count):
    image = Image.open('cache/%06i.bmp' % j)
    image_array = np.array(image)

    buffer[j%b_length] = image_array

    if j in idxs:
        diagram = np.mean(buffer, axis=0).astype(np.uint8)
        ax[i].imshow(diagram)

        i += 1
        print(i, j)

for aa in ax:
    aa.set_xticks([])
    aa.set_yticks([])

plt.tight_layout()
plt.savefig('docs/foo.png')
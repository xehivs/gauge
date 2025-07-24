import numpy as np
import matplotlib.pyplot as plt
import glob
from PIL import Image

# Image parameters
n_cols, n_rows = (8, 8)
bw = 12

# Count bitmaps
count = len(glob.glob('smooth/*.png'))
print(count, 'images acquired')

# Establish indexes by quantized linear space
idx = np.linspace(1, count-1, n_cols*n_rows).astype(int)

print(idx)

# Prepare the canvas
fig, ax = plt.subplots(n_cols, n_rows, figsize=(bw,bw))
fig.patch.set_facecolor('black')

for i, (aa, _idx) in enumerate(zip(ax.ravel(), idx)):
    print(i, aa, _idx)

    # Open image
    image = Image.open('smooth/%06i.png' % _idx)
    image_array = np.array(image)
    
    # Print image
    aa.imshow(image_array)
    
    # Stylize frame
    aa.set_xticks([])
    aa.set_yticks([])
    aa.spines['top'].set_visible(False)
    aa.spines['left'].set_visible(False)
    aa.spines['right'].set_visible(False)
    aa.spines['bottom'].set_visible(False)

plt.tight_layout()
plt.savefig('docs/foo.png')
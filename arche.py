import numpy as np
import matplotlib.pyplot as plt
import matplotlib

def imply(x):
    return (x[:,None,:] * x[None,:,:]).reshape(-1,x.shape[1])

def expand(x):
    return (x[:,None,:] + x[None,:,:]).reshape(-1,x.shape[1])

q = 128

carrier = np.array([
    np.sin(np.linspace(-np.pi,np.pi,q+1)),
    np.cos(np.linspace(-np.pi,np.pi,q+1))
]).T

signal = carrier + 0

from scipy.signal import medfilt

#signal += np.random.normal(0,.1,size=carrier.shape)

#signal[:,0] = medfilt(signal[:,0], 5)
#signal[:,1] = medfilt(signal[:,1], 5)

l = 1

implication = imply(signal)
expansion = expand(signal)

canvas_shape = (6,6)
bg = 'black'

fig, ax = plt.subplots(figsize=canvas_shape)
fig.patch.set_facecolor(bg)
ax.set_facecolor(bg)

ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)
ax.spines['left'].set_visible(False)
ax.spines['bottom'].set_visible(False)

ax.set_xticks([])
ax.set_yticks([])

plt.subplots_adjust(left=0, right=1, top=1, bottom=0)

fg = 'xkcd:salmon'

#ax.scatter(*signal.T, c=fg, s=32)
#ax.scatter(*implication.T, c='white', s=1)
ax.plot(*implication.T, c=fg, lw=.125)
ax.plot(*expansion.T, c=fg, lw=.5)

ax.set_aspect('equal')

r = 3
ax.set_xlim(-r,r)
ax.set_ylim(-r,r)

plt.savefig('foo.png', dpi=500)
plt.savefig('foo.eps')
plt.savefig('foo.jpg')

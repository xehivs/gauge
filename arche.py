import numpy as np
import matplotlib.pyplot as plt
import matplotlib
def prod(x):
    return (x[:,None,:] * x[None,:,:]).reshape(-1,x.shape[1])

def sum(x):
    return (x[:,None,:] + x[None,:,:]).reshape(-1,x.shape[1])

seed_size = 32
seed = np.array([
    np.sin(np.linspace(0,np.pi*2,seed_size+1)),
    np.cos(np.linspace(0,np.pi*2,seed_size+1))
]).T

# seed += np.random.normal(0,.1,size=seed.shape)

l = 1

layers = [seed]
for i in range(l):
    layers.append(prod(layers[-1]))


depths = [seed]
for i in range(l):
    depths.append(sum(depths[-1]))

letter = (8.5, 11)

fig, ax = plt.subplots(figsize=letter)
fig.patch.set_facecolor('black')
ax.set_facecolor('black')

ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)
ax.spines['left'].set_visible(False)
ax.spines['bottom'].set_visible(False)

ax.set_xticks([])
ax.set_yticks([])

ax.text(-.05,2.5,'International\nStudents\nWorkshop', c='xkcd:salmon', ha='right', va='center', fontsize=32)

ax.text(.05,-2.5,"Kamienna Góra'25", c='xkcd:salmon', ha='left', va='center', fontsize=16)

#ax.text(0,-3.14,'ISBN 978-83-933924-2-1', c='xkcd:salmon', ha='center', va='center')

plt.subplots_adjust(left=0.05, right=0.95, top=1, bottom=0)


ax.plot(*seed.T, c='xkcd:salmon', lw=4)
ax.plot(*layers[1].T, c='xkcd:salmon', lw=.5)
ax.plot(*depths[1].T, c='xkcd:salmon', lw=.5)

# ax.scatter(*seed.T, s=50, c='black')
# ax.scatter(*layers[1].T, s=50, c='black')
# ax.scatter(*depths[1].T, c='black')

ax.set_aspect('equal')

# plt.suptitle('International\nStudents Workshop', fontsize=48)

# ax.set_xlim(-m*letter[0],m*letter[0])
# ax.set_ylim(-m*letter[1],m*letter[1])

plt.savefig('foo.png', dpi=500)
plt.savefig('foo.eps')
plt.savefig('foo.jpg')

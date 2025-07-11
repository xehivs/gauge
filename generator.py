import numpy as np
np.set_printoptions(suppress=True, precision=True)

q = 10000;
l = 32;
ls = np.linspace(-np.pi*l,l*np.pi,q)
A = np.sin(ls)

# A = np.random.uniform(size=q)

for a in A:
    print('%.8f' % a)

print('-2137\n')
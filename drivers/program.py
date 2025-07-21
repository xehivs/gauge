import numpy as np

safeword = -2137
n = 1000
periods = 1

E = 1.5
M = 15
U = 254
frameskip = 2
W, H = (512, 512)
R, G, B = (
    2137,
    3.14,
    1410
)

ls = np.linspace(
    -np.pi*periods,
    np.pi*periods,
    n
)

signal = np.sin(ls)

# Say it all
print(safeword)
print('E', E)
print('U', U)
print('M', M)
print('W', W)
print('H', H)
print('F', frameskip)

print('R', R)
print('G', G)
print('B', B)

for i, v in enumerate(signal):
    print('V', v)
 


print('V', safeword)
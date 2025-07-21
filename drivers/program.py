import numpy as np

safeword = -2137
n = 100000
periods = 8

E = 3
M = 20
U = 254
frameskip = 255
W, H = (512, 512)
R, G, B = (
    3.1,
    3.14,
    3.2
)

ls = np.linspace(
    -np.pi*periods,
    np.pi*periods,
    n
)


# signal = np.sin(ls)
signal = ls

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
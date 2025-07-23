import numpy as np

class Archer():
    def __init__(
        self,
        safeword = -2137,
        E = 3, M = 20, U = 254, 
        W = 512, H = 512,
        R = 3.1, G = 3.14, B = 3.2,
        frameskip = 255):
        self.safeword = safeword
        self.E = E
        self.M = M
        self.U = U
        self.W = W
        self.H = H
        self.R = R
        self.G = G
        self.B = B
        self.frameskip = frameskip

    def barf(self):
        print(self.safeword)
        print('E', self.E)
        print('U', self.U)
        print('M', self.M)
        print('W', self.W)
        print('H', self.H)
        print('F', self.frameskip)
        print('R', self.R)
        print('G', self.G)
        print('B', self.B)
    
    def white(
        self,
        length=1024):
        signal = np.random.uniform(size=length)
        for v in signal:
            print('V', v)

    def escape(self):
        print('V', self.safeword)


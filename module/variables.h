//
// Steering variables
//

// Framing and exposition control
int _U = 31;                    // image increment
int _W = 512, _H = 512;         // resolution
int _frameskip = 4;             // frameskip

double _M = 3;                  // image margin
float _E = .1;                  // elasticity
float _signature[] = {          // spectral signature
    2137,
    3.14,
    1410
};

// Interface switches
int _n_points = 0;  // vaporized [lines are tough]


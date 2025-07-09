#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "const.h"
#include "dimage.h"
#include "ksienie.h"
#include "dandelion.h"

int main(void){
    // Variables
    int q = 32;     // number of quants (angles)
    
    // Reserve memory for image
    unsigned char *img = dimage(W,H);
    
    // Reserve memory for point location
    int n = q * q;  // number of derivatives
    double *seed = array(2, q);
    double *expansion = array(2,n);
    double *reduction = array(2,n);

    /* Seed loop [circular] */
    for (int i = 0 ; i < q ; i++){
        double val = i * (2*PI)/q;

        double vs = sin(val);
        double vc = cos(val);

        seed[i] = vs;
        seed[i+q] = vc;
    }

    /* Expansion loop */
    for (int i = 0 ; i < q ; i++){
        for (int j = 0 ; j < q ; j++){
            double ax = seed[i];
            double ay = seed[i+q];

            double bx = seed[j];
            double by = seed[j+q];

            double x = 0.;
            double y = 0.;
            
            expansion[i+j*q] = ax + bx;
            expansion[i+j*q+n] = ay + by;
            
            reduction[i+j*q] = ax * bx;
            reduction[i+j*q+n] = ay * by;
        }
    }
    
    /* plotting */
    // Example line
    int *_line = line(0, 0, 3, 1);
    for (int i = 1 ; i < _line[0] + 1 ; i++){
        img[ravel(_line[i], _line[i+_line[0]], 2)] = 255;
    }
    
    // Plot [seed]
    // Iterate points
    for (int i = 0 ; i < q ; i++) {
        double vs = seed[i];
        double vc = seed[i+q];

        int px = dx(vs);
        int py = dy(vc);

        img[ravel(px,py,0)] = 255;
        img[ravel(px,py,1)] = 255;
        img[ravel(px,py,2)] = 255;
    }

    for (int i = 0 ; i < n ; i++) {
        double vs = 0;
        double vc = 0;
        int px = 0;
        int py = 0;

        vs = expansion[i];
        vc = expansion[i+n];

        px = dx(vs);
        py = dy(vc);

        img[ravel(px,py,0)] = 255;
        img[ravel(px,py,1)] = 255;
        // img[ravel(px,py,2)] = 255;

        vs = reduction[i];
        vc = reduction[i+n];

        px = dx(vs);
        py = dy(vc);

        img[ravel(px,py,0)] = 255;
        // img[ravel(px,py,1)] = 255;
        img[ravel(px,py,2)] = 255;
    }

    bmp(img, W, H, "foo.bmp");

    return 0;
}

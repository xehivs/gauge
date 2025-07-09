#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "const.h"
#include "image.h"
#include "model.h"
#include "dandelion.h"

int main(void){
    // Variables
    int q = 128;     // number of quants (angles)
    
    // Reserve memory for image
    unsigned char *image = dimage(W,H);
    
    // Calculate
    double *seed = circle(q);
    double *expansion = expand(seed, q);
    double *reduction = reduce(seed, q);
    
    // Plot
    scatter(image, seed, q);
    plot(image, expansion, q*q);
    plot(image, reduction, q*q);

    // Store
    bmp(image, W, H, "foo.bmp");

    return 0;
}

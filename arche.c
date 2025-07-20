#include "const.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model.h"
#include "image.h"
#include "dandelion.h"

int main(int argc, char **argv){
    // Restrict parameter
    if (argc != 2) {
        printf("Please specify q-value (integer) as program argument.\n");
        return 1;
    }

    // Read register size from command line argument
    int q = atoi(argv[1]);                      // number of quants (angles)
    double *reg = malloc(sizeof(double) * q);   // Initialize register and head
    
    // Prepare storage for input
    float val = 0.0;
    int idx = 0, head = 0, subidx = 0;
    
    // Begin the operation loop
    do {
        // Wait for the standard input to present you with a float
        scanf("%f", &val);
        reg[head++] = val;
        head = head % q;
        subidx++;

        if (subidx == frameskip){
            subidx = 0;

            // Normalize register
            double *nreg = norm(reg, q);

            // Reserve memory for image
            unsigned char *image = dimage(W,H);
            for (int d = 0 ; d < 3 ; d++) {
                // Get theta
                float theta = signature[d];

                // Calculate
                double *seed = circle(q, nreg, theta);     
                double *expansion = expand(seed, q);
                double *reduction = reduce(seed, q);
                
                // Plot
                scatter(image, seed, q, d);
                scatter(image, expansion, q*q, d);
                scatter(image, reduction, q*q, d);

                free(seed);
                free(expansion);
                free(reduction);
            }            

            // Store
            char filename[16];
            sprintf(filename, "cache/%06i.bmp", idx);

            printf("%s\n", filename);
            bmp(image, W, H, filename);

            // Clean up before next iteration
            idx++;

            free(nreg);
        }

    } while (val != -2137);

    return 0;
}

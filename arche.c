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
    float val;
    int idx, head, subidx = 0;
    
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
            
            // Calculate
            double *seed = circle(q, nreg);     
            double *expansion = expand(seed, q);
            double *reduction = reduce(seed, q);
            
            // Plot
            scatter(image, seed, q);
            plot(image, expansion, q*q);
            plot(image, reduction, q*q);

            // Store
            char filename[16];
            sprintf(filename, "cache/%04i.bmp", idx % BUFFER_SIZE);

            printf("%s\n", filename);
            bmp(image, W, H, filename);

            // Clean up before next iteration
            idx++;

            free(seed);
            free(expansion);
            free(reduction);
            free(nreg);
        }

    } while (val != -2137);

    return 0;
}

//
// Arche -- windmill
//

#include "module/variables.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "module/model.h"
#include "module/image.h"
#include "module/dandelion.h"

int main(int argc, char **argv){
    // Restrict parameter
    if (argc != 2) {
        printf("Please specify q-value (integer) as program argument.\n");
        return 1;
    }

    // Read register size from command line argument and allocate it
    int q = atoi(argv[1]);
    double *reg = malloc(sizeof(double) * q);
    
    // Prepare variables for handling input
    float val = 0.0;
    int idx = 0, head = 0, subidx = 0;
    char sign;

    // Gather safeword from the first line of a stream
    float safeword = 0.0;
    scanf("%f", &safeword);
    flush();

    // Begin the operation loop
    do {
        // Wait for a char followed by float
        sign = getchar();        
        scanf("%f", &val);
        flush();

        // Operate on it
        if (operate(val, sign))
        {
            // If sign==V update the register and counters
            reg[head++] = val;
            head = head % q;
            subidx++;

            // At every given frameskip
            if (subidx == _frameskip){
                // Clean the counter
                subidx = 0;
    
                // Normalize register
                double *nreg = norm(reg, q);
    
                // Reserve memory for image
                unsigned char *image = dimage(_W,_H);
                
                // Expose image
                for (int d = 0 ; d < 3 ; d++) {
                    // Get spectral band angle theta
                    float theta = _signature[d];
    
                    // Calculate sample positions
                    double *seed = circle(q, nreg, theta);     
                    double *expansion = expand(seed, q);
                    double *reduction = reduce(seed, q);
                    
                    // Scatter samples around pixels
                    scatter(image, seed, q, d);
                    scatter(image, expansion, q*q, d);
                    scatter(image, reduction, q*q, d);
    
                    // Free memory
                    free(seed);
                    free(expansion);
                    free(reduction);
                }            
    
                // Do the posterior process [vaporized]
                // negate(image, _W, _H);
                // mono(image, _W, _H);
    
                // Save image on drive
                char filename[16];
                sprintf(filename, "cache/%06i.bmp", idx);
                printf("%s\n", filename);
                bmp(image, _W, _H, filename);
    
                // Update frame counter and free memory
                idx++;
                free(nreg);
            }
        }
    } while (val != safeword);  // Until the safeword occur

    return 0;
}

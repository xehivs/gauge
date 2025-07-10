#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "const.h"
#include "model.h"
#include "image.h"
#include "dandelion.h"

void print_reg(double *reg, int n){
    for (int i = 0 ; i < n ; i++){
        printf("[%.3f] ", reg[i]);
    }
    printf("\n\n");
}

int main(int argc, char **argv){
    if (argc != 2) {
        printf("Please specify q-value (integer) as program argument.\n");
        return 1;
    }

    // Read register size from command line argument
    int q = atoi(argv[1]);                      // number of quants (angles)
    double *reg = malloc(sizeof(double) * q);   // Initialize register and head
    
    float val;
    int idx, head;
    
    do {
        // Wait for the standard input to present you with a float
        scanf("%f", &val);
        reg[head++] = val;
        head = head % q;    //printf("%i-",idx); print_reg(reg, q);
        idx++;

        // Reserve memory for image
        unsigned char *image = dimage(W,H);
        
        // Calculate
        double *seed = circle(q);
        seed[idx%q]= 3;//idx * .01;
        // seed[3]=idx*32;
        // seed[-2]=idx*32;
        
        double *expansion = expand(seed, q);
        double *reduction = reduce(seed, q);

        
        // Plot
        plot(image, seed, q);
        scatter(image, expansion, q*q);
        scatter(image, reduction, q*q);

        // Store
        char filename[16];
        sprintf(filename, "cache/%04i.bmp", idx % BUFFER_SIZE);

        printf("%s\n", filename);
        // bmp(image, W, H, "foo.bmp");
        bmp(image, W, H, filename);

        free(seed);
        free(expansion);
        free(reduction);
        // free(image);

    } while (idx < BUFFER_SIZE);
    // } while (val != -2137);

    return 0;
}

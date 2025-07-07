#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ksienie.h"

/* Constants */
const float PI = 3.1416;
const int W = 512, H = 512;
const float M = 2., FX = 0, FY = .0;

/* Digital image mapping */
float xd(int px){ return (2*M*px/(W-1))-M-FX; }
float yd(int py){ return (2*M*py/(H-1))-M-FY; }

int dx(float x){ return ((x+M)/(2*M))*(W-1); }
int dy(float y){ return ((y+M)/(2*M))*(H-1); }

int ravel(int x, int y, int c) { return (x+y*W)*3+c; } // ravel

/* Metric function */
double metric(float x, float y, double p){
    switch ((int) p)
    {
    case 1:
        return _abs(x) + _abs(y);
    case 2:
        return sqrt(x*x + y*y);
    default:
        return pow((pow(_abs(x), p) + pow(_abs(y), p)), 1/p);
    }
}

/* Business logic */
int is_circle(int px, int py, float cx, float cy, float radius){
    float x = xd(px) - cx;
    float y = yd(py) - cy;

    float distance = metric(x, y, 2);

    float lw = .01;
    int verify = distance < radius;
    // int verify = (distance < radius + lw) && (distance > radius - lw);

    return verify*255;
}

/* main() function */
int main(void){
    // Reserve memory for image
    unsigned char *img = NULL;
    img = (unsigned char *)malloc(3*W*H);    
    memset(img,32,3*W*H);
    
    // Reserve memory for seed
    int q = 128;
    double *seed = NULL;
    seed = (double *)malloc(sizeof(double) * 2 * q);
    memset(seed,0.,2*q);

    // expand seed
    int n = q * q;
    double *expansion = NULL;
    expansion = (double *)malloc(sizeof(double) * 2 * n);
    memset(expansion,0.,2*n);

    /* Seed loop */
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

            double x = ax + bx;
            double y = ay + by;

            expansion[i+j*q] = x;
            expansion[i+j*q+n] = y;
        }
    }
    
    /* plotting */
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
        double vs = expansion[i];
        double vc = expansion[i+n];

        int px = dx(vs);
        int py = dy(vc);

        img[ravel(px,py,0)] = 255;
        img[ravel(px,py,1)] = 255;
        img[ravel(px,py,2)] = 255;

        // img[ravel(px,py,0)] = img[ravel(px,py,0)] % 255;
        // img[ravel(px,py,1)] = img[ravel(px,py,1)] % 255;
        // img[ravel(px,py,2)] = img[ravel(px,py,2)] % 255;
    }

    // for (int px=0 ; px<W ; px++){
    //     for (int py=0 ; py<H ; py++){
    //         if (is_circle(px, py, 0., .0, .25)) {
    //             img[ravel(px,py,0)] = 255;
    //             img[ravel(px,py,1)] = 255;
    //             img[ravel(px,py,2)] = 255;
    //         }
    //     }
    // }

    bmp(img, W, H);

    return 0;
}

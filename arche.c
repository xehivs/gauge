#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ksienie.h"

/* Constants */
const float PI = 3.1416;
const int W = 1024, H = 1024;
const float M = 2., FX = 0, FY = .0;

/* Digital image mapping */
float xd(int px){ return (2*M*px/(W-1))-M-FX; }
float yd(int py){ return (2*M*py/(H-1))-M-FY; }
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
    
    int verify = distance < radius;

    return verify*255;
}

/* main() function */
int main(void){
    printf("Arche gauge start\n");

    unsigned char *img = NULL;
    img = (unsigned char *)malloc(3*W*H);    
    memset(img,0,3*W*H);
    
    for (int px=0 ; px<W ; px++){
        for (int py=0 ; py<H ; py++){
            img[ravel(px,py,0)] = is_circle(px, py, 0., .0, 1);
        }
    }

    bmp(img, W, H);

    return 0;
}
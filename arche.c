#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ksienie.h"

/* Constants */
const float PI = 3.1416;
const int W = 256, H = 256;
const float M = 2.125;

/* Digital image mapping */
float xd(int px){ return (2*M*px/(W-1))-M; }
float yd(int py){ return (2*M*py/(H-1))-M; }

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

    return verify*255;
}

int *line(float ax, float ay, float bx, float by) {
    int dax = dx(ax), day = dy(ay);
    int dbx = dx(bx), dby = dy(by);

    int mx = _iabs(dax - dbx);
    int my = _iabs(day - dby);

    int n_points = mx > my ? mx : my;

    int *_line = NULL;
    _line = (int *)malloc(sizeof(int) * (n_points * 2 + 1));
    _line[0] = n_points;

    for (int i = 0 ; i < n_points ; i++){
        _line[i+1] = dx(ax+(i*_abs(ax-bx)/n_points));
        _line[i+1+n_points] = dy(ay+(i*_abs(ay-by)/n_points));
    }

    return _line;
}

/* main() function */
int main(void){
    int q = 32;     // number of quants (angles)
    int n = q * q;  // number of derivatives

    // Reserve memory for image
    unsigned char *img = dimage(W,H);
    
    // Reserve memory for point location
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
    int *_line = line(0, 0, 1, .5);

    printf("%i !!!\n", _line[0]);
    
    // Plot seed
    for (int i = 1 ; i < _line[0] + 1 ; i++){
        int px = _line[i];
        int py = _line[i+_line[0]];
        img[ravel(px, py, 2)] = 255;
    }


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

    bmp(img, W, H);

    return 0;
}

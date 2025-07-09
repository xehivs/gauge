//
// Various utilities
//

/* Inline absolute value */
double fabs(double v){ return v > 0 ? v : -v; }
int dabs(int v){ return v > 0 ? v : -v; }

/* Array allocator */
double *array(int width, int height){
    double *_array = NULL;
    _array = (double *)malloc(sizeof(double)*width*height);
    memset(_array,0.,width*height);
    return _array;
}

/* Minkowski metric function */
double metric(float x, float y, double p){
    switch ((int) p)
    {
    case 1:
        return fabs(x) + fabs(y);
    case 2:
        return sqrt(x*x + y*y);
    default:
        return pow((pow(fabs(x), p) + pow(fabs(y), p)), 1/p);
    }
}
//
// Definition of laws and transformations
//

/* Inline absolute value */
double fabs(double v){ return v > 0 ? v : -v; }
int dabs(int v){ return v > 0 ? v : -v; }

int dmax(int a, int b){ return a > b ? a : b; }
double fmax(double a, double b){ return a > b ? a : b; }

/* Array allocator */
double *array(int width, int height){
    double *_array = NULL;
    _array = (double *)malloc(sizeof(double)*width*height);
    memset(_array,0.,width*height);
    return _array;
}

/* Minkowski metric function */
double metric(float x, float y, double p){
    switch ((int) p){
    case 1:
        return fabs(x) + fabs(y);
    case 2:
        return sqrt(x*x + y*y);
    default:
        return pow((pow(fabs(x), p) + pow(fabs(y), p)), 1/p);
    }
}

/* Prepare circular seed loop [Apostle] */
double *circle(int q){
    double *seed = array(2, q);

    for (int i = 0 ; i < q ; i++){
        double val = i * (2*PI)/q;

        double vs = sin(val);
        double vc = cos(val);

        seed[i] = vs;
        seed[i+q] = vc;
    }

    return seed;
}

/* Expand array */
double *expand(double *X, int n){
    int nn = n*n;
    double *Y = array(2,nn);
    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < n ; j++){
            double ax = X[i];
            double ay = X[i+n];

            double bx = X[j];
            double by = X[j+n];

            double x = 0.;
            double y = 0.;
            
            Y[i+j*n] = ax + bx;
            Y[i+j*n+nn] = ay + by;
        }
    }
    return Y;
}

/* Reduce array */
double *reduce(double *X, int n){
    int nn = n*n;
    double *Y = array(2,nn);
    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < n ; j++){
            double ax = X[i];
            double ay = X[i+n];

            double bx = X[j];
            double by = X[j+n];

            double x = 0.;
            double y = 0.;
            
            Y[i+j*n] = ax * bx;
            Y[i+j*n+nn] = ay * by;
        }
    }
    return Y;
}

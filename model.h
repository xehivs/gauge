//
// Definition of laws and transformations
//

/* Inline absolute value */
double fabs(double v){ return v > 0 ? v : -v; }
int dabs(int v){ return v > 0 ? v : -v; }

/* Basic statistics */
int dmax(int a, int b){ return a > b ? a : b; }
double fmax(double a, double b){ return a > b ? a : b; }

double sum(double *X, int n){
    double buffer = 0;
    for (int i = 0 ; i < n ; i++){
        buffer += X[i];
    }
    return buffer;
}

double mean(double *X, int n){
    return sum(X, n) / n;
}

double var(double *X, int n){
    double acc = 0;
    double _mean = mean(X, n);
    for (int i = 0 ; i < n ; i++){
        float v = X[i]-_mean;
        acc += v*v;
    }
    return acc / n;
}

double std(double *X, int n){
    return sqrt(var(X, n));
}

double *norm(double *X, int n){
    double _mean = mean(X, n);
    double _std = std(X, n);
    double *buffer = malloc(sizeof(double)*n);
    for (int i = 0 ; i < n ; i++){
        buffer[i] = (X[i] - _mean) / _std;
    }
    return buffer;
}

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
double *circle(int q, double *nreg, double theta){
    double *seed = array(2, q);

    for (int i = 0 ; i < q ; i++){
        double val = i * (2*theta)/q;

        double vs = sin(val) * (1+nreg[i]*S);
        double vc = cos(val) * (1+nreg[i]*S);

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

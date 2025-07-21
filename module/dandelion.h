//
// Canvas decorators
//

int is_circle(int px, int py, float cx, float cy, float radius){
    float x = xd(px) - cx;
    float y = yd(py) - cy;

    float distance = metric(x, y, 2);

    float lw = .01;
    int verify = distance < radius;

    return verify * 255;
}

/*  Return a line

    Defined as a set of points (digital) preceeded by their number.

*/
int *line(float ax, float ay, float bx, float by) {
    // Convert A and B to digital
    int dax = dx(ax), day = dy(ay);
    int dbx = dx(bx), dby = dy(by);

    // Calculate digital distance (Chebyshev)
    int mx = dabs(dax - dbx);
    int my = dabs(day - dby);
    int n_points = mx > my ? mx : my;
    if (_n_points > 0){
        n_points = _n_points;
    }

    // Allocate memory
    int *_line = NULL;
    _line = (int *)malloc(sizeof(int) * (n_points * 2 + 1));
    _line[0] = n_points;

    // Probe colinear space
    float sx = (ax-bx) / (n_points-1);
    float sy = (ay-by) / (n_points-1);
    for (int i = 0 ; i < n_points ; i++){
        _line[1+i] = dx(ax - sx * i);
        _line[1+i+n_points] = dx(ay - sy * i);
    }

    return _line;
}

void draw_line(unsigned char* image, int* line, int d){
    for (int i = 1 ; i < line[0] + 1 ; i++){
        image[ravel(line[i], line[i+line[0]], d)] += _U;
    }
}

void scatter(unsigned char* image, double *X, int n, int d){
    for (int i = 0 ; i < n ; i++) {
        double x = X[i];
        double y = X[i+n];

        int px = dx(x);
        int py = dy(y);

        image[ravel(px,py,d)] += _U;
    }
}

void plot(unsigned char* image, double *X, int n, int d){
    double _x = X[n-1], _y = X[n-1+n];
    for (int i = 0 ; i < n ; i++) {
        double x = X[i];
        double y = X[i+n];

        draw_line(image, line(_x, _y, x, y), d);

        _x = x;
        _y = y;
    }
}

void print_reg(double *reg, int n){
    for (int i = 0 ; i < n ; i++){
        printf("[%.3f] ", reg[i]);
    }
    printf("\n\n");
}

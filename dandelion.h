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

    int mx = dabs(dax - dbx);
    int my = dabs(day - dby);

    int n_points = mx > my ? mx : my;

    int *_line = NULL;
    _line = (int *)malloc(sizeof(int) * (n_points * 2 + 1));
    _line[0] = n_points;

    for (int i = 0 ; i < n_points ; i++){
        _line[i+1] = dx(ax+(i*fabs(ax-bx)/n_points));
        _line[i+1+n_points] = dy(ay+(i*fabs(ay-by)/n_points));
    }

    return _line;
}

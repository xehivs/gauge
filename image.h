//
// Digital Image Mapping
//

/* Directional conversion */
float xd(int px){ return (2*M*px/(W-1))-M; }
float yd(int py){ return (2*M*py/(H-1))-M; }

int dx(float x){ return (int)(((x+M)/(2*M))*(W-1))%W; }
int dy(float y){ return (int)(((y+M)/(2*M))*(H-1))%H; }

/* Circular addresation */
int ravel(int x, int y, int c) { return (x+y*W)*3+c; }

/* Image generation */
unsigned char *dimage(int width, int height){
    unsigned char *_dimage = NULL;
    _dimage = (unsigned char *)malloc(sizeof(double)*width*height*3);
    memset(_dimage,0.,width*height*3);
    return _dimage;
}

void bmp(unsigned char * image, int w, int h, char *filename){
    FILE *f;
    
    int filesize = 54 + 3 * w * h;

    unsigned char bmpfileheader[14] = { 'B','M',
         0, 0, 0, 0, 
         0, 0, 0, 0,
        54, 0, 0, 0
    };
    unsigned char bmpinfoheader[40] = {
        40, 0, 0, 0, 
         0, 0, 0, 0, 
         0, 0, 0, 0, 
         1, 0,24, 0
    };
    unsigned char bmppad[3] = {0,0,0};

    bmpfileheader[ 2] = (unsigned char)(filesize    );
    bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
    bmpfileheader[ 4] = (unsigned char)(filesize>>16);
    bmpfileheader[ 5] = (unsigned char)(filesize>>24);

    bmpinfoheader[ 4] = (unsigned char)(       w    );
    bmpinfoheader[ 5] = (unsigned char)(       w>> 8);
    bmpinfoheader[ 6] = (unsigned char)(       w>>16);
    bmpinfoheader[ 7] = (unsigned char)(       w>>24);
    bmpinfoheader[ 8] = (unsigned char)(       h    );
    bmpinfoheader[ 9] = (unsigned char)(       h>> 8);
    bmpinfoheader[10] = (unsigned char)(       h>>16);
    bmpinfoheader[11] = (unsigned char)(       h>>24);

    f = fopen(filename,"wb");
    fwrite(bmpfileheader,1,14,f);
    fwrite(bmpinfoheader,1,40,f);
    for(int i=0; i<h; i++)
    {
        fwrite(image+(w*(h-i-1)*3),3,w,f);
        fwrite(bmppad,1,(4-(w*3)%4)%4,f);
    }

    free(image);
    fclose(f);
}

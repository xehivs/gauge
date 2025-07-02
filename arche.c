#include <stdio.h>

const float PI = 3.1416;

int main(void){
    printf("Arche gauge start\n");

    int val = 312;
    float fval = (float) val;

    char bunch[] = "Bunch'a words.";

    printf("Value is %4i\n", val);
    printf("Fvalue is %.3f\n", fval);
    printf(bunch, "\n");

    printf("%i\n", sizeof(val));
    printf("%i\n", sizeof(bunch));

    printf("%f\n", PI);

    int flag = -1;

    if (flag)
    {
        printf("ON!\n");
    }
    else {
        printf("OFF!\n");
    }

    int q = 1024;
    int signal[q*q];

    for (int i = 0; i < q; i++)
    {
        for (int j = 0; j < q; j++)
        {
            /* code */
            signal[i*q+j] = (i+j) % 255;
        }
        
    }

    printf("Value is %4i\n", val);

    printf("%i\n", signal[2137]);

    return 0;
}
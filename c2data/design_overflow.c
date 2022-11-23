#include <stdio.h>

main()
{
    short a, b;
    a=32767;
    b=a+2;
    printf("length of short: %d bit\n", sizeof(short)*8);
    //printf("%d\n",(2>>1));
    //int n=1;
    //printf("%d %d %d\n",b,(b>>1),n);
    printf("%d,%d,%d\n",a, a+2, b>>15?(1<<16)+b:b);

    return 0;

}


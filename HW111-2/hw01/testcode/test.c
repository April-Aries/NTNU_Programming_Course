#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

int main()
{
    int32_t a = 1; /* 4 byte */
    int32_t *pa = &a;
    double b = 2.0; /* 8 byte */
    char c = 70; /* 1 byte */

    printf("int32_t a: ( %p ) %d\n", &a, a );
    printf("double  b: ( %p ) %f\n", &b, b );
    printf("char    c: ( %p ) %c\n", &c, c );

    printf("pa                            : ( %p ): %d\n", pa, *pa );
    printf("pa + ( double *)1             : ( %p ): %f\n", (double*)( pa + 1 ), *(double*)( pa + 1) );
    printf("pa + ( double *)1 + ( char *)1: ( %p ): %c\n", ( char *)( (double*)( pa + 1 ) + 1 ), *(char *)( (double*)( pa + 1) + 1 ) );

    return 0;
}

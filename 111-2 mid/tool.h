#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* Comparison 2 numbers */

int32_t max_int( int32_t a, int32_t b )
{
    if( a >= b )    return a;
    else	    return b;
}

double max_double( double a, double b )
{
    if( a >= b )    return a;
    else	    return b;
}

int32_t min_int( int32_t a, int32_t b )
{
    if( a <= b )    return a;
    else	    return b;
}

double min_double( double a, double b )
{
    if( a <= b )    return a;
    else	    return b;
}

/* Clean String */

void clean_str( char *str, int32_t size )
{
    if( !str ||  size == 0 )	return NULL;

    for( int32_t i = 0; i < size; i++ )
    {
	str[i] = 0;
    }

    return;
}

#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>

#include"insert.h"

int32_t strinsert( char **ppResult, const char *pStr1, int32_t location, const char *pStr2 )
{
    /* Error check */
    if( location > strlen( pStr1 ) || location < 0 )
    {
	printf("Overflow!\n");
	return -1;
    }

    if( !pStr1 || !pStr2 || !ppResult )
    {
	printf("Null Input!\n");
	return -1;
    }

    /* Allocate the result array */
    char *new = calloc( strlen( pStr1 ) + strlen( pStr2 ) + 1, sizeof( char ) );

    /* String insert */
    for( int32_t i = 0; i < location; i++ )
    {
	new[i] = pStr1[i];
    }

    for( int32_t i = 0; i < strlen( pStr2 ); i++ )
    {
	new[ location + i ] = pStr2[i];
    }

    for( int32_t i = location; i < strlen( pStr1 ); i++ )
    {
	new[ i + strlen( pStr2 ) ] = pStr1[i];
    }

    /* Assign ppResult = result array */
    *ppResult = calloc( 1, sizeof( char * ) );
    *ppResult = new;

    return 0;
}

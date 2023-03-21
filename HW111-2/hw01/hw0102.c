#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>

#include"insert.h"

int main()
{
    char *result;
    char *str1 = calloc( 100, sizeof( char ) );
    char *str2 = calloc( 100, sizeof( char ) );

    printf("Please input str1: ");
    fgets( str1, 99, stdin );

    printf("Please input str2: ");
    fgets( str2, 99, stdin );

    printf("Please input location: ");
    int32_t location = 0;
    scanf("%d", &location );

    if( str1[ strlen( str1 ) - 1 ] == '\n' )	str1[ strlen( str1 ) - 1 ] = 0;
    if( str2[ strlen( str2 ) - 1 ] == '\n' )	str2[ strlen( str2 ) - 1 ] = 0;

    printf("str1      : %s\n", str1 );
    printf("str2      : %s\n", str2 );

    int32_t num = strinsert( &result, str1, location, str2 );

    if( num == -1 )
    {
	printf("FAILED!\n");
    }
    else if( num == 0 )
    {
	printf("Result: %s\n", result );
    }

    free( str1 );
    free( str2 );
    free( result );

    return 0;
}

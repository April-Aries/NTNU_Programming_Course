#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "bmp.h"
#include "color.h"

int32_t GET_INPUT( char *fileName, int32_t *length, double *ratio, int32_t *iteration );

int main()
{
    /* Get input */
    char *fileName = calloc( 999, sizeof( char ) );
    int32_t length = 0;
    double ratio = 0;
    int32_t iteration = 0;
    int32_t check = 0;
    if( ( check = GET_INPUT( fileName, &length, &ratio, &iteration ) ) == -1 )
    {
	printf("%s---\nError input, terminate\n---%s\n", TEXT_F_LRED, TEXT_DEFAULT );
	return 0;
    }

    FILE *pFile = NULL;
    if( ( pFile = fopen( fileName, "w+" ) ) == NULL )
    {
	perror( "Fail: " );
	return 0;
    }

    sBmpHeader header = {0};
    header.bm[0] = 'B';
    header.bm[1] = 'M';
    header.size = length * length * 54;
    header.offset = 54;
    header.header_size = 40;
    header.width = length;
    header.height = length;
    header.planes = 1;
    header.bpp = 16;
    header.bitmap_size = length * length;
    header.hres = 9449;
    header.vres = 9449;

    fwrite( &header, sizeof( header ), 1, pFile );



    fclose( pFile );

    free( fileName );
    return 0;
}

int32_t GET_INPUT( char *fileName, int32_t *length, double *ratio, int32_t *iteration )
{
    /* Get output file name */
    printf("Output file: ");
    fgets( fileName, 999, stdin );
    if( fileName[ strlen( fileName ) - 1 ] == '\n' )
    {
	fileName[ strlen( fileName ) - 1 ] = 0;
    }

    /* Get side length */
    char *length_str = calloc( 10, sizeof( char ) );
    printf("Side length ( pixel, 480 - 4096 ): ");
    fgets( length_str , 10, stdin );
    /* Error input check and string to integer */
    if( length_str[ strlen( length_str ) - 1 ] == '\n' )
    {
	length_str[ strlen( length_str ) - 1 ] = 0;
    }
    for( int32_t i = 0; i < strlen( length_str ); i++ )
    {
	if( isdigit( length_str[i] ) == 0 )
	{
	    printf("Error: length\n");
	    return -1;
	}
	else
	{
	    *length = *length * 10 + ( length_str[i] - '0' );
	}
    }
    if( *length < 480 || *length > 4096 )
    {
	printf("Error: length\n");
	return -1;
    }

    /* Get ratio */
    char *ratio_str = calloc( 10, sizeof( char ) );
    printf("Move ratio ( 0-1 ): ");
    fgets( ratio_str , 10, stdin );
    /* Error input check and string to integer */
    if( ratio_str[ strlen( ratio_str ) - 1 ] == '\n' )
    {
	ratio_str[ strlen( ratio_str ) - 1 ] = 0;
    }
    int32_t flag = 0;
    for( int32_t i = 0; i < strlen( ratio_str ); i++ )
    {
	if( isdigit( ratio_str[i] ) == 0 )
	{
	    if( ratio_str[i] == '.' && flag == 0 )
	    {
		flag = 1;
	    }
	    else
	    {
		printf("Error: ratio\n");
		return -1;
	    }
	}
    }
    flag = 0;
    int32_t num = 1;
    double num_ = 0.0;
    for( int32_t i = 0; i < strlen( ratio_str ); i++ )
    {
	if( ratio_str[i] == '.' )
	{
	    flag = 1;
	    continue;
	}

	if( flag == 0 )	*ratio = *ratio * 10 + ( ratio_str[i] - '0' );
	else if( flag == 1 )
	{
	    num_ = num_ + pow( 10, -1 * num ) * ( ratio_str[i] - '0' );
	    num += 1;
	}
    }
    *ratio += num_;
    if( *ratio < 0 || *ratio > 1 )
    {
	printf("Error: ratio\n");
	return -1;
    }

    /* Get Iteration number */
    char *iteration_str = calloc( 10, sizeof( char ) );
    printf("Iteration number ( 1-1024 ): ");
    fgets( iteration_str , 10, stdin );
    /* Error input check and string to integer */
    if( iteration_str[ strlen( iteration_str ) - 1 ] == '\n' )
    {
	iteration_str[ strlen( iteration_str ) - 1 ] = 0;
    }
    for( int32_t i = 0; i < strlen( iteration_str ); i++ )
    {
	if( isdigit( iteration_str[i] ) == 0 )
	{
	    printf("Error: iteration\n");
	    return -1;
	}
	else
	{
	    *iteration = *iteration * 10 + ( iteration_str[i] - '0' );
	}
    }
    if( *iteration < 1 || *iteration > 1024 )
    {
	printf("Error: iteration\n");
	return -1;
    }

    free( length_str );
    free( iteration_str );
    free( ratio_str );

    return 0;
}

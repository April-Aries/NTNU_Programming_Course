#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "bmp.h"

int main()
{
    /* Get input, output filenames */
    printf("Input image: ");
    char *input = calloc( 999, sizeof( char ) );
    fgets( input, 999, stdin );

    if( input[ strlen( input ) - 1 ] == '\n' )
    {
	input[ strlen( input ) - 1 ] = 0;
    }
    
    printf("Output image: ");
    char *output = calloc( 999, sizeof( char ) );
    fgets( output, 999, stdin );

    if( output[ strlen( output ) - 1 ] == '\n' )
    {
	output[ strlen( output ) - 1 ] = 0;
    }

    /* Open files */
    FILE *pFile = NULL;
    if( ( pFile = fopen( input, "r" ) ) == NULL )
    {
	perror( "Fail: " );
	return 0;
    }

    sBmpHeader header = {0};
    fread( &header, sizeof( header ), 1, pFile );

    /* Shrink original .bmp file */
    FILE *pFile_shrink = NULL;
    if( ( pFile_shrink = fopen( "shrink.bmp", "w+" ) ) == NULL )
    {
	perror( "Fail: " );
	return 0;
    }

    sBmpHeader header_shrink = header;
    header_shrink.width /= 2;
    header_shrink.height /= 2;

    fwrite( &header_shrink, 1, sizeof( header_shrink ), pFile_shrink );

    uint8_t *arr = calloc( 3 * header.width, sizeof( uint8_t ) );
    uint8_t origin[3] = {0};
    while( !feof( pFile ) )
    {
	for( int32_t i = 0; i < header.width / 2; i++ )
	{
	    fread( origin, 3, 1, pFile );
	    fwrite( origin, 3, 1, pFile_shrink );
	    fread( origin, 3, 1, pFile );
	}
	fread( arr, 3, header.width, pFile );
    }

    fclose( pFile );
    fclose( pFile_shrink );

    /* 3 filps */
    bmp_horizontal_flip( "shrink.bmp", "shrink_h.bmp" );

    bmp_vertical_flip( "shrink.bmp", "shrink_v.bmp" );

    bmp_horizontal_flip( "shrink_v.bmp", "shrink_hv.bmp" );

    /* Combine */
    pFile = NULL;
    if( ( pFile = fopen( output, "w" ) ) == NULL )
    {
	perror( "Fail: " );
    }

    fwrite( &header, sizeof( header ), 1, pFile );

    /* Combine: top-left */
    FILE *pFile2 = NULL;
    if( ( pFile2 = fopen( "shrink_v.bmp", "r" ) ) == NULL )
    {
	perror( "Fail: " );
    }

    uint8_t *trash = calloc( 54, sizeof( uint8_t ) );
    fread( trash, 1, 54, pFile2 );

    uint8_t *arr_ = calloc( 3 * header_shrink.width, sizeof( uint8_t ) );
    for( int32_t i = 0; i < header_shrink.height; i++ )
    {
	fseek( pFile, 54 + 3 * header.width * i, SEEK_SET );
	fread( arr, 3, header_shrink.width, pFile2 );
	fwrite( arr, 3, header_shrink.width, pFile );
    }

    fclose( pFile2 );

    /* Combine: top-right */
    pFile2 = NULL;
    if( ( pFile2 = fopen( "shrink_hv.bmp", "r" ) ) == NULL )
    {
	perror( "Fail: " );
    }

    fread( trash, 1, 54, pFile2 );

    for( int32_t i = 0; i < header_shrink.height; i++ )
    {
	fseek( pFile, 54 + 3 * header.width * i + 3 * header_shrink.width, SEEK_SET );
	fread( arr, 3, header_shrink.width, pFile2 );
	fwrite( arr, 3, header_shrink.width, pFile );
    }

    fclose( pFile2 );

    /* Combine: bottom-left */
    pFile2 = NULL;
    if( ( pFile2 = fopen( "shrink.bmp", "r" ) ) == NULL )
    {
	perror( "Fail: " );
    }

    fread( trash, 1, 54, pFile2 );

    for( int32_t i = 0; i < header_shrink.height; i++ )
    {
	fseek( pFile, 54 + 3 * header.width * i + 3 * header.width * header_shrink.height, SEEK_SET );
	fread( arr, 3, header_shrink.width, pFile2 );
	fwrite( arr, 3, header_shrink.width, pFile );
    }

    fclose( pFile2 );

    /* Combine: bottom-right */
    pFile2 = NULL;
    if( ( pFile2 = fopen( "shrink_h.bmp", "r" ) ) == NULL )
    {
	perror( "Fail: " );
    }

    fread( trash, 1, 54, pFile2 );

    for( int32_t i = 0; i < header_shrink.height; i++ )
    {
	fseek( pFile, 54 + 3 * header.width * i + 3 * header.width * header_shrink.height + 3 * header_shrink.width, SEEK_SET );
	fread( arr, 3, header_shrink.width, pFile2 );
	fwrite( arr, 3, header_shrink.width, pFile );
    }

    fclose( pFile2 );

    free( input );
    free( output );

    free( arr );
    free( arr_ );
    free( trash );

    system( "rm -rf shrink.bmp" );
    system( "rm -rf shrink_v.bmp" );
    system( "rm -rf shrink_h.bmp" );
    system( "rm -rf shrink_hv.bmp" );

    return 0;
}

/* bmp reader */

#pragma once

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "color.h"

typedef struct _sBmpHeader sBmpHeader;

struct _sBmpHeader
{
    char	bm[2];
    uint32_t	size;
    uint32_t	reserve;
    uint32_t	offset;
    uint32_t	header_size;
    uint32_t	width;
    uint32_t	height;
    uint16_t	planes;
    uint16_t	bpp;
    uint32_t	compression;
    uint32_t	bitmap_size;
    uint32_t	hres;
    uint32_t	vres;
    uint32_t	used;
    uint32_t	important;
}__attribute__ ((__packed__));

void print_bmp_header( sBmpHeader *pHeader );
int32_t bmp_vertical_flip( const char *fileName, const char *fileName2 );
int32_t bmp_horizontal_flip( const char *fileName, const char *fileName2 );
int32_t bmp_focus( const char *fileName, const char *fileName2, int32_t x0, int32_t y0, int32_t r );


void print_bmp_header( sBmpHeader *pHeader )
{
    printf( "ID              : %c%c\n", pHeader -> bm[0], pHeader -> bm[1] );
    printf( "Size            : %u\n", pHeader -> size );
    printf( "Reserve         : %u\n", pHeader -> reserve );
    printf( "Offset          : %u\n", pHeader -> offset );
    printf( "Header Size     : %u\n", pHeader -> header_size );
    printf( "Width           : %u\n", pHeader -> width );
    printf( "Height          : %u\n", pHeader -> height );
    printf( "Planes          : %u\n", pHeader -> planes );
    printf( "Bits Per Pixel  : %u\n", pHeader -> bpp );
    printf( "Compression     : %u\n", pHeader -> compression );
    printf( "Bitmap Data Size: %u\n", pHeader -> bitmap_size );
    printf( "H-Resolution    : %u\n", pHeader -> hres );
    printf( "V-Resolution    : %u\n", pHeader -> vres );
    printf( "Used Colors     : %u\n", pHeader -> used );
    printf( "Important Colors: %u\n", pHeader -> important );
    
    return;
}

int32_t bmp_focus( const char *fileName, const char *fileName2, int32_t x0, int32_t y0, int32_t r )
{
    /* Open files */

    // pFile -> Original file
    FILE *pFile = NULL;
    if( ( pFile = fopen( fileName, "r" ) ) == NULL )
    {
	printf("Fail to open file \"%s\"\n", fileName );
	return -1;
    }

    sBmpHeader header = {0};
    fread( &header, sizeof( header ), 1, pFile );

    // pFile2 -> New file
    FILE *pFile2 = NULL;
    if( ( pFile2 = fopen( fileName2, "w+" ) ) == NULL )
    {
	printf("Fail to open file \"%s\"\n", fileName2 );
	return -1;
    }

    fwrite( &header, sizeof( header ), 1, pFile2 );

    x0 = header.width - x0;
    y0 = header.height - y0;

    int32_t X = 0;  int32_t Y = 0;
    while( !feof( pFile ) )
    {
	uint8_t origin[3] = {0};
	fread( origin, 1, 3, pFile );

	uint8_t modified[3] = {0};
	if( ( r * r ) >= ( ( X - x0 ) * ( X - x0 ) + ( Y - y0 ) * ( Y - y0 ) ) )
	{
	    for( int32_t i = 0; i < 3; i++ )	modified[i] = origin[i];
	}
	else
	{
	    for( int32_t i = 0; i < 3; i++ )	modified[i] = 255;
	}

	fwrite( modified, 1, 3, pFile2 );

	X += 1;
	if( X >= header.width )
	{
	    X = 0;
	    Y += 1;
	}
    }

    fclose( pFile );
    fclose( pFile2 );

    return 0;
}

int32_t bmp_horizontal_flip( const char *fileName, const char *fileName2 )
{
    /* Open files */

    // pFile -> Original file
    FILE *pFile = NULL;
    if( ( pFile = fopen( fileName, "r" ) ) == NULL )
    {
	printf("Fail to open file \"%s\"\n", fileName );
	return -1;
    }

    sBmpHeader header = {0};
    fread( &header, sizeof( header ), 1, pFile );

    // pFile2 -> New file
    FILE *pFile2 = NULL;
    if( ( pFile2 = fopen( fileName2, "w+" ) ) == NULL )
    {
	printf("Fail to open file \"%s\"\n", fileName2 );
	return -1;
    }

    fwrite( &header, sizeof( header ), 1, pFile2 );

    uint8_t *arr = calloc( header.width * 3, sizeof( uint8_t ) );
    for( int32_t i = 0; i < header.height; i++ )
    {
	fread( arr, 3, header.width, pFile );

	uint8_t tmp[3] = {0};

	for( int32_t i = 0; i < ( header.width / 2 ); i++ )
	{
	    for( int32_t j = 0; j < 3; j++ )
	    {
		tmp[j] = arr[ 3 * i + j ];
		arr[ 3 * i + j ] = arr[ header.width * 3 - 3 - 3 * i + j ];
		arr[ header.width * 3 - 3 - 3 * i + j ] = tmp[j];
	    }
	}

	fwrite( arr, 3, header.width, pFile2 );
    }

    fclose( pFile );
    fclose( pFile2 );

    free( arr );

    return 0;
}

int32_t bmp_vertical_flip( const char *fileName, const char *fileName2 )
{
    /* Open files */

    // pFile -> Original file
    FILE *pFile = NULL;
    if( ( pFile = fopen( fileName, "r" ) ) == NULL )
    {
	printf("Fail to open file \"%s\"\n", fileName );
	return -1;
    }

    sBmpHeader header = {0};
    fread( &header, sizeof( header ), 1, pFile );

    // pFile2 -> New file
    FILE *pFile2 = NULL;
    if( ( pFile2 = fopen( fileName2, "w+" ) ) == NULL )
    {
	printf("Fail to open file \"%s\"\n", fileName2 );
	return -1;
    }

    fwrite( &header, sizeof( header ), 1, pFile2 );

    uint8_t *arr = calloc( header.width * 3, sizeof( uint8_t ) );
    for( int32_t i = 0; i < header.height; i++ )
    {
	fread( arr, 3, header.width, pFile );

	int32_t offset = header.height - 1 - i;
	offset *= ( 3 * header.width );
	fseek( pFile2, offset, SEEK_CUR );

	fwrite( arr, 3, header.width, pFile2 );

	fseek( pFile2, 54, SEEK_SET );
    }

    fclose( pFile );
    fclose( pFile2 );

    free( arr );

    return 0;
}

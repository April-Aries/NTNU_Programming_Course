#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int main()
{

    printf("Please enter the tetris file: ");
    char *fileName = calloc( 999, sizeof( char ) );
    fgets( fileName, 999, stdin );
    if( fileName[ strlen( fileName ) - 1 ] == '\n' )
    {
	fileName[ strlen( fileName ) - 1 ] = 0;
    }

    FILE *pFile = NULL;
    if( ( pFile = fopen( fileName, "r" ) ) == NULL )
    {
	perror( "Fail: " );
	return 0;
    }

    /*
    printf("\n");

    int32_t width = 0;
    int32_t height = 0;
    fscanf( pFile, "%[^ ] %[^ ]", &width, &height );

    int32_t **board = calloc( height, sizeof( int32_t * ) );
    for( int32_t i = 0; i < height; i++ )
    {
	board[i] = calloc( width, sizeof( int32_t ) );
    }



    for( int32_t i = 0; i < height; i++ )
    {
	free( board[i] );
    }
    free( board );
    */

    fclose( pFile );
    free( fileName );

    return 0;
}

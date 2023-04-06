#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#include "FIFA_tool.h"

int main()
{
    /* Get dataset & open file */
    char *dataset = calloc( 1001, sizeof( char ) );
    while( get_dataset( dataset, 1001 ) == -1 )
    {
	printf("Error input!\n");
    }

    FILE *pFile = NULL;
    while( ( pFile = fopen( dataset, "r" ) ) == NULL )
    {
	perror("Cannot open the file: ");
	clean_str( dataset, 1001 );
	get_dataset( dataset, 1001 );
    }

    /* Get squad */
    char *squad_str = calloc( 51, sizeof( char ) );
    char **squad = calloc( 11, sizeof( char* ) );
    for( int32_t i = 0; i < 11; i++ )	squad[i] = calloc( 10, sizeof( char ) );
    while( get_squad( squad_str, 51, squad ) == -1 )	{}

    /* Get budget */
    int64_t *budget = calloc( 11, sizeof( int64_t ) );
    printf("Budget:\n");
    get_budget( budget, squad );

    /* Read dataset file */
    FIFA *head = read_dataset( pFile, squad, budget );
    FIFA_list_print( head );

    /* Free */
    free( dataset );
    free( squad_str );
    free( squad );
    free( budget );

    /* Close files */
    fclose( pFile );

    return 0;
}

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#include <sys/types.h>
#include <dirent.h>

#include "list_dir.h"

#include "color.h"

/* Functions */
bool READ_DIR( DIREC *current, char **meet, int32_t *meet_size );

int main()
{

    /* Allocate "." DIR and DIREC list */
    DIREC *current = DIREC_init();
    strncpy( current->path, ".", 2 );

    /* Allocate meet array */
    char **meet = calloc( 1001, sizeof( char * ) );
    int32_t meet_size = 0;

    if( READ_DIR( current, meet, &meet_size ) == false )
    {
	printf("error\n");
	return 0;
    }

    return 0;
}

bool READ_DIR( DIREC *current, char **meet, int32_t *meet_size )
{
    /* NULL Input */
    if( !current )  return false;

    /* Open Directory */
    DIR *dir = NULL;
    if( ( dir = opendir( current->path ) ) == NULL )
    {
	perror( "Directory cannot be opened: " );
	return false;
    }

    /* Read data & Sorting */
    struct dirent *entity = NULL;
    entity = readdir( dir );
    while( entity != NULL )
    {
	if( strcmp( entity->d_name, "." ) == 0 || strcmp( entity->d_name, ".." ) == 0 )
	{
	    entity = readdir( dir );
	    continue;
	}

	ELEMENT *node = ELEMENT_init();
	strncpy( node->name, entity->d_name, strlen( entity->d_name ) );
	node->type = entity->d_type;
	ELEMENT_insert( current, node );

	if( node->type == DT_DIR )
	{
	    DIREC *folder = DIREC_init( );

	    strcat( folder->path, current->path );
	    strcat( folder->path, "/" );
	    strcat( folder->path, entity->d_name );

	    DIREC_push( current, folder );
	}

	entity = readdir( dir );
    }

    /* Print this directory */
    DIREC_print( current, meet, meet_size );

    /* Recursive call */
    if( ( current = current->link_DIREC ) != NULL )
    {
	if( READ_DIR( current, meet, meet_size ) == false )
	{
	    printf("error\n");
	    return 0;
	}
    }

    /* Close Directory */
    closedir( dir );

    return true;
}

#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct data data;

struct data
{
    char *commit;

    char *author;
    char *mail;

    char *year;	    char *month;    char *date;
    char *hour;	    char *min;	    char *sec;

    int32_t file_change;
    int32_t insertion;
    int32_t deletion;

    int32_t commit_num;

    data *link;
}__attribute__((packed));

data *node_init( )
{
    data *node = calloc( 1, sizeof( data ) );

    node->commit = calloc( 41, sizeof( char ) );

    node->author = calloc( 51, sizeof( char ) );
    node->mail = calloc( 51, sizeof( char ) );

    node->year = calloc( 5, sizeof( char ) );
    node->month = calloc( 4, sizeof( char ) );
    node->date = calloc( 3, sizeof( char ) );

    node->hour = calloc( 3, sizeof( char ) );
    node->min = calloc( 3, sizeof( char ) );
    node->sec = calloc( 3, sizeof( char ) );

    node->link = NULL;

    return node;
}

void node_free( data *node )
{
    free( node->commit );

    free( node->author );
    free( node->mail );

    free( node->year );
    free( node->month );
    free( node->date );

    free( node->hour );
    free( node->min );
    free( node->sec );

    free( node );

    return;
}

void list_free( data *header )
{
    data *node = header;
    data *tmp = node->link;

    while( tmp )
    {
	node_free( node );
	node = tmp;
	tmp = tmp->link;
    }
    free( node );

    return;
}

void node_print( data *node )
{
    printf("( %s )\n", node->commit );
    printf("- %s <%s>\n", node->author, node->mail );
    printf("- %s/%s/%s %s:%s:%s\n", node->year, node->month, node->date, node->hour, node->min, node->sec );
    printf("- %d file(s) changed, %d insertion(s), %d deletion(s)\n\n", node->file_change, node->insertion, node->deletion );

    return;
}

void list_print( data *header )
{
    data *tmp = header;

    while( tmp )
    {
	printf("( %s )\n", tmp->commit );
	printf("- %s <%s>\n", tmp->author, tmp->mail );
	printf("- %s/%s/%s %s:%s:%s\n", tmp->year, tmp->month, tmp->date, tmp->hour, tmp->min, tmp->sec );
	printf("- %d file(s) changed, %d insertion(s), %d deletion(s)\n\n", tmp->file_change, tmp->insertion, tmp->deletion );

	tmp = tmp->link;
    }

    return;
}

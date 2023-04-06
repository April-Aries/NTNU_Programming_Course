#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"

typedef struct ELEMENT ELEMENT;

struct ELEMENT
{
    char *name;
    int32_t type;
    ELEMENT *link;
}__attribute__((packed));

typedef struct DIREC DIREC;

struct DIREC
{
    char *path;
    ELEMENT *link_ELEMENT;
    DIREC *link_DIREC;
}__attribute__((packed));

ELEMENT *ELEMENT_init( )
{
    ELEMENT *node = calloc( 1, sizeof( ELEMENT ) );

    node->name = calloc( 256, sizeof( char ) );
    node->link = NULL;

    return node;
}

void ELEMENT_list_free( ELEMENT *header )
{
    ELEMENT *current = header;
    ELEMENT *next = current->link;

    while( current )
    {
	next = current->link;

	free( current->name );
	free( current );

	current = next;
    }

    return;
}

void ELEMENT_insert( DIREC *header, ELEMENT *current )
{
    ELEMENT *record = header->link_ELEMENT;
    ELEMENT *pre = NULL;
    ELEMENT *next = record;

    if( record == NULL ) // No element in current header
    {
	header->link_ELEMENT = current;
	return;
    }

    while( record )
    {
	if( strcmp( current->name, record->name ) < 0 )
	{
	    break;
	}
	else
	{
	    pre = record;
	    next = record->link;
	    record = record->link;
	}
    }

    if( record == NULL )
    {
	pre->link = current;
    }
    else if( pre == NULL )
    {
	header->link_ELEMENT = current;
	current->link = next;
    }
    else
    {
	pre->link = current;
	current->link = next;
    }

    return;
}

DIREC *DIREC_init( )
{
    DIREC *node = calloc( 1, sizeof( DIREC ) );

    node->path = calloc( 4097, sizeof( char ) );
    node->link_ELEMENT = NULL;
    node->link_DIREC = NULL;

    return node;
}

void DIREC_push( DIREC *head, DIREC *current )
{
    DIREC *tmp = head;
    while( tmp->link_DIREC )    tmp = tmp->link_DIREC;

    tmp->link_DIREC = current;

    return;
}

void DIREC_print( DIREC *node, char **meet, int32_t *meet_size )
{
    /* Check: met or not */
    char *real_path = calloc( 4097, sizeof( real_path ) );
    realpath( node->path, real_path );
    for( int32_t i = 0; i < *meet_size; i++ )
    {
	if( strcmp( real_path, meet[i] ) == 0 )
	{
	    return;
	}
    }
    *meet_size += 1;
    meet[ *meet_size - 1 ] = real_path;
    ELEMENT *pointer = node->link_ELEMENT;

    printf("%s%s%s:\n", TEXT_F_RED, node->path, TEXT_DEFAULT );

    while( pointer )
    {
	if( pointer->type == DT_DIR )
	{
	    printf("\t%s%s%s\n", TEXT_F_BLUE, pointer->name, TEXT_DEFAULT );
	}
	else
	{
	    printf("\t%s\n", pointer->name );
	}

	pointer = pointer->link;
    }
    printf("\n");

    return;
}

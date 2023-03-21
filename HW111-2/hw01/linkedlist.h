#pragma once

#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

typedef struct node node;
struct node
{
    int16_t up;
    int16_t low;
    node *link;
};

node* create_node( )
{
    node* a = calloc( 1, sizeof( node ) );

    /*
    a->up = 0;
    a->low = 0;
    a->link = NULL;
    */

    return a;
}

int32_t link_length( node *head )
{
    node *tmp = head;

    int32_t count = 0;
    while( tmp )
    {
	count++;
	tmp = tmp->link;
    }

    return count;
}

void linked_list_print( node *head )
{
    node *tmp = head;

    if( !tmp )
    {
	printf("NULL\n");
	return;
    }

    while( 1 )
    {
	printf("\t\t%p: ( %d, %d )\n", tmp, tmp->up, tmp->low );
	if( tmp->link )	tmp = tmp->link;
	else	break;
    }
    printf("\n");

    return;
}

void linked_list_free( node *head )
{
    node *tmp = head;
    node *tmp2 = NULL;

    if( !tmp )	return;

    while( tmp->link )
    {
	tmp2 = tmp->link;
	free( tmp );
	tmp = tmp2;
    }
    free( tmp );

    return;
}

void linked_list_tail( node *head, node **tail, node **tail2 )
{
    node *tmp = head;

    if( !head )
    {
	*tail = NULL;;
	*tail2 = NULL;
    }
    if( link_length( head ) == 1 )
    {
	*tail = head;
	*tail2 = NULL;
    }

    while( tmp->link )
    {
	*tail2 = tmp;
	tmp = tmp->link;
    }

    *tail = tmp;

    return;
}

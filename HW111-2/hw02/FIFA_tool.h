#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* FIFA structure & related functions */

typedef struct FIFA FIFA;

struct FIFA
{
    bool choosed;
    char *sofia_id;
    char *short_name;
    char *club_name;
    int32_t value;
    int32_t wage;
    int32_t *data; // ls, st, rs, ..., rb, gk

    FIFA *link;
}__attribute__((packed));

FIFA *FIFA_init( )
{
    FIFA *node = calloc( 1, sizeof( FIFA ) );

    node->choosed = false;
    node->sofia_id = calloc( 11, sizeof( char ) );
    node->short_name = calloc( 21, sizeof( char ) );
    node->club_name = calloc( 21, sizeof( char ) );

    node->data = calloc( 27, sizeof( int32_t ) );

    node->link = NULL;

    return node;
}

FIFA* FIFA_node_free( FIFA *node )
{
    FIFA *next = node->link;

    free( node->sofia_id );
    free( node->short_name );
    free( node->club_name );
    free( node->data );

    free( node );

    return next;
}

void FIFA_list_free( FIFA *head )
{
    FIFA *tmp = head;

    while( tmp )
    {
	tmp = FIFA_node_free( tmp );
    }

    return;
}

/* Little functions */

bool IsDigit( char a )
{
    if( a >= '0' && a <= '9' )	return true;
    else    return false;
}

void clean_str( char *str, int32_t size )
{
    for( int32_t i = 0; i < size; i++ )
    {
	str[i] = 0;
    }
    return;
}

/* Get requirements functions */

int32_t get_dataset( char *dataset, int32_t size )
{
    if( !dataset || size == 0 )	return -1;

    printf("Please enter the dataset: ");
    fgets( dataset, size, stdin );
	if( dataset[ strlen( dataset ) - 1 ] == '\n' )
	{
	    dataset[ strlen( dataset ) - 1 ] = 0;
	}

    return 0;
}

int32_t get_squad( char *squad_str, int32_t size, char **squad )
{
    if( !squad_str || size == 0 )	return -1;

    clean_str( squad_str, 51 );
    printf("Please enter the squad: ");
    fgets( squad_str, size, stdin );
	if( squad_str[ strlen( squad_str ) - 1 ] == '\n' )
	{
	    squad_str[ strlen( squad_str ) - 1 ] = 0;
	}

    for( int32_t i = 0; i < 11; i++ )   clean_str( squad[i], 11 );

    char *token = strtok( squad_str, " " );
    for( int32_t i = 0; token != NULL; i++ )
    {
	squad[i] = token;

	if( i != 10 && squad[i] == "gk" )
	{
	    printf("The %d squad cannot be \"gk\"\n\"gk\" should be put in the last\n", i + 1 );
	    return -1;
	}
	if( i == 10 && strcmp( squad[i], "gk" ) != 0 )
	{
	    printf("Last input should be \"gk\"\n");
	    return -1;
	}

	token = strtok( NULL, " " );
    }

    return 0;
}

void get_budget( int64_t *budget, char **squad )
{
    for( int32_t i = 0; i < 11; i++ )
    {
	printf("\t%s: ", squad[i] );
	char *budget_str = calloc( 30, sizeof( char ) );
	fgets( budget_str, 30, stdin );
	    if( budget_str[ strlen( budget_str ) - 1 ] == '\n' )
	    {
		budget_str[ strlen( budget_str ) - 1 ] = 0;
	    }
	int32_t flag = 1;
	for( int32_t j = 0; j < strlen( budget_str ); j++ )
	{
	    if( IsDigit( budget_str[j] ) == false )
	    {
		printf("\t( Error input! Please enter again! )\n" ); 
		i--;
		flag = 0;
		break;
	    }
	}

	if( flag == 1 )
	{
	    for( int32_t j = 0; j < strlen( budget_str ); j++ )
	    {
		budget[i] = budget[i] * 10 + ( budget_str[j] - '0' );
	    }
	}

	free( budget_str );
    }

    return;
}

FIFA* read_dataset( FILE *pFile, char **squad, int64_t *budget )
{
    char *str = calloc( 10000, sizeof( char ) );
    FIFA *head = FIFA_init();
    FIFA *node = head;

    while( !feof( pFile ) )
    {
	fgets( str, 10000, pFile );

	node->sofia_id = strtok( str, "," );

	node->short_name = strtok( str, "," );

	for( int32_t i = 2; i < 7; i++ )    strtok( str, "," );

	char *tmp = calloc( 11, sizeof( char ) );
	tmp = strtok( str, "," );
	for( int32_t i = 0; i < strlen( tmp ); i++ )
	{
	    if( IsDigit( tmp[i] ) )
	    {
		node->value = node->value * 10 + ( tmp[i] - '0' );
	    }
	}

	clean_str( tmp, 11 );
	tmp = strtok( str, "," );
	for( int32_t i = 0; i < strlen( tmp ); i++ )
	{
	    if( IsDigit( tmp[i] ) )
	    {
		node->wage = node->wage * 10 + ( tmp[i] - '0' );
	    }
	}

	for( int32_t i = 9; i < 14; i++ )    strtok( str, "," );
	node->club_name = strtok( str, "," );

	for( int32_t i = 14; i < 78; i++ )    strtok( str, "," );

	for( int32_t i = 0; i < 27; i++ )
	{
	    clean_str( tmp, 11 );
	    tmp = strtok( str, "," );
	    int32_t num1 = 0;	int32_t num2 = 0;   bool flag = false;
	    for( int32_t i = 0; i < strlen( tmp ); i++ )
	    {
		if( IsDigit( tmp[i] ) && flag == false )
		{
		    num1 = num1 * 10 + ( tmp[i] - '0' );
		}
		else if( tmp[i] == '+' )
		{
		    flag = true;
		}
		else if( flag == true && IsDigit( tmp[i] ) )
		{
		    num2 = num2 * 10 + ( tmp[i] - '0' );
		}
	    }
	    node->data[i] = num1 + num2;
	}

	node->link = FIFA_init();
	node = node->link;
    }

    return head;
}

void FIFA_list_print( FIFA *head )
{
    FIFA *tmp = head;

    while( tmp )
    {
	printf("---\n");
	printf("id        : %s\n", tmp->sofia_id );
	printf("short name: %s\n", tmp->short_name );
	printf("club name : %s\n", tmp->club_name );

	tmp = tmp->link;
    }

    return;
}

#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>

#include"color.h"
#include"abacus.h"
#include"linkedlist.h"

/* Extra function I need */
int32_t max_member( uint8_t a, uint8_t b ) // Extra functions I need
{
    if( a > b )		    return 1;
    else if( a < b )	    return 2;
    else		    return 3;	/* a == b */
}


sAbacus* abacus_init( void )
{
    sAbacus* a = calloc( 1, sizeof( sAbacus ) );

    return a;
}

void abacus_free( sAbacus* a ) // unknown name, to be asked
{
    free( a );

    return;
}

// Set pA according to pStr
// For example , pStr is "123456789"
// pA -> number = 9;
// pA -> pUpperRod: {0,0,0,0,1,1,1,1,1}
// pA -> pLowerRod: {1,2,3,4,0,1,2,3,4}
// if the length of pStr > 255 or the string contains alphabets or special racter or NULL , return -1.
// Otherwise , return 0
int32_t abacus_set( sAbacus *pA , char *pStr )
{
    /* Error input */
    // length of pStr is too long or NULL input
    if( strlen( pStr ) > 255 || !pA )	return -1;
    // pStr contains invalid character
    for( int32_t i = 0; i < strlen( pStr ); i++ )
    {
	if( !( pStr[i] >= '0' && pStr[i] <= '9' ) ) return -1;
    }

    /* abacus set */
    pA->number = strlen( pStr );
    pA->pUpperRod = calloc( pA->number, sizeof( uint8_t ) );
    pA->pLowerRod = calloc( pA->number, sizeof( uint8_t ) );
    for( int32_t i = 0; i < strlen( pStr ); i++ )
    {
	if( pStr[i] < '5' )
	{
	    pA->pUpperRod[i] = 0;
	    pA->pLowerRod[i] = pStr[i] - '0';
	}
	else if( pStr[i] >= '5' )
	{
	    pA->pUpperRod[i] = 1;
	    pA->pLowerRod[i] = pStr[i] - '5';
	}
    }

    return 0;
}

// a = b + c
// Successful: return 0; otherwise , return -1


int32_t abacus_add( sAbacus *pA , sAbacus b, sAbacus c )
{
    /* Error Check */
    if( !pA )	return -1;
    if( b.number > 255 || c.number > 255 )  return -1;

    /* Addition */
    node *tmp = NULL;
    node *head = NULL;
    switch( max_member( b.number, c.number ) )
    {
	case 1: /* b.number > a.number */
	    {
		int32_t count = 1;
		for( int32_t i = b.number - 1; i >= 0; i-- )
		{
		    node *N = create_node( );
		    if( !tmp )
		    {
			tmp = N;
			head = N;
		    }
		    else
		    {
			tmp->link = N;
			tmp = N;
		    }

		    if( count <= c.number )
		    {
			N->up += c.pUpperRod[ c.number - count ];
			N->low += c.pLowerRod[ c.number - count ];
			count++;
		    }

		    N->up += b.pUpperRod[i];
		    N->low += b.pLowerRod[i];

		}
		break;
	    }
	case 2: case 3: /* b.number <= a.number */
	    {
		int32_t count = 1;
		for( int32_t i = c.number - 1; i >= 0; i-- )
		{
		    node *N = create_node( );
		    if( !tmp )
		    {
			tmp = N;
			head = N;
		    }
		    else
		    {
			tmp->link = N;
			tmp = N;
		    }

		    if( count <= b.number )
		    {
			N->up += b.pUpperRod[ b.number - count ];
			N->low += b.pLowerRod[ b.number - count ];
			count++;
		    }

		    N->up += c.pUpperRod[i];
		    N->low += c.pLowerRod[i];

		}
		break;
	    }
	default:
	    break;
    }

    /* Check */
    int32_t carry = 0;
    tmp = head;
    while( 1 )
    {
	if( carry == 1 )
	{
	    tmp->low += 1;
	    carry = 0;
	}

	if( tmp->low >= 5 && tmp->up == 1 )
	{
	    carry = 1;
	    tmp->low -= 5;
	    tmp->up = 0;
	}
	else if( tmp->low >= 5 && tmp->up == 0 )
	{
	    tmp->low -= 5;
	    tmp->up = 1;
	}

	if( tmp->link )	tmp = tmp->link;
	else	break;

    }

    if( carry == 1 )
    {
	node *new = create_node( );
	new->up = 0;
	new->low = 1;
	new->link = NULL;
	tmp->link = new;
    }

    /* Result length check */
    if( link_length( head ) > 255 ) return -1;

    /* Linked list -> pA */
    // pA calloc yet or not?
    pA->number = link_length( head );
    pA->pUpperRod = calloc( pA->number, sizeof( uint8_t ) );
    pA->pLowerRod = calloc( pA->number, sizeof( uint8_t ) );

    tmp = head;
    int32_t count = 1;
    while( tmp )
    {
	pA->pUpperRod[ pA->number - count ] = tmp->up;
	pA->pLowerRod[ pA->number - count ] = tmp->low;

	tmp = tmp->link;
	count++;
    }

    /* free linked list */
    linked_list_free( head );

    return 0;
}

// a = b - c
// Successful: return 0; otherwise , return -1
int32_t abacus_del( sAbacus *pA , sAbacus b, sAbacus c )
{
    /* Error Check */
    if( !pA )	return -1;
    if( b.number > 255 || c.number > 255 )  return -1;

    /* Deletion */
    node *tmp = NULL;
    node *head = NULL;
    switch( max_member( b.number, c.number ) )
    {
	case 1: case 3:	/* b.number >= a.number */
	    {
		int32_t count = 1;
		for( int32_t i = b.number - 1; i >= 0; i-- )
		{
		    node *N = create_node( );
		    if( !tmp )
		    {
			tmp = N;
			head = N;
		    }
		    else
		    {
			tmp->link = N;
			tmp = N;
		    }

		    if( count <= c.number )
		    {
			N->up = b.pUpperRod[i] - c.pUpperRod[ c.number - count ];
			N->low += b.pLowerRod[i] - c.pLowerRod[ c.number - count ];
			count++;
		    }
		    else
		    {
			N->up = b.pUpperRod[i];
			N->low += b.pLowerRod[i];
		    }
		}

		break;
	    }
	case 2: /* b.number < a.number */
	    return -1;
    }

    /* Check */
    int32_t carry = 0;
    tmp = head;

    while( tmp )
    {
	if( carry == 1 )
	{
	    tmp->low -= 1;
	    carry = 0;
	}

	if( tmp->low < 0 && tmp->up == 1 )
	{
	    tmp->up = 0;
	    tmp->low += 5;
	}
	else if( tmp->low < 0 && tmp->up < 1)
	{
	    tmp->low += 10;
	    carry = 1;
	}
	else if( tmp->up < 0 )
	{
	    carry = 1;
	    tmp->up += 2;
	}

	if( tmp->low >= 5 )
	{
	    tmp->low -= 5;
	    tmp->up += 1;
	}

	tmp = tmp->link;
    }

    /* Negative Result */
    if( carry == 1 )	return -1;

    /* Linked list -> pA */
    // pA calloc yet or not?
    pA->number = link_length( head );

    /* Beginning 0 deletion */
    while( 1 )
    {
	node *tail = NULL;
	node *tail2 = NULL;
	linked_list_tail( head, &tail, &tail2 );

	if( tail != NULL && tail2 != NULL )
	{
	    if( tail->up == 0 && tail->low == 0 )
	    {
		tail2->link = NULL;
		free( tail );
		pA->number -= 1;
		continue;
	    }
	    else
	    {
		break;
	    }
	}
	else
	{
	    break;
	}
    }

    tmp = head;
    int32_t count = 1;

    pA->pUpperRod = calloc( pA->number, sizeof( uint8_t ) );
    pA->pLowerRod = calloc( pA->number, sizeof( uint8_t ) );

    tmp = head;
    while( tmp )
    {
	pA->pUpperRod[ pA->number - count ] = tmp->up;
	pA->pLowerRod[ pA->number - count ] = tmp->low;

	tmp = tmp->link;
	count++;
    }

    /* free linked list */
    linked_list_free( head );

    return 0;
}

// EX: "172" , you should print
// upper -> red, lower -> yellow
// * *
//  *
// ---
// ***
//  **
// *
// ***
// ***
// Successful: return 0; otherwise , return -1
int32_t abacus_print( sAbacus a ) // make sure is struct but not a pointer, to be asked
{
    /* upper */
    printf("%s", TEXT_F_RED );

    //line 1.
    for( int32_t i = 0; i < a.number; i++ )
    {
	if( a.pUpperRod[i] == 1 )	printf(" ");
	else if( a.pUpperRod[i] == 0 )	printf("*");
    }
    printf("\n");
    
    //line 2.
    for( int32_t i = 0; i < a.number; i++ )
    {
	if( a.pUpperRod[i] == 0 )	printf(" ");
	else if( a.pUpperRod[i] == 1 )	printf("*");
    }
    printf("\n");

    printf("%s", TEXT_DEFAULT );

    /* horizontal line */
    for( int32_t i = 0; i < a.number; i++ )
    {
	printf("-");
    }
    printf("\n");

    /* upper */
    printf("%s", TEXT_F_YELLOW );

    for( int32_t i = 0; i < 5; i++ )
    {
	for( int32_t j = 0; j < a.number; j++ )
	{
	    switch( i )
	    {
		case 0:
		    if( a.pLowerRod[j] == 5 || a.pLowerRod[j] == 0 )  printf(" ");
		    else					    printf("*");
		    break;
		case 1:
		    if( a.pLowerRod[j] == 1 || a.pLowerRod[j] == 6 )  printf(" ");
		    else					    printf("*");
		    break;
		case 2:
		    if( a.pLowerRod[j] == 2 || a.pLowerRod[j] == 7 )  printf(" ");
		    else					    printf("*");
		    break;
		case 3:
		    if( a.pLowerRod[j] == 3 || a.pLowerRod[j] == 8 )  printf(" ");
		    else					    printf("*");
		    break;
		case 4:
		    if( a.pLowerRod[j] == 4 || a.pLowerRod[j] == 9 )  printf(" ");
		    else					    printf("*");
		    break;
	    }
	}
	printf("\n");
    }

    printf("%s", TEXT_DEFAULT );

    return 0;
}

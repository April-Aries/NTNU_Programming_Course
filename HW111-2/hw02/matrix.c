#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "matrix.h"

// Memory allocation for a m*n matrix. Fill zeros to all matrix element.
sMatrix* matrix_init( uint8_t m, uint8_t n)
{
    /* Error Check */
    if( ( m == 0 && n == 0 ) || ( m < 0 ) || ( n < 0 ) )  return NULL;	// Though uint8_t won't give negative number

    sMatrix *matrix = calloc( 1, sizeof( sMatrix ) );

    matrix->row = m;
    matrix->col = n;

    matrix->board = calloc( m, sizeof( int32_t* ) );
    for( int32_t i = 0; i < matrix->row; i++ )
    {
	matrix->board[i] = calloc( n, sizeof( int32_t ) );
    }

    return matrix;
}

// Set the element in m-th row and n-th column to value.
// Note that m and n start from 0.
// If error , return -1; otherwise , return 0;
int32_t matrix_set( sMatrix *pM , uint8_t m, uint8_t n, int32_t value )
{
    /* Error Check */
    if( !pM )	return -1;
    if( m >= pM->row || n >= pM->col )	return -1;

    pM->board[m][n] = value;

    return 0;
}

// Print the matrix as follows
// 1 0
// 0 1
void matrix_print( const sMatrix *pM )
{
    if( !pM )	return;

    for( int32_t i = 0; i < pM->row; i++ )
    {
	for( int32_t j = 0; j < pM->col; j++ )
	{
	    printf("%d ", pM->board[i][j] );
	}
	printf("\n");
    }

    return;
}

// A = B + C
// If error , return -1; otherwise , return 0;
int32_t matrix_add( sMatrix *pA , const sMatrix *pB , const sMatrix *pC )
{
    /* Error Check */
    if( !pA || !pB || !pC )	return -1;
    if( pB->row != pC->row || pB->col != pC->col )  return -1;

    pA->row = pB->row;
    pA->col = pB->col;
    for( int32_t i = 0; i < pA->row; i++ )
    {
	for( int32_t j = 0; j < pA->col; j++ )
	{
	    pA->board[i][j] = pB->board[i][j] + pC->board[i][j];
	}
    }

    return 0;
}

// A = B * C
// If error , return -1; otherwise , return 0;
int32_t matrix_multiply( sMatrix *pA , const sMatrix *pB , const sMatrix *pC )
{
    /* Error Check */
    if( !pA || !pB || !pC )	return -1;
    if( pB->row != pC->col || pB->col != pC->row )  return -1;

    pA->row = pB->row;
    pA->col = pC->col;

    for( int32_t i = 0; i < pA->row; i++ )
    {
	for( int32_t j = 0; j < pA->col; j++ )
	{
	    for( int32_t k = 0; k < pB->col; k++ )
	    {
		pA->board[i][j] += pB->board[i][k] * pC->board[k][j];
	    }
	}
    }

    return 0;
}

// A = A^T
// If error , return -1; otherwise , return 0;
int32_t matrix_transpose( sMatrix *pA )
{
    if( !pA )	return -1;

    int32_t tmp = pA->row;
    pA->row = pA->col;
    pA->col = tmp;

    int32_t **board = calloc( pA->row, sizeof( int32_t* ) );
    for( int32_t i = 0; i < pA->row; i++ )
    {
	board[i] = calloc( pA->col, sizeof( int32_t ) );
    }

    for( int32_t i = 0; i < pA->row; i++ )
    {
	for( int32_t j = 0; j < pA->col; j++ )
	{
	    board[j][i] = pA->board[i][j];
	}
    }

    
    for( int32_t i = 0; i < pA->col; i++ )
    {
	free( pA->board[i] );
    }
    free( pA->board );

    pA->board = board;

    return 0;
}

// Determinant
// Determinant should be put to *pAns
// If error , return -1; otherwise , return 0;
int32_t matrix_det(const sMatrix *pA , int32_t *pAns)
{
    /* Error Check */
    if( !pA )	return -1;
    if( pA->row != pA->col )	return -1;

    /* Calculating determinant */
    int32_t pos = 0;
    int32_t neg = 0;

    /* Pos */
    int32_t col_num = 0;
    while( col_num < pA->col )
    {
	int32_t tmp = 1;
	int32_t k = 0;
	while( ( k < pA->col ) && ( col_num + k < pA->col ) )
	{
	    tmp *= pA->board[ k ][ col_num + k ];
	    k++;
	}
	k = 0;
	while( ( pA->row - 1 - k >= 0 ) && ( col_num - 1 - k >= 0 ) )
	{
	    tmp *= pA->board[ pA->row - 1 - k ][ col_num - 1 - k ];
	    k++;
	}
	pos += tmp;
	col_num++;
    }

    /* Neg */
    col_num = 0;
    while( col_num < pA->col )
    {
	int32_t k = 0;
	int32_t tmp = 1;
	while( ( pA->row - 1 - k >= 0 ) && ( col_num + k < pA->col ) )
	{
	    tmp *= pA->board[ pA->row - 1 - k ][ col_num + k ];
	    k++;
	}
	k = 0;
	while( ( k < pA->row ) && ( col_num - 1 - k >= 0 ) )
	{
	    tmp *= pA->board[ k ][ col_num - 1 - k ];
	    k++;
	}
	neg += tmp;
	col_num++;
    }

    *pAns = pos - neg;

    return 0;
}

// Free
// If error , return -1; otherwise , return 0;
int32_t matrix_free( sMatrix *pA)
{
    /* Error Check */
    if( !pA )	return -1;
    
    /* Free pA->board */
    for( int32_t i = 0; i < pA->row; i++ )
    {
	free( pA->board[i] );
    }
    free( pA->board );

    free( pA );

    return 0;
}

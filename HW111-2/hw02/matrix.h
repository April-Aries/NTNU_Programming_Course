#pragma once

#include <stdint.h>

typedef struct Matrix sMatrix;

struct Matrix
{
    int32_t row;
    int32_t col;
    int32_t **board;
};

// Memory allocation for a m*n matrix. Fill zeros to all matrix element.
sMatrix* matrix_init( uint8_t m, uint8_t n);

// Set the element in m-th row and n-th column to value.
// Note that m and n start from 0.
// If error , return -1; otherwise , return 0;
int32_t matrix_set( sMatrix *pM , uint8_t m, uint8_t n, int32_t value );

// Print the matrix as follows
// 1 0
// 0 1
void matrix_print( const sMatrix *pM );

// A = B + C
// If error , return -1; otherwise , return 0;
int32_t matrix_add( sMatrix *pA , const sMatrix *pB , const sMatrix *pC );

// A = B * C
// If error , return -1; otherwise , return 0;
int32_t matrix_multiply( sMatrix *pA , const sMatrix *pB , const sMatrix *pC );

// A = A^T
// If error , return -1; otherwise , return 0;
int32_t matrix_transpose( sMatrix *pA );

// Determinant
// Determinant should be put to *pAns
// If error , return -1; otherwise , return 0;
int32_t matrix_det(const sMatrix *pA , int32_t *pAns);

// Free
// If error , return -1; otherwise , return 0;
int32_t matrix_free( sMatrix *pA);

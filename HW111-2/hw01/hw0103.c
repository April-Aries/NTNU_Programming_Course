#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>

#include"abacus.h"

int main()
{
    /* Abacus A */
    sAbacus *A = abacus_init( );

    int32_t check = abacus_set( A, "1000" );

    if( !check )
    {
	printf("Set abacus A:\n");
	printf("\tnumber: %d\n", A->number );
	printf("\tpUpperRod: " );
	for( int32_t i = 0; i < A->number; i++ )
	{
	    printf("%d ", A->pUpperRod[i] );
	}
	printf("\n");
	printf("\tpLowerRod: " );
	for( int32_t i = 0; i < A->number; i++ )
	{
	    printf("%d ", A->pLowerRod[i] );
	}
	printf("\n\n");
    }

    printf("Print abacus A:\n\n");
    if( abacus_print( *A ) == -1 )
    {
	printf("Fail to print\n");
    }

    printf("\n--------------------\n\n");

    /* Abacus B */
    sAbacus *B = abacus_init( );

    check = abacus_set( B, "999" );

    if( !check )
    {
	printf("Set abacus B:\n");
	printf("\tnumber: %d\n", B->number );
	printf("\tpUpperRod: " );
	for( int32_t i = 0; i < B->number; i++ )
	{
	    printf("%d ", B->pUpperRod[i] );
	}
	printf("\n");
	printf("\tpLowerRod: " );
	for( int32_t i = 0; i < B->number; i++ )
	{
	    printf("%d ", B->pLowerRod[i] );
	}
	printf("\n\n");
    }

    printf("Print abacus B:\n\n");
    if( abacus_print( *B ) == -1 )
    {
	printf("Fail to print\n");
    }
    printf("\n--------------------\n\n");

    /* Abacus C */
    printf("Abacus C = A + B\n");
    sAbacus *C = abacus_init( );
    check = abacus_add( C, *A, *B );
    if( check == -1 )
    {
	printf("Fail\n");
    }
    else
    {
	abacus_print( *C );
    }

    printf("\n--------------------\n\n");

    /* Abacus D */
    printf("Abacus C = A - B\n");
    sAbacus *D = abacus_init( );
    check = abacus_del( D, *A, *B );
    if( check == -1 )
    {
	printf("Fail\n");
    }
    else
    {
	abacus_print( *D );
    }

    printf("\n");
    abacus_free( A );
    abacus_free( B );
    abacus_free( C );
    abacus_free( D );

    return 0;
}

#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#include"mystring.h"

int32_t Isdigit( char a )
{
    if( a >= '0' && a <= '9' )
    {
	return ( a - '0' );
    }
    else    return -1;
}

char *mystrchr(const char *s, int c)
{
    char *ptr = NULL;
    for( int32_t i = 0; i < strlen( s ); i++ )
    {
	if( ( int )s[i] == c )
	{
	    ptr = (char *)&s[i];
	    break;
	}
    }

    return ptr;
}

char *mystrrchr(const char *s, int c)
{
    char *ptr = NULL;
    for( int32_t i = 0; i < strlen( s ); i++ )
    {
	if( ( int )s[i] == c )
	{
	    ptr = (char *)&s[i];
	}
    }

    return ptr;
}

size_t mystrspn(const char *s, const char *accept)
{
    int32_t flag = 0;
    for( int32_t i = 0; i < strlen( s ); i++ )
    {
	flag = 0;
	for( int32_t j = 0; j < strlen( accept ); j++ )
	{
	    if( s[i] == accept[j] )
	    {
		flag = 1;
		break;
	    }
	}

	if( flag == 0 )	return i;
    }

    return -1; /*Needed to be checked */
}

size_t mystrcspn(const char *s, const char *reject)
{
    int32_t flag = 0;
    for( int32_t i = 0; i < strlen( s ); i++ )
    {
	flag = 0;
	for( int32_t j = 0; j < strlen( reject ); j++ )
	{
	    if( s[i] == reject[j] )
	    {
		flag = 1;
		break;
	    }
	}

	if( flag == 1 )	return i;
    }

    return -1; /*Needed to be checked */
}

char *mystrpbrk(const char *s, const char *accept)
{
    int32_t flag = 0;
    char *ptr = NULL;
    for( int32_t i = 0; i < strlen( s ); i++ )
    {
	flag = 0;
	for( int32_t j = 0; j < strlen( accept ); j++ )
	{
	    if( s[i] == accept[j] )
	    {
		flag = 1;
		break;
	    }
	}

	if( flag == 1 )
	{
	    ptr = (char *)&s[i];
	    break;
	}
    }

    return ptr; /*Needed to be checked */
}

char *mystrstr(const char *haystack, const char *needle)
{
    // NULL input
    if( !haystack || !needle )	return NULL;

    int32_t flag = 0;
    char *tmp = NULL;
    for( int32_t i = 0; i < strlen( haystack ); i++ )
    {
	for( int32_t j = 0; j < strlen( needle ); j++ )
	{
	    if( haystack[i+j] != needle[j] )	break;
	    if( j == strlen( needle ) - 1 )	flag = 1;
	}
	if( flag )
	{
	    tmp = (char*)&haystack[i];
	    break;
	}
    }

    return tmp;
}

char *DelimInPtr( char *ptr, const char *delim )
{
    if( !ptr || !delim )    return NULL;

    while( *ptr != 0 )
    {
	for( int32_t j = 0; j < strlen( delim ); j++ )
	{
	    if( *ptr == delim[j] )
	    {
		return ptr;
	    }
	}

	ptr += 1;
    }

    if( *ptr == 0 )
    {
	return ptr;
    }
    else	    return NULL;
}

char *mystrtok(char *str, const char *delim)
{
    if( !delim )    return NULL;

    static char *var = NULL;

    if( !str && *var == 0 )
    {
	return NULL;
    }

    if( str != NULL && !var )
    {
	var = str;
    }

    char *return_ptr = var;

    for( int32_t i = 0; i < strlen( var ); i++ )
    {
	char *tmp = DelimInPtr( var, delim );
	if( tmp )
	{
	    if( *tmp != 0 )
	    {
		var = tmp + 1;
		*tmp = 0;
	    }
	    else /* *tmp == 0 */
	    {
		var = tmp;
	    }
	    return return_ptr;
	}
    }

    return NULL;
}

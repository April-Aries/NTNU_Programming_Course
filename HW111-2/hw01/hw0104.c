#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#include"color.h"

/* functions */
int32_t key_cases( char *key );
int32_t search_case0( char *str, char *key, char **value );
int32_t search_case1( char *str, char *key, char **value );
int32_t search_case3( char *str, char *key, char **value );
bool isEmpty( char *key );

int main()
{
    /* Input JSON String */
    printf("Please enter the JSON string:\n");
    char *str = calloc( 8193, sizeof( char ) );
    fgets( str, 8192, stdin );
    if( str[ strlen( str ) - 1 ] == '\n' )
    {
	str[ strlen( str ) - 1 ] = 0;
    }

    /* Selections */
    while( 1 )
    {
	printf("Choice (0:Exit ,1: Get) : ");
	char *choice = calloc( 3, sizeof( char ) );
	fgets( choice, 2, stdin );
	if( choice[ strlen( choice ) - 1 ] == '\n' )
	{
	    choice[ strlen( choice ) - 1 ] = 0;
	}

	getchar();

	switch( choice[0] )
	{
	    case '0':
		printf("bye\n");
		return 0;
	    case '1':
		{
		    /* Get Key */
		    printf("Key: ");
		    char *key = calloc( 1001, sizeof( char ) );
		    fgets( key, 1000, stdin );
		    if( key[ strlen( key ) - 1 ] == '\n' )
		    {
			key[ strlen( key ) - 1 ] = 0;
		    }

		    if( isEmpty( key ) )
		    {
			printf("%sI cannot find such key!%s\n", TEXT_F_LRED, TEXT_DEFAULT );
			continue;
		    }

		    /* Main processing */
		    int32_t cases = key_cases( key );
		    char *value = calloc( 1001, sizeof( char ) );

		    switch( cases )
		    {
			case 0:
			    {
				int32_t num = search_case0( str, key, &value );

				if( num == 1 )	    continue;
				else		    break;
			    }
			case 1:
			    {
				int32_t num = search_case1( str, key, &value );

				if( num == 1 )	    continue;
				else		    break;
			    }
			case 2:
			    {
				int32_t num = search_case1( str, key, &value );

				if( num == 1 )	    continue;
				else		    break;

				break;
			    }
			case 3:
			    {
				int32_t num = search_case3( str, key, &value );

				if( num == 1 )	    continue;
				else		    break;

				break;
			    }
		    }

		    /* Print Value */
		    printf("Value: %s\n", value );

		    /* Break & free */
		    free( key );
		    free( value );
		    break;
		}
	    default:
		printf("\t\"%s\": Invalid Input! Please enter again\n", choice );
		break;
	}

	free( choice );
    }

    /* Free */
    free( str );

    return 0;
}

int32_t key_cases( char *key )
{
    int32_t flag = 0; // 0 -> normal case, 1 -> '.' cases, 2 -> array cases, 3 -> '.' and array cases
    for( int32_t i = 0; i < strlen( key ); i++ )
    {
	if( key[i] == '.' && flag == 0 )
	{
	    flag = 1;
	}
	else if( key[i] == '.' && flag == 2 )
	{
	    flag = 3;
	    break;
	}
	else if( key[i] == '[' && flag == 0 )
	{
	    flag = 2;
	}
	else if( key[i] == '[' && flag == 1 )
	{
	    flag = 3;
	    break;
	}
    }

    return flag;
}

int32_t search_case0( char *str, char *key, char **value )
{
    char *pos = strstr( str, key );
    char *value_tmp = *value;
    while( pos )
    {
	pos = strchr( pos, '\"');
	while( *pos != ':' && *pos != ',' && pos != NULL )
	{
	    pos += 1;
	}

	if( *pos == ',' )
	{
	    pos = strstr( pos, key );
	    continue;
	}
	else // *pos == ':' || pos == NULL
	{
	    break;
	}
    }

    if( !pos ) // pos == NULL
    {
	printf("%sI cannot find such key!%s\n", TEXT_F_LRED, TEXT_DEFAULT );
	return 1;
    }

    pos += 1;

    int32_t flag = 0; // 0 -> not yes, 1 -> '\"' case, 2 -> number case
    int32_t flag_ = 0;
    for( int32_t i = 0; *pos != ','; i++ )
    {
	/* When flag == 0 */
	if( flag == 0 && *pos == ' ' )
	{
	    i--;
	    pos += 1;
	    continue;
	}
	else if( flag == 0 && *pos == '\"' )
	{
	    flag = 1;
	    pos += 1;
	    i--;
	    continue;
	}
	else if( flag == 0 )
	{
	    flag = 2;
	    i--;
	    continue;
	}

	/* When flag != 0 */
	if( flag == 1 )
	{
	    if( *pos != '\"')
	    {
		*value_tmp = *pos;
		pos += 1;
		value_tmp += 1;
	    }
	    else
	    {
		break;
	    }
	}
	else if( flag == 2 )
	{
	    if( flag_ == 0 && *pos == ' ' )
	    {
		pos += 1;
		i--;
		continue;
	    }
	    else if( flag_ == 0 && *pos != ' ' )
	    {
		*value_tmp = *pos;
		pos += 1;
		flag_ = 1;
		value_tmp += 1;
	    }
	    else if( flag_ == 1 )
	    {
		*value_tmp = *pos;
		pos += 1;
		value_tmp += 1;
	    }
	}
    }

    return 0;
}


int32_t search_case1( char *str, char *key, char **value )
{
    char *substr = calloc( 1001, sizeof( char ) );
    char *subkey = calloc( strlen( key ), sizeof( char ) );

    for( int32_t i = 0; key[i] != '.' ;i++ )
    {
	subkey[i] = key[i];
    }

    char *pos = strstr( str, subkey );
    pos = strchr( pos, '{' );
    int32_t k = 0;
    for( k = 0; *pos != '}'; k++ )
    {
	substr[k] = *pos;
	pos += 1;
    }
    substr[k] = '}';

    for( int32_t i = 0; i < strlen( subkey ); i++ )
    {
	subkey[i] = 0;
    }

    pos = strchr( key, '.' );
    pos += 1;
    char *tmp = subkey;
    for( int32_t i = 0; *pos != 0; i++ )
    {
	*tmp = *pos;
	pos += 1;
	tmp += 1;
    }
    *tmp = 0;

    int32_t num = search_case0( substr, subkey, value );

    free( substr );
    free( subkey );

    if( num == 1 )	    return 1;
    else if( num == 2 )	    return 2;
    else		    return 2;
}

int32_t search_case3( char *str, char *key, char **value )
{
    char *substr = calloc( 1001, sizeof( char ) );
    char *subkey = calloc( strlen( key ), sizeof( char ) );

    for( int32_t i = 0; key[i] != '[' ;i++ )
    {
	subkey[i] = key[i];
    }

    char *pos = strstr( str, subkey );
    char *tmp = pos;

    for( int32_t i = 0; i < strlen( subkey ); i++ )
    {
	subkey[i] = 0;
    }

    pos = strchr( key, '[' );
    pos += 1;
    int32_t index = 0;
    while( *pos != ']' )
    {
	index = index * 10 + (int32_t)( *pos - '0' );
	pos += 1;
    }

    pos = tmp;
    for( int32_t i = 0; i < index; i++ )
    {
	pos = strchr( pos, '}' );
    }

    pos = strchr( pos, '{' );
    int32_t k = 0;
    for( k = 0; *pos != '}'; k++ )
    {
	substr[k] = *pos;
	pos += 1;
    }
    substr[k] = '}';

    for( int32_t i = 0; i < strlen( subkey ); i++ )
    {
	subkey[i] = 0;
    }

    pos = strchr( key, '.' );
    pos += 1;
    tmp = subkey;
    for( int32_t i = 0; *pos != 0; i++ )
    {
	*tmp = *pos;
	pos += 1;
	tmp += 1;
    }
    *tmp = 0;

    int32_t num = search_case0( substr, subkey, value );

    free( substr );
    free( subkey );

    if( num == 1 )	    return 1;
    else if( num == 2 )	    return 2;
    else		    return 2;
}

bool isEmpty( char *key )
{
    for( int32_t i = 0; i < strlen(key); i++ )
    {
	if( key[i] != ' ' ) return false;
    }

    return true;
}

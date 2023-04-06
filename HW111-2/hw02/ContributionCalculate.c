#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#include "ContributionCalculate.h"
#include "list.h"

/* Functions I need here */
char* month_transform( char *month_str );
bool IsCommit( char *str );
void clean_str( char *str );
void read_data( FILE *pFile, data *header, data **last, data **last2 );
bool commit_match( const char *hashVal, data *recent_data );

void searchCommitInformationByHashVal(const char *hashVal)
{
    /* Error Check */
    if( hashVal == NULL )
    {
	printf("hashVal is NULL!\n");
	return;
    }

    /* Open file */
    FILE *pFile = NULL;

    if( ( pFile = fopen( "frontend.txt", "r" ) ) == NULL )
    {
	perror("File cannot be open!\nReason: ");
	return;
    }

    /* Open file 2 to write */
    FILE *pFile2 = NULL;

    if( ( pFile2 = fopen( "contribution.txt", "a" ) ) == NULL )
    {
	perror("File cannot be open!\nReason: ");
	return;
    }

    /* Allocate header and first node */
    data *node = node_init( );
    data *header = node;
    data *last = NULL;
    data *last2 = NULL;

    /* Read data in file, store into memory */
    read_data( pFile, node, &last, &last2 );

    /* Find data with given commit */
    data *recent_data = header;
    data *record = NULL;
    int32_t count = 0;
    while( recent_data )
    {
	if( commit_match( hashVal, recent_data ) )
	{
	    count++;
	    record = recent_data;
	}
	recent_data = recent_data->link;
    }

    if( count == 0 )	    fprintf( pFile2, "(%s) Not found\n\n", hashVal );
    else if( count >= 2 )   fprintf( pFile2, "(%s) More than two results\n\n", hashVal );
    else // count == 1
    {
	fprintf( pFile2, "(%s)\n", hashVal );
	fprintf( pFile2, "- %s\n", record->author );
	fprintf( pFile2, "\t- %s\n", record->mail );
	fprintf( pFile2, "\t- %s/%s/%s/%s:%s:%s\n", record->year, record->month, record->date, record->hour, record->min, record->sec );

	if( record->file_change == 1 )	fprintf( pFile2, "\t- %d file changed\n", record->file_change );
	else				fprintf( pFile2, "\t- %d files changed\n", record->file_change );

	if( record->insertion == 1 )	fprintf( pFile2, "\t- %d insertion\n", record->insertion );
	else				fprintf( pFile2, "\t- %d insertions\n", record->insertion);

	if( record->deletion == 1 )	fprintf( pFile2, "\t- %d deletion\n\n", record->deletion );
	else			        fprintf( pFile2, "\t- %d deletions\n\n", record->deletion );
    }

    /* Close file & Free memory */
    fclose( pFile );
    fclose( pFile2 );
    list_free( header );

    return;
}

void searchMonthlyContribution(const char *monthAbbrev)
{
    /* Error Check */
    if( monthAbbrev == NULL )
    {
	printf("hashVal is NULL!\n");
	return;
    }

    /* monthAbbrev str -> integer & check */
    int32_t month_num = 0;
    if     ( !strncmp( monthAbbrev, "Jan", 3 ) )   month_num = 1;
    else if( !strncmp( monthAbbrev, "Feb", 3 ) )   month_num = 2;
    else if( !strncmp( monthAbbrev, "Mar", 3 ) )   month_num = 3;
    else if( !strncmp( monthAbbrev, "Apr", 3 ) )   month_num = 4;
    else if( !strncmp( monthAbbrev, "May", 3 ) )   month_num = 5;
    else if( !strncmp( monthAbbrev, "Jun", 3 ) )   month_num = 6;
    else if( !strncmp( monthAbbrev, "Jul", 3 ) )   month_num = 7;
    else if( !strncmp( monthAbbrev, "Aug", 3 ) )   month_num = 8;
    else if( !strncmp( monthAbbrev, "Sep", 3 ) )   month_num = 9;
    else if( !strncmp( monthAbbrev, "Oct", 3 ) )   month_num = 10;
    else if( !strncmp( monthAbbrev, "Nov", 3 ) )   month_num = 11;
    else if( !strncmp( monthAbbrev, "Dec", 3 ) )   month_num = 12;
    else
    {
	printf("Not a legal monthAbbrev!\n");
	return;
    }

    /* Open file */
    FILE *pFile = NULL;

    if( ( pFile = fopen( "frontend.txt", "r" ) ) == NULL )
    {
	perror("File cannot be open!\nReason: ");
	return;
    }

    /* Open file 2 to write */
    FILE *pFile2 = NULL;

    if( ( pFile2 = fopen( "contribution.txt", "a" ) ) == NULL )
    {
	perror("File cannot be open!\nReason: ");
	return;
    }

    /* Allocate header and first node */
    data *node = node_init( );
    data *header = node;
    data *last = NULL;
    data *last2 = NULL;

    /* Read data in file, store into memory */
    read_data( pFile, node, &last, &last2 );

    /* Find data with given month */
    data *recent_data = header;
    data *node_month = node_init( );
    data *header_month = node_month;
    while( recent_data )
    {
	int32_t num = 0;
	if	( !strncmp( recent_data->month, "10", 3 ) )   num = 10;
	else if	( !strncmp( recent_data->month, "11", 3 ) )   num = 11;
	else if	( !strncmp( recent_data->month, "12", 3 ) )   num = 12;
	else if	( !strncmp( recent_data->month, "1",  1 ) )   num = 1;
	else if	( !strncmp( recent_data->month, "2",  1 ) )   num = 2;
	else if	( !strncmp( recent_data->month, "3",  1 ) )   num = 3;
	else if	( !strncmp( recent_data->month, "4",  1 ) )   num = 4;
	else if	( !strncmp( recent_data->month, "5",  1 ) )   num = 5;
	else if	( !strncmp( recent_data->month, "6",  1 ) )   num = 6;
	else if	( !strncmp( recent_data->month, "7",  1 ) )   num = 7;
	else if	( !strncmp( recent_data->month, "8",  1 ) )   num = 8;
	else if	( !strncmp( recent_data->month, "9",  1 ) )   num = 9;

	int32_t flag = 0;
	data *record = header_month;
	while( record )
	{
	    if( strncmp( record->author, recent_data->author, strlen( recent_data->author ) ) == 0 )
	    {
		flag = 1;
		break;
	    }
	    else
	    {
		record = record->link;
	    }
	}

	if( flag == 1 && month_num == num )
	{
	    record->commit_num += 1;
	    record->file_change += recent_data->file_change;
	    record->insertion   += recent_data->insertion  ;
	    record->deletion    += recent_data->deletion   ;
	}
	else if( flag == 0 )
	{
	    data *next_node = node_init( );
	    node_month->link = next_node;
	    strncpy( node_month->author, recent_data->author, strlen( recent_data->author ) );

	    if( month_num == num )
	    {
		node_month->commit_num += 1;
		node_month->file_change = recent_data->file_change;
		node_month->insertion   = recent_data->insertion  ;
		node_month->deletion    = recent_data->deletion   ;
	    }

	    last2 = node_month;
	    node_month = next_node;
	}

	recent_data = recent_data->link;
    }

    node_free( node_month );
    last2->link = NULL;

    node_month = header_month;

    /* Print result */
    fprintf( pFile2, "(%s)\n", monthAbbrev );

    while( node_month )
    {
	fprintf( pFile2, "- %s\n", node_month->author );
	if( node_month->commit_num == 1 )
	{
	    fprintf( pFile2, "\t- 1 commit\n" );
	}
	else
	{
	    fprintf( pFile2, "\t- %d commits\n", node_month->commit_num );
	}

	if( node_month->file_change == 1 )
	{
	    fprintf( pFile2, "\t- 1 file changed\n" );
	}
	else
	{
	    fprintf( pFile2, "\t- %d files changed\n", node_month->commit_num );
	}
	if( node_month->insertion == 1 )
	{
	    fprintf( pFile2, "\t- 1 insertion\n" );
	}
	else
	{
	    fprintf( pFile2, "\t- %d insertions\n", node_month->insertion );
	}
	if( node_month->deletion == 1 )
	{
	    fprintf( pFile2, "\t- 1 deletion\n\n" );
	}
	else
	{
	    fprintf( pFile2, "\t- %d deletions\n\n", node_month->deletion );
	}

	node_month = node_month->link;
    }

    /* Close file & Free memory */
    fclose( pFile );
    fclose( pFile2 );
    list_free( header );

    return;
}

char* month_transform( char *month_str )
{
    char *month = calloc( 3, sizeof( char ) );

    if     ( !strncmp( month_str, "Jan", 3 ) )   month = "1";
    else if( !strncmp( month_str, "Feb", 3 ) )   month = "2";
    else if( !strncmp( month_str, "Mar", 3 ) )   month = "3";
    else if( !strncmp( month_str, "Apr", 3 ) )   month = "4";
    else if( !strncmp( month_str, "May", 3 ) )   month = "5";
    else if( !strncmp( month_str, "Jun", 3 ) )   month = "6";
    else if( !strncmp( month_str, "Jul", 3 ) )   month = "7";
    else if( !strncmp( month_str, "Aug", 3 ) )   month = "8";
    else if( !strncmp( month_str, "Sep", 3 ) )   month = "9";
    else if( !strncmp( month_str, "Oct", 3 ) )   month = "10";
    else if( !strncmp( month_str, "Nov", 3 ) )   month = "11";
    else if( !strncmp( month_str, "Dec", 3 ) )   month = "12";

    return month;
}

bool IsCommit( char *str )
{
    if( !str || strlen( str ) < 7 ) return false;
    if( str[0] == 'c' && str[1] == 'o' && str[2] == 'm' && str[3] == 'm' && str[4] == 'i' && str[5] == 't' && str[6] == ' ' )
    {
	return true;
    }
    else
    {
	return false;
    }
}

void clean_str( char *str )
{
    for( int32_t i = 0; i < strlen( str ); i++ )    str[i] = 0;

    return;
}

bool IsDigit( char a )
{
    if( a >= '0' && a <= '9' )	return true;
    else			return false;
}

void read_data( FILE *pFile, data *header, data **last, data **last2 )
{
    data *node = header;
    char *str = calloc( 1001, sizeof( char ) );
    fscanf( pFile, "%[^\n]%*c", str );
    while( !feof( pFile ) )
    {
	if( IsCommit( str ) )
	{
	    data *next_node = node_init( );
	    node->link = next_node;
	    *last = next_node;
	    *last2 = node;

	    char *tmp = NULL;

	    /* commit */
	    tmp = strchr( str, ' ' );
	    tmp += 1;
	    for( int32_t i = 0; *tmp != 0 && i < 8; i++ )
	    {
		node->commit[i] = *tmp;
		tmp += 1;
	    }

	    clean_str( str );

	    /* Author & mail */
	    int32_t merge_flag = 0;
	    fscanf( pFile, "%[^\n]%*c", str );
	    if( str[0] == 'M' && str[1] == 'e' )
	    {
		clean_str( str );
		merge_flag = 1;
		fscanf( pFile, "%[^\n]%*c", str );
	    }
	    tmp = strchr( str, ':' );
	    tmp += 2;
	    for( int32_t i = 0; *tmp != '<'; i++ )
	    {
		node->author[i] = *tmp;
		tmp += 1;
	    }

	    tmp += 1;
	    for( int32_t i = 0; *tmp != '>'; i++ )
	    {
		node->mail[i] = *tmp;
		tmp += 1;
	    }

	    clean_str( str );

	    /* Time */
	    fscanf( pFile, "%[^\n]%*c", str );
	    tmp = strchr( str, ':' );
	    tmp += 1;
	    while( *tmp == ' ' )    tmp += 1;

	    for( int32_t i = 0; *tmp != ' '; i++ )	     {	tmp += 1;			    } // day
	    tmp += 1;

	    char *month_tmp = calloc( 4, sizeof( char ) );
	    for( int32_t i = 0; *tmp != ' ' && i < 4; i++ )  {	month_tmp[i] = *tmp;	tmp += 1;   } // month
	    tmp += 1;

	    // Month transform
	    char *month_tmp2 = month_transform( month_tmp );
	    strncpy( node->month, month_tmp2, 2 );
	    free( month_tmp );

	    for( int32_t i = 0; *tmp != ' ' && i < 3; i++ )  {	node->date[i]  = *tmp;  tmp += 1;   } // date
	    tmp += 1;
	    for( int32_t i = 0; *tmp != ':' && i < 3; i++ )  {	node->hour[i]  = *tmp;  tmp += 1;   } //hour
	    tmp += 1;
	    for( int32_t i = 0; *tmp != ':' && i < 3; i++ )  {	node->min[i]   = *tmp;	tmp += 1;   } // min
	    tmp += 1;
	    for( int32_t i = 0; *tmp != ' ' && i < 3; i++ )  {	node->sec[i]   = *tmp;	tmp += 1;   } // sec
	    tmp += 1;
	    for( int32_t i = 0; *tmp != ' ' && i < 5; i++ )  {	node->year[i]  = *tmp;  tmp += 1;   } // year

	    clean_str( str );

	    /* Change */
	    if( merge_flag == 1 )
	    {
		node = node->link;
		fscanf( pFile, "%[^\n]%*c", str );
	    }
	    else
	    {
		fscanf( pFile, "%[^\n]%*c", str );

		while( strstr( str, "file changed" ) == NULL && strstr( str, "files changed" ) == NULL )
		{
		    fscanf( pFile, "%[^\n]%*c", str );
		}

		if( ( tmp = strstr( str, "file changed" ) ) != NULL )
		{
		    node->file_change = 1;
		}
		else if( ( tmp = strstr( str, "files changed" ) ) != NULL )
		{
		    tmp -= 2;
		    while( IsDigit( *tmp ) )    tmp -= 1;
		    tmp += 1;

		    while( IsDigit( *tmp ) )
		    {
			node->file_change = node->file_change * 10 + ( *tmp - '0' );
			tmp += 1;
		    }
		}

		if( ( tmp = strstr( str, "insertion(+)" ) ) != NULL )
		{
		    node->insertion = 1;
		}
		else if( ( tmp = strstr( str, "insertions(+)" ) ) != NULL )
		{
		    tmp -= 2;
		    while( *tmp != ' ' )    tmp -= 1;
		    tmp += 1;

		    while( IsDigit( *tmp ) )
		    {
			node->insertion = node->insertion * 10 + ( *tmp - '0' );
			tmp += 1;
		    }
		}

		if( ( tmp = strstr( str, "deletion(-)" ) ) != NULL )
		{
		    node->deletion = 1;
		}
		else if( ( tmp = strstr( str, "deletions(-)" ) ) != NULL )
		{
		    tmp -= 2;
		    while( *tmp != ' ' )    tmp -= 1;
		    tmp += 1;

		    while( IsDigit( *tmp ) )
		    {
			node->deletion = node->deletion * 10 + ( *tmp - '0' );
			tmp += 1;
		    }
		}

		clean_str( str );

		//test 
		//node_print( node );

		node = node->link;
		fscanf( pFile, "%[^\n]%*c", str );
	    }
	}
	else
	{
	    clean_str( str );
	    fscanf( pFile, "%[^\n]%*c", str );
	    continue;
	}
    }

    node_free( *last );
    ( *last2 )->link = NULL;
    free( str );
}

bool commit_match( const char *hashVal, data *recent_data )
{
    bool flag = true;
    
    for( int32_t i = 0; i < 8; i++ )
    {
	if( hashVal[i] != recent_data->commit[i] )
	{
	    flag = false;
	    break;
	}
    }

    return flag;
}

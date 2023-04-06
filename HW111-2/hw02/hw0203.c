#define _GNU_SOURCE

#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include<error.h>

int main()
{
    /* Input target */
    printf("Please enter the search target: ");
    char *target = calloc( 1024, sizeof( char ) );
    
    if(fgets(target, 1024, stdin) == NULL )
    {
	perror("Invalid!! ");
	return 0;
    }
    
    if( target[ strlen( target ) - 1 ] == '\n' )
    {
	target[ strlen( target ) - 1 ] = 0;
    }
    
    /* open file */
    FILE *pFile = NULL;
    if( ( pFile = fopen( "bible.txt" , "r" ) ) == NULL )
    {
	perror( "Error: " );
	return 0;
    }
    
    //parameters
    int32_t index = 0;
    char *id = malloc(10);
    int32_t chapter = 0;
    int32_t verse = 0;
    char *sentence = calloc( 1024, sizeof( char ) );
    char *t_id = malloc( 10 );
    char *name = malloc( 10 );

    /* Find how many times does the target is found */
    while( !feof( pFile ) )
    {
	/* read file */
	fscanf( pFile, "{\"chapter\":%d,\"verse\":%d,\"text\":\"%[^\"]\",\"translation_id\":\"%[^\"]\",\"book_id\":\"%[^\"]\",\"book_name\":\"%[^\"]\"}\n", &chapter, &verse, sentence, t_id, id, name );
    
	/* Find matched words and print */
	if( strcasestr(sentence, target) != NULL )
	{
	    index++;
	}
    }

    if( index == 0 )
    {
	printf("Not found\n");
	return 0;
    }
    else if( index == 1 )
    {
	printf("Found 1 time\n");
    }
    else
    {
	printf("Found %d times\n", index );
    }

    rewind( pFile );
    index = 0;

    /* Find target in the file */
    while( !feof( pFile ) )
    {
	/* read file */
	fscanf( pFile, "{\"chapter\":%d,\"verse\":%d,\"text\":\"%[^\"]\",\"translation_id\":\"%[^\"]\",\"book_id\":\"%[^\"]\",\"book_name\":\"%[^\"]\"}\n", &chapter, &verse, sentence, t_id, id, name );
	
	/* Find matched words and print */
	if( strcasestr(sentence, target) != NULL )
	{
	    index++;
	    printf("%d. %s %d:%d %s\n", index, id, chapter, verse, sentence);
	    fflush(stdout);
	}
	
	/* Reset Parameters */
	for(int32_t i = 0; i < 10; i++)
	{
	    id[i] = 0;
	    t_id[i] = 0;
	    name[i] = 0;
	}
	
	for(int32_t i = 0; i <1024; i++)
	{
	    sentence[i] = 0;
	}
		
	verse = 0;
	chapter = 0;
    }
    
    /* free and close file */
    free( target );
    free( id );
    free( sentence );
    free( t_id );
    free( name );
    
    fclose( pFile );
    
    return 0;
}

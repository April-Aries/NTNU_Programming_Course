#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include"mystring.h"

int main()
{
    const char  *str = "I have an apple.";

    int c = 'a';

    printf( "str: \"%s\"\n", str );
    printf( "strchr( str, c ) = %s\n", strchr( str, c ) );
    printf( "> mystrchr( str, c ) = %s\n", mystrchr( str, c ) );
    printf( "location is %ld\n", strchr( str, c ) - str );
    printf( "> mylocation is %ld\n", mystrchr( str, c ) - str );
    printf( "strrchr( str, c ) = %s\n", strrchr( str, c ) );
    printf( "> mystrrchr( str, c ) = %s\n", mystrrchr( str, c ) );
    printf( "location is %ld\n", strrchr( str, c ) - str );
    printf( "> mylocation is %ld\n", mystrrchr( str, c ) - str );

    printf( "\n" );

    const char  *str2 = "the value of pi is 3.14";
    const char  *accept = "abcdefghijklmnopqrstuvwxyz";
    const char  *reject = "0123456789";
    const char  *accept2 = "abc";

    printf( "str2: \"%s\"\n", str2 );
    printf( "accept: \"%s\"\n", accept );
    printf( "reject: \"%s\"\n", reject );
    printf( "accept2: \"%s\"\n", accept2 );

    printf( "strspn( str2, accept ) = %ld\n", strspn( str2, accept ) );
    printf( "> mystrspn( str2, accept ) = %ld\n", mystrspn( str2, accept ) );
    printf( "strcspn( str2, reject ) = %ld\n", strcspn( str2, reject ) );
    printf( "> mystrcspn( str2, reject ) = %ld\n", mystrcspn( str2, reject ) );
    printf( "strpbrk( str2, accept2 ) = %c, which is in %ld\n", *( strpbrk( str2, accept2 ) ), strpbrk( str2, accept2 ) - str2 );
    printf( "> mystrpbrk( str2, accept2 ) = %c, which is in %ld\n", *( mystrpbrk( str2, accept2 ) ), mystrpbrk( str2, accept2 ) - str2 );

    printf( "\n" );

    const char  *needle = "pi";

    printf( "needle: \"%s\"\n", needle );
    printf( "strstr( str2, needle ): %s\n", strstr( str2, needle ) );
    printf( "> mystrstr( str2, needle ): %s\n", mystrstr( str2, needle ) );

    printf( "\n" );

    char    str3[] = "the value of pi is 3.14";
    char    *token = strtok( str3, " " );
    int32_t i = 0;

    while( token != NULL )
    {
        printf( "%d: (%p) %s\n", i, token, token );
        token = strtok( NULL, " " );
        i++;
    }

    printf( "\n" );

    char    str4[] = "the value of pi is 3.14";
    char    *mytoken = mystrtok( str4, " " );
    i = 0;

    while( mytoken != NULL )
    {
        printf( "%d: (%p) %s\n", i, mytoken, mytoken );
        mytoken = mystrtok( NULL, " " );
        i++;
    }

    return 0;
}

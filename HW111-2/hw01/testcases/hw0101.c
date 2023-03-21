// hw0101.c
#include "mystring.h"
#include <stdio.h>

#include<string.h>

int main() {
    char str1[] = "Hello world";
    char str2[] = "banana";
    char str3[] = "This is a string";
    char *result;
    char *result2;

    // Test mystrchr
    result2 = strchr(str1, 'o');
    printf("strchr  : %s\n", result2);
    result = mystrchr(str1, 'o');
    printf("mystrchr: %s\n", result);

    // Test mystrrchr
    result2 = strrchr(str1, 'l');
    printf("strrchr: %s\n", result2);
    result = mystrrchr(str1, 'l');
    printf("mystrrchr: %s\n", result);

    // Test mystrspn
    size_t len2 = strspn(str2, "an");
    printf("strspn: %lu\n", len2);
    size_t len = mystrspn(str2, "an");
    printf("mystrspn: %lu\n", len);

    // Test mystrcspn
    len2 = strcspn(str2, "n");
    printf("strcspn: %lu\n", len2);
    len = mystrcspn(str2, "n");
    printf("mystrcspn: %lu\n", len);

    // Test mystrpbrk
    result2 = strpbrk(str2, "na");
    printf("strpbrk: %s\n", result2);
    result = mystrpbrk(str2, "na");
    printf("mystrpbrk: %s\n", result);

    // Test mystrstr
    result2 = strstr(str3, "is");
    printf("strstr: %s\n", result2);
    result = mystrstr(str3, "is");
    printf("mystrstr: %s\n", result);

    // Test mystrtok
    char str4[] = "This is a string";
    char *token2 = strtok(str4, " ");
    while(token2 != NULL) {
        printf("strtok: %s\n", token2);
        token2 = strtok(NULL, " ");
    }
    char *token = mystrtok(str3, " ");
    while(token != NULL) {
        printf("mystrtok: %s\n", token);
        token = mystrtok(NULL, " ");
    }

    return 0;
}

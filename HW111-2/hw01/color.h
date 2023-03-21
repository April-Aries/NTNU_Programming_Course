# pragma once

#include<stdio.h>
#include<stdint.h>

//default
#define TEXT_DEFAULT "\x1B[0m"

//front color
#define TEXT_F_BLACK "\x1B[30m"
#define TEXT_F_RED "\x1B[31m"
#define TEXT_F_GREEN "\x1B[32m"
#define TEXT_F_YELLOW "\x1B[33m"
#define TEXT_F_BLUE "\x1B[34m"
#define TEXT_F_PINK "\x1B[35m"
#define TEXT_F_QING "\x1B[36m"
#define TEXT_F_WHITE "\x1B[37m"
#define TEXT_F_GRAY "\x1B[90m"
#define TEXT_F_LRED "\x1B[91m"
#define TEXT_F_LGREEN "\x1B[92m"
#define TEXT_F_LYELLOW "\x1B[93m"
#define TEXT_F_LBLUE "\x1B[94m"
#define TEXT_F_LPINK "\x1B[95m"
#define TEXT_F_LQING "\x1B[96m"
#define TEXT_F_LWHITE "\x1B[97m"

//background color
#define TEXT_B_BLACK "\x1B[40m"
#define TEXT_B_RED "\x1B[41m"
#define TEXT_B_GREEN "\x1B[42m"
#define TEXT_B_YELLOW "\x1B[43m"
#define TEXT_B_BLUE "\x1B[44m"
#define TEXT_B_PINK "\x1B[45m"
#define TEXT_B_QING "\x1B[46m"
#define TEXT_B_WHITE "\x1B[47m"
#define TEXT_B_GRAY "\x1B[100m"
#define TEXT_B_LRED "\x1B[101m"
#define TEXT_B_LGREEN "\x1B[102m"
#define TEXT_B_LYELLOW "\x1B[103m"
#define TEXT_B_LBLUE "\x1B[104m"
#define TEXT_B_LPINK "\x1B[105m"
#define TEXT_B_LQING "\x1B[106m"
#define TEXT_B_LWHITE "\x1B[107m"

// Others
#define TEXT_BOLD "\x1B[1m"
#define TEXT_ITALIC "\x1B[3m"
#define TEXT_UNDERLINE "\x1B[4m"
#define TEXT_FLASH "\x1B[5m"
#define TEXT_FLASH_FAST "\x1B[6m"
// #define TEXT_FRAME "\x1B[51m"
// #define TEXT_ENCIRCLED "\x1B[52m"

/*
To make colorful word -> Do as following
Example: print front color red word
Note: Turn this back to original word!
printf("%sXXX%s", F_RED, F_WHITE);
*/
/**
 * @file 将输入变为大写
 */

#include <stdio.h>
#include <ctype.h>

int main(void)
{
    int ch;
    while((ch = getchar()) != EOF) {
        putchar(toupper(ch));
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
void fpusWithInfo(char *string, FILE *fp)
{
    fputs(string, fp);
    printf("%s", string);
}
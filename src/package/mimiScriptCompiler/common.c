#include <stdio.h>
#include <stdlib.h>
FILE *fpNow = NULL;
void fpusWithInfo(char *string, FILE *fp)
{
    fputs(string, fp);
    printf("%s", string);
}
#include <stdio.h>
#include <stdlib.h>
#include "MimiObj.h"
#include "dataStrs.h"

static char * getMimiscriptPythonApiText(char * filePath)
{
    FILE *f = fopen(filePath, "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);  /* same as rewind(f); */
    char *pyText = malloc(fsize + 1);
    fread(pyText, 1, fsize, f);
    fclose(f);
    pyText[fsize] = 0;
    return pyText;
}

void compiler_build(MimiObj *self, char *pythonApiPath)
{
    Args *buffs = New_args(NULL);
    char *pyText = strsCopy(buffs, getMimiscriptPythonApiText(pythonApiPath));
    printf("%s\r\n", pyText);
}
#include <stdio.h>
#include <stdlib.h>
#include "sysObj.h"
#include "MimiObj.h"

char * getMimiscriptPythonApiText(char * filePath)
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

int main()
{
    char * pyText = getMimiscriptPythonApiText("../mimiscript-python-api/mimiscript-api.py");
    printf("%s\r\n", pyText);
    return 0;
}

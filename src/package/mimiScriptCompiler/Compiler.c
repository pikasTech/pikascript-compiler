#include <stdio.h>
#include <stdlib.h>
#include "MimiObj.h"
#include "dataStrs.h"

static char *getMimiscriptPythonApiText(char *filePath)
{
    FILE *f = fopen(filePath, "rb");
    if (NULL == f)
    {
        return NULL;
    }
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET); /* same as rewind(f); */
    char *pyText = malloc(fsize + 1);
    fread(pyText, 1, fsize, f);
    fclose(f);
    pyText[fsize] = 0;
    return pyText;
}

static void analizePass(MimiObj *self, char *line, Args *buffs)
{
}

static void analizeClass(MimiObj *self, char *line, Args *buffs)
{
    char *classSentence = strsRemovePrefix(buffs, line, "class ");
    printf("\tclassSentence: %s\r\n", classSentence);
    char *superClassName = strsCut(buffs, classSentence, '(', ')');
    printf("\tsuperClassName: %s\r\n", superClassName);
}

static void analizeDef(MimiObj *self, char *line, Args *buffs)
{
}

static void analizeLine(MimiObj *self, char *line)
{
    Args *buffs = New_args(NULL);
    if (strIsStartWith(line, "class "))
    {
        return analizeClass(self, line, buffs);
    }

    if (strIsStartWith(line, "    def "))
    {
        return analizeDef(self, line, buffs);
    }

    if (strIsStartWith(line, "        pass"))
    {
        return analizePass(self, line, buffs);
    }
}

void compiler_build(MimiObj *self, char *pythonApiPath)
{
    Args *buffs = New_args(NULL);
    char *pyTextFromFile = getMimiscriptPythonApiText(pythonApiPath);
    if (NULL == pyTextFromFile)
    {
        printf("[error] compiler: load file faild\r\n");
        return;
    }
    char *pyTextBuff = strsCopy(buffs, pyTextFromFile);
    free(pyTextFromFile);
    int lineNum = strCountSign(pyTextBuff, '\n');
    for (int i = 0; i < lineNum; i++)
    {
        char *line = strsPopToken(buffs, pyTextBuff, '\n');
        printf("line %d: %s\r\n", i, line);
        analizeLine(self, line);
    }
}
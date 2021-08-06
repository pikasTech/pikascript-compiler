#include <stdio.h>
#include <stdlib.h>
#include "baseObj.h"
#include "dataStrs.h"
#include "PyMethodClass.h"

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

static void printInfo(char *argName, char *argVal)
{
    printf("\t\t[info] %s: \"%s\"\r\n", argName, argVal);
}

static void analizePass(MimiObj *self, char *line, Args *buffs)
{
    obj_setStr(self, "currentClassName", "(none)");
}

static void analizeClass(MimiObj *self, char *line, Args *buffs)
{
    char *classSentenceWithBlock = strsRemovePrefix(buffs, line, "class ");
    char *classSentence = strsDeleteChar(buffs, classSentenceWithBlock, ' ');
    printInfo("classSentence", classSentence);
    char *className = strsGetFirstToken(buffs, classSentence, '(');
    printInfo("className", className);
    obj_newObj(self, className, "PyClass");

    char *superClassName = strsCut(buffs, classSentence, '(', ')');
    printInfo("superClassName", superClassName);
    obj_setStr(self, strsAppend(buffs, className, ".superClassName"), superClassName);
    obj_setStr(self, "currentClassName", className);
}

static void analizeDef(MimiObj *self, char *line, Args *buffs)
{
    char *currentClassName = obj_getStr(self, "currentClassName");
    printInfo("currentClassName", currentClassName);
    char *defSentenceWithBlock = strsRemovePrefix(buffs, line, "    def ");
    char *defSentence = strsDeleteChar(buffs, defSentenceWithBlock, ' ');
    printInfo("defSentence", defSentence);
    char *methodName = strsGetFirstToken(buffs, defSentence, '(');
    printInfo("methodName", methodName);
    char *methodObjPath = strsAppend(buffs, strsAppend(buffs, currentClassName, "."), methodName);
    printInfo("methodObjPath", methodObjPath);
    obj_newObj(self, methodObjPath, "PyMethod");
    char *returnType = strsCut(buffs, defSentence, '>', ':');
    printInfo("returnType", returnType);
    obj_setStr(self, strsAppend(buffs, methodObjPath, ".returnType"), returnType);

    char *typeList = strsCut(buffs, defSentence, '(', ')');
    printInfo("typeList", typeList);
    int argNum = strCountSign(typeList, ',') + 1;
    for (int i = 0; i < argNum; i++)
    {
        char *typeDeclearation = strsPopToken(buffs, typeList, ',');
        printInfo("typeDeclearation", typeDeclearation);
        char *argName = strsGetFirstToken(buffs, typeDeclearation, ':');
        printInfo("argName", argName);
        char *argType = strsGetLastToken(buffs, typeDeclearation, ':');
        printInfo("argType", argType);
        obj_setStr(self,
                   strAppend(strsAppend(buffs,
                                        methodObjPath,
                                        "."),
                             argName),
                   argType);
    }
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
        printf("|%d|>>>%s\r\n", i, line);
        analizeLine(self, line);
    }
}
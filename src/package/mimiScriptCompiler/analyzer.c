#include "MimiObj.h"
#include "BaseObj.h"
#include <stdio.h>
#include <stdlib.h>
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

static void msc_analizePass(MimiObj *self, char *line, Args *buffs)
{
}

static void msc_analizeNew(MimiObj *self, char *line, Args *buffs)
{
    char *cleanLine = strsDeleteChar(buffs, line, ' ');
    char *currentClassName = obj_getStr(self, "currentClassName");
    char *pyObjName = strsGetFirstToken(buffs, cleanLine, '=');
    char *pyClassName = strsCut(buffs, cleanLine, '=', '(');

    printInfo("cleanLine", cleanLine);
    printInfo("currentClassName", currentClassName);
    printInfo("pyObjName", pyObjName);
    printInfo("pyClassName", pyClassName);

    char *pyObjPath = strsAppend(buffs, strsAppend(buffs, currentClassName, "._new_"), pyObjName);
    char *pyClassPath = strsAppend(buffs, strsAppend(buffs, pyObjPath, "."), "class");
    char *pyNamePath = strsAppend(buffs, strsAppend(buffs, pyObjPath, "."), "name");
    printInfo("pyObjPath", pyObjPath);
    printInfo("pyClassPath", pyClassPath);
    printInfo("pyNamePath", pyNamePath);

    obj_newObj(self, pyObjPath, "PyObj");
    obj_setStr(self, pyClassPath, pyClassName);
    obj_setStr(self, pyNamePath, pyObjName);
}

static void msc_analizeClass(MimiObj *self, char *line, Args *buffs)
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

static void msc_analizeDef(MimiObj *self, char *line, Args *buffs)
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
    /* init methodObjPath object directly */
    obj_getObj(self, methodObjPath, 0);
    char *returnType = strsCut(buffs, defSentence, '>', ':');
    printInfo("returnType", returnType);
    if (NULL != returnType)
    {
        obj_setStr(self, strsAppend(buffs, methodObjPath, ".returnType"), returnType);
    }

    char *typeList = strsCut(buffs, defSentence, '(', ')');
    printInfo("typeList", typeList);
    if (0 == strGetSize(typeList))
    {
        return;
    }
    obj_setStr(self, strsAppend(buffs, methodObjPath, ".typeList"), typeList);
    int argNum = strCountSign(typeList, ',') + 1;
    for (int i = 0; i < argNum; i++)
    {
        char *typeDeclearation = strsPopToken(buffs, typeList, ',');
        printInfo("typeDeclearation", typeDeclearation);
        char *argName = strsGetFirstToken(buffs, typeDeclearation, ':');
        printInfo("argName", argName);
        char *argType = strsGetLastToken(buffs, typeDeclearation, ':');
        printInfo("argType", argType);
        obj_setStr(self, strAppend(strsAppend(buffs, methodObjPath, "."), argName), argType);
    }
}

static void msc_analizeLine(MimiObj *self, char *line)
{
    Args *buffs = New_args(NULL);
    if (strIsStartWith(line, "class "))
    {
        msc_analizeClass(self, line, buffs);
        goto exit;
    }

    if (strIsStartWith(line, "    def "))
    {
        msc_analizeDef(self, line, buffs);
        goto exit;
    }

    if (strIsStartWith(line, "        pass"))
    {
        msc_analizePass(self, line, buffs);
        goto exit;
    }

    if (strIsStartWith(line, "    ") && strIsContain(line, '='))
    {
        msc_analizeNew(self, line, buffs);
        goto exit;
    }
exit:
    args_deinit(buffs);
    return;
}

void msc_analizeFile(MimiObj *msc, char *pythonApiPath)
{
    Args *buffs = New_args(NULL);
    char *pyTextFromFile = getMimiscriptPythonApiText(pythonApiPath);
    if (NULL == pyTextFromFile)
    {
        printf("[error] compiler: load file faild\r\n");
        goto exit;
    }
    char *pyTextBuff = strsCopy(buffs, pyTextFromFile);
    free(pyTextFromFile);
    int lineNum = strCountSign(pyTextBuff, '\n');
    for (int i = 0; i < lineNum; i++)
    {
        char *line = strsPopToken(buffs, pyTextBuff, '\n');
        printf("|%d|>>>%s\r\n", i, line);
        msc_analizeLine(msc, line);
    }
exit:
    args_deinit(buffs);
    return;
}
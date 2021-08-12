#include <stdio.h>
#include <stdlib.h>
#include "Compiler.h"
#include "MimiObj.h"
#include "BaseObj.h"
#include "dataString.h"
#include "dataStrs.h"
#include "common.h"
#include "PyMethod.h"
#include "PyClass.h"

int __foreach_Compiler_makeApi(Arg *argEach, Args *haneldArgs)
{
    char *type = arg_getType(argEach);
    if (strEqu(type, "_class-PyClass"))
    {
        MimiObj *pyClass = arg_getPtr(argEach);
        MimiObj *msc = obj_getPtr(pyClass, "__context");
        char *outputPath = obj_getStr(msc, "outputPath");
        PyClass_makeApi(pyClass, outputPath);
    }
    return 0;
}

int __foreach_Compiler_makeHead(Arg *argEach, Args *haneldArgs)
{
    char *type = arg_getType(argEach);
    if (strEqu(type, "_class-PyClass"))
    {
        MimiObj *pyClass = arg_getPtr(argEach);
        MimiObj *msc = obj_getPtr(pyClass, "__context");
        char *outputPath = obj_getStr(msc, "outputPath");
        PyClass_makeHead(pyClass, outputPath);
    }
    return 0;
}

void Compiler_gererateCode(MimiObj *msc, char *outputPath)
{
    printf("generating class source file.\r\n");
    obj_setStr(msc, "outputPath", outputPath);
    args_foreach(msc->attributeList, __foreach_Compiler_makeApi, NULL);
    args_foreach(msc->attributeList, __foreach_Compiler_makeHead, NULL);
}

int Compiler_build(MimiObj *msc, char *pythonApiPath, char *outputPath)
{
    int res = 0;
    res = Compiler_analizeFile(msc, pythonApiPath);
    if (0 != res)
    {
        return res;
    }
    Compiler_gererateCode(msc, outputPath);
}

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

static void Compiler_analizePass(MimiObj *self, char *line, Args *buffs)
{
}

static void Compiler_analizeNew(MimiObj *self, char *line)
{
    Args *buffs = New_args(NULL);
    char *cleanLine = strsDeleteChar(buffs, line, ' ');
    char *currentClassName = obj_getStr(self, "currentClassName");
    char *pyObjName = NULL;
    char *pyClassName = NULL;
    if (strIsContain(cleanLine, '='))
    {
        pyObjName = strsGetFirstToken(buffs, cleanLine, '=');
        pyClassName = strsCut(buffs, cleanLine, '=', '(');
    }
    if (!strIsContain(cleanLine, '='))
    {
        pyClassName = strsGetFirstToken(buffs, cleanLine, '(');
    }

    printInfo("cleanLine", cleanLine);
    printInfo("currentClassName", currentClassName);
    printInfo("pyObjName", pyObjName);
    printInfo("pyClassName", pyClassName);
    char *pyObjPath = NULL;

    if (NULL != pyObjName)
    {
        pyObjPath = strsAppend(buffs, strsAppend(buffs, currentClassName, "._new_"), pyObjName);
        printInfo("pyObjPath", pyObjPath);
    }
    if (NULL == pyObjName)
    {
        pyObjPath = strsAppend(buffs, strsAppend(buffs, currentClassName, "._import_"), pyClassName);
        printInfo("pyObjPath", pyObjPath);
    }

    char *pyClassPath = strsAppend(buffs, strsAppend(buffs, pyObjPath, "."), "class");
    printInfo("pyClassPath", pyClassPath);
    obj_newObj(self, pyObjPath, "PyObj");
    obj_setStr(self, pyClassPath, pyClassName);

    if (NULL != pyObjName)
    {
        char *pyNamePath = strsAppend(buffs, strsAppend(buffs, pyObjPath, "."), "name");
        printInfo("pyNamePath", pyNamePath);
        obj_setStr(self, pyNamePath, pyObjName);
    }
    args_deinit(buffs);
}

static void Compiler_analizeClass(MimiObj *self, char *line, Args *buffs)
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

static void Compiler_analizeDef(MimiObj *self, char *line, Args *buffs)
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
    char *typeListBuff = strsCopy(buffs, typeList);
    for (int i = 0; i < argNum; i++)
    {
        char *typeDeclearation = strsPopToken(buffs, typeListBuff, ',');
        printInfo("typeDeclearation", typeDeclearation);
        char *argName = strsGetFirstToken(buffs, typeDeclearation, ':');
        printInfo("argName", argName);
        char *argType = strsGetLastToken(buffs, typeDeclearation, ':');
        printInfo("argType", argType);
        obj_setStr(self, strAppend(strsAppend(buffs, methodObjPath, "."), argName), argType);
    }
}

int Compiler_analizeLine(MimiObj *self, char *line)
{
    Args *buffs = New_args(NULL);
    int res = 0;
    if (strIsContain(line, '#'))
    {
        // comments
        goto exit;
    }

    if (strIsStartWith(line, "class "))
    {
        Compiler_analizeClass(self, line, buffs);
        goto exit;
    }

    if (strIsStartWith(line, "    def "))
    {
        Compiler_analizeDef(self, line, buffs);
        goto exit;
    }

    if (strIsStartWith(line, "        pass"))
    {
        Compiler_analizePass(self, line, buffs);
        goto exit;
    }

    if (strIsStartWith(line, "    ") && strIsContain(line, '(') && strIsContain(line, ')'))
    {
        Compiler_analizeNew(self, line);
        goto exit;
    }
exit:
    args_deinit(buffs);
    return res;
}

int Compiler_analizeFile(MimiObj *msc, char *pythonApiPath)
{
    Args *buffs = New_args(NULL);
    int res = 0;
    char *pyTextFromFile = getMimiscriptPythonApiText(pythonApiPath);
    if (NULL == pyTextFromFile)
    {
        printf("[error] compiler: load file faild\r\n");
        res = 1;
        goto exit;
    }
    char *pyTextBuff = strsCopy(buffs, pyTextFromFile);
    free(pyTextFromFile);
    int lineNum = strCountSign(pyTextBuff, '\n');
    for (int i = 0; i < lineNum + 1; i++)
    {
        char *line = strsPopToken(buffs, pyTextBuff, '\n');
        line = strsDeleteChar(buffs, line, '\r');
        printf("[   %d\t]%s\r\n", i + 1, line);
        Compiler_analizeLine(msc, line);
    }
    res = 0;
    goto exit;
exit:
    args_deinit(buffs);
    return res;
}

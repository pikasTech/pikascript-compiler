#include "BaseObj.h"
#include "SysObj.h"
#include "dataStrs.h"
#include "MimiObj.h"
#include "Compiler.h"
#include "PyMethod.h"
#include "common.h"
#include "PyClass.h"
#include "PyObj.h"
#include "Compiler.h"
#include <stdio.h>

void PyClass_setSuper(MimiObj *self, char *superClassName)
{
    obj_setStr(self, "superClassName", superClassName);
}

int __foreach_PyClass_makeMethodFun(Arg *argEach, Args *handleArgs)
{
    FILE *fp = args_getPtr(handleArgs, "fp");
    char *type = arg_getType(argEach);
    if (strEqu(type, "_class-PyMethod"))
    {
        MimiObj *pyMethod = arg_getPtr(argEach);
        PyMethod_makeMethodFun(pyMethod, fp);
    }
    return 0;
}
static void PyClass_makeMethodFun(MimiObj *pyClass, FILE *fp)
{
    Args *handleArgs = New_args(NULL);
    args_setPtr(handleArgs, "fp", fp);
    args_foreach(pyClass->attributeList, __foreach_PyClass_makeMethodFun, handleArgs);
    args_deinit(handleArgs);
}

int __foreach_PyClass_makeMethodDefine(Arg *argEach, Args *handleArgs)
{
    FILE *fp = args_getPtr(handleArgs, "fp");
    char *type = arg_getType(argEach);
    if (strEqu(type, "_class-PyMethod"))
    {
        MimiObj *pyMethod = arg_getPtr(argEach);
        PyMethod_makeMethodDefine(pyMethod, fp);
    }
    return 0;
}

int __foreach_PyClass_makeNewObj(Arg *argEach, Args *handleArgs)
{
    FILE *fp = args_getPtr(handleArgs, "fp");
    char *type = arg_getType(argEach);
    if (strEqu(type, "_class-PyObj"))
    {
        MimiObj *pyObj = arg_getPtr(argEach);
        PyObj_makeNewObj(pyObj, fp);
    }
    return 0;
}

static void PyClass_makeNewFun(MimiObj *pyClass, FILE *fp)
{
    char *name = obj_getStr(pyClass, "__name");
    Args *buffs = New_strBuff();
    char *superClassName = obj_getStr(pyClass, "superClassName");
    char *newFunDeclearation = args_getBuff(buffs, 512);
    char *deriveCmd = args_getBuff(buffs, 512);
    char *returnCmd = args_getBuff(buffs, 512);
    char *endLine = args_getBuff(buffs, 512);

    sprintf(newFunDeclearation, "MimiObj *New_%s(Args *args){\n", name);
    sprintf(deriveCmd, "    MimiObj *self = New_%s(args);\n", superClassName);

    fpusWithInfo(newFunDeclearation, fp);
    fpusWithInfo(deriveCmd, fp);

    Args *handleArgs = New_args(NULL);
    args_setPtr(handleArgs, "fp", fp);
    args_foreach(pyClass->attributeList, __foreach_PyClass_makeNewObj, handleArgs);
    args_foreach(pyClass->attributeList, __foreach_PyClass_makeMethodDefine, handleArgs);
    args_deinit(handleArgs);

    sprintf(returnCmd, "    return self;\n");
    sprintf(endLine, "}\n");

    fpusWithInfo(returnCmd, fp);
    fpusWithInfo(endLine, fp);
    args_deinit(buffs);
}

void pyClass_gnenrateDefineMethodFun(MimiObj *pyClass, FILE *fp)
{
    Args *handleArgs = New_args(NULL);
    args_setPtr(handleArgs, "fp", fp);
    args_foreach(pyClass->attributeList, __foreach_PyClass_makeMethodDefine, handleArgs);
    args_deinit(handleArgs);
}

int __foreach_PyClass_makeImportInclude(Arg *argEach, Args *handleArgs)
{
    FILE *fp = args_getPtr(handleArgs, "fp");
    char *type = arg_getType(argEach);
    if (strEqu(type, "_class-PyObj"))
    {
        MimiObj *pyObj = arg_getPtr(argEach);
        PyObj_makeInlcude(pyObj, fp);
    }
    return 0;
}

int __foreach_PyClass_getImportInclude(Arg *argEach, Args *handleArgs)
{
    char *type = arg_getType(argEach);
    if (strEqu(type, "_class-PyObj"))
    {
        Args *buffs = args_getPtr(handleArgs, "buffs");
        char *allInclude = args_getStr(handleArgs, "allInclude");
        MimiObj *pyObj = arg_getPtr(argEach);
        char *thisInclude = PyObj_getInclude(pyObj, buffs);
        allInclude = strsAppend(buffs, allInclude, thisInclude);
    }
    return 0;
}

char *PyClass_getImportInclude(MimiObj *pyClass, Args *buffs)
{
    Args *handleArgs = New_args(NULL);
    args_setPtr(handleArgs, "buffs", buffs);
    args_setStr(handleArgs, "allInclude", "");
    args_foreach(pyClass->attributeList, __foreach_PyClass_getImportInclude, handleArgs);
    char *allInclude = args_getStr(handleArgs, "allInclude");
    args_deinit(handleArgs);
    return allInclude;
}

static void PyClass_makeImportInclude(MimiObj *pyClass, FILE *fp)
{
    Args *handleArgs = New_args(NULL);
    args_setPtr(handleArgs, "fp", fp);
    args_foreach(pyClass->attributeList, __foreach_PyClass_makeImportInclude, handleArgs);
    args_deinit(handleArgs);
}

/* main operation */
void PyClass_makeApi(MimiObj *pyClass, char *path)
{
    Args *buffs = New_args(NULL);
    char *name = obj_getStr(pyClass, "__name");
    char *superClassName = obj_getStr(pyClass, "superClassName");
    char *fileName = strsAppend(buffs, name, "-api.c");
    char *filePath = strsAppend(buffs, path, fileName);
    char *includeSuperClass = args_getBuff(buffs, 512);
    char *includeImpl = args_getBuff(buffs, 512);

    FILE *fp = fopen(filePath, "w+");
    printf("\n--------[%s]--------\n", filePath);
    sprintf(includeSuperClass, "#include \"%s.h\"\n", superClassName);
    sprintf(includeImpl, "#include \"%s.h\"\n", name);
    fpusWithInfo("/* Warning!!! Don't modify this file!!! */\n", fp);
    fpusWithInfo(includeSuperClass, fp);
    fpusWithInfo(includeImpl, fp);
    fpusWithInfo("#include <stdio.h>\n", fp);
    fpusWithInfo("#include \"BaseObj.h\"\n", fp);
    PyClass_makeImportInclude(pyClass, fp);
    fpusWithInfo("\n", fp);

    PyClass_makeMethodFun(pyClass, fp);
    PyClass_makeNewFun(pyClass, fp);

    args_deinit(buffs);
    fclose(fp);
}

int __foreach_PyClass_makeMethodDeclear(Arg *argEach, Args *handleArgs)
{
    FILE *fp = args_getPtr(handleArgs, "fp");
    char *type = arg_getType(argEach);
    if (strEqu(type, "_class-PyMethod"))
    {
        MimiObj *pyMethod = arg_getPtr(argEach);
        PyMethod_makeMethodDeclear(pyMethod, fp);
    }
    return 0;
}

void PyClass_makeHead(MimiObj *pyClass, char *path)
{
    Args *buffs = New_args(NULL);
    char *newFunDeclearation = args_getBuff(buffs, 512);
    char *name = obj_getStr(pyClass, "__name");
    char *fileName = strsAppend(buffs, name, ".h");
    char *filePath = strsAppend(buffs, path, fileName);
    char *ifndef = args_getBuff(buffs, 512);
    char *define = args_getBuff(buffs, 512);

    printf("\n--------[%s]--------\n", filePath);
    FILE *fp = fopen(filePath, "w+");

    fpusWithInfo("/* Warning!!! Don't modify this file!!! */\n", fp);
    sprintf(ifndef, "#ifndef __%s__H\n", name);
    sprintf(define, "#define __%s__H\n", name);

    fpusWithInfo(ifndef, fp);
    fpusWithInfo(define, fp);
    fpusWithInfo("#include \"MimiObj.h\"\n", fp);
    fpusWithInfo("#include <stdio.h>\n", fp);
    fpusWithInfo("#include <stdlib.h>\n", fp);

    sprintf(newFunDeclearation, "MimiObj *New_%s(Args *args);\n", name);
    fpusWithInfo(newFunDeclearation, fp);

    Args *handleArgs = New_args(NULL);
    args_setPtr(handleArgs, "fp", fp);
    args_foreach(pyClass->attributeList, __foreach_PyClass_makeMethodDeclear, handleArgs);
    args_deinit(handleArgs);

    fpusWithInfo("#endif\n", fp);

    args_deinit(buffs);
    fclose(fp);
}

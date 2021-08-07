#include "baseObj.h"
#include "sysObj.h"
#include "dataStrs.h"
#include "MimiObj.h"
#include "Compiler.h"
#include "PyMethod.h"
#include "PyObj.h"
#include "Compiler.h"
#include <stdio.h>

void PyObj_setSuper(MimiObj *self, char *superClassName)
{
    obj_setStr(self, "superClassName", superClassName);
}

static void setSuper(MimiObj *self, Args *args)
{
    char *superClassName = args_getStr(args, "superClassName");
    PyObj_setSuper(self, superClassName);
}

static void pyClass_writeMethodFun(MimiObj *pyClass, FILE *fp)
{
    Args *handleArgs = New_args(NULL);
    args_setPtr(handleArgs, "fp", fp);
    args_foreach(pyClass->attributeList, pyMetod_writeEachMethodFun, handleArgs);
}

static void pyClass_writeNewFun(MimiObj *pyClass, FILE *fp)
{
    char *name = obj_getStr(pyClass, "name");
    Args *buffs = New_strBuff();
    char *superClassName = obj_getStr(pyClass, "superClassName");
    char *newFunDeclearation = args_getBuff(buffs, 512);
    char *deriveCmd = args_getBuff(buffs, 512);
    char *returnCmd = args_getBuff(buffs, 512);
    char *endLine = args_getBuff(buffs, 512);

    sprintf(newFunDeclearation, "MimiObj *New_%s(Args *args){\n", name);
    sprintf(deriveCmd, "    self = New_%s(args);\n", superClassName);

    fpusWithInfo(newFunDeclearation, fp);
    fpusWithInfo(deriveCmd, fp);

    Args *handleArgs = New_args(NULL);
    args_setPtr(handleArgs, "fp", fp);
    args_foreach(pyClass->attributeList, pyMethod_writeEachMethodDefine, handleArgs);

    sprintf(returnCmd, "    return self;\n");
    sprintf(endLine, "}\n", name);

    fpusWithInfo(returnCmd, fp);
    fpusWithInfo(endLine, fp);
}

void pyClass_gnenrateDefineMethodFun(MimiObj *pyClass, FILE *fp)
{
    Args *handleArgs = New_args(NULL);
    args_setPtr(handleArgs, "fp", fp);
    args_foreach(pyClass->attributeList, pyMethod_writeEachMethodDefine, handleArgs);
}

/* main operation */
void pyClass_writeOneClassSourceFile(MimiObj *pyClass, char *path)
{
    Args *buffs = New_args(NULL);
    char *name = obj_getStr(pyClass, "name");
    char *superClassName = obj_getStr(pyClass, "superClassName");
    char *fileName = strsAppend(buffs, name, "Class.c");
    char *filePath = strsAppend(buffs, path, fileName);
    char *includeSuperClass = args_getBuff(buffs, 512);
    char *includeImpl = args_getBuff(buffs, 512);

    FILE *fp = fopen(filePath, "w+");
    printf("\n--------[%s]--------\n", filePath);
    sprintf(includeSuperClass, "#include \"%s.h\"\n", superClassName);
    sprintf(includeImpl, "#include \"%s.h\"\n", name);
    fpusWithInfo(includeSuperClass, fp);
    fpusWithInfo(includeImpl, fp);
    fpusWithInfo("#include <stdio.h>\n\n", fp);

    pyClass_writeMethodFun(pyClass, fp);
    pyClass_writeNewFun(pyClass, fp);

    args_deinit(buffs);
    fclose(fp);
}

int pyClass_gererateEachClassSourceFile(Arg *argEach, Args *haneldArgs)
{
    char *type = arg_getType(argEach);
    if (strEqu(type, "_class-PyClass"))
    {
        MimiObj *pyClass = arg_getPtr(argEach);
        MimiObj *msc = obj_getPtr(pyClass, "context");
        char *outputPath = obj_getStr(msc, "outputPath");
        pyClass_writeOneClassSourceFile(pyClass, outputPath);
    }
}

MimiObj *New_PyObj(Args *args)
{
    MimiObj *self = New_MimiObj_sys(args);
    class_defineMethod(self, "setSuper(superClassName:str)", setSuper);
    return self;
}
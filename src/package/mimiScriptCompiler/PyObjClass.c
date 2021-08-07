#include "baseObj.h"
#include "sysObj.h"
#include "dataStrs.h"
#include "Compiler.h"
#include "PyMethod.h"
#include <stdio.h>

static void setSuper(MimiObj *self, Args *args)
{
    char *superClassName = args_getStr(args, "superClassName");
    PyObj_setSuper(self, superClassName);
}


static void pyClass_generateNewFun(MimiObj *pyClass, FILE *fp)
{
    char *name = obj_getStr(pyClass, "name");
    fprintf(fp, "MimiObj *New_%s(Args *args){\n", name);
    char *superClassName = obj_getStr(pyClass, "superClassName");
    fprintf(fp, "    self = New_%s(args);\n", superClassName);

    Args *handleArgs = New_args(NULL);
    args_setPtr(handleArgs, "fp", fp);
    args_foreach(pyClass->attributeList, pyMethod_generateEachMethodDefine, handleArgs);

    fprintf(fp, "    return self;\n");
    fprintf(fp, "}\n", name);
}


void pyClass_gnenrateMethodFun(MimiObj *pyClass, FILE *fp)
{
    Args *handleArgs = New_args(NULL);
    args_setPtr(handleArgs, "fp", fp);
    args_foreach(pyClass->attributeList, pyMethod_generateEachMethodFun, handleArgs);
}

void pyClass_generateOneClassSourceFile(MimiObj *pyClass)
{
    Args *buffs = New_args(NULL);
    char path[] = "dist/";
    char *name = obj_getStr(pyClass, "name");
    char *superClassName = obj_getStr(pyClass, "superClassName");
    char *fileName = strsAppend(buffs, name, "Class.c");
    char *filePath = strsAppend(buffs, path, fileName);
    FILE *fp = fopen(filePath, "w+");
    fprintf(fp, "#include \"%s.h\"\n", superClassName);
    fprintf(fp, "#include <stdio.h>\n\n");
    pyClass_generateNewFun(pyClass, fp);

    args_deinit(buffs);
    fclose(fp);
}

int pyClass_gererateEachClassSourceFile(Arg *argEach, Args *haneldArgs)
{
    char *type = arg_getType(argEach);
    if (strEqu(type, "_class-PyClass"))
    {
        MimiObj *pyClass = arg_getPtr(argEach);
        pyClass_generateOneClassSourceFile(pyClass);
    }
}

MimiObj *New_PyObj(Args *args)
{
    MimiObj *self = New_MimiObj_sys(args);
    class_defineMethod(self, "setSuper(superClassName:str)", setSuper);
    return self;
}
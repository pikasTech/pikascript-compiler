#include <stdio.h>
#include <stdlib.h>
#include "baseObj.h"
#include "dataStrs.h"

void pyMethod_generateOneMethod(MimiObj *pyMethod, FILE *fp)
{
    char *methodName = obj_getStr(pyMethod, "name");
    char *typeList = obj_getStr(pyMethod, "typeList");
    char *returnType = obj_getStr(pyMethod, "returnType");

    if ((NULL == typeList) && (NULL == returnType))
    {
        fprintf(fp, "    class_defineMethod(\"%s()\", %s);\n",
                methodName,
                methodName);
        return;
    }

    if (NULL == typeList)
    {
        fprintf(fp, "    class_defineMethod(\"%s()->%s\", %s);\n", methodName,
                returnType,
                methodName);
        return;
    }

    if (NULL == returnType)
    {
        fprintf(fp, "    class_defineMethod(\"%s(%s)\", %s);\n",
                methodName,
                typeList,
                methodName);
        return;
    }

    fprintf(fp, "    class_defineMethod(\"%s(%s)->%s\", %s);\n", methodName,
            typeList,
            returnType,
            methodName);
    return;
}

int pyMethod_generateEachMethodDefine(Arg *argEach, Args *handleArgs)
{
    FILE *fp = args_getPtr(handleArgs, "fp");
    char *type = arg_getType(argEach);
    if (strEqu(type, "_class-PyMethod"))
    {
        MimiObj *pyMethod = arg_getPtr(argEach);
        pyMethod_generateOneMethod(pyMethod, fp);
    }
}

static void pyMethod_generateMethodFun(MimiObj *pyMethod, FILE *fp)
{
    MimiObj *pyClass = obj_getPtr(pyMethod, "context");
    char *className = obj_getStr(pyClass, "name");
    char *methodName = obj_getStr(pyMethod, "name");
    fprintf(fp, "method\n");
}

int pyMethod_generateEachMethodFun(Arg *argEach, Args *handleArgs)
{
    FILE *fp = args_getPtr(handleArgs, "fp");
    char *type = arg_getType(argEach);
    if (strEqu(type, "_class-PyMethod"))
    {
        MimiObj *pyMethod = arg_getPtr(argEach);
        pyMethod_generateOneMethod(pyMethod, fp);
    }
}


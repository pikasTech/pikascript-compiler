#include <stdio.h>
#include <stdlib.h>
#include "baseObj.h"
#include "dataStrs.h"
#include "Compiler.h"

void pyMethod_writeOneMethodDefine(MimiObj *pyMethod, FILE *fp)
{
    Args *buffs = New_strBuff();
    MimiObj *pyClass = obj_getPtr(pyMethod, "context");
    char *className = obj_getStr(pyClass, "name");
    char *methodName = obj_getStr(pyMethod, "name");
    char *typeList = obj_getStr(pyMethod, "typeList");
    char *returnType = obj_getStr(pyMethod, "returnType");

    if ((NULL == typeList) && (NULL == returnType))
    {
        char *defineMethod = args_getBuff(buffs, 512);
        sprintf(defineMethod, "    class_defineMethod(\"%s()\", %s_%sFun);\n",
                methodName,
                className,
                methodName);
        fpusWithInfo(defineMethod, fp);
        goto exit;
    }

    if (NULL == typeList)
    {
        char *defineMethod = args_getBuff(buffs, 512);
        sprintf(defineMethod, "    class_defineMethod(\"%s()->%s\", %s_%sFun);\n", methodName,
                returnType,
                className,
                methodName);
        fpusWithInfo(defineMethod, fp);
        goto exit;
    }

    if (NULL == returnType)
    {
        char *defineMethod = args_getBuff(buffs, 512);
        sprintf(defineMethod, "    class_defineMethod(\"%s(%s)\", %s_%sFun);\n",
                methodName,
                typeList,
                className,
                methodName);
        fpusWithInfo(defineMethod, fp);
        goto exit;
    }

    char *defineMethod = args_getBuff(buffs, 512);
    sprintf(defineMethod, "    class_defineMethod(\"%s(%s)->%s\", %s_%sFun);\n", methodName,
            typeList,
            returnType,
            className,
            methodName);
    fpusWithInfo(defineMethod, fp);
    goto exit;
exit:
    args_deinit(buffs);
    return;
}

int pyMethod_writeEachMethodDefine(Arg *argEach, Args *handleArgs)
{
    FILE *fp = args_getPtr(handleArgs, "fp");
    char *type = arg_getType(argEach);
    if (strEqu(type, "_class-PyMethod"))
    {
        MimiObj *pyMethod = arg_getPtr(argEach);
        pyMethod_writeOneMethodDefine(pyMethod, fp);
    }
}

static void pyMethod_writeMethodFun(MimiObj *pyMethod, FILE *fp)
{
    MimiObj *pyClass = obj_getPtr(pyMethod, "context");
    char *className = obj_getStr(pyClass, "name");
    char *methodName = obj_getStr(pyMethod, "name");
    fprintf(fp, "method\n");
}

char *getTypeInC(Args *buffs, char *argType)
{
    if (strEqu(argType, "int"))
    {
        return strsCopy(buffs, "int");
    }
    if (strEqu(argType, "float"))
    {
        return strsCopy(buffs, "float");
    }
    if (strEqu(argType, "pointer"))
    {
        return strsCopy(buffs, "void *");
    }
    if (strEqu(argType, "str"))
    {
        return strsCopy(buffs, "char *");
    }
    return NULL;
}

char *getGetFunName(Args *buffs, char *argType)
{

    if (strEqu(argType, "int"))
    {
        return strsCopy(buffs, "args_getInt");
    }
    if (strEqu(argType, "float"))
    {
        return strsCopy(buffs, "args_getFloat");
    }
    if (strEqu(argType, "pointer"))
    {
        return strsCopy(buffs, "args_getPtr");
    }
    if (strEqu(argType, "str"))
    {
        return strsCopy(buffs, "args_getStr");
    }
}

int getArgNum(char *typeList)
{
    int argNum = 1 + strCountSign(typeList, ',');
    if (!strIsContain(typeList, ','))
    {
        argNum = 0;
    }
    return argNum;
}

void pyMethod_writeOneMethodFun(MimiObj *pyMethod, FILE *fp)
{
    Args *buffs = New_strBuff();
    MimiObj *pyClass = obj_getPtr(pyMethod, "context");
    char *methodFunName = args_getBuff(buffs, 256);
    char *className = obj_getStr(pyClass, "name");
    char *methodName = obj_getStr(pyMethod, "name");
    char *typeList = obj_getStr(pyMethod, "typeList");
    char *returnType = obj_getStr(pyMethod, "returnType");
    char *returnTypeInC = getTypeInC(buffs, returnType);

    sprintf(methodFunName, "void %s_%sFun(MimiObj *self, Args *args){\n",
            className,
            methodName);
    int argNum = getArgNum(typeList);
    fpusWithInfo(methodFunName, fp);

    char *typeListBuff = strsCopy(buffs, typeList);
    char *localCallArglist = strsCopy(buffs, "");
    for (int i = 0; i < argNum; i++)
    {
        char *argDeclearation = strsPopToken(buffs, typeListBuff, ',');
        char *argName = strsGetFirstToken(buffs, argDeclearation, ':');
        char *argType = strsGetLastToken(buffs, argDeclearation, ':');
        char *argTypeInC = getTypeInC(buffs, argType);
        char *getFunName = getGetFunName(buffs, argType);
        localCallArglist = strsAppend(buffs, localCallArglist, argName);
        if (i != argNum - 1)
        {
            localCallArglist = strsAppend(buffs, localCallArglist, " ,");
        }

        char *transferArgCmd = args_getBuff(buffs, 256);
        sprintf(transferArgCmd, "    %s %s = %s(args, \"%s\");\n",
                argTypeInC,
                argName,
                getFunName,
                argName);

        fpusWithInfo(transferArgCmd, fp);
    }

    char *callLocalFunCmd = args_getBuff(buffs, 256);
    char *devideSign = NULL;
    if (argNum > 0)
    {
        devideSign = strsCopy(buffs, ", ");
    }
    if (argNum == 0)
    {
        devideSign = strsCopy(buffs, "");
    }

    if (NULL == returnType)
    {
        sprintf(callLocalFunCmd, "    %s_%s(self%s%s);\n",
                className,
                methodName,
                devideSign,
                localCallArglist);
    }
    if (NULL != returnType)
    {
        sprintf(callLocalFunCmd, "    %s res = %s_%s(self%s%s);\n",
                returnTypeInC,
                className,
                methodName,
                devideSign,
                localCallArglist);
    }

    fpusWithInfo(callLocalFunCmd, fp);
    fpusWithInfo("}\n\n", fp);
}

int pyMetod_writeEachMethodFun(Arg *argEach, Args *handleArgs)
{
    FILE *fp = args_getPtr(handleArgs, "fp");
    char *type = arg_getType(argEach);
    if (strEqu(type, "_class-PyMethod"))
    {
        MimiObj *pyMethod = arg_getPtr(argEach);
        pyMethod_writeOneMethodFun(pyMethod, fp);
    }
}
#include <stdio.h>
#include <stdlib.h>
#include "analyzer.h"
#include "MimiObj.h"
#include "BaseObj.h"
#include "dataStrs.h"
#include "common.h"
#include "PyMethod.h"
#include "PyClass.h"

int __foreach_msc_makeApi(Arg *argEach, Args *haneldArgs)
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

int __foreach_msc_makeHead(Arg *argEach, Args *haneldArgs)
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

void msc_gererateCode(MimiObj *msc, char *outputPath)
{
    printf("generating class source file.\r\n");
    obj_setStr(msc, "outputPath", outputPath);
    args_foreach(msc->attributeList, __foreach_msc_makeApi, NULL);
    args_foreach(msc->attributeList, __foreach_msc_makeHead, NULL);
}

void compiler_build(MimiObj *msc, char *pythonApiPath, char *outputPath)
{
    msc_analizeFile(msc, pythonApiPath);
    msc_gererateCode(msc, outputPath);
}
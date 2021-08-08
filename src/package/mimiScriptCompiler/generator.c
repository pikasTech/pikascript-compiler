#include <stdio.h>
#include <stdlib.h>
#include "BaseObj.h"
#include "dataStrs.h"
#include "PyMethodClass.h"
#include "MimiObj.h"
#include "PyMethod.h"
#include "PyClass.h"

int __foreach_PyClass_gererateClassCode(Arg *argEach, Args *haneldArgs)
{
    char *type = arg_getType(argEach);
    if (strEqu(type, "_class-PyClass"))
    {
        MimiObj *pyClass = arg_getPtr(argEach);
        MimiObj *msc = obj_getPtr(pyClass, "__context");
        char *outputPath = obj_getStr(msc, "outputPath");
        pyClass_writeOneClassSourceFile(pyClass, outputPath);
    }
    return 0;
}

int __foreach_PyClass_gererateHeadCode(Arg *argEach, Args *haneldArgs)
{
    char *type = arg_getType(argEach);
    if (strEqu(type, "_class-PyClass"))
    {
        MimiObj *pyClass = arg_getPtr(argEach);
        MimiObj *msc = obj_getPtr(pyClass, "__context");
        char *outputPath = obj_getStr(msc, "outputPath");
        pyClass_writeClassHeadFileMain(pyClass, outputPath);
    }
    return 0;
}

void msc_gererateCode(MimiObj *msc, char *outputPath)
{
    printf("generating class source file.\r\n");
    obj_setStr(msc, "outputPath", outputPath);
    args_foreach(msc->attributeList, __foreach_PyClass_gererateClassCode, NULL);
    args_foreach(msc->attributeList, __foreach_PyClass_gererateHeadCode, NULL);
}
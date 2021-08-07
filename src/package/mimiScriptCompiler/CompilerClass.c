#include "baseObj.h"
#include "sysObj.h"
#include "Compiler.h"
#include "PyObjClass.h"
#include "PyMethodClass.h"

static void buildMethod(MimiObj *self, Args *args)
{
    char *pythonApiPath = args_getStr(args, "pythonApiPath");
    compiler_build(self, pythonApiPath);
}

MimiObj *New_Compiler(Args *args)
{
    MimiObj *self = New_MimiObj_sys(args);
    obj_import(self, "PyClass", New_PyObj);
    obj_import(self, "PyMethod", New_PyMethod);
    class_defineMethod(self, "build(pythonApiPath:str)", buildMethod);
    return self;
}
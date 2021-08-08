#include "BaseObj.h"
#include "SysObj.h"
#include "Compiler.h"
#include "PyClass.h"
#include "PyMethod.h"
#include "PyObj.h"

static void buildMethod(MimiObj *self, Args *args)
{
    char *pythonApiPath = args_getStr(args, "pythonApiPath");
    char *outputPath = args_getStr(args, "outputPath");
    compiler_build(self, pythonApiPath, outputPath);
}

MimiObj *New_Compiler(Args *args)
{
    MimiObj *self = New_SysObj(args);
    obj_import(self, "PyClass", New_PyClass);
    obj_import(self, "PyMethod", New_PyMethod);
    obj_import(self, "PyObj", New_PyObj);
    class_defineMethod(self, "build(pythonApiPath:str,outputPath:str)", buildMethod);
    return self;
}
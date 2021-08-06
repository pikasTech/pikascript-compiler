#include "baseObj.h"
#include "Compiler.h"

static void buildMethod(MimiObj *self, Args *args)
{
    char * pythonApiPath = args_getStr(args, "pythonApiPath");
    compiler_build(self, pythonApiPath);
}

MimiObj *New_Compiler(Args *args)
{
    MimiObj *self = New_baseObj(args);
    class_defineMethod(self, "build(pythonApiPath:string)", buildMethod);
    return self;
}
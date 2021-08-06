#include "baseObj.h"
#include "sysObj.h"
#include "Compiler.h"

static void setSuper(MimiObj *self, Args *args)
{
    char *superClassName = args_getStr(args, "superClassName");
    PyObj_setSuper(self, superClassName);
}

MimiObj *New_PyObj(Args *args)
{
    MimiObj *self = New_MimiObj_sys(args);
    class_defineMethod(self, "setSuper(superClassName:str)", setSuper);
    return self;
}
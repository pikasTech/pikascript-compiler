#include "BaseObj.h"
#include "SysObj.h"
#include "Compiler.h"

MimiObj *New_PyMethod(Args *args)
{
    MimiObj *self = New_SysObj(args);
    return self;
}
/* Warning!!! Don't modify this file!!!*/
#include "SysObj.h"
#include "Root.h"
#include <stdio.h>
#include "BaseObj.h"

void Root_rebootMethod(MimiObj *self, Args *args){
    Root_reboot(self);
}

MimiObj *New_Root(Args *args){
    MimiObj *self = New_SysObj(args);
    class_defineMethod(self, "reboot()", Root_rebootMethod);
    return self;
}

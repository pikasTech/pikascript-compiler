/* Warning!!! Don't modify this file!!! */
#include "BaseObj.h"
#include "Test.h"
#include <stdio.h>
#include "BaseObj.h"
#include "TinyObj.h"
#include "SysObj.h"
#include "BaseObj.h"

MimiObj *New_Test(Args *args){
    MimiObj *self = New_BaseObj(args);
    obj_import(self, "TinyObj", New_TinyObj);
    obj_newObj(self, "tiny", "TinyObj");
    obj_import(self, "SysObj", New_SysObj);
    obj_newObj(self, "sys", "SysObj");
    obj_import(self, "BaseObj", New_BaseObj);
    obj_newObj(self, "base", "BaseObj");
    return self;
}

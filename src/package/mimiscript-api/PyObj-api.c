/* Warning!!! Don't modify this file!!!*/
#include "TinyObj.h"
#include "PyObj.h"
#include <stdio.h>
#include "BaseObj.h"

void PyObj_importCLassMethod(MimiObj *self, Args *args){
    char * className = args_getStr(args, "className");
    PyObj_importCLass(self, className);
}

MimiObj *New_PyObj(Args *args){
    MimiObj *self = New_TinyObj(args);
    class_defineMethod(self, "importCLass(className:str)", PyObj_importCLassMethod);
    return self;
}

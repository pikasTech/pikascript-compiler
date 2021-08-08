/* Warning!!! Don't modify this file!!!*/
#include "TinyObj.h"
#include "PyObj.h"
#include <stdio.h>
#include "BaseObj.h"

void PyObj_newObjMethod(MimiObj *self, Args *args){
    char * objName = args_getStr(args, "objName");
    char * className = args_getStr(args, "className");
    FILE * fp = args_getPtr(args, "fp");
    PyObj_newObj(self, objName ,className ,fp);
}

void PyObj_importCLassMethod(MimiObj *self, Args *args){
    char * className = args_getStr(args, "className");
    FILE * fp = args_getPtr(args, "fp");
    PyObj_importCLass(self, className ,fp);
}

MimiObj *New_PyObj(Args *args){
    MimiObj *self = New_TinyObj(args);
    class_defineMethod(self, "newObj(objName:str,className:str,fp:FILE)", PyObj_newObjMethod);
    class_defineMethod(self, "importCLass(className:str,fp:FILE)", PyObj_importCLassMethod);
    return self;
}

/* Warning!!! Don't modify this file!!! */
#include "TinyObj.h"
#include "PyObj.h"
#include <stdio.h>
#include "BaseObj.h"
#include "TinyObj.h"
#include "SysObj.h"
#include "BaseObj.h"

void PyObj_makeNewObjMethod(MimiObj *self, Args *args){
    FILE * fp = args_getPtr(args, "fp");
    PyObj_makeNewObj(self, fp);
}

void PyObj_makeInlcudeMethod(MimiObj *self, Args *args){
    FILE * fp = args_getPtr(args, "fp");
    PyObj_makeInlcude(self, fp);
}

void PyObj_newObjMethod(MimiObj *self, Args *args){
    char * objName = args_getStr(args, "objName");
    char * className = args_getStr(args, "className");
    FILE * fp = args_getPtr(args, "fp");
    PyObj_newObj(self, objName ,className ,fp);
}

void PyObj_importClassMethod(MimiObj *self, Args *args){
    char * className = args_getStr(args, "className");
    FILE * fp = args_getPtr(args, "fp");
    PyObj_importClass(self, className ,fp);
}

MimiObj *New_PyObj(Args *args){
    MimiObj *self = New_TinyObj(args);
    class_defineMethod(self, "makeNewObj(fp:FILE)", PyObj_makeNewObjMethod);
    class_defineMethod(self, "makeInlcude(fp:FILE)", PyObj_makeInlcudeMethod);
    class_defineMethod(self, "newObj(objName:str,className:str,fp:FILE)", PyObj_newObjMethod);
    class_defineMethod(self, "importClass(className:str,fp:FILE)", PyObj_importClassMethod);
    return self;
}

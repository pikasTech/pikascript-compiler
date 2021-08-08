/* Warning!!! Don't modify this file!!! */
#include "SysObj.h"
#include "PyClass.h"
#include <stdio.h>
#include "BaseObj.h"

void PyClass_makeHeadMethod(MimiObj *self, Args *args){
    char * path = args_getStr(args, "path");
    PyClass_makeHead(self, path);
}

void PyClass_makeApiMethod(MimiObj *self, Args *args){
    char * path = args_getStr(args, "path");
    PyClass_makeApi(self, path);
}

void PyClass_setSuperMethod(MimiObj *self, Args *args){
    char * superClassName = args_getStr(args, "superClassName");
    PyClass_setSuper(self, superClassName);
}

MimiObj *New_PyClass(Args *args){
    MimiObj *self = New_SysObj(args);
    class_defineMethod(self, "makeHead(path:str)", PyClass_makeHeadMethod);
    class_defineMethod(self, "makeApi(path:str)", PyClass_makeApiMethod);
    class_defineMethod(self, "setSuper(superClassName:str)", PyClass_setSuperMethod);
    return self;
}

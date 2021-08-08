/* Warning!!! Don't modify this file!!! */
#include "SysObj.h"
#include "PyMethod.h"
#include <stdio.h>
#include "BaseObj.h"

void PyMethod_makeMethodDefineMethod(MimiObj *self, Args *args){
    FILE * fp = args_getPtr(args, "fp");
    PyMethod_makeMethodDefine(self, fp);
}

void PyMethod_makeMethodDeclearMethod(MimiObj *self, Args *args){
    FILE * fp = args_getPtr(args, "fp");
    PyMethod_makeMethodDeclear(self, fp);
}

void PyMethod_makeMethodFunMethod(MimiObj *self, Args *args){
    FILE * fp = args_getPtr(args, "fp");
    PyMethod_makeMethodFun(self, fp);
}

MimiObj *New_PyMethod(Args *args){
    MimiObj *self = New_SysObj(args);
    class_defineMethod(self, "makeMethodDefine(fp:FILE)", PyMethod_makeMethodDefineMethod);
    class_defineMethod(self, "makeMethodDeclear(fp:FILE)", PyMethod_makeMethodDeclearMethod);
    class_defineMethod(self, "makeMethodFun(fp:FILE)", PyMethod_makeMethodFunMethod);
    return self;
}

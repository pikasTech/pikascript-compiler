/* Warning!!! Don't modify this file!!! */
#include "SysObj.h"
#include "Compiler.h"
#include <stdio.h>
#include "BaseObj.h"
#include "PyObj.h"
#include "PyClass.h"
#include "PyMethod.h"

void Compiler_analizeFileMethod(MimiObj *self, Args *args){
    char * pythonApiPath = args_getStr(args, "pythonApiPath");
    Compiler_analizeFile(self, pythonApiPath);
}

void Compiler_buildMethod(MimiObj *self, Args *args){
    char * pythonApiPath = args_getStr(args, "pythonApiPath");
    char * outputPath = args_getStr(args, "outputPath");
    Compiler_build(self, pythonApiPath ,outputPath);
}

MimiObj *New_Compiler(Args *args){
    MimiObj *self = New_SysObj(args);
    obj_import(self, "PyObj", New_PyObj);
    obj_import(self, "PyClass", New_PyClass);
    obj_import(self, "PyMethod", New_PyMethod);
    class_defineMethod(self, "analizeFile(pythonApiPath:str)", Compiler_analizeFileMethod);
    class_defineMethod(self, "build(pythonApiPath:str,outputPath:str)", Compiler_buildMethod);
    return self;
}

/* Warning!!! Don't modify this file!!! */
#include "SysObj.h"
#include "Compiler.h"
#include <stdio.h>
#include "BaseObj.h"
#include "PyClass.h"
#include "PyMethod.h"

void Compiler_analizeLineMethod(MimiObj *self, Args *args){
    char * line = args_getStr(args, "line");
    int res = Compiler_analizeLine(self, line);
    method_returnInt(args, res);
}

void Compiler_analizeFileMethod(MimiObj *self, Args *args){
    char * pythonApiPath = args_getStr(args, "pythonApiPath");
    int res = Compiler_analizeFile(self, pythonApiPath);
    method_returnInt(args, res);
}

void Compiler_buildMethod(MimiObj *self, Args *args){
    char * pythonApiPath = args_getStr(args, "pythonApiPath");
    char * outputPath = args_getStr(args, "outputPath");
    int res = Compiler_build(self, pythonApiPath ,outputPath);
    method_returnInt(args, res);
}

MimiObj *New_Compiler(Args *args){
    MimiObj *self = New_SysObj(args);
    obj_import(self, "PyClass", New_PyClass);
    obj_import(self, "PyMethod", New_PyMethod);
    class_defineMethod(self, "analizeLine(line:str)->int", Compiler_analizeLineMethod);
    class_defineMethod(self, "analizeFile(pythonApiPath:str)->int", Compiler_analizeFileMethod);
    class_defineMethod(self, "build(pythonApiPath:str,outputPath:str)->int", Compiler_buildMethod);
    return self;
}

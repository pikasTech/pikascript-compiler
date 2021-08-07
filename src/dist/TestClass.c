/* Warning!!! Don't modify this file!!!*/
#include "BaseObj.h"
#include "Test.h"
#include <stdio.h>
#include "BaseObj.h"

void Test_testMethod(MimiObj *self, Args *args){
    char * val1 = args_getStr(args, "val1");
    int val2 = args_getInt(args, "val2");
    float res = Test_test(self, val1 ,val2);
    method_returnFloat(args, res);
}

MimiObj *New_Test(Args *args){
    MimiObj *self = New_BaseObj(args);
    class_defineMethod(self, "test(val1:str,val2:int)->float", Test_testMethod);
    return self;
}

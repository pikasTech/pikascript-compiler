/* Warning!!! Don't modify this file!!!*/
#include "Test.h"
#include "Test1.h"
#include <stdio.h>
#include "BaseObj.h"

void Test1_getInfoMethod(MimiObj *self, Args *args){
    int res = Test1_getInfo(self);
    method_returnInt(args, res);
}

void Test1_test2Method(MimiObj *self, Args *args){
    Test1_test2(self);
}

void Test1_testMethod(MimiObj *self, Args *args){
    Test1_test(self);
}

MimiObj *New_Test1(Args *args){
    MimiObj *self = New_Test(args);
    class_defineMethod(self, "getInfo()->int", Test1_getInfoMethod);
    class_defineMethod(self, "test2()", Test1_test2Method);
    class_defineMethod(self, "test()", Test1_testMethod);
    return self;
}

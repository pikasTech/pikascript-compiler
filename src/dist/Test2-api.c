/* Warning!!! Don't modify this file!!!*/
#include "Test.h"
#include "Test2.h"
#include <stdio.h>
#include "BaseObj.h"

void Test2_testMethod(MimiObj *self, Args *args){
    float val1 = args_getFloat(args, "val1");
    int val2 = args_getInt(args, "val2");
    Test2_test(self, val1 ,val2);
}

MimiObj *New_Test2(Args *args){
    MimiObj *self = New_Test(args);
    class_defineMethod(self, "test(val1:float,val2:int)", Test2_testMethod);
    return self;
}

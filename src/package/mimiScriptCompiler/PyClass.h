#include <stdio.h>
#include "MimiObj.h"
void PyClass_setSuper(MimiObj *self, char *superClassName);

int PyClass_gererateClassCode(Arg *argEach, Args *haneldArgs);
int PyClass_gererateHeadCode(Arg *argEach, Args *haneldArgs);
MimiObj *New_PyClass(Args *args);
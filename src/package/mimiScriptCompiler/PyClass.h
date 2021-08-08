#include <stdio.h>
#include "MimiObj.h"
void PyObj_setSuper(MimiObj *self, char *superClassName);

int pyClass_gererateClassCode(Arg *argEach, Args *haneldArgs);
int pyClass_gererateHeadCode(Arg *argEach, Args *haneldArgs);
MimiObj *New_PyObj(Args *args);
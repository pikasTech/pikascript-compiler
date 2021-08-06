#include <stdio.h>
#include <stdlib.h>
#include "baseObj.h"
#include "dataStrs.h"

void pyObj_setSuper(MimiObj *self, char *superClassName)
{
    obj_setStr(self, "superClassName", superClassName);
}
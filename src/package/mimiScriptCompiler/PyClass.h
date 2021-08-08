#include <stdio.h>
#include "MimiObj.h"
void PyClass_setSuper(MimiObj *self, char *superClassName);

void pyClass_writeOneClassSourceFile(MimiObj *pyClass, char *path);
void pyClass_writeClassHeadFileMain(MimiObj *pyClass, char *path);
MimiObj *New_PyClass(Args *args);
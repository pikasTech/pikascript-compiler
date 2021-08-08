/* Warning!!! Don't modify this file!!!*/
#ifndef __PyClass__H
#define __PyClass__H
#include "MimiObj.h"
#include <stdio.h>
#include <stdlib.h>
MimiObj *New_PyClass(Args *args);
void PyClass_makeHead(MimiObj *self, char * path);
void PyClass_makeApi(MimiObj *self, char * path);
void PyClass_setSuper(MimiObj *self, char * superClassName);
#endif

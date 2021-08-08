/* Warning!!! Don't modify this file!!! */
#ifndef __PyMethod__H
#define __PyMethod__H
#include "MimiObj.h"
#include <stdio.h>
#include <stdlib.h>
MimiObj *New_PyMethod(Args *args);
void PyMethod_makeMethodDefine(MimiObj *self, FILE * fp);
void PyMethod_makeMethodDeclear(MimiObj *self, FILE * fp);
void PyMethod_makeMethodFun(MimiObj *self, FILE * fp);
#endif

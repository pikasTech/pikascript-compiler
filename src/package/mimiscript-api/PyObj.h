/* Warning!!! Don't modify this file!!! */
#ifndef __PyObj__H
#define __PyObj__H
#include "MimiObj.h"
#include <stdio.h>
#include <stdlib.h>
MimiObj *New_PyObj(Args *args);
void PyObj_makeNewObj(MimiObj *self, FILE * fp);
void PyObj_makeInlcude(MimiObj *self, FILE * fp);
void PyObj_newObj(MimiObj *self, char * objName, char * className, FILE * fp);
void PyObj_importClass(MimiObj *self, char * className, FILE * fp);
#endif

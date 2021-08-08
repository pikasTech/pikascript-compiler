/* Warning!!! Don't modify this file!!!*/
#ifndef __PyObj__H
#define __PyObj__H
#include "MimiObj.h"
MimiObj *New_PyObj(Args *args);
void PyObj_newObj(MimiObj *self, char * objName, char * className);
void PyObj_importCLass(MimiObj *self, char * className);
#endif

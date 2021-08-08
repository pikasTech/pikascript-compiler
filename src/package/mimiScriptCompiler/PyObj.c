#include "MimiObj.h"
#include "Compiler.h"
#include "dataStrs.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
void PyObj_newObj(MimiObj *self, char *objName, char *className, FILE *fp)
{
}
void PyObj_importClass(MimiObj *self, char *className, FILE *fp)
{
}
void PyObj_makeInlcude(MimiObj *self, FILE *fp)
{
    Args *buffs = New_strBuff();
    char *objName = obj_getStr(self, "name");
    char *className = obj_getStr(self, "class");
    char *inlcudeCmd = args_getBuff(buffs, 512);
    sprintf(inlcudeCmd, "#include \"%s.h\"\n", className);
    fpusWithInfo(inlcudeCmd, fp);
    args_deinit(buffs);
}

void PyObj_makeNewObj(MimiObj *self, FILE *fp)
{
    Args *buffs = New_strBuff();
    char *objName = obj_getStr(self, "name");
    char *className = obj_getStr(self, "class");
    char *importCmd = args_getBuff(buffs, 512);
    char *newObjCmd = args_getBuff(buffs, 512);
    sprintf(importCmd, "    obj_import(self, \"%s\", New_%s);\n",
            className,
            className);
    sprintf(newObjCmd, "    obj_newObj(self, \"%s\", \"%s\");\n",
            objName,
            className);
    fpusWithInfo(importCmd, fp);
    fpusWithInfo(newObjCmd, fp);
    args_deinit(buffs);
}

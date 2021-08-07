#include <stdio.h>
#include <stdlib.h>
#include "BaseObj.h"
#include "dataStrs.h"
#include "PyMethodClass.h"
#include "MimiObj.h"
#include "PyMethod.h"
#include "PyObj.h"

void msc_gererateCode(MimiObj *msc, char *outputPath)
{
    printf("generating class source file.\r\n");
    obj_setStr(msc, "outputPath", outputPath);
    args_foreach(msc->attributeList, pyClass_gererateClassCode, NULL);
    args_foreach(msc->attributeList, pyClass_gererateHeadCode, NULL);
}
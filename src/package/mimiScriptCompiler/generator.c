#include <stdio.h>
#include <stdlib.h>
#include "baseObj.h"
#include "dataStrs.h"
#include "PyMethodClass.h"
#include "MimiObj.h"
#include "PyMethod.h"
#include "PyObj.h"

void msc_gererateClassSourceFile(MimiObj *msc)
{
    printf("generating class source file.\r\n");
    args_foreach(msc->attributeList, pyClass_gererateEachClassSourceFile, NULL);
}

void msc_gererateClassHeadFile(MimiObj *msc)
{
}

void msc_gererateImplHeadFile(MimiObj *msc)
{
}
#include <stdio.h>
#include <stdlib.h>
#include "generator.h"
#include "analyzer.h"
#include "MimiObj.h"
#include "baseObj.h"
#include "dataStrs.h"
#include "PyMethodClass.h"

void compiler_build(MimiObj *msc, char *pythonApiPath)
{
    msc_analizeFile(msc, pythonApiPath);
    msc_gererateClassSourceFile(msc);
}
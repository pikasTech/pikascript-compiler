#include <stdio.h>
#include <stdlib.h>
#include "generator.h"
#include "analyzer.h"
#include "MimiObj.h"
#include "BaseObj.h"
#include "dataStrs.h"
#include "PyMethodClass.h"

void fpusWithInfo(char *string, FILE *fp)
{
    fputs(string, fp);
    printf("%s", string);
}

void compiler_build(MimiObj *msc, char *pythonApiPath, char *outputPath)
{
    msc_analizeFile(msc, pythonApiPath);
    msc_gererateCode(msc, outputPath);
}
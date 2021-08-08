#include <stdio.h>
#include "MimiObj.h"

MimiObj *New_Compiler(Args *args);
void Compiler_build(MimiObj *msc, char *pythonApiPath, char *outputPath);
void Compiler_analizeFile(MimiObj *msc, char *pythonApiPath);
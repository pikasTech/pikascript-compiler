/* Warning!!! Don't modify this file!!! */
#ifndef __Compiler__H
#define __Compiler__H
#include "MimiObj.h"
#include <stdio.h>
#include <stdlib.h>
MimiObj *New_Compiler(Args *args);
int Compiler_analizeLine(MimiObj *self, char * line);
int Compiler_analizeFile(MimiObj *self, char * pythonApiPath);
int Compiler_build(MimiObj *self, char * pythonApiPath, char * outputPath);
#endif

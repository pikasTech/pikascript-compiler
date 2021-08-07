#include <stdio.h>
#include "MimiObj.h"

void pyMethod_generateOneMethod(MimiObj *pyMethod, FILE *fp);
int pyMethod_generateEachMethodDefine(Arg *argEach, Args *handleArgs);
int pyMethod_generateEachMethodFun(Arg *argEach, Args *handleArgs);
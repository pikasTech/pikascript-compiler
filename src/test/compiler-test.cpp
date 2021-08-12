#include "gtest/gtest.h"

extern "C"
{
#include <stdio.h>
#include <stdlib.h>
#include "SysObj.h"
#include "MimiObj.h"
#include "dataMemory.h"
#include "Compiler.h"
}
extern DMEM_STATE DMEMS;
TEST(compiler_test, test1)
{
    char inputBuff[256] = {0};
    MimiObj *msc = newRootObj((char *)"msc", New_Compiler);
    obj_run(msc, (char *)"build('../src/mimiscript-api.py', '../src/dist/')");
    // obj_run(msc, (char *)"build('mimiscript-api.py', 'mimiscript-api/')");

    float dmemBlockNum = DMEM_BLOCK_NUM;
    printf("memory used max = %0.2fKb (%0.2f%) \r\n",
           DMEMS.maxNum * DMEM_BLOCK_SIZE / 1024.0,
           DMEMS.maxNum / dmemBlockNum * 100.0);
    printf("memory request times = %d \r\n", DMEMS.reqTimes);
    obj_deinit(msc);
}

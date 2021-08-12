#include "gtest/gtest.h"

extern "C"
{
#include <stdio.h>
#include <stdlib.h>
#include "SysObj.h"
#include "MimiObj.h"
#include "dataMemory.h"
#include "Compiler.h"
#include "PyClass.h"
#include "PyMethod.h"
#include "PyObj.h"
}
extern DMEM_STATE DMEMS;
TEST(compiler_test, analize1)
{
    MimiObj *msc = newRootObj((char *)"msc", New_Compiler);
    Compiler_analizeLine(msc, (char *)"class Test()");
    obj_deinit(msc);
}

TEST(compiler_test, analize2)
{
    MimiObj *msc = newRootObj((char *)"msc", New_Compiler);
    Compiler_analizeLine(msc, (char *)"class Test()");
    Compiler_analizeLine(msc, (char *)"    def test:");
    Compiler_analizeLine(msc, (char *)"    pass");
    obj_deinit(msc);
}

TEST(compiler_test, analize3)
{
    MimiObj *msc = newRootObj((char *)"msc", New_Compiler);
    Compiler_analizeLine(msc, (char *)"class Test()");
    Compiler_analizeLine(msc, (char *)"    def test:");
    Compiler_analizeLine(msc, (char *)"    pass");
    obj_deinit(msc);
}

TEST(compiler_test, testcompile)
{
    MimiObj *msc = newRootObj((char *)"msc", New_Compiler);
    int res = 0;
    // res = Compiler_build(msc, (char *)"../src/test/test-mimiscript-api2.py", (char *)"../src/dist/");
    EXPECT_EQ(0, res);
    float dmemBlockNum = DMEM_BLOCK_NUM;
    printf("memory used max = %0.2fKb (%0.2f%) \r\n",
           DMEMS.maxNum * DMEM_BLOCK_SIZE / 1024.0,
           DMEMS.maxNum / dmemBlockNum * 100.0);
    printf("memory request times = %d \r\n", DMEMS.reqTimes);
    obj_deinit(msc);
}

TEST(compiler_test, mem)
{
    EXPECT_EQ(DMEMS.blk_num, 0);
}
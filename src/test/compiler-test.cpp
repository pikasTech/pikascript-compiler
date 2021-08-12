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
static int mem;
TEST(compiler_test, analize1)
{
    mem = DMEMS.blk_num;
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

TEST(compiler_test, analizeFile2)
{
    MimiObj *msc = newRootObj((char *)"msc", New_Compiler);
    int res = Compiler_analizeFile(msc, (char *)"../src/test/test-mimiscript-api2.py");
    EXPECT_EQ(0, res);
    obj_deinit(msc);
}

TEST(compiler_test, mem)
{
    EXPECT_EQ(DMEMS.blk_num, mem);
}
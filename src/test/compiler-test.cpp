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
TEST(compiler_test, membefore)
{
    EXPECT_EQ(DMEMS.blk_num, 0);
    mem = DMEMS.blk_num;
}

TEST(compiler_test, analize1)
{
    MimiObj *msc = newRootObj((char *)"msc", New_Compiler);
    Compiler_analizeLine(msc, (char *)"class Test()");
    obj_deinit(msc);
    EXPECT_EQ(DMEMS.blk_num, mem);
}

TEST(compiler_test, analize2)
{
    mem = DMEMS.blk_num;
    MimiObj *msc = newRootObj((char *)"msc", New_Compiler);
    Compiler_analizeLine(msc, (char *)"class Test()");
    Compiler_analizeLine(msc, (char *)"    def test:");
    Compiler_analizeLine(msc, (char *)"    pass");
    obj_deinit(msc);
    EXPECT_EQ(DMEMS.blk_num, mem);
}

TEST(compiler_test, analize3)
{
    mem = DMEMS.blk_num;
    MimiObj *msc = newRootObj((char *)"msc", New_Compiler);
    Compiler_analizeLine(msc, (char *)"class Test()");
    Compiler_analizeLine(msc, (char *)"    def test:");
    Compiler_analizeLine(msc, (char *)"    pass");
    obj_deinit(msc);
    EXPECT_EQ(DMEMS.blk_num, mem);
}

TEST(compiler_test, analize4)
{
    mem = DMEMS.blk_num;
    MimiObj *msc = newRootObj((char *)"msc", New_Compiler);
    Compiler_analizeLine(msc, (char *)"class Compiler(SysObj):");
    Compiler_analizeLine(msc, (char *)"    PyClass()");
    obj_deinit(msc);
    EXPECT_EQ(DMEMS.blk_num, mem);
}

TEST(compiler_test, analize5)
{
    mem = DMEMS.blk_num;
    MimiObj *msc = newRootObj((char *)"msc", New_Compiler);
    Compiler_analizeLine(msc, (char *)"class Compiler(SysObj):");
    Compiler_analizeLine(msc, (char *)"    def analizeFile(pythonApiPath: str):");
    Compiler_analizeLine(msc, (char *)"    pass");
    obj_deinit(msc);
    EXPECT_EQ(DMEMS.blk_num, mem);
}

TEST(compiler_test, analizeFile1)
{
    mem = DMEMS.blk_num;
    MimiObj *msc = newRootObj((char *)"msc", New_Compiler);
    int res = Compiler_analizeFile(msc, (char *)"../src/test/test-mimiscript-api.py");
    EXPECT_EQ(0, res);
    obj_deinit(msc);
    EXPECT_EQ(DMEMS.blk_num, mem);
}

TEST(compiler_test, analizeFile2)
{
    mem = DMEMS.blk_num;
    MimiObj *msc = newRootObj((char *)"msc", New_Compiler);
    int res = Compiler_analizeFile(msc, (char *)"../src/test/test-mimiscript-api2.py");
    EXPECT_EQ(0, res);
    obj_deinit(msc);
    EXPECT_EQ(DMEMS.blk_num, mem);
}

TEST(compiler_test, analizeFile3)
{
    mem = DMEMS.blk_num;
    MimiObj *msc = newRootObj((char *)"msc", New_Compiler);
    int res = Compiler_analizeFile(msc, (char *)"../src/test/test-mimiscript-api3.py");
    EXPECT_EQ(0, res);
    obj_deinit(msc);
    EXPECT_EQ(DMEMS.blk_num, mem);
}

TEST(compiler_test, analizeFile4)
{
    mem = DMEMS.blk_num;
    MimiObj *msc = newRootObj((char *)"msc", New_Compiler);
    int res = Compiler_analizeFile(msc, (char *)"../src/test/test-mimiscript-api4.py");
    EXPECT_EQ(0, res);
    obj_deinit(msc);
    EXPECT_EQ(DMEMS.blk_num, mem);
}

TEST(compiler_test, analizeFile5)
{
    mem = DMEMS.blk_num;
    MimiObj *msc = newRootObj((char *)"msc", New_Compiler);
    int res = Compiler_analizeFile(msc, (char *)"../src/test/test-mimiscript-api5.py");
    EXPECT_EQ(0, res);
    obj_deinit(msc);
    EXPECT_EQ(DMEMS.blk_num, mem);
}

TEST(compiler_test, build2)
{
    MimiObj *msc = newRootObj((char *)"msc", New_Compiler);
    int res = Compiler_build(msc, (char *)"../src/test/test-mimiscript-api2.py", (char *)"../src/dist/");
    EXPECT_EQ(0, res);
    obj_deinit(msc);
}

TEST(compiler_test, build2_mem)
{
    EXPECT_EQ(DMEMS.blk_num, mem);
    mem = DMEMS.blk_num;
}

TEST(compiler_test, build3)
{
    MimiObj *msc = newRootObj((char *)"msc", New_Compiler);
    int res = Compiler_build(msc, (char *)"../src/test/test-mimiscript-api3.py", (char *)"../src/dist/");
    EXPECT_EQ(0, res);
    obj_deinit(msc);
}

TEST(compiler_test, build3_mem)
{
    EXPECT_EQ(DMEMS.blk_num, mem);
    mem = DMEMS.blk_num;
}

TEST(compiler_test, build4)
{
    MimiObj *msc = newRootObj((char *)"msc", New_Compiler);
    int res = Compiler_build(msc, (char *)"../src/test/test-mimiscript-api4.py", (char *)"../src/dist/");
    EXPECT_EQ(0, res);
    obj_deinit(msc);
}

TEST(compiler_test, build4_mem)
{
    EXPECT_EQ(DMEMS.blk_num, mem);
    mem = DMEMS.blk_num;
}

TEST(compiler_test, build5)
{
    MimiObj *msc = newRootObj((char *)"msc", New_Compiler);
    int res = Compiler_build(msc, (char *)"../src/test/test-mimiscript-api5.py", (char *)"../src/dist/");
    EXPECT_EQ(0, res);
    obj_deinit(msc);
}

TEST(compiler_test, build5_mem)
{
    EXPECT_EQ(DMEMS.blk_num, mem);
    mem = DMEMS.blk_num;
}

TEST(compiler_test, build1)
{
    MimiObj *msc = newRootObj((char *)"msc", New_Compiler);
    int res = Compiler_build(msc, (char *)"../src/test/test-mimiscript-api.py", (char *)"../src/dist/");
    EXPECT_EQ(0, res);
    obj_deinit(msc);
}

TEST(compiler_test, build1_mem)
{
    EXPECT_EQ(DMEMS.blk_num, mem);
    mem = DMEMS.blk_num;
}

TEST(compiler_test, getImport)
{
    MimiObj *msc = newRootObj((char *)"msc", New_Compiler);
    Compiler_analizeLine(msc, (char *)"class Compiler(SysObj):");
    Compiler_analizeLine(msc, (char *)"    PyClass()");
    MimiObj *Compiler = obj_getObj(msc, (char *)"Compiler", 0);
    Args *buffs = New_args(NULL);
    char *allInclude = PyClass_getImportInclude(Compiler, buffs);
    printf("all inlcude is :%s\r\n", allInclude);
    args_deinit(buffs);
    obj_deinit(msc);
}
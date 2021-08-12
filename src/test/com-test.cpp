#include "gtest/gtest.h"
extern "C"
{
#include "mimiCom.h"
#include "dataString.h"
}

TEST(com_test, test1)
{
    MimiCom *com = New_mimiCom(NULL);
    com->getChar(com, 'a');
    com->getChar(com, 'a');
    com->getChar(com, 'a');
    com->getChar(com, '\r');
    com->getChar(com, '\n');

    char *RxSingleLine = args_getStr(com->args, (char *)"RxSingleLine");
    EXPECT_TRUE(strEqu((char *)"aaa", RxSingleLine));
    com->deinit(com);
}

extern DMEM_STATE DMEMS;
TEST(com_test, mem)
{
    EXPECT_EQ(DMEMS.blk_num, 0);
}
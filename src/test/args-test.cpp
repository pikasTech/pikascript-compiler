#include "gtest/gtest.h"
extern "C"
{
#include "dataArgs.h"
}

TEST(blaTest, test1)
{
    //arrange
    //act
    //assert
    Args *args = New_args(NULL);
    args_setInt(args, "a", 1);
    int a = args_getInt(args, "a");
    EXPECT_EQ(a,1);
}
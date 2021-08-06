#include <stdio.h>
#include <stdlib.h>
#include "sysObj.h"
#include "MimiObj.h"

#include "CompilerClass.h"

int main()
{
    char inputBuff[256] = {0};
    MimiObj *root = newRootObj("msc", New_Compiler);
    while (1)
    {
        fgets(inputBuff, sizeof(inputBuff), stdin);
        /* get user input */
        fgets(inputBuff, sizeof(inputBuff), stdin);

        /* run mimiScript and get res */
        Args *resArgs = obj_runDirect(root, inputBuff);

        /* get system output of mimiScript*/
        char *sysOut = args_getStr(resArgs, "sysOut");

        if (NULL != sysOut)
        {
            /* print out the system output */
            printf("%s\r\n", sysOut);
        }

        /* deinit the res */
        args_deinit(resArgs);
    }
}

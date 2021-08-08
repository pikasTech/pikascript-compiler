#include <stdio.h>
#include <stdlib.h>
#include "SysObj.h"
#include "MimiObj.h"
#include "dataMemory.h"

#include "CompilerClass.h"
extern DMEM_STATE DMEMS;
int main()
{
    char inputBuff[256] = {0};
    MimiObj *msc = newRootObj("msc", New_Compiler);
    obj_run(msc, "build('../src/mimiscript-api.py', '../src/package/mimiscript-api/')");

    float dmemBlockNum = DMEM_BLOCK_NUM;
    printf("memory used max = %0.2fKb (%0.2f%) \r\n",
           DMEMS.maxNum * DMEM_BLOCK_SIZE / 1024.0,
           DMEMS.maxNum / dmemBlockNum * 100.0);
    printf("memory request times = %d \r\n", DMEMS.reqTimes);
    return 0;

    while (1)
    {
        fgets(inputBuff, sizeof(inputBuff), stdin);

        /* run mimiScript and get res */
        Args *resArgs = obj_runDirect(msc, inputBuff);

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



#include "xc.h"
#include "pepin024_lab6_DELAY_v001.h"
#include <p24Fxxxx.h>

void wait(int t)
{
    int i = 0;
    while(i<t)
    {
        delay_1ms();
        i++;
    }
}


#include "Gpt.h"

extern Gpt_NotifyType settedCallbackFunc;

TIMER1A_Handler()
{
    settedCallbackFunc();
}


#include "tm4c123gh6pm.h" // Header file accesses registers in TMC123 microcontroller
#include <stdint.h>
#include "Dio.h"
#include "Port.h"
#include "Gpt.h"
#include "Irq.h"

void timerISRcustom(void)
{
  if (TIMER1->MIS & 0x1)
    Dio_FlipChannel(PortF_PIN3);
  TIMER1->ICR = 0x1; /* Timer1A timeout flag bit clears*/
}

const Port_ConfigType Port_Configuration[] = {

    {PORT_PIN_LED1_DIRECTION,
     PORT_PIN_LED1_ID,
     PORT_PIN_LED1_INITIAL_MODE,
     PORT_PIN_LED1_LEVEL_VALUE,
     PORT_PIN_LED1_INTERNAL_RESISTOR},

};

const Gpt_ConfigType Gpt_Configuration[] = {
    {
        .gptChannelID = TIMER1_ID,
        .tickValueMax = TIMER_1_MAX_TICK,
        .channelMode = GPT_CH_MODE_CONTINUOUS,
        .fnPtrNotifyFunction = timerISRcustom,
        .prescale = 250,
    },

};

int main(void)
{
  Port_Init(&Port_Configuration[0]);
  Gpt_Init(&Gpt_Configuration[0]);
  Gpt_StartTimer(TIMER1_ID, 64000);
}

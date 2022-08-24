#include "Gpt.h"
#include "Common_Macros.h"

Gpt_NotifyType settedCallbackFunc;

void Gpt_StartTimer(Gpt_ChannelType channel, Gpt_ValueType period_ticks)
{

    volatile uint32_t *baseRegAddr = 0; /* point to the required Port Registers base address */
    switch (channel)
    {
    case TIMER0_ID:
        baseRegAddr = TIMER0_BASE_ADDRESS;
        break;
    case TIMER1_ID:
        baseRegAddr = TIMER1_BASE_ADDRESS;
        break;
    case TIMER2_ID:
        baseRegAddr = TIMER2_BASE_ADDRESS;
        break;
    case TIMER3_ID:
        baseRegAddr = TIMER3_BASE_ADDRESS;
        break;
    case TIMER4_ID:
        baseRegAddr = TIMER4_BASE_ADDRESS;
        break;
    case TIMER5_ID:
        baseRegAddr = TIMER5_BASE_ADDRESS;
        break;
    };
    *(volatile uint32_t *)((volatile uint8_t *)baseRegAddr + TIMER_TAILR_REG_OFFSET) = period_ticks; // set timer overflow
    SET_BIT(*(volatile uint32_t *)((volatile uint8_t *)baseRegAddr + TIMER_CTL_REG_OFFSET), 0);      //Enable timer A
}

void Gpt_StopTimer(Gpt_ChannelType channel)
{
    volatile uint32_t *baseRegAddr = 0; /* point to the required Port Registers base address */
    switch (channel)
    {
    case TIMER0_ID:
        baseRegAddr = TIMER0_BASE_ADDRESS;
        break;
    case TIMER1_ID:
        baseRegAddr = TIMER1_BASE_ADDRESS;
        break;
    case TIMER2_ID:
        baseRegAddr = TIMER2_BASE_ADDRESS;
        break;
    case TIMER3_ID:
        baseRegAddr = TIMER3_BASE_ADDRESS;
        break;
    case TIMER4_ID:
        baseRegAddr = TIMER4_BASE_ADDRESS;
        break;
    case TIMER5_ID:
        baseRegAddr = TIMER5_BASE_ADDRESS;
        break;
    };
    CLEAR_BIT(*(volatile uint32_t *)((volatile uint8_t *)baseRegAddr + TIMER_CTL_REG_OFFSET), 0); //Enable timer A
}

void Gpt_Init(const Gpt_ConfigType *ConfigPtr)
{
    volatile uint32_t *baseRegAddr = 0; /* point to the required Port Registers base address */
    switch (ConfigPtr->gptChannelID)
    {
    case TIMER0_ID:
        baseRegAddr = TIMER0_BASE_ADDRESS;
        break;
    case TIMER1_ID:
        baseRegAddr = TIMER1_BASE_ADDRESS;
        break;
    case TIMER2_ID:
        baseRegAddr = TIMER2_BASE_ADDRESS;
        break;
    case TIMER3_ID:
        baseRegAddr = TIMER3_BASE_ADDRESS;
        break;
    case TIMER4_ID:
        baseRegAddr = TIMER4_BASE_ADDRESS;
        break;
    case TIMER5_ID:
        baseRegAddr = TIMER5_BASE_ADDRESS;
        break;
    };

    CLEAR_BIT(*(volatile uint32_t *)((volatile uint8_t *)baseRegAddr + TIMER_CTL_REG_OFFSET), 0); //disable timer A
    CLEAR_BIT(*(volatile uint32_t *)((volatile uint8_t *)baseRegAddr + TIMER_CTL_REG_OFFSET), 8); //disable timer B
    if ((ConfigPtr->tickValueMax) > (uint32_t)65535)
    {
        *(volatile uint32_t *)((volatile uint8_t *)baseRegAddr + TIMER_CFG_REG_OFFSET) = 0x00; // set timer As 32 bit timer
    }
    else
    {
        *(volatile uint32_t *)((volatile uint8_t *)baseRegAddr + TIMER_CFG_REG_OFFSET) = 0x04; // set as 16 bit timer
    }
    if (ConfigPtr->channelMode == GPT_CH_MODE_CONTINUOUS)
    {
        SET_BIT(*(volatile uint32_t *)((volatile uint8_t *)baseRegAddr + TIMER_TAMR_REG_OFFSET), 1); //Continous mode
    }
    else
    {
        SET_BIT(*(volatile uint32_t *)((volatile uint8_t *)baseRegAddr + TIMER_TAMR_REG_OFFSET), 0); //One shot mode
    }
    CLEAR_BIT(*(volatile uint32_t *)((volatile uint8_t *)baseRegAddr + TIMER_TAMR_REG_OFFSET), 4); //set as decrement counter

    *(volatile uint32_t *)((volatile uint8_t *)baseRegAddr + TIMER_TAPR_REG_OFFSET) = ConfigPtr->prescale;
    *(volatile uint32_t *)((volatile uint8_t *)baseRegAddr + TIMER_ICR_REG_OFFSET) = 0x1;       // clear all interrupt flags
    SET_BIT(*(volatile uint32_t *)((volatile uint8_t *)baseRegAddr + TIMER_IMR_REG_OFFSET), 0); //Enable overflow/Timeout interrupt

    settedCallbackFunc = ConfigPtr->fnPtrNotifyFunction;

    // *(volatile uint32_t *)((volatile uint8_t *)baseRegAddr + TIMER_TAILR_REG_OFFSET) = ConfigPtr->tickValueMax; // set timer overflow
}
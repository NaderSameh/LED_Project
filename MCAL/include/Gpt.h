#ifndef GPT_H
#define GPT_H

#include "stdint.h"
#include "Gpt_Cfg.h"

#define TIMER0_ID 0
#define TIMER1_ID 1
#define TIMER2_ID 2
#define TIMER3_ID 3
#define TIMER4_ID 4
#define TIMER5_ID 5

#define TIMER0_BASE_ADDRESS 0x40030000UL
#define TIMER1_BASE_ADDRESS 0x40031000UL
#define TIMER2_BASE_ADDRESS 0x40032000UL
#define TIMER3_BASE_ADDRESS 0x40033000UL
#define TIMER4_BASE_ADDRESS 0x40034000UL
#define TIMER5_BASE_ADDRESS 0x40035000UL

#define TIMER_SYSCTL_BASE_REG 0x400FE000UL
#define TIMER_RCGCTIMER_REG_OFFSET 0x604

#define TIMER_CTL_REG_OFFSET 0x00C
#define TIMER_CFG_REG_OFFSET 0x000
#define TIMER_TAMR_REG_OFFSET 0x004
#define TIMER_TAPR_REG_OFFSET 0x038
#define TIMER_TAILR_REG_OFFSET 0x028
#define TIMER_ICR_REG_OFFSET 0x018
#define TIMER_IMR_REG_OFFSET 0x024

typedef uint8_t Gpt_ChannelType;
typedef uint16_t Gpt_ValueType;
typedef void (*Gpt_NotifyType)(void);

typedef uint8_t Gpt_PrescaleValueType;

enum Gpt_ChannelMode
{
    GPT_CH_MODE_CONTINUOUS = 0U,
    GPT_CH_MODE_ONESHOT
};

enum Gpt_ChannelStateType
{
    GPT_UNINITIALIZED = 0U,
    GPT_INITIALIZED,
    GPT_RUNNING,
    GPT_STOPPED,
    GPT_EXPIRED
};

typedef struct
{
    Gpt_ChannelType gptChannelID;
    uint32_t tickValueMax;
    enum Gpt_ChannelMode channelMode;
    Gpt_NotifyType fnPtrNotifyFunction;
    Gpt_PrescaleValueType prescale;
} Gpt_ConfigType;

void Gpt_StartTimer(Gpt_ChannelType channel, Gpt_ValueType period_ticks);

void Gpt_StopTimer(Gpt_ChannelType channel);

void Gpt_Init(const Gpt_ConfigType *ConfigPtr);

#endif

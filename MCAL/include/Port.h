
#ifndef PORT_H
#define PORT_H

#include <stdint.h>
#include "Port_Cfg.h"

#define GPIO_PORTA_BASE_ADDRESS 0x40004000U
#define GPIO_PORTE_BASE_ADDRESS 0x40024000U
#define GPIO_PORTF_BASE_ADDRESS 0x40025000U

#define GPIO_PORTF_LOCK_R (*((volatile unsigned long *)0x40025520))
#define GPIO_PORTF_CR_R (*((volatile unsigned long *)0x40025524))

// Registers Offsets

#define PORT_DATA_REG_OFFSET 0x3FC
#define PORT_DIR_REG_OFFSET 0x400
#define PORT_ALT_FUNC_REG_OFFSET 0x420
#define PORT_PULL_UP_REG_OFFSET 0x510
#define PORT_PULL_DOWN_REG_OFFSET 0x514
#define PORT_DIGITAL_ENABLE_REG_OFFSET 0x51C
#define PORT_LOCK_REG_OFFSET 0x520
#define PORT_COMMIT_REG_OFFSET 0x524
#define PORT_ANALOG_MODE_SEL_REG_OFFSET 0x528
#define PORT_CTL_REG_OFFSET 0x52C

// PIN MODES

#define MAX_MODE_NUMBER 15
#define PORT_PIN_MODE_ADC (0U)
#define PORT_PIN_MODE_DIO (10U)
#define PORT_PIN_NOT_ACTIVE (9U)
#define PORT_PIN_MODE_UART (1U)
#define PORT_PIN_MODE_SSI (2U)
#define PORT_PIN_MODE_UART1 (2U)
#define PORT_PIN_MODE_I2C (3U)
#define PORT_PIN_MODE_CAN0 (3U)
#define PORT_PIN_MODE_PWM0 (4U)
#define PORT_PIN_MODE_PWM1 (5U)
#define PORT_PIN_MODE_QEI (6U)
#define PORT_PIN_MODE_GPT (7U)
#define PORT_PIN_MODE_CAN (8U)
#define PORT_PIN_MODE_USB (8U)

// PIN LEVELS

#define PORT_PIN_LEVEL_HIGH 0x01
#define PORT_PIN_LEVEL_LOW 0x00

//typedef uint8_t Port_PinType;
typedef enum
{
    PORT_PIN_IN,
    PORT_PIN_OUT
} Port_PinDirectionType;

typedef uint8_t Port_PinModeType;
typedef uint8_t Port_PinLevelType;
typedef enum
{
    PORT_RESISTOR_OFF,
    PORT_RESISTOR_PULL_UP,
    PORT_RESISTOR_PULL_DOWN
} Port_InternalResistorType;

typedef struct
{
    Port_PinDirectionType pinDirection;
    Port_PinType pinId;
    Port_PinModeType pinInitialMode;
    Port_PinLevelType pinInitialLevel;
    Port_InternalResistorType pinInternalResistor;
} Port_ConfigType;

void Port_Init(const Port_ConfigType *ConfigPtr);

#endif /* PORT_H */
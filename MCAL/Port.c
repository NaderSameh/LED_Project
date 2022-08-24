/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Nader Sameh
 ******************************************************************************/

#include "Port.h"
#include "Common_Macros.h"
#include "tm4c123gh6pm_registers.h"

void Port_Init(const Port_ConfigType *ConfigPtr)
{

    volatile uint32_t *baseRegAddr = 0; /* point to the required Port Registers base address */
    volatile uint32_t delay = 0;

    // If ports A to D. Ports E and F don't have 8 pins so they're treated differently.
    if (ConfigPtr->pinId <= PortD_PIN7)
    {
        baseRegAddr = (volatile uint32_t *)(GPIO_PORTA_BASE_ADDRESS + ((ConfigPtr->pinId / 8) * (0x1000)));
    }
    else if (ConfigPtr->pinId <= PortE_PIN5)
    {
        baseRegAddr = (volatile uint32_t *)GPIO_PORTE_BASE_ADDRESS;
    }
    else
    {
        baseRegAddr = (volatile uint32_t *)GPIO_PORTF_BASE_ADDRESS;
    }

    SYSCTL_REGCGC2_REG |= (1 << (ConfigPtr->pinId / 8));
    delay = SYSCTL_REGCGC2_REG;
    GPIO_PORTF_LOCK_R = 0x4C4F434B; // 2) unlock PortF PF0
    GPIO_PORTF_CR_R = 0x1F;         // allow changes to PF4-0

    // if ((((ConfigPtr->pinId / 8) == 3) && ((ConfigPtr->pinId % 8) == 7)) || (((ConfigPtr->pinId / 8) == 5) && ((ConfigPtr->pinId % 8) == 0))) /* PD7 or PF0 */
    // {
    //     *(volatile uint32_t *)((volatile uint8_t *)baseRegAddr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                       /* Unlock the GPIOCR register */
    //     SET_BIT(*(volatile uint32_t *)((volatile uint8_t *)baseRegAddr + PORT_COMMIT_REG_OFFSET), (ConfigPtr->pinId % 8)); /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
    // }
    // else if (((ConfigPtr->pinId / 8) == 2) && ((ConfigPtr->pinId % 8) <= 3)) /* PC0 to PC3 */
    // {
    //     /* Do Nothing ...  this is the JTAG pins */
    //     return;
    // }
    // else
    // {
    //     /* Do Nothing ... No need to unlock the commit register for this pin */
    // }

    CLEAR_BIT(*(volatile uint32_t *)((volatile uint8_t *)baseRegAddr + PORT_ANALOG_MODE_SEL_REG_OFFSET), (ConfigPtr->pinId % 8));   /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
    CLEAR_BIT(*(volatile uint32_t *)((volatile uint8_t *)baseRegAddr + PORT_ALT_FUNC_REG_OFFSET), (ConfigPtr->pinId % 8));          /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
    *(volatile uint32_t *)((volatile uint8_t *)baseRegAddr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << ((ConfigPtr->pinId % 8) * 4)); /* Clear the PMCx bits for this pin */

    if (ConfigPtr->pinDirection == PORT_PIN_OUT)
    {
        SET_BIT(*(volatile uint32_t *)((volatile uint8_t *)baseRegAddr + PORT_DIR_REG_OFFSET), (ConfigPtr->pinId % 8)); /* Set the corresponding bit in the GPIODIR register to configure it as output pin */

        if (ConfigPtr->pinInitialLevel == 0x01)
        {
            SET_BIT(*(volatile uint32_t *)((volatile uint8_t *)baseRegAddr + PORT_DATA_REG_OFFSET), (ConfigPtr->pinId % 8)); /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
        }
        else
        {
            CLEAR_BIT(*(volatile uint32_t *)((volatile uint8_t *)baseRegAddr + PORT_DATA_REG_OFFSET), (ConfigPtr->pinId % 8)); /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
        }
    }
    else if (ConfigPtr->pinDirection == PORT_PIN_IN)
    {
        CLEAR_BIT(*(volatile uint32_t *)((volatile uint8_t *)baseRegAddr + PORT_DIR_REG_OFFSET), (ConfigPtr->pinId % 8)); /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */

        if (ConfigPtr->pinInternalResistor == PORT_RESISTOR_PULL_UP)
        {
            SET_BIT(*(volatile uint32_t *)((volatile uint8_t *)baseRegAddr + PORT_PULL_UP_REG_OFFSET), (ConfigPtr->pinId % 8)); /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
        }
        else if (ConfigPtr->pinInternalResistor == PORT_RESISTOR_PULL_DOWN)
        {
            SET_BIT(*(volatile uint32_t *)((volatile uint8_t *)baseRegAddr + PORT_PULL_DOWN_REG_OFFSET), (ConfigPtr->pinId % 8)); /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
        }
        else
        {
            CLEAR_BIT(*(volatile uint32_t *)((volatile uint8_t *)baseRegAddr + PORT_PULL_UP_REG_OFFSET), (ConfigPtr->pinId % 8));   /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
            CLEAR_BIT(*(volatile uint32_t *)((volatile uint8_t *)baseRegAddr + PORT_PULL_DOWN_REG_OFFSET), (ConfigPtr->pinId % 8)); /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
        }
    }
    else
    {
        /* Do Nothing */
    }

    SET_BIT(*(volatile uint32_t *)((volatile uint8_t *)baseRegAddr + PORT_DIGITAL_ENABLE_REG_OFFSET), (ConfigPtr->pinId % 8)); /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
}

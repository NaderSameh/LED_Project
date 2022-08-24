/******************************************************************************
 *
 * Module: Dio
 *
 * File Name: Dio.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Dio Driver
 *
 * Author: Nader Sameh
 ******************************************************************************/

#include "Dio.h"
#include "Dio_Regs.h"
#include "Common_Macros.h"

#define DIO_GET_PORT_FROM_CHANNEL_ID(_channelId) (_channelId / 8)

/************************************************************************************
* Service Name: Dio_WriteChannel
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelId - ID of DIO channel.
*                  Level - Value to be written.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to set a level of a channel.
************************************************************************************/
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)
{
    volatile uint32_t *Port_Ptr = 0;
    uint8_t port = DIO_GET_PORT_FROM_CHANNEL_ID(ChannelId);
    /* Point to the correct PORT register according to the Port Id stored in the Port_Num member */
    switch (port)
    {
    case 0:
        Port_Ptr = &GPIO_PORTA_DATA_REG;
        break;
    case 1:
        Port_Ptr = &GPIO_PORTB_DATA_REG;
        break;
    case 2:
        Port_Ptr = &GPIO_PORTC_DATA_REG;
        break;
    case 3:
        Port_Ptr = &GPIO_PORTD_DATA_REG;
        break;
    case 4:
        Port_Ptr = &GPIO_PORTE_DATA_REG;
        break;
    case 5:
        Port_Ptr = &GPIO_PORTF_DATA_REG;
        break;
    }
    if (Level == 0x01)
    {
        /* Write Logic High */
        SET_BIT(*Port_Ptr, ChannelId % 8);
    }
    else if (Level == 0x00)
    {
        /* Write Logic Low */
        CLEAR_BIT(*Port_Ptr, ChannelId % 8);
    }
}

/************************************************************************************
* Service Name: Dio_ReadChannel
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelId - ID of DIO channel.
* Parameters (inout): None
* Parameters (out): None
* Return value: Dio_LevelType
* Description: Function to return the value of the specified DIO channel.
************************************************************************************/
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
    volatile uint32_t *Port_Ptr = 0;
    uint8_t port = DIO_GET_PORT_FROM_CHANNEL_ID(ChannelId);
    Dio_LevelType output;
    /* Point to the correct PORT register according to the Port Id stored in the Port_Num member */
    switch (port)
    {
    case 0:
        Port_Ptr = &GPIO_PORTA_DATA_REG;
        break;
    case 1:
        Port_Ptr = &GPIO_PORTB_DATA_REG;
        break;
    case 2:
        Port_Ptr = &GPIO_PORTC_DATA_REG;
        break;
    case 3:
        Port_Ptr = &GPIO_PORTD_DATA_REG;
        break;
    case 4:
        Port_Ptr = &GPIO_PORTE_DATA_REG;
        break;
    case 5:
        Port_Ptr = &GPIO_PORTF_DATA_REG;
        break;
    }
    /* Read the required channel */
    if (BIT_IS_SET(*Port_Ptr, ChannelId % 8))
    {
        output = 0x01;
    }
    else
    {
        output = 0x00;
    }

    return output;
}
/************************************************************************************
Service name: Dio_FlipChannel
Service ID[hex]: 0x11
Sync/Async: Synchronous
Reentrancy: Reentrant
Parameters (in): ChannelId ID of DIO channel
Parameters
(inout):
None
Parameters (out): None
Return value:
Dio_LevelType STD_HIGH: The physical level of the corresponding Pin is
STD_HIGH.
STD_LOW: The physical level of the corresponding Pin is
STD_LOW.
Description: Service to flip (change from 1 to 0 or from 0 to 1) the level of a channel and return
the level of the channel after flip
************************************************************************************/

Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId)
{
    volatile uint32_t *Port_Ptr = 0;
    uint8_t port = DIO_GET_PORT_FROM_CHANNEL_ID(ChannelId);
    Dio_LevelType output;
    /* Point to the correct PORT register according to the Port Id stored in the Port_Num member */
    switch (port)
    {
    case 0:
        Port_Ptr = &GPIO_PORTA_DATA_REG;
        break;
    case 1:
        Port_Ptr = &GPIO_PORTB_DATA_REG;
        break;
    case 2:
        Port_Ptr = &GPIO_PORTC_DATA_REG;
        break;
    case 3:
        Port_Ptr = &GPIO_PORTD_DATA_REG;
        break;
    case 4:
        Port_Ptr = &GPIO_PORTE_DATA_REG;
        break;
    case 5:
        Port_Ptr = &GPIO_PORTF_DATA_REG;
        break;
    }
    /* flip the required channel */

    TOGGLE_BIT(*Port_Ptr, ChannelId % 8);
    if (BIT_IS_SET(*Port_Ptr, ChannelId % 8))
    {
        output = 0x01;
    }
    else
    {
        output = 0x00;
    }

    return output;
}
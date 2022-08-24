
/******************************************************************************
 *
 * Module: Dio
 *
 * File Name: Dio.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Dio Driver
 *
 * Author: Nader Sameh
 ******************************************************************************/

#ifndef DIO_H
#define DIO_H

#include <stdint.h>

/* Type definition for Dio_LevelType used by the DIO APIs */
typedef uint8_t Dio_LevelType;

/* Type definition for Dio_ChannelType used by the DIO APIs */
typedef uint8_t Dio_ChannelType;

/* Type definition for Dio_PortType used by the DIO APIs */
typedef uint8_t Dio_PortType;

/* Type definition for Dio_PortLevelType used by the DIO APIs */
typedef uint8_t Dio_PortLevelType;

/* Function for DIO read Port API */
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);

/* Function for DIO write Port API */
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);

Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId);

#endif
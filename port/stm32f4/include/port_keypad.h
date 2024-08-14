/**
 * @file port_keypad.h
 * @brief Header for port_keypad.c file.
 * @author Pablo de la Cruz Gómez
 * @author David Fuentes Martin
 * @date 19/05/2024
 */

#ifndef PORT_KEYPAD_H_
#define PORT_KEYPAD_H_

/* Includes ------------------------------------------------------------------*/
/* Standard C includes */
#include <stdint.h>
#include <stdbool.h>
#include "port_system.h"
#include <stm32f446xx.h>
#include "stdio.h"

/* Defines and enums ----------------------------------------------------------*/
/* Defines */

#define KEYPAD_0_ID 0                   /*!< Id of the Keypad*/
#define KEYPAD_0_GPIO GPIOC             /*!< Port of Keypad GPIO*/

/**
 * @brief Initializes a buzzer object given a buzzer ID.
 * 
 */
void port_keypad_init(void);

/**
 * @brief Reads the Key that is being pressed from an array of posible chars.
 * 
 * @return char The key that is being pressed.
 */
char port_keypad_read(void);

/**
 * @brief Decodes the char with the column and row.
 * 
 * @param col Column of the key that is being pressed.
 * @param row Row of the key that is being pressed
 * @return char The key that is being pressed.
 */
char decode_keypad(uint8_t col, uint8_t row);

#endif
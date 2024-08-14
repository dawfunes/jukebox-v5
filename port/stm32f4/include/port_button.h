/**
 * @file port_button.h
 * @brief Header for port_button.c file.
 * @author Pablo de la Cruz Gómez
 * @author David Fuentes Martin
 * @date 27/02/2024
 */

#ifndef PORT_BUTTON_H_
#define PORT_BUTTON_H_

/* Includes ------------------------------------------------------------------*/
/* Standard C includes */
#include <stdint.h>
#include <stdbool.h>
#include "port_system.h"
#include <stm32f446xx.h>

/* HW dependent includes */

/* Defines and enums ----------------------------------------------------------*/
/* Defines */

#define BUTTON_0_ID 0                   /*!< Id of the Button*/
#define BUTTON_0_GPIO GPIOC             /*!< Port of Button GPIO*/
#define BUTTON_0_PIN 13                 /*!< Pin of Button GPIO*/
#define BUTTON_0_DEBOUNCE_TIME_MS 150   /*!< Debounce time of the Button*/

/* Typedefs --------------------------------------------------------------------*/
/**
 * @brief HW structure of button
 * 
 * @param *p_port
 * @param pin
 * @param flag_pressed
 */
typedef struct
{
    GPIO_TypeDef *p_port;
    uint8_t pin;
    bool flag_pressed;
} port_button_hw_t;

/* Global variables */
/**
 * @brief array for the HW characteristics of buttons
 * 
 */
extern port_button_hw_t buttons_arr[];

/* Function prototypes and explanation -------------------------------------------------*/
/**
 * @brief Function for the configuration of the HW specificatios of button.
 * Configures the button as input with no pull up neither pull down calling the function 
 * port_system_gpio_config with the port and pin of the button given.
 * Then, configures the interruption mode for rising and falling edges, and interrupt request 
 * enabled, by calling port_system_gpio_config_exti with the port and pin of the button given.
 * And, configures the button to enable interrupt line and sets priority to 1 and subprority to 0.
 * 
 * @param button_id ID of button given
 */
void port_button_init(uint32_t button_id);

/**
 * @brief return if button is pressed or not pressed
 * 
 * @param button_id ID of button given
 * @return true if button is pressed
 * @return false if button isn't pressed
 */
bool port_button_is_pressed(uint32_t button_id);
/**
 * @brief return the System tick (in ms)
 * 
 * @return uint32_t number of ticks (in ms)
 */
uint32_t port_button_get_tick();

#endif

/**
 * @file port_buzzer.h
 * @brief Header for port_buzzer.c file.
 * @author David Fuentes Martín
 * @author Pablo de la Cruz
 * @date 09/04/2024
 */
#ifndef PORT_BUZZER_H_
#define PORT_BUZZER_H_

/* Includes ------------------------------------------------------------------*/
/* Standard C includes */
#include <stdint.h>
#include <stdbool.h>

/* HW dependent includes */
#include "port_system.h"

/* Defines and enums ----------------------------------------------------------*/
/* Defines */

#define BUZZER_0_ID 0                   /*!< Id of the Buzzer*/
#define BUZZER_0_GPIO GPIOA             /*!< Port of Buzzer GPIO*/ 
#define BUZZER_0_PIN 6                  /*!< Pin of Buzzer GPIO*/
#define BUZZER_PWM_DC 0.5               /*!< Duty Cycle of the Buzzer*/

/* Typedefs --------------------------------------------------------------------*/

/**
 * @brief HW structure of buzzer
 * 
 * @param *p_port
 * @param pin
 * @param alt_func
 * @param note_end
 */
typedef struct
{
    GPIO_TypeDef * p_port;
    uint8_t pin;
    uint8_t alt_func;
    bool note_end;
} port_buzzer_hw_t;

/* Global variables */

/**
 * @brief array for the HW characteristics of buzzers
 * 
 */
extern port_buzzer_hw_t buzzers_arr[];


/* Function prototypes and explanation -------------------------------------------------*/

/**
 * @brief Initializes a buzzer object given a buzzer ID
 * 
 * @param buzzer_id ID of given buzzer
 */
void port_buzzer_init(uint32_t buzzer_id);

/**
 * @brief Sets the duration for a note
 * 
 * @param buzzer_id ID of given buzzer
 * @param duration_ms time for the duration (in ms)
 */
void port_buzzer_set_note_duration(uint32_t buzzer_id, uint32_t duration_ms);

/**
 * @brief Sets the frequency for a buzzer
 * 
 * @param buzzer_id ID of given buzzer
 * @param frequency_hz frequency for the buzzer (in Hz)
 */
void port_buzzer_set_note_frequency(uint32_t buzzer_id, double frequency_hz);

/**
 * @brief check if a note has ended
 * 
 * @param buzzer_id ID of given buzzer
 * @return true note has ended
 * @return false note has not ended
 */
bool port_buzzer_get_note_timeout(uint32_t buzzer_id);

/**
 * @brief stop the buzzer with the given ID
 * 
 * @param buzzer_id ID of given buzzer
 */
void port_buzzer_stop(uint32_t buzzer_id);

#endif
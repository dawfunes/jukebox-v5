/**
 * @file fsm_button.h
 * @brief Header for fsm_button.c file.
 * @author David Fuentes Martín
 * @author Pablo de la Cruz Gómez
 * @date 20/02/2024
 */

#ifndef FSM_BUTTON_H_
#define FSM_BUTTON_H_

/* Includes ------------------------------------------------------------------*/
/* Standard C includes */
#include <stdint.h>
#include <stdbool.h>


/* Other includes */
#include "fsm.h"
#include <stm32f446xx.h>

/* Defines and enums ----------------------------------------------------------*/
/* Enums */
/**
 * @brief STATUS ENUMERATION for the FSM button.
 * 
 */
enum FSM_BUTTON
{
    BUTTON_RELEASED = 0,  /*!< INITIAL STATUS. Unpressed button status*/
    BUTTON_RELEASED_WAIT, /*!< Unpressed button and waiting status*/
    BUTTON_PRESSED,       /*!< Pressed button status*/
    BUTTON_PRESSED_WAIT,  /*!< Pressed button and waiting status*/
};

/* Typedefs --------------------------------------------------------------------*/

/**
 * @brief FSM Button strutcture.
 * @param f 
 * @param debounce_time
 * @param next_timeout
 * @param tick_pressed
 * @param duration
 * @param button_id
 *
 */
typedef struct
{
    fsm_t f;
    uint32_t debounce_time;
    uint32_t next_timeout;
    uint32_t tick_pressed;
    uint32_t duration;
    uint32_t button_id;
} fsm_button_t;

/* Function prototypes and explanation -------------------------------------------------*/
/**
 * @brief Creates a new FSM for measuring how long a button with an ID is pressed.
 *
 * @param debounce_time time (in ms) the FSM will wait between presses.
 * @param button_id button ID.
 * @return fsm_t* pointer to a FSM with a FSM button in it.
 */
fsm_t *fsm_button_new(uint32_t debounce_time, uint32_t button_id);

/**
 * @brief Initializes all the parameters for an FSM that measures how long a button with an ID is pressed.
 *
 * @param p_this pointer to a FSM with a FSM button in it.
 * @param debounce_time time (in ms) the FSM will wait between presses.
 * @param button_id button ID.
 */
void fsm_button_init(fsm_t *p_this, uint32_t debounce_time, uint32_t button_id);

/**
 * @brief Returns the duration the button has been pressed.
 *
 * @param p_this pointer to a FSM with a FSM button in it.
 * @return uint32_t time (in ms) the button has been pressed.
 */
uint32_t fsm_button_get_duration(fsm_t *p_this);

/**
 * @brief Resets the duration the button has been pressed
 *
 * @param p_this pointer to a FSM with a FSM button in it.
 */
void fsm_button_reset_duration(fsm_t *p_this);

/**
 * @brief Check the current status of the button.
 *
 * @param p_this pointer to a FSM with a FSM button in it.
 * @return true if the button is pressed
 * @return false if the button isn't pressed
 */
bool fsm_button_check_activity(fsm_t *p_this);

#endif

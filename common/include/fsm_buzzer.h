/**
 * @file fsm_buzzer.h
 * @brief Header for fsm_buzzer.c file.
 * @author David Fuentes Martín
 * @author Pablo de la Cruz Gómez
 * @date 09/04/2024
 */

#ifndef FSM_BUZZER_H_
#define FSM_BUZZER_H_

/* Includes ------------------------------------------------------------------*/
/* Standard C includes */
#include <stdint.h>
#include <stdbool.h>

/* Other includes */
#include <fsm.h>
#include "melodies.h"

/* HW dependent includes */


/* Defines and enums ----------------------------------------------------------*/
/* Typedefs --------------------------------------------------------------------*/

/**
 * @brief FSM Buzzer strutcture
 * @param f 
 * @param p_melody
 * @param note_index
 * @param buzzer_id
 * @param user_action
 * @param player_speed
 * 
 */
typedef struct
{
    fsm_t f;
    melody_t * p_melody;
    uint32_t note_index;
    uint8_t buzzer_id;
    uint8_t user_action;
    double player_speed;
} fsm_buzzer_t;

/* Enums */

/**
 * @brief STATUS ENUMERATION for the FSM buzzer
 * 
 */
enum FSM_BUZZER 
{
  WAIT_START = 0,       //
  PLAY_NOTE,            //
  PAUSE_NOTE,           //
  WAIT_NOTE,            //
  WAIT_MELODY           //
};

/**
 * @brief STATUS ENUMERATION for the media player
 * 
 */
enum USER_ACTIONS 
{
  STOP = 0,             //
  PLAY,                 //
  PAUSE                 //
};

/* Function prototypes and explanation -------------------------------------------------*/
/**
 * @brief Set melody to queue.
 * 
 * @param p_this pointer to a FSM with a FSM buzzer in it.
 * @param p_melody pointer to a melody that is going to be queued
 */
void fsm_buzzer_set_melody (fsm_t *p_this, const melody_t *p_melody);
//void fsm_buzzer_set_reverse_melody (fsm_t *p_this, const melody_t *p_melody);
/**
 * @brief Set speed that the media player should play at.
 * 
 * @param p_this pointer to a FSM with a FSM buzzer in it.
 * @param speed speed that the media player should play at.
 */
void fsm_buzzer_set_speed (fsm_t *p_this, double speed);

/**
 * @brief Set action that the media player should do
 * 
 * @param p_this pointer to a FSM with a FSM buzzer in it.
 * @param action action that the media player should do
 */
void fsm_buzzer_set_action (fsm_t *p_this, uint8_t action);

/**
 * @brief Get action that the MEDIA player is currently at.
 * 
 * @param p_this pointer to a FSM with a FSM buzzer in it.
 * @return uint8_t action that the MEDIA player is currently at.
 */
uint8_t fsm_buzzer_get_action (fsm_t *p_this);

/**
 * @brief Creates a new FSM buzzer.
 * 
 * @param buzzer_id ID for the new buzzer we want to create.
 * @return fsm_t* pointer to the new FSM with the new buzzer we just created
 */
fsm_t * fsm_buzzer_new (uint32_t buzzer_id);

/**
 * @brief Initializes a FSM buzzer
 * 
 * @param p_this pointer to a FSM with a FSM buzzer in it.
 * @param buzzer_id ID for the buzzer
 */
void fsm_buzzer_init (fsm_t *p_this, uint32_t buzzer_id);

/**
 * @brief Check whether the MEDIA player is playing a song or not.
 * 
 * @param p_this pointer to a FSM with a FSM buzzer in it.
 * @return true Currently playing
 * @return false Currently not playing
 */
bool fsm_buzzer_check_activity (fsm_t *p_this);


#endif /* FSM_BUZZER_H_ */
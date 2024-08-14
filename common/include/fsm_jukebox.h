/**
 * @file fsm_jukebox.h
 * @brief Header for fsm_jukebox.c file.
 * @author David Fuentes Martín
 * @author Pablo de la Cruz Gómez
 * @date 22/04/2024
 */
#ifndef FSM_JUKEBOX_H_
#define FSM_JUKEBOX_H_

/* Includes ------------------------------------------------------------------*/
/* Standard C includes */
#include <stdint.h>
#include <fsm.h>

/* Other includes */
#include "melodies.h"

/* Defines and enums ----------------------------------------------------------*/
/* Defines */
#define MELODIES_MEMORY_SIZE 11     /*!< Size of the memory of melodies*/

/* Enums */
/**
 * @brief STATUS ENUMERATION for the FSM jukebox.
 * 
 */
enum FSM_JUKEBOX
{
  OFF = 0,
  START_UP,
  WAIT_COMMAND,
  SLEEP_WHILE_OFF,
  SLEEP_WHILE_ON
};

/* Typedefs ------------------------------------------------------------------*/

/**
 * @brief FSM Jukebox strutcture.
 * @param f 
 * @param melodies
 * @param melody_idx
 * @param p_melody
 * @param on_off_press_time_ms
 * @param p_fsm_usart
 * @param p_fsm_buzzer 
 * @param next_song_press_time_ms
 * @param speed
 * @param p_fsm_keypad
 * 
 */
typedef struct
{
    fsm_t f;
    melody_t melodies [MELODIES_MEMORY_SIZE];
    uint8_t melody_idx;
    char * p_melody;
    fsm_t * p_fsm_button;
    uint32_t on_off_press_time_ms;
    fsm_t * p_fsm_usart;
    fsm_t * p_fsm_buzzer;
    uint32_t next_song_press_time_ms;
    double speed;

    // v5
    fsm_t * p_fsm_keypad;
  } fsm_jukebox_t;

/* Function prototypes and explanation ---------------------------------------*/
/**
 * @brief Create a new jukebox FSM object with a button, usart, buzzer and in the v5, a 4x4 keypad.
 * 
 * @param p_fsm_button pointer to a FSM with the FSM button we want in it.
 * @param on_off_press_time_ms time in ms to turn it on or off.
 * @param p_fsm_usart pointer to a FSM with the FSM usart we want in it.
 * @param p_fsm_buzzer pointer to a FSM with the FSM buzzer we want in it.
 * @param next_song_press_time_ms time in ms to select the next song.
 * @param p_fsm_keypad pointer to a FSM with the FSM keypad we want in it.
 * @return fsm_t* pointer to a FSM with a FSM jukebox in it.
 * 
 */
fsm_t * fsm_jukebox_new(fsm_t *p_fsm_button, uint32_t on_off_press_time_ms, fsm_t *p_fsm_usart, fsm_t *p_fsm_buzzer, uint32_t next_song_press_time_ms, /* v5 */ fsm_t *p_fsm_keypad);

/**
 * @brief Initialize a jukebox FSM object.
 * 
 * @param p_fsm_button pointer to a FSM with the FSM button we want in it.
 * @param on_off_press_time_ms time in ms to turn it on or off.
 * @param p_fsm_usart pointer to a FSM with the FSM usart we want in it.
 * @param p_fsm_buzzer pointer to a FSM with the FSM buzzer we want in it.
 * @param next_song_press_time_ms time in ms to select the next song.
 * @param p_fsm_keypad pointer to a FSM with the FSM keypad we want in it.
 */
void fsm_jukebox_init(fsm_t *p_this, fsm_t *p_fsm_button, uint32_t on_off_press_time_ms, fsm_t *p_fsm_usart, fsm_t *p_fsm_buzzer, uint32_t next_song_press_time_ms, /* v5 */ fsm_t *p_fsm_keypad);


#endif /* FSM_JUKEBOX_H_ */
/**
 * @file fsm_keypad.h
 * @brief Header for fsm_keypad.c file.
 * @author David Fuentes Martin
 * @author Pablo de la Cruz
 * @date 19/05/2024
 */

#ifndef FSM_KEYPAD_H_
#define FSM_KEYPAD_H_

#include "fsm.h"
#include <stdint.h>

/* Defines and enums ----------------------------------------------------------*/
/* Enums */
enum {
    STATE_WAIT_KEY=0,   /*!< INITIAL STATUS. Waiting for key status*/
    STATE_KEY_PRESSED,  /*!< Key being pressed status*/
};

/* Typedefs --------------------------------------------------------------------*/
/**
 * @brief 
 * @param f
 * @param keypad_id
 * @param last_key
 * @param key_received
 */
typedef struct {
    fsm_t f;  
    uint32_t keypad_id;
    char last_key;
    bool key_received;
} fsm_keypad_t;

/* Function prototypes and explanation -------------------------------------------------*/
/**
 * @brief Creates a new FSM that registers keypad presses with an ID.
 * 
 * @param id keypad ID.
 * @return fsm_t* pointer to a FSM with a FSM keypad in it.
 */
fsm_t* fsm_keypad_new(uint32_t id);

/**
 * @brief Initializes all the parameters for an FSM that registers keypad presses with a given ID.
 * 
 * @param p_this pointer to a FSM with a FSM keypad in it.
 * @param keypad_id keypad ID.
 */
void fsm_keypad_init(fsm_t *p_this, uint32_t keypad_id);

/**
 * @brief checks whether a key has or has not been received.
 * 
 * @param p_this pointer to a FSM with a FSM keypad in it.
 * @return true a key has been received.
 * @return false a key has not been received.
 */
bool fsm_keypad_check_key_received(fsm_t *p_this);

/**
 * @brief Get the key that is currently being pressed in the keypad.
 * 
 * @param p_this pointer to a FSM with a FSM keypad in it.
 * @return char contains the key that is being pressed from 0-9, A-D, # or *.
 */
char fsm_keypad_get_key(fsm_t *p_this);

/**
 * @brief Check the current status of the keypad.
 * 
 * @param p_this pointer to a FSM with a FSM keypad in it.
 * @return true if the status is STATE_WAIT_KEY
 * @return false if the status is different from STATE_WAIT_KEY
 */
bool fsm_keypad_check_activity(fsm_t * p_this);

#endif /* FSM_KEYPAD_H_ */

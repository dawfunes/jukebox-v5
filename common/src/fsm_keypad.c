/**
 * @file fsm_keypad.c
 * @brief Keypad FSM main file.
 * @author David Fuentes Martín
 * @author Pablo de la Cruz Gómez
 * @date 19/05/2024
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include <stdlib.h>
#include "stdio.h"
#include <string.h>

#include "fsm_keypad.h"
#include "port_keypad.h"

/* State machine output or action functions */
/**
 * @brief Check if there is a key press.
 * 
 * @param p_this pointer to a FSM with a FSM keypad in it.
 * @return true if the key read by the method port_keypad_read is different than an empty char (\0).
 * @return false if there is a key being read by the method port_keypad_read.
 */
static bool check_key_pressed(fsm_t* p_this) {
    /*fsm_keypad_t* p_fsm = (fsm_keypad_t*)p_this;
    p_fsm->last_key = port_keypad_read();
    return (p_fsm->last_key != '\0');*/
    return(port_keypad_read() != '\0');
}

/**
 * @brief Check if there is no longer a key press.
 * 
 * @param p_this pointer to a FSM with a FSM keypad in it.
 * @return true if there is no key press.
 * @return false if there is still a key pressed.
 */
static bool check_key_unpressed(fsm_t* p_this) {
    /*fsm_keypad_t* p_fsm = (fsm_keypad_t*)p_this;
    p_fsm->last_key = port_keypad_read();
    return (p_fsm->last_key == '\0');*/
    return(port_keypad_read() == '\0');
}

/**
 * @brief Changes the last_key field to the pressed key and prints in terminal the key.
 * 
 * @param p_this pointer to a FSM with a FSM keypad in it.
 */
static void do_process_key(fsm_t* p_this) {
    fsm_keypad_t* p_fsm = (fsm_keypad_t*)p_this;
    p_fsm->key_received=true;
    p_fsm->last_key = port_keypad_read();
    printf("Key pressed: [%c].\n", p_fsm->last_key);
}

/**
 * @brief Empties the last_key field and prints in terminal an informative message.
 * 
 * @param p_this pointer to a FSM with a FSM keypad in it.
 */
static void do_delete_key(fsm_t* p_this) {
    fsm_keypad_t* p_fsm = (fsm_keypad_t*)p_this;
    p_fsm->key_received=false;
    p_fsm->last_key = port_keypad_read();
    printf("Key let go.\n");
}

/**
 * @brief Status transitions of the FSM keypad.
 * 
 */
fsm_trans_t fsm_trans_keypad[] = {
    {STATE_WAIT_KEY, check_key_pressed, STATE_KEY_PRESSED, do_process_key },
    {STATE_KEY_PRESSED, check_key_unpressed, STATE_WAIT_KEY, do_delete_key },
    {-1,NULL,-1,NULL}};

/* Other auxiliary functions */

fsm_t *fsm_keypad_new(uint32_t keypad_id)
{
    fsm_t *p_fsm = malloc(sizeof(fsm_keypad_t)); /* Do malloc to reserve memory of all other FSM elements, although it is interpreted as fsm_t (the first element of the structure) */
    fsm_keypad_init(p_fsm, keypad_id);
    return p_fsm;
}

void fsm_keypad_init(fsm_t *p_this, uint32_t keypad_id)
{
    fsm_keypad_t *p_fsm = (fsm_keypad_t *)(p_this);
    fsm_init(p_this, fsm_trans_keypad);

    p_fsm->keypad_id = keypad_id;
    p_fsm->last_key = '\0';
    port_keypad_init();
}

bool fsm_keypad_check_key_received(fsm_t *p_this){
    fsm_keypad_t *p_fsm = (fsm_keypad_t *)(p_this);
    return p_fsm->key_received;
}

char fsm_keypad_get_key(fsm_t *p_this){
    fsm_keypad_t *p_fsm = (fsm_keypad_t *)(p_this);
    return p_fsm->last_key;
}

bool fsm_keypad_check_activity(fsm_t * p_this)
{
    fsm_keypad_t *p_fsm = (fsm_keypad_t *)(p_this);
    return (p_fsm->f.current_state==STATE_WAIT_KEY);
}
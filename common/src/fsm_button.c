/**
 * @file fsm_button.c
 * @brief Button FSM main file.
 * @author David Fuentes Martín
 * @author Pablo de la Cruz Gómez
 * @date 27/02/2024
 */

/* Includes ------------------------------------------------------------------*/
#include "fsm_button.h"
#include "port_button.h"
#include <stdlib.h>

/* State machine input or transition functions */
/**
 * @brief Return if the button has been pressed
 * 
 * @param p_this pointer to a FSM with a FSM button in it.
 * @return true if the button has been pressed
 * @return false if the button hasn't been pressed
 */
static bool check_button_pressed(fsm_t *p_this)
{
    fsm_button_t *p_fsm = (fsm_button_t *)(p_this);
    return port_button_is_pressed(p_fsm->button_id);
}
/**
 * @brief Return if the button has been released
 * 
 * @param p_this pointer to a FSM with a FSM button in it.
 * @return true if the button has been released
 * @return false if the button hasn't been released
 */
static bool check_button_released(fsm_t *p_this)
{
    fsm_button_t *p_fsm = (fsm_button_t *)(p_this);
    return !port_button_is_pressed(p_fsm->button_id);
}
/**
 * @brief Check in the time (in ms) is higher than the debounce time
 * 
 * @param p_this pointer to a FSM with a FSM button in it.
 * @return true if the debounce time has already passed
 * @return false if the debounce time hasn't passed
 */
static bool check_timeout(fsm_t *p_this)
{
    fsm_button_t *p_fsm = (fsm_button_t *)(p_this);
    if (port_button_get_tick() > p_fsm->next_timeout)
        return true;
    else
        return false;
}

/* State machine output or action functions */
/**
 * @brief Store the System tick (in ms) when the button has been pressed.
 * 
 * @param p_this pointer to a FSM with a FSM button in it.
 */
static void do_store_tick_pressed(fsm_t *p_this)
{
    fsm_button_t *p_fsm = (fsm_button_t *)(p_this);
    uint32_t current = port_button_get_tick();
    p_fsm->tick_pressed = current;
    p_fsm->next_timeout = current + p_fsm->debounce_time;
}
/**
 * @brief  Store the time (in ms) the button has been pressed.
 * 
 * @param p_this pointer to a FSM with a FSM button in it.
 */
static void do_set_duration(fsm_t *p_this)
{
    fsm_button_t *p_fsm = (fsm_button_t *)(p_this);
    uint32_t current = port_button_get_tick();
    p_fsm->duration = current - p_fsm->tick_pressed;
    p_fsm->next_timeout = current + p_fsm->debounce_time;
}

/**
 * @brief Status transitions of the FSM button.
 * 
 */
fsm_trans_t fsm_trans_button[] = {
    {BUTTON_RELEASED, check_button_pressed, BUTTON_PRESSED_WAIT, do_store_tick_pressed},
    {BUTTON_PRESSED_WAIT, check_timeout, BUTTON_PRESSED, NULL},
    {BUTTON_PRESSED, check_button_released, BUTTON_RELEASED_WAIT, do_set_duration},
    {BUTTON_RELEASED_WAIT, check_timeout, BUTTON_RELEASED, NULL},
    {-1, NULL, -1, NULL}};

/* Other auxiliary functions */
uint32_t fsm_button_get_duration(fsm_t *p_this)
{
    fsm_button_t *p_fsm = (fsm_button_t *)(p_this);
    return p_fsm->duration;
}

void fsm_button_reset_duration(fsm_t *p_this)
{
    fsm_button_t *p_fsm = (fsm_button_t *)(p_this);
    p_fsm->duration = 0;
}

fsm_t *fsm_button_new(uint32_t debounce_time, uint32_t button_id)
{
    fsm_t *p_fsm = malloc(sizeof(fsm_button_t)); /* Do malloc to reserve memory of all other FSM elements, although it is interpreted as fsm_t (the first element of the structure) */
    fsm_button_init(p_fsm, debounce_time, button_id);
    return p_fsm;
}

void fsm_button_init(fsm_t *p_this, uint32_t debounce_time, uint32_t button_id)
{
    fsm_button_t *p_fsm = (fsm_button_t *)(p_this);
    fsm_init(p_this, fsm_trans_button);

    p_fsm->debounce_time = debounce_time;
    p_fsm->button_id = button_id;
    p_fsm->tick_pressed = 0;
    p_fsm->duration = 0;
    port_button_init(button_id);
}

bool fsm_button_check_activity(fsm_t * p_this)
{
    fsm_button_t *p_fsm = (fsm_button_t *)(p_this);
    return (p_fsm->f.current_state!=BUTTON_RELEASED);
}

/**
 * @file fsm_usart.h
 * @brief Header for fsm_usart.c file.
 * @author David Fuentes Martín
 * @author Pablo de la Cruz Gómez
 * @date 06/03/2024
 */

#ifndef FSM_USART_H_
#define FSM_USART_H_

/* Includes ------------------------------------------------------------------*/
/* Standard C includes */
#include <stdint.h>
#include <stdbool.h>

/* Other includes */
#include <fsm.h>
#include "port_usart.h"


/* HW dependent includes */


/* Defines and enums ----------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------*/
/**
 * @brief FSM USART structure.
 * @param f 
 * @param data_received
 * @param in_data
 * @param out_data
 * @param usart_id
 * 
 */
typedef struct
{
    fsm_t f;
    bool data_received;
    char in_data[USART_INPUT_BUFFER_LENGTH];
    char out_data[USART_OUTPUT_BUFFER_LENGTH];
    uint32_t usart_id;
} fsm_usart_t;

/* Enums */
/**
 * @brief STATUS ENUMERATION for the FSM USART.
 * 
 */
enum FSM_USART
{
    WAIT_DATA = 0,
    SEND_DATA,
};

/* Function prototypes and explanation -------------------------------------------------*/
/**
 * @brief create a new FSM USART
 * 
 * @param usart_id USART ID
 * @return fsm_t* pointer to a FSM with a FSM USART in it.
 */
fsm_t *fsm_usart_new(uint32_t usart_id);

/**
 * @brief Initializes the given FSM USART
 * 
 * @param p_this pointer to a FSM with a FSM USART in it.
 * @param usart_id USART ID
 */
void fsm_usart_init(fsm_t *p_this, uint32_t usart_id);

/**
 * @brief Check whether data has or has not been received.
 * 
 * @param p_this pointer to a FSM with a FSM USART in it.
 * @return true data has been received
 * @return false data hasn't been received
 */
bool fsm_usart_check_data_received(fsm_t *p_this);

/**
 * @brief Copy the received data to the p_data array.
 * 
 * @param p_this pointer to a FSM with a FSM USART in it.
 * @param p_data pointer to an array where we will copy the received data.
 */
void fsm_usart_get_in_data(fsm_t *p_this, char *p_data);

/**
 * @brief Copy the data from the p_data array to send it.
 * 
 * @param p_this pointer to a FSM with a FSM USART in it.
 * @param p_data pointer to an array where we will copy the sent data from.
 */
void fsm_usart_set_out_data(fsm_t *p_this, char *p_data);

/**
 * @brief Resets the input data buffer.
 * 
 * @param p_this pointer to a FSM with a FSM USART in it.
 */
void fsm_usart_reset_input_data(fsm_t *p_this);

/**
 * @brief Check whether the FSM USART is active or not.
 * 
 * @param p_this pointer to a FSM with a FSM USART in it.
 * @return true FSM USART is active.
 * @return false FSM USART isn't active.
 */
bool fsm_usart_check_activity(fsm_t *p_this);

/**
 * @brief Disable the RX interrupt for the USART.
 * 
 * @param p_this pointer to a FSM with a FSM USART in it.
 */
void fsm_usart_disable_rx_interrupt(fsm_t *p_this);

/**
 * @brief Disable the TX interrupt for the USART.
 * 
 * @param p_this pointer to a FSM with a FSM USART in it.
 */
void fsm_usart_disable_tx_interrupt(fsm_t *p_this);

/**
 * @brief Enable the RX interrupt for the USART.
 * 
 * @param p_this pointer to a FSM with a FSM USART in it.
 */
void fsm_usart_enable_rx_interrupt(fsm_t *p_this);

/**
 * @brief Enable the TX interrupt for the USART.
 * 
 * @param p_this pointer to a FSM with a FSM USART in it.
 */
void fsm_usart_enable_tx_interrupt(fsm_t *p_this);

#endif /* FSM_USART_H_ */

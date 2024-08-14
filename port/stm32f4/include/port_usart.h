/**
 * @file port_usart.h
 * @brief Header for port_usart.c file.
 * @author David Fuentes Martín
 * @author Pablo de la Cruz Gómez
 * @date 11/03/2024
 */
#ifndef PORT_USART_H_
#define PORT_USART_H_

/* Includes ------------------------------------------------------------------*/
/* Standard C includes */
#include <stdint.h>
#include <stdbool.h>

/* HW dependent includes */
#include "stm32f4xx.h"

/* Defines and enums ----------------------------------------------------------*/
/* Defines */
#define USART_0_ID 0                        /*!< Id of the USART*/
#define USART_0 USART3                      /*!< USART we are going to use*/
#define USART_0_GPIO_TX GPIOB               /*!< Port for TX pin*/
#define USART_0_GPIO_RX GPIOC               /*!< Port for RX pin*/
#define USART_0_PIN_TX 10                   /*!< Pin of TX GPIO*/
#define USART_0_PIN_RX 11                   /*!< Pin of RX GPIO*/
#define USART_0_AF_TX 0x07                  /*!< TX Alternative Function*/
#define USART_0_AF_RX 0x07                  /*!< RX Alternative Function*/
#define BRR_9600_8_N_1 0x683                /*!< Dividimos 1000000/9600 y obtenemos 104,167. Pasamos la parte entera a hexadecimal (104 en decimal es 68 en hexadecimal). Convertimos la parte decimal en binario usando el método de la multiplicación sucesiva por 2. Repetimos este proceso cuatro veces y nos queda 0010, lo cual en hexadecimal es 2. 0x682*/

#define USART_INPUT_BUFFER_LENGTH 10        /*!< Length for the input buffer*/
#define USART_OUTPUT_BUFFER_LENGTH 256      /*!< Length for the output buffer*/
#define EMPTY_BUFFER_CONSTANT 0x0           /*!< Constant that represents en empty buffer*/
#define END_CHAR_CONSTANT 0xA               /*!< Constant that represents the end of a char*/

/* Typedefs --------------------------------------------------------------------*/
/**
 * @brief PORT USART strutcture
 * @param p_usart 
 * @param p_port_tx
 * @param p_port_rx
 * @param pin_tx
 * @param pin_rx
 * @param alt_func_tx
 * @param alt_func_rx
 * @param input_buffer
 * @param i_idx
 * @param read_complete
 * @param output_buffer
 * @param o_idx
 * @param write_complete
 *
 */
typedef struct
{
    USART_TypeDef *p_usart;
    GPIO_TypeDef *p_port_tx;
    GPIO_TypeDef *p_port_rx;
    uint8_t pin_tx;
    uint8_t pin_rx;
    uint8_t alt_func_tx;
    uint8_t alt_func_rx;
    char input_buffer [USART_INPUT_BUFFER_LENGTH];
    uint8_t i_idx;
    bool read_complete;
    char output_buffer [USART_OUTPUT_BUFFER_LENGTH];
    uint8_t o_idx;
    bool write_complete;
} port_usart_hw_t;

/* Global variables */
/**
 * @brief array for the HW characteristics of USARTs
 * 
 */
extern port_usart_hw_t usart_arr[];

/* Function prototypes and explanation -------------------------------------------------*/
/**
 * @brief Initializes with certain set of  specifications
 * 
 * @param usart_id ID of the USART.
 */
void port_usart_init(uint32_t usart_id);

/**
 * @brief Checks the value of the write_complete fieldo of the given USART
 * and returns it's value.
 * 
 * @param usart_id ID of the USART.
 * @return true write completed. 
 * @return false write not completed.
 */
bool port_usart_tx_done(uint32_t usart_id);


/**
 * @brief Checks the value of the read_complete field of the given USART
 * and returns it's value.
 * 
 * @param usart_id ID of the USART.
 * @return true read completed
 * @return false read not completed
 */
bool port_usart_rx_done(uint32_t usart_id);

/**
 * @brief Using the memcpy function copies the input_buffer field of the given USART 
 * into the buffer.
 * 
 * @param usart_id ID of the USART.
 * @param p_buffer pointer to the buffer where the message will be stored.
 */
void port_usart_get_from_input_buffer(uint32_t usart_id, char *p_buffer);

/**
 * @brief Checks the TXE flag status and returns it's value.
 * 
 * @param usart_id ID of the USART.
 * @return true if TXE flag is set
 * @return false if TXE flag is not set  
 */
bool port_usart_get_txr_status(uint32_t usart_id);

/**
 * @brief Using the memcpy funcion copies the message passed into 
 * the output_buffer field of the given USART.
 * 
 * @param usart_id ID of the USART.
 * @param p_data pointer to the message to send.
 * @param length length of the message to send
 */
void port_usart_copy_to_output_buffer(uint32_t usart_id, char *p_data, uint32_t length);

/**
 * @brief Resets the content of the input buffer.
 * 
 * @param usart_id ID of the USART.
 */
void port_usart_reset_input_buffer(uint32_t usart_id);

/**
 * @brief Resets the content of the output buffer.
 * 
 * @param usart_id ID of the USART.
 */
void port_usart_reset_output_buffer(uint32_t usart_id);

/**
 * @brief Writes from the USART Data Register (DA) into input buffer.
 * 
 * @param usart_id ID of the USART.
 */
void port_usart_store_data(uint32_t usart_id);

/**
 * @brief Writes from the output buffer into the USART Data Register (DA).
 * 
 * @param usart_id ID of the USART.
 */
void port_usart_write_data(uint32_t usart_id);

/**
 * @brief Disable the RX interrupt for the USART.
 * 
 * @param usart_id ID of the USART.
 */
void port_usart_disable_rx_interrupt(uint32_t usart_id);

/**
 * @brief Disable the TX interrupt for the USART.
 * 
 * @param usart_id ID of the USART.
 */
void port_usart_disable_tx_interrupt(uint32_t usart_id);

/**
 * @brief Enable the RX interrupt for the USART.
 * 
 * @param usart_id ID of the USART.
 */
void port_usart_enable_rx_interrupt(uint32_t usart_id);

/** 
 * @brief Enable the TX interrupt for the USART.
 * 
 * @param usart_id ID of the USART.
 */
void port_usart_enable_tx_interrupt(uint32_t usart_id);


#endif
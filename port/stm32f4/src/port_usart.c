/**
 * @file port_usart.c
 * @brief Portable functions to interact with the USART FSM library.
 * @author Pablo de la Cruz Gómez
 * @author David Fuentes Martin
 * @date 21/03/2024
 */
/* Includes ------------------------------------------------------------------*/
/* Standard C libraries */
#include <string.h>
#include <stdlib.h>

/* HW dependent libraries */
#include "port_system.h"
#include "port_usart.h"

/* Global variables */
port_usart_hw_t usart_arr[] = {
    [USART_0_ID] = {.p_usart = USART_0, 
                    .p_port_tx = USART_0_GPIO_TX,
                    .p_port_rx = USART_0_GPIO_RX, 
                    .pin_tx = USART_0_PIN_TX, 
                    .pin_rx = USART_0_PIN_RX, 
                    .alt_func_tx = USART_0_AF_TX, 
                    .alt_func_rx = USART_0_AF_RX, 
                    .input_buffer = {EMPTY_BUFFER_CONSTANT}, 
                    .i_idx = 0, 
                    .read_complete = false, 
                    .output_buffer = {EMPTY_BUFFER_CONSTANT}, 
                    .o_idx = 0, 
                    .write_complete = false},
};

/* Private functions */
/**
 * @brief Using the function memset set the value of the buffer given 
 * to default with EMPTY_BUFFER_CONSTANT.
 * 
 * @param buffer pointer to the buffer to be reset.
 * @param length length of the buffer.
 */
void _reset_buffer(char *buffer,uint32_t length){
    memset(buffer, EMPTY_BUFFER_CONSTANT, length);
}


/* Public functions */

void port_usart_init(uint32_t usart_id)
{
    USART_TypeDef *p_usart = usart_arr[usart_id].p_usart;
    GPIO_TypeDef *p_port_tx = usart_arr[usart_id].p_port_tx;
    GPIO_TypeDef *p_port_rx = usart_arr[usart_id].p_port_rx;
    uint8_t pin_tx = usart_arr[usart_id].pin_tx;
    uint8_t pin_rx = usart_arr[usart_id].pin_rx;
    uint8_t alt_func_tx = usart_arr[usart_id].alt_func_tx;
    uint8_t alt_func_rx = usart_arr[usart_id].alt_func_rx;

    port_system_gpio_config(p_port_tx, pin_tx, GPIO_MODE_ALTERNATE, GPIO_PUPDR_PUP);
    port_system_gpio_config(p_port_rx, pin_rx, GPIO_MODE_ALTERNATE, GPIO_PUPDR_PUP);                // 1. Configurar la RX y TX
    port_system_gpio_config_alternate(p_port_tx, pin_tx, alt_func_tx);                
    port_system_gpio_config_alternate(p_port_rx, pin_rx, alt_func_rx);                            // 2. Configurar la funcion alternativa de RX y TX
    
    p_usart -> CR1 &= ~ USART_CR1_UE;                                                                // 4. Disable the USART
    /* Configuramos la longitud de los datos a 8 bits */
    p_usart -> CR1 &= ~ USART_CR1_M ; // Limpiamos el bit M (8 bits )
    /* Configuramos el bit de parada a 1 bit */
    p_usart -> CR2 &= ~ USART_CR2_STOP ; // Limpiamos los bits STOP (1 bit)
    /* Configuramos el bit de paridad a no paridad */
    p_usart -> CR1 &= ~ USART_CR1_PCE ; // Limpiamos el bit PCE ( no paridad )
    /* Aseguramos oversampling de 16 ( por defecto ) */
    p_usart -> CR1 &= ~ USART_CR1_OVER8 ; // Limpiamos el bit OVER8 (oversampling de 16)


    /* Habilitamos la transmision y la recepcion */

    /* No habilitamos las i n t e r r u p c i o n e s de transmision generalmente al inicio ,
    sino solo cuando es necesario */
    p_usart -> CR1 &= ~(USART_CR1_RXNEIE | USART_CR1_TCIE);                                          // 7. Disable reception and transmission interrupts

    p_usart -> SR &= ~USART_SR_RXNE;                                                                 // 8. Clear the interrupt flags RXNE



    // Enable USART interrupts globally
    if (p_usart == USART3)
    {
        NVIC_SetPriority(USART3_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 2, 0));       // 9. Interrupcion USART prioridad 2 y subprioridad 0
        
        NVIC_EnableIRQ(USART3_IRQn);                                                                // 10. Activamos las interruciones de USART globalmente
        RCC -> APB1ENR |= RCC_APB1ENR_USART3EN;                                                     // 3. Enable the clock for the USART peripheral
    }

    /* Configuramos el baud rate ( ver ejemplo de calculo ) */
    p_usart -> BRR = BRR_9600_8_N_1; // 9600 baudios                                                 // 5. Configuracion 9600-8-N-1

    p_usart -> CR1 |= USART_CR1_TE | USART_CR1_RE ;                                                  // 6. Enable transmission and reception

    p_usart -> CR1 |= USART_CR1_UE;                                                                  // 11. Activamos la USART

    _reset_buffer(usart_arr[usart_id].input_buffer, USART_INPUT_BUFFER_LENGTH);                   // 12. Reseteamos el input_buffer

    _reset_buffer(usart_arr[usart_id].output_buffer, USART_OUTPUT_BUFFER_LENGTH);                 // 13. Reseteamos el output_buffer   
}

void port_usart_get_from_input_buffer(uint32_t usart_id, char *p_buffer){
    memcpy(p_buffer, usart_arr[usart_id].input_buffer, USART_INPUT_BUFFER_LENGTH);
}

bool port_usart_get_txr_status(uint32_t usart_id){
    return (usart_arr[usart_id].p_usart->SR & USART_SR_TXE);
}

void port_usart_copy_to_output_buffer(uint32_t usart_id, char *p_data, uint32_t length){
    memset(usart_arr[usart_id].output_buffer, EMPTY_BUFFER_CONSTANT, USART_OUTPUT_BUFFER_LENGTH);
    memcpy(usart_arr[usart_id].output_buffer, p_data, length);
}

void port_usart_reset_input_buffer(uint32_t usart_id){
    _reset_buffer(usart_arr[usart_id].input_buffer, USART_INPUT_BUFFER_LENGTH);
    usart_arr[usart_id].read_complete = false;
}

void port_usart_reset_output_buffer(uint32_t usart_id){
    _reset_buffer(usart_arr[usart_id].output_buffer, USART_OUTPUT_BUFFER_LENGTH);
    usart_arr[usart_id].write_complete = false;
}

bool port_usart_rx_done(uint32_t usart_id){
    return usart_arr[usart_id].read_complete;
}

bool port_usart_tx_done(uint32_t usart_id){
    return usart_arr[usart_id].write_complete;
}

void port_usart_store_data(uint32_t usart_id){
    char data = (usart_arr[usart_id].p_usart->DR & USART_DR_DR);                     //Retrieve data in DR register
    if(data != END_CHAR_CONSTANT){
        uint8_t i_idx = usart_arr[usart_id].i_idx;              // retrieve input data index
        if(i_idx >= USART_INPUT_BUFFER_LENGTH){
            usart_arr[usart_id].i_idx = 0;                      // Reset input buffer index
        }
        usart_arr[usart_id].input_buffer[i_idx] = data;         //Load data in input buffer
        usart_arr[usart_id].i_idx++;                            //update input buffer index
    }else{
        usart_arr[usart_id].read_complete = true;               //set usart_arr[usart_id].read_complete
        usart_arr[usart_id].i_idx = 0;                          // Reset input buffer index
    }
}

void port_usart_write_data(uint32_t usart_id){
    uint8_t o_idx = usart_arr[usart_id].o_idx;                  // retrieve input data index
    char data = usart_arr[usart_id].output_buffer[o_idx];
    if(o_idx == USART_OUTPUT_BUFFER_LENGTH-1 || data == END_CHAR_CONSTANT){
        (usart_arr[usart_id].p_usart->DR)=data;                 // load data in DR register
        port_usart_disable_tx_interrupt(usart_id);              // Disable USART TX interrupts
        usart_arr[usart_id].o_idx = 0;                          // Reset output buffer index
        usart_arr[usart_id].write_complete = true;              // update write_complete
    }else{
        if(data != EMPTY_BUFFER_CONSTANT){
            (usart_arr[usart_id].p_usart->DR)=data;             // Load data in DR register
            usart_arr[usart_id].o_idx++;                        // update outputbuffer index
        }
    }
}

void port_usart_enable_rx_interrupt (uint32_t usart_id) {
    usart_arr[usart_id].p_usart -> CR1 |= USART_CR1_RXNEIE;
}

void port_usart_enable_tx_interrupt (uint32_t usart_id) {
    usart_arr[usart_id].p_usart -> CR1 |= USART_CR1_TXEIE;
}

void port_usart_disable_rx_interrupt (uint32_t usart_id) {
    usart_arr[usart_id].p_usart -> CR1 &= ~(USART_CR1_RXNEIE);
}

void port_usart_disable_tx_interrupt (uint32_t usart_id) {
    usart_arr[usart_id].p_usart -> CR1 &= ~(USART_CR1_TXEIE);
}

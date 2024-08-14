/**
 * @file interr.c
 * @brief Interrupt service routines for the STM32F4 platform.
 * @author Sistemas Digitales II
 * @date 2024-01-01
 */
// Include HW dependencies:
#include "port_system.h"
#include "port_button.h"
#include "port_usart.h"
#include "port_buzzer.h"

// Include headers of different port elements:

//------------------------------------------------------
// INTERRUPT SERVICE ROUTINES
//------------------------------------------------------
/**
 * @brief Interrupt service routine for the System tick timer (SysTick).
 *
 * @note This ISR is called when the SysTick timer generates an interrupt.
 * The program flow jumps to this ISR and increments the tick counter by one millisecond.
 *
 */
void SysTick_Handler(void)
{
    volatile uint32_t msTicks = port_system_get_millis();
    port_system_set_millis(msTicks+1);
}

/**
 * @brief Handles Px10-Px15 global interrupts.
 * From the button's port and pin, read the GPIO value, then if the value is HIGH
 * it means that the button is no longer pressed so set the value of flag_pressed to false.
 * If value is LOW, the button is pressed so set the value of flag_pressed to true.
 * Then, clean in the PR register the indicated bit.
 *
 */
void EXTI15_10_IRQHandler(void)
{
    port_system_systick_resume();
    GPIO_TypeDef* p_port = buttons_arr[BUTTON_0_ID].p_port;
    uint8_t pin = buttons_arr[BUTTON_0_ID].pin;
    /* ISR user button */
    if (EXTI->PR & BIT_POS_TO_MASK(pin))
    {
        bool value = port_system_gpio_read(p_port, pin);
        if (value)
            buttons_arr[BUTTON_0_ID].flag_pressed = LOW;
        else
            buttons_arr[BUTTON_0_ID].flag_pressed = HIGH;
        EXTI -> PR = BIT_POS_TO_MASK(pin);
    }
}
/**
 * @brief Handles USART3 global interrupts.
 * Check RXNE flag and RXNEIE bit, to check if there has been new data received, 
 * and if RXNE is set and RXNEIE enabled, call the function port_usart_store_data 
 * to store the new data.
 * Also, checks TXE flag and TXEIE bit to see if there is new data in need to be 
 * transmited, so, if TXE is set and TXEIE enabled, call the function port_usart_write_data 
 * to write the data to the USART Data Register.
 * 
 */
void USART3_IRQHandler(void){
    port_system_systick_resume();
    if((USART3 -> SR & USART_SR_RXNE) && (USART3 -> CR1 & USART_CR1_RXNEIE))
        port_usart_store_data(USART_0_ID);
    if((USART3 -> SR & USART_SR_TXE) && (USART3 -> CR1 & USART_CR1_TXEIE))
        port_usart_write_data(USART_0_ID);
}

void TIM2_IRQHandler(void){
    TIM2->SR &= ~TIM_SR_UIF; 
    buzzers_arr[BUZZER_0_ID].note_end = true;
}

/**
 * @file port_buzzer.c
 * @brief Portable functions to interact with the Buzzer melody player FSM library.
 * @author David Fuentes Martín
 * @author Pablo de la Cruz Gómez
 * @date 16/04/2024
 */
/* Includes ------------------------------------------------------------------*/
/* Standard C libraries */
#include <math.h>

/* HW dependent libraries */
#include "port_buzzer.h"

/* Macros */
#define ALT_FUNC2_TIM3 0x02 /*!< AFx TIM3_CH1 */

/* Global variables */

port_buzzer_hw_t buzzers_arr[] = {
    [BUZZER_0_ID] = {.p_port = BUZZER_0_GPIO,
                     .pin = BUZZER_0_PIN,
                     .alt_func = ALT_FUNC2_TIM3,
                     .note_end = false},
};

/* Private functions */
/**
 * @brief Configures the timer that controls the duration of the note.
 * First enables the clock source, then disable the counter and enables
 * the autoreload preload. After that, cleans the Update Interrupt flag
 * of the SR register and enable the Update Interrupt of the DIER register.
 * Finally configures the interrupt with level 3 priority and 0 subpriority,
 * and enables the interrupt in the NVIC.
 * 
 * @param buzzer_id ID of the buzzer
 */
static void _timer_duration_setup(uint32_t buzzer_id)
{
  if (buzzer_id == BUZZER_0_ID)
  {
    // 1
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    // 2
    TIM2->CR1 &= ~TIM_CR1_CEN;
    TIM2->CR1 |= TIM_CR1_ARPE;

    // 3
    TIM2->SR = ~TIM_SR_UIF;

    // 4
    TIM2->DIER |= TIM_DIER_UIE;

    /* Configure interruptions */
    NVIC_SetPriority(TIM2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 3, 0));
    NVIC_EnableIRQ(TIM2_IRQn);
  }
}

/**
 * @brief Configures the timer that controls the PWM of the buzzer.
 * First enables the clock source, then disable the counter, enables
 * the autoreload preload, resets the counter and set the ARR register
 * and the PSC register to 0. Then generates an update event by setting
 * the UG bit. Finally disables the output of the CCER register and sets
 * the PWM mode to 1 and enable the preload.
 * 
 * @param buzzer_id ID of the buzzer
 */
static void _timer_pwm_setup(uint32_t buzzer_id)
{
  // 1
  RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

  // 2.
  TIM3->CR1 &= ~TIM_CR1_CEN;
  TIM3->CR1 |= TIM_CR1_ARPE;

  // 3.
  TIM3->CNT = 0;
  TIM3->ARR = 0;
  TIM3->PSC = 0;

  // 4.
  TIM3->EGR = TIM_EGR_UG;

  // 5. cHANNEL 1
  TIM3->CCER &= ~TIM_CCER_CC1E;

  // 6.
  TIM3 -> CCMR1 |= 0x0060 ; /* Modo PWM 1 */
  TIM3 -> CCMR1 |= TIM_CCMR1_OC1PE ; /* Habilita el preload */
  
}

/* Public functions -----------------------------------------------------------*/

void port_buzzer_init(uint32_t buzzer_id)
{
  port_buzzer_hw_t buzzer = buzzers_arr[buzzer_id];

  port_system_gpio_config(buzzer.p_port, buzzer.pin, GPIO_MODE_ALTERNATE, GPIO_PUPDR_NOPULL);
  port_system_gpio_config_alternate(buzzer.p_port, buzzer.pin, ALT_FUNC2_TIM3);
  _timer_duration_setup(buzzer_id);
  _timer_pwm_setup(buzzer_id);
}

void port_buzzer_set_note_duration(uint32_t buzzer_id, uint32_t duration_ms)
{
  if (buzzer_id == BUZZER_0_ID)
  { // creo que esta es la que hay que comprobar
    // usar timer2 https://moodle.upm.es/titulaciones/oficiales/pluginfile.php/11367877/mod_resource/content/10/2024_SDG2_libro.pdf pagina 78-80
    //port_buzzer_hw_t buzzer = buzzers_arr[buzzer_id];
    // 1.
    TIM2->CR1 &= ~TIM_CR1_CEN;
    TIM2->CNT = 0;

    // 2.
    double sysclk_as_double = (double)SystemCoreClock; // Important to cast to double
    double ms_as_double = (double)duration_ms;         // Important to cast to double

    // 3.
    double psc = ((sysclk_as_double * ms_as_double / 1000.0) / 65536.0) - 1.0;

    // 4.
    double arr = ((sysclk_as_double * ms_as_double / 1000.0) / (round(psc) + 1.0)) - 1.0;

    // 5.
    if (round(arr) > 65535.0)
    {
      psc++;
      arr = ((sysclk_as_double * ms_as_double / 1000.0) / (round(psc) + 1.0)) - 1.0;
    }

    // 6.
    TIM2->PSC = (uint32_t)(round(psc));
    TIM2->ARR = (uint32_t)(round(arr));

    // 7.
    TIM2->EGR = TIM_EGR_UG;

    // 8.
    buzzers_arr[buzzer_id].note_end = false;

    // 9.
    TIM2->CR1 |= TIM_CR1_CEN;
  }
}

bool port_buzzer_get_note_timeout(uint32_t buzzer_id)
{
  if (buzzer_id < sizeof(buzzers_arr))
  {
    port_buzzer_hw_t buzzer = buzzers_arr[buzzer_id];
    return buzzer.note_end;
  }
  return false;
}

void port_buzzer_set_note_frequency(uint32_t buzzer_id, double frequency_hz)
{//meter en if?¿
  // 1.
  if (frequency_hz == 0.0)
  {
    TIM3->CR1 &= ~TIM_CR1_CEN;
    return;
  }

  TIM3->CR1 &= ~TIM_CR1_CEN;
  TIM3->CNT = 0;

  // 2.
  double sysclk_as_double = (double)SystemCoreClock; // Important to cast to double
  double s_as_double = 1.0 / frequency_hz;

  double psc = ((sysclk_as_double * s_as_double) / 65536.0) - 1.0;
  double arr = ((sysclk_as_double * s_as_double) / (round(psc) + 1.0)) - 1.0;

  if (round(arr) > 65535.0)
  {
    psc++;
    arr = ((sysclk_as_double * s_as_double) / (round(psc) + 1.0)) - 1.0;
  }

  TIM3->PSC = (uint32_t)(round(psc));
  TIM3->ARR = (uint32_t)(round(arr));

  // 3.
  TIM3->CCR1 = BUZZER_PWM_DC*(TIM3->ARR+1);

  // 4.
  TIM3->EGR = TIM_EGR_UG;

  // 5.
  TIM3->CCER |= TIM_CCER_CC1E;

  // 6.
  TIM3->CR1 |= TIM_CR1_CEN;
}

void port_buzzer_stop(uint32_t buzzer_id)
{
  //if (buzzer_id < sizeof(buzzers_arr))
  //{
    if(buzzer_id == BUZZER_0_ID){
      TIM3->CR1 &= ~TIM_CR1_CEN;/*CCER &= ~TIM_CCER_CC1E;*/ // aqui en realidad estamos activando el output compare, creo que es lo que pide
      TIM2->CR1 &= ~TIM_CR1_CEN;
    }
    
  //}
}

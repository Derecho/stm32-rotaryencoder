#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/exti.h>
#include "rotaryencoder.h"

#define ROTENC_PORT GPIOA
#define ROTENC_RCC RCC_GPIOA
#define ROTENC_A GPIO0
#define ROTENC_B GPIO1
#define ROTENC_EXTI EXTI0

void rotenc_setup(void)
{

    // Used https://www.reddit.com/r/ECE/comments/4cg293/anyone_use_libopencm3_with_external_interrupts_on/
    // as reference (STM32F3 code).

    //_disable_interrupts();
    rcc_periph_clock_enable(ROTENC_RCC /*| RCC_SYSCFG*/);
    gpio_set_mode(ROTENC_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT,
            ROTENC_A | ROTENC_B);
 
    // Pin A triggers an external interrupt, pin B is read when this happens.
    exti_select_source(ROTENC_EXTI, ROTENC_PORT);  // Needs SYSCFG to work?
    exti_set_trigger(ROTENC_EXTI, EXTI_TRIGGER_RISING);
    exti_enable_request(ROTENC_EXTI);
}

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/exti.h>
#include "rotaryencoder.h"

#define ROTENC_PORT GPIOA
#define ROTENC_RCC RCC_GPIOA
#define ROTENC_GPIOA GPIO1
#define ROTENC_GPIOB GPIO2
#define ROTENC_EXTIA EXTI1
#define ROTENC_EXTIB EXTI2

void rotenc_setup(void)
{
    //_disable_interrupts();
    rcc_periph_clock_enable(ROTENC_RCC /*| RCC_SYSCFG*/);
    gpio_set_mode(ROTENC_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT,
            ROTENC_GPIOA | ROTENC_GPIOB);
 
    exti_select_source(ROTENC_EXTIA, ROTENC_PORT);
    exti_select_source(ROTENC_EXTIB, ROTENC_PORT);
    exti_set_trigger(ROTENC_EXTIA | ROTENC_EXTIB, EXTI_TRIGGER_RISING);
    exti_enable_request(ROTENC_EXTIA | ROTENC_EXTIB);
}

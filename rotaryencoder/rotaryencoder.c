#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/exti.h>
#include <libopencm3/cm3/nvic.h>
#include "rotaryencoder.h"

#define ROTENC_PORT GPIOA
#define ROTENC_RCC RCC_GPIOA
#define ROTENC_NVIC NVIC_EXTI0_IRQ
#define ROTENC_A GPIO0
#define ROTENC_B GPIO1
#define ROTENC_EXTI EXTI0

// TODO Try a different GPIO port

void exti0_isr(void)
{
    // TODO

    exti_reset_request(ROTENC_EXTI);
}

void rotenc_setup(void)
{

    // Prepare pin A, B and the AFIO and NVIC for external interrupts.
    // Pin A triggers an external interrupt, pin B is read when this happens.
    rcc_periph_clock_enable(ROTENC_RCC | RCC_AFIO);
    nvic_enable_irq(ROTENC_NVIC);
    gpio_set_mode(ROTENC_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT,
            ROTENC_A | ROTENC_B);
    exti_select_source(ROTENC_EXTI, ROTENC_PORT);
    exti_set_trigger(ROTENC_EXTI, EXTI_TRIGGER_RISING);
    exti_enable_request(ROTENC_EXTI);
}

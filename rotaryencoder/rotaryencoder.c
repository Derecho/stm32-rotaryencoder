#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/exti.h>
#include <libopencm3/cm3/nvic.h>
#include "rotaryencoder.h"

// Currently only GPIOA seems to work
#define ROTENC_PORT GPIOA
#define ROTENC_RCC RCC_GPIOA
#define ROTENC_NVIC NVIC_EXTI0_IRQ
#define ROTENC_A GPIO0
#define ROTENC_B GPIO1
#define ROTENC_EXTI EXTI0
#define ROTENC_ISR exti0_isr
#define ROTENC_DIV 2

void (*rotenc_dec_cb)(void) = 0;
void (*rotenc_inc_cb)(void) = 0;
static uint8_t _rotenc_counter = 0;

void ROTENC_ISR(void)
{
    if(gpio_get(ROTENC_PORT, ROTENC_B)) {
        if(rotenc_inc_cb && (++_rotenc_counter == ROTENC_DIV)) {
            _rotenc_counter = 0;
            rotenc_inc_cb();
        }
    }
    else {
        if(rotenc_dec_cb && (++_rotenc_counter == ROTENC_DIV)) {
            _rotenc_counter = 0;
            rotenc_dec_cb();
        }
    }

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

#include "rotaryencoder.h"
#include "example.h"

uint32_t counter = 0;
uint8_t counter_updated = 0;

void decrement_counter(void)
{
    counter--;
    counter_updated = 1;
}

void increment_counter(void)
{
    counter++;
    counter_updated = 1;
}

int main(void)
{
    rotenc_dec_cb = decrement_counter;
    rotenc_inc_cb = increment_counter;
    rotenc_setup();

    while(1) {
        if(counter_updated) {
            // Do something with counter
            counter_updated = 0;
        }
    }

    return 0;
}

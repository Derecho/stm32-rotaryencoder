#ifndef ROTARYENCODER_H
#define ROTARYENCODER_H

#include <stdint.h>

// Set these callbacks to handle rotary encoder turns.
// Keep the functions short as they're called from an interrupt.
extern void (*rotenc_dec_cb)(void);
extern void (*rotenc_inc_cb)(void);

void rotenc_setup(void);

#endif  // ROTARYENCODER_H

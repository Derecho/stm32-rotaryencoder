# stm32-rotaryencoder
Simple library to interface with an incremental rotary encoder. Code may be
suitable for porting to other libopencm3-compatible processors. Currently only
GPIO bank A is supported.

## Running the example

    git clone https://git.drk.sc/Derecho/stm32-rotaryencoder.git
    cd stm32-rotaryencoder
    git submodule update --init
    cd libopencm3 && make && cd ..
    cd rotaryencoder && make
   
Having compiled the example you can now flash `example.elf` onto your microcontroller.

## Divider
By default the rotary encoder will have to pulse twice in order for a callback
to be triggered. This behaviour can be changed by defining `ROTENC_DIV`.

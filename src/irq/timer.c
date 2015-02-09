#include "system.h"

void set_timer(int hz){
    int divisor = 1193180 / hz;
    outb(0x43, 0x36);   // 0x36 => 0b00(counter 0 channel0 ) 11 (lsb then msb) 011（square wave mode) 0(binary)
    outb(0x40, divisor & 0xff);
    outb(0x40, divisor >> 8 );
}

void timer_handler(struct regs* r){
    time_ticks++;
    if( time_ticks % CLOCK_FREQ == 0){
        ;
    }
}

#include "system.h"

extern void __isr0();
extern void __isr1();
extern void __isr2();
extern void __isr3();
extern void __isr4();
extern void __isr5();
extern void __isr6();
extern void __isr7();
extern void __isr8();
extern void __isr9();
extern void __isr10();
extern void __isr11();
extern void __isr12();
extern void __isr13();
extern void __isr14();
extern void __isr15();
extern void __isr16();
extern void __isr17();
extern void __isr18();
extern void __isr19();
extern void __isr20();
extern void __isr21();
extern void __isr22();
extern void __isr23();
extern void __isr24();
extern void __isr25();
extern void __isr26();
extern void __isr27();
extern void __isr28();
extern void __isr29();
extern void __isr30();
extern void __isr31();

extern void __irq0();
extern void __irq1();
extern void __irq2();
extern void __irq3();
extern void __irq4();
extern void __irq5();
extern void __irq6();
extern void __irq7();
extern void __irq8();
extern void __irq9();
extern void __irq10();
extern void __irq11();
extern void __irq12();
extern void __irq13();
extern void __irq14();
extern void __irq15();

void* irq_routines[16] = {0};

void idt_set_gate(\
        unsigned char num,\
        unsigned long base,\
        unsigned short sel,\
        unsigned char flags){
    idt[num].base_low = base & 0xffff;
    idt[num].base_high = base >> 16;
    idt[num].selector = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

void idt_install(){
    idtp.limit = sizeof(idt) - 1;
    idtp.base = (unsigned int)idt;

    char * _s = (char*)idt;
    int n = sizeof(idt);
    while (n > 0){
        n -= 1;
        _s[n] = (char)0;
    }
    idt_load();
    idt_set_gate(0,(int)__isr0,0x8,0x8e);
}

void fault_handler(struct regs * r){
    print_c('X');
    print_c('Y');
    for(;;);
}

void irq_install_handler(int irq, void (*handler)(struct regs *r)){
    irq_routines[irq] = handler;
}

void pic_install(){
    outb(PIC_1_CTRL,0x11);  //icw1_init
    outb(PIC_2_CTRL,0x11);  //icw1_init

    outb(PIC_1_DATA,32);   //icw2 map pic_1_data to offset1(32);
    outb(PIC_2_DATA,40);   //icw2 map pic_2_data to offset2(40);

    outb(PIC_1_DATA,4);     //set bit 0x00000100, use line 2 connect to slave
    outb(PIC_2_DATA,2);     //set bit 0x00000010, tell slave that master use line 2

    outb(PIC_1_DATA,1);     //8086 mode
    outb(PIC_2_DATA,1);     //8086 mode

    outb(PIC_1_DATA,0x0);     //clear mask
    outb(PIC_2_DATA,0x0);     //clear mask

    set_timer(CLOCK_FREQ);
    irq_install_handler(0,timer_handler);
    idt_set_gate(32, (unsigned)__irq0, 0x08, 0x8e);

    irq_install_handler(1,keyboard_handler);
    idt_set_gate(33, (unsigned)__irq1, 0x08, 0x8e);
}

void irq_handler(struct regs* r){
    void (*handler) (struct regs* r);
    handler = irq_routines[r->int_no - 32];
    if (handler){
        handler(r);
    }
    if (r -> int_no >= 40){
        outb(PIC_2_CTRL,0x20);      //tell end of int
    }
    outb(PIC_1_CTRL,0x20);
}

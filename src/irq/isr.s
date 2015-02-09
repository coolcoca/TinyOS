bits 32

global idt_load
global __isr0
global __isr1
global __isr2
global __isr3
global __isr4
global __isr5
global __isr6
global __isr7
global __isr8
global __isr9
global __isr10
global __isr11
global __isr12
global __isr13
global __isr14
global __isr15
global __isr16
global __isr17
global __isr18
global __isr19

global __irq0
global __irq1
global __irq2
global __irq3
global __irq4
global __irq5
global __irq6
global __irq7
global __irq8
global __irq9
global __irq10
global __irq11
global __irq12
global __irq13
global __irq14
global __irq15

extern fault_handler
extern idtp
extern irq_handler

idt_load:
    lidt [idtp]
    ret

__isr0:
    cli
    push byte 0
    push byte 0
    jmp isr_common_stub

                            
__isr1:
     cli
     push byte 0
     push byte 1
     jmp isr_common_stub

__isr2:
     cli
     push byte 0
     push byte 2
     jmp isr_common_stub

__isr3:
     cli
     push byte 0
     push byte 3
     jmp isr_common_stub

__isr4:
     cli
     push byte 0
     push byte 4
     jmp isr_common_stub

__isr5:
     cli
     push byte 0
     push byte 5
     jmp isr_common_stub

__isr6:
     cli
     push byte 0
     push byte 6
     jmp isr_common_stub

__isr7:
     cli
     push byte 0
     push byte 7
     jmp isr_common_stub

__isr8:
     cli
     push byte 8
     jmp isr_common_stub

__isr9:
     cli
     push byte 0
     push byte 9
     jmp isr_common_stub

__isr10:
     cli
     push byte 10
     jmp isr_common_stub

__isr11:
     cli
     push byte 11
     jmp isr_common_stub

__isr12:
     cli
     push byte 12
     jmp isr_common_stub

__isr13:
     cli
     push byte 13
     jmp isr_common_stub

__isr14:
     cli
     push byte 14
     jmp isr_common_stub

__isr15:
     cli
     push byte 0
     push byte 15
     jmp isr_common_stub

__isr16:
     cli
     push byte 0
     push byte 16
     jmp isr_common_stub

__isr17:
     cli
     push byte 0
     push byte 17
     jmp isr_common_stub

__isr18:
     cli
     push byte 0
     push byte 18
     jmp isr_common_stub

__isr19:
     cli
     push byte 0
     push byte 19
     jmp isr_common_stub

isr_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    call fault_handler
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret

;C call ASM the stack is 
;| X2 |
;|----|
;| X1 |
;|----|
;| ret|
;|----| <- esp
global outb
outb:
    push ebp
    mov ebp,esp
    push dx
    push ax
    mov dx,[ebp+8]      ;first arg,  since declare pass a short and a char, but pass a dword to it,WHY?
    mov al,[ebp+12]      ;second arg,
    out dx, al
    pop ax
    pop dx
    pop ebp
    ret

global inb
inb:
    push ebp
    mov ebp, esp
    push dx

    mov dx, [ebp+8]
    xor eax,eax
    in al,dx

    pop dx
    pop ebp
    ret

global store_int
store_int:
    sti
    ret

__irq0: 
    cli
    push byte 0
    push byte 32
    jmp irq_common_stub

__irq1: 
    cli
    push byte 0
    push byte 33
    jmp irq_common_stub

__irq2: 
    cli
    push byte 0
    push byte 34
    jmp irq_common_stub

__irq3: 
    cli
    push byte 0
    push byte 35
    jmp irq_common_stub


__irq4: 
    cli
    push byte 0
    push byte 36
    jmp irq_common_stub


__irq5: 
    cli
    push byte 0
    push byte 37
    jmp irq_common_stub

__irq6: 
    cli
    push byte 0
    push byte 38
    jmp irq_common_stub


__irq7: 
    cli
    push byte 0
    push byte 39
    jmp irq_common_stub


__irq8: 
    cli
    push byte 0
    push byte 40
    jmp irq_common_stub


__irq9:
    cli
    push byte 0
    push byte 41
    jmp irq_common_stub

__irq10: 
    cli
    push byte 0
    push byte 42
    jmp irq_common_stub


__irq11: 
    cli
    push byte 0
    push byte 43
    jmp irq_common_stub


__irq12:
    cli
    push byte 0
    push byte 44
    jmp irq_common_stub


__irq13: 
    cli
    push byte 0
    push byte 45
    jmp irq_common_stub

__irq14: 
    cli
    push byte 0
    push byte 46
    jmp irq_common_stub

__irq15: 
    cli
    push byte 0
    push byte 47
    jmp irq_common_stub

irq_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    call irq_handler
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret

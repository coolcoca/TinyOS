bits 32
extern kmain
global load
load:
    push ebp
    mov ebp,esp
    call kmain
    mov esp,ebp
    pop ebp
    ret

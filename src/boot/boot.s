;note pusha/popa push 16 bytes
bits 16
org 0x7C00
xor ax, ax
mov ds, ax   ;data register to 0
mov ss, ax   ;segment register to 0
mov esp,0xf000 ;stack size
mov esp,0x7ffff

read_floppy:
    mov ax, 0x100
    mov es,ax
    mov bx, 0

    mov ah, 0x02    ;read sectors
    mov al, 50       ;sectors to read
    mov ch, 0       ;cylinder
    mov cl, 2       ;sector
    mov dh, 0       ;head
    mov dl, 0x00    ;drive
    int 0x13
    jc err_read_floppy
    mov [reg16],al
    call printReg16

jmp start

err_read_floppy:
    .ee db 'Err',13,10
    mov si, .ee
    call printStr
    mov [reg16],ah
    call printReg16
    mov [reg16], al
    call printReg16
    int 0x18

printStr:
    lodsb
    or al,al
    jz .done
    mov ah, 0x0E
    int 0x10
    jmp printStr
.done:
    ret

printReg16:
    mov di,outStr16
    mov ax, [reg16]
    mov si, hexStr
    mov cx, 4

    .hexloop:
        rol ax,4
        mov bx, ax
        and bx, 0x0f
        mov bl, [si + bx]
        mov [di],bl
        inc di
        dec cx
        jnz .hexloop
    mov si,outStr16 
    call printStr
    mov si,CLSR
    call printStr
    ret


start:
    mov si, hello
    call printStr

    cli
    lgdt [gdt_desc]
    mov eax, cr0
    or al, 1
    mov cr0, eax

    mov ax,0x10
    mov ds,ax
    mov es,ax
    mov fs,ax
    mov gs,ax
    mov ss,ax

    jmp 0x08:0x1000

reg16 dw '0'
outStr16 db '0000'
CLSR db 13,10,0
hexStr db '0123456789ABCEDE'
hello db 'hello world from real MODE',13,10,0

gdt:
    dd 0x00000000
    dd 0x00000000   ;null

    dd 0x0000ffff   ;code
    dd 0x00cf9a00

    dd 0x0000ffff
    dd 0x00cf9200   ;data

gdt_desc:
    dw gdt_desc - gdt - 1
    dd gdt


bits 32

times 510-($-$$) db '0'
dw 0xaa55

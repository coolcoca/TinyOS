#include <system.h>

void scroll(int l){
    if( l > csr_y || l <= 0){
        return;
    }
    int disp = CHAR_MEM(0,l);
    int end = CHAR_MEM(MAX_COLUMNS,MAX_LINES);
    char *p = (char*)VIDEO_RAM;
    int i = 0;
    for(;i < end ; i+=1){
        if(i + disp < end){
            *(p+i) = *(p+i+disp);
        }
        else{
            *p = '\0';
        }
    }
    csr_y -= l;
}

void print_c(char c){
    char *p = (char*)(VIDEO_RAM + CHAR_MEM(csr_x,csr_y) );
    char mode = 0x1f;
    
    if(c == '\n'){
        csr_y += 1;
        csr_x = 0;
    }
    else if(c == '\r'){
        csr_x = 0;
    }
    else if(c == '\b'){
        if((int)p <= VIDEO_RAM){
            return;
        }
        *(p-2) = '\0';
        *(p-1) = '\0';
        if(csr_x > 0){
            csr_x -= 1;
        }
        else{
            csr_y -= 1;
            csr_x = MAX_COLUMNS-1;
        }
    }
    else{
        *p++ = c;
        *p++ = mode;
        csr_x += 1; 
    }

    if(csr_x >= MAX_COLUMNS){
        csr_y += 1;
        csr_x = 0;
    }

    if(csr_y >= MAX_LINES){
        scroll(1);
    }
}

int kmain(){
    idt_install();
    pic_install();
    store_int();
    char * hello = "hello world from protect mode";
    char * ptr;

    for(ptr = hello; * ptr ; ptr +=1 ){
        print_c(*ptr);
    }
    for(;;);
    return 0;
}

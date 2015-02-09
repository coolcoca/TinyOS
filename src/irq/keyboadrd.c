#include <system.h>

unsigned char kbdus[0x3a][2] = {
    /*00*/{0x0, 0x0}, {0x0, 0x0}, {'1', '!'}, {'2', '@'}, 
    /*04*/{'3', '#'}, {'4', '$'}, {'5', '%'}, {'6', '^'}, 
    /*08*/{'7', '&'}, {'8', '*'}, {'9', '('}, {'0', ')'},
    /*0c*/{'-', '_'}, {'=', '+'}, {'\b','\b'},{'\t','\t'},
    /*10*/{'q', 'Q'}, {'w', 'W'}, {'e', 'E'}, {'r', 'R'},
    /*14*/{'t', 'T'}, {'y', 'Y'}, {'u', 'U'}, {'i', 'I'},
    /*18*/{'o', 'O'}, {'p', 'P'}, {'[', '{'}, {']', '}'},
    /*1c*/{'\n','\n'},{0x0, 0x0}, {'a', 'A'}, {'s', 'S'},
    /*20*/{'d', 'D'}, {'f', 'F'}, {'g', 'G'}, {'h', 'H'},
    /*24*/{'j', 'J'}, {'k', 'K'}, {'l', 'L'}, {';', ':'},
    /*28*/{'\'','\"'},{'`', '~'}, {0x0, 0x0}, {'\\','|'}, 
    /*2c*/{'z', 'Z'}, {'x', 'X'}, {'c', 'C'}, {'v', 'V'}, 
    /*30*/{'b', 'B'}, {'n', 'N'}, {'m', 'M'}, {',', '<'},
    /*34*/{'.', '>'}, {'/', '?'}, {0x0, 0x0}, {'*', '*'},
    /*38*/{0x0, 0x0}, {' ', ' '},
};  

void keyboard_handler(struct regs* r){
    unsigned char scancode = inb(0x60);
    unsigned char mark = scancode & 0x7f;
    if(scancode & 0x80){
        if( mark == 0x36 || mark == 0x2a )
            __flag_shift = 0;
    }
    else if( mark == 0x36 || mark == 0x2a ){
            __flag_shift = 1;
    }
    else{
        print_c(kbdus[mark][__flag_shift]);
    }
    unsigned char com = inb(0x61);  //status
    outb(com|0x80, 0x61);       //disable
    outb(com&0x7f, 0x61);       //enable
}

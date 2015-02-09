#define MAX_LINES 24
#define MAX_COLUMNS 80

#define TAB_WIDTH 4
#define VIDEO_RAM 0xb8000

#define PIC_1_CTRL 0x20
#define PIC_2_CTRL 0xA0
#define PIC_1_DATA 0x21
#define PIC_2_DATA 0xA1

#define CHAR_MEM(x,y) ((MAX_COLUMNS * y + x) * 2)

#define CLOCK_FREQ 1000

static int csr_x = 0;
static int csr_y = 0;
static char __flag_shift = 0;
static volatile unsigned int time_ticks;

struct idt_entry{
    unsigned short base_low;
    unsigned short selector; 
    unsigned char always0;
    unsigned char flags;
    unsigned short base_high;
} __attribute__((packed));  //防止GCC自动填充

struct idt_ptr{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

struct regs {
    unsigned int gs, fs, es,ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;
} __attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr idtp;

extern void load_idt();
extern void outb(unsigned short, unsigned char);
extern void store_int();
void idt_set_gate(unsigned char, unsigned long, unsigned short, unsigned char);
void pic_install();
void print_c(char);
void set_timer(int);
void timer_handler(struct regs*);
void keyboard_handler(struct regs*);

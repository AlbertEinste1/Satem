#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "io.h"


/*checks if its linux or NOT LINUX fuck*/

#if defined (__linux__)
    #error "STOP USING LINUX NOW!"
    #endif

#if !defined (__i386__)
    #error "no other than this PC"
    #endif

    /*This just replaces the names with numbers making the code more readable*/
    enum vga_color {
        VGA_COLOR_BLACK = 0,
        VGA_COLOR_BLUE = 1,
        VGA_COLOR_GREEN = 2,
        VGA_COLOR_CYAN = 3,
        VGA_COLOR_RED = 4,
        VGA_COLOR_MAGENTA = 5,
        VGA_COLOR_BROWN = 6,
	    VGA_COLOR_LIGHT_GREY = 7,
	    VGA_COLOR_DARK_GREY = 8,
	    VGA_COLOR_LIGHT_BLUE = 9,
	    VGA_COLOR_LIGHT_GREEN = 10,
	    VGA_COLOR_LIGHT_CYAN = 11,
	    VGA_COLOR_LIGHT_RED = 12,
	    VGA_COLOR_LIGHT_MAGENTA = 13,
	    VGA_COLOR_LIGHT_BROWN = 14,
	    VGA_COLOR_WHITE = 15,
    };

    /**/
    static inline uint8_t 
    vga_entry_color(enum vga_color fg, enum vga_color bg)
    {
        return fg | bg << 4;
    }

    static inline uint16_t
    vga_entry(unsigned char uc, uint8_t color)
    {
        return (uint16_t) uc | (uint16_t) color << 8;
    }

    size_t strlen(const char* str)
    {
        size_t len = 0;
        while (str[len])
        len++;
        return len;
    }

    #define VGA_WIDTH 80
    #define VGA_HEIGHT 25
    #define VGA_MEMORY 0xB8000 


    size_t terminal_row;
    size_t terminal_column;
    uint8_t terminal_color;
    uint16_t* terminal_buffer = (uint16_t*)VGA_MEMORY;


    void terminal_initialize(void)
    {
        terminal_row = 0;
        terminal_column = 0;
        terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    
        for (size_t y = 0; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
        const size_t index = y * VGA_WIDTH + x;
        terminal_buffer[index] = vga_entry(' ', terminal_color);
    }
}


    /*that is why os dev is so beautiful, im so lost rn LEL, i mean rn uhhhhhh yeahhh its 12 am rn*/


    
    }
    void terminal_setcolor(uint8_t color)
    {
        terminal_color = color;
    }


    void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
    {

        const size_t index = y * VGA_WIDTH + x;
        terminal_buffer[index] = vga_entry(c, color);
    }

     void terminal_scroll(void){
        for (size_t y = 0; y < VGA_HEIGHT -1; y++){
        for (size_t x = 0; x < VGA_WIDTH; x++){
            const size_t index = y * VGA_WIDTH + x;
            const size_t next_index = (y + 1) * VGA_WIDTH + x;
            terminal_buffer[index] = terminal_buffer[next_index];
            
        }
    }
        for (size_t x = 0; x < VGA_WIDTH; x++){
            const size_t last_index = (VGA_HEIGHT - 1) * VGA_WIDTH + x;
            terminal_buffer[last_index] = vga_entry(' ', terminal_color);
        }
    
    }

    void terminal_putchar(char c)
    {
        /*handles the \n support for the excercise*/

         if (terminal_column == VGA_WIDTH){
                terminal_column = 0;
            }

                
    /*keys keys o algo*/


           if (c == '\n'){
            terminal_column = 0;
            ++terminal_row;
            if (terminal_row == VGA_HEIGHT){
                    terminal_scroll();
                    terminal_column = VGA_HEIGHT - 1;
                }
            return;

           
        }

        terminal_putentryat(c, terminal_color, terminal_column, terminal_row); {
        if (++terminal_column == VGA_WIDTH){
            terminal_column = 0;
            if (++terminal_row == VGA_HEIGHT){
            terminal_scroll();
            terminal_column = VGA_HEIGHT -1;
            }
            
          
        }
       }
    }

   

    void terminal_write(const char* data, size_t size)
    {
        for (size_t i = 0; i < size; i++)
        terminal_putchar(data[i]);

        
    }

    void terminal_writestring(const char* data)
    {
        terminal_write(data, strlen(data));
    }

    
/*basic keyboard driver*/

    static inline void readkey(void){
        const char keymap[128] = {
            0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
            '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',
            '[', ']', '\n', 0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 

        };
        
        uint16_t port = 0x64;
        uint8_t status = inb(port);

        /*eh, just a character map*/
        
        if (status & 0x01){ 
        uint16_t port2 = 0x60;
        uint8_t data = inb(port2);

        if (data < 128){
            char c = keymap[data];
        

            if (c == '\b'){
                --terminal_column;
                
                terminal_writestring(" ");
                --terminal_column;

                if (terminal_column > 0){
                    return;
                }
            }
            else if (c != 0){
                terminal_putchar(c);
            }
                
                
            
        }

        
        
    }


    }
    void kernel_main(void)
    {
        
        terminal_initialize();

        terminal_writestring("hehehehe\n");
        terminal_writestring("TEST\n");

        

                
        
    
    

    terminal_writestring("BOTTOM\n");

    while(1){
        readkey();
    }
    }
    /*very happy moment*/
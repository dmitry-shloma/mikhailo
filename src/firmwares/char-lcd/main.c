#include <avr/io.h>

#include "lcd.h"

int main( void )
{
    lcd_init();
    lcd_goto(0,0);
    lcd_puts("***");
    lcd_goto(0,1);
    lcd_puts("***");
    while(1) {}
    return 0;
}

















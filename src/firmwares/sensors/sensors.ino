#include "onewirehelper.h"
#include "hih4000helper.h"
#include "lcdtexthelper.h"

#define HIH4000_PIN 0
#define ONE_SEC 1000

// LCD size's
#define LCD_COLS 24
#define LCD_ROWS 2

unsigned char addrv[3][8] = {{0}};
uint8_t addrc = 0;

void setup()
{
    lcd_init(LCD_COLS, LCD_ROWS);
    onewire_enum_avaliable_devices(&addrc, addrv);
}

void loop()
{
    for (int i = 0; i < addrc; ++i) {
        char str[19] = "";  // 0...15 byte for addr, 16 byte - ':', 17 byte - ' ', 18 byte - '\0'
        onewire_addr_to_str(addrv[i], str);
        str[16] = ':';
        str[17] = ' ';
        // str[18] is already '\0';

        // memcpy(&str[16], ": ", 2); // don't use this, because it requires 7942, instead of 7934 bytes
                
        lcd_clear();
        float t = onewire_get_temperature(addrv[i], C);
        lcd_out_value(str, t, 4, 1, "DEGREE_C", 0, 0);
        
        float rh = get_humidity(HIH4000_PIN);
        lcd_out_value("RH: ", rh, 4, 1, "RH", 0, 1);
        delay(2 * ONE_SEC);
    }
        
}

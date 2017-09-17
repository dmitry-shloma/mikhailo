#include <string.h>

#include "onewirehelper.h"
#include "hih4000helper.h"
#include "lcdtexthelper.h"

#define HIH4000_PIN 0
#define ONE_SEC 1000

unsigned char addrv[3][8] = {{0}};
uint8_t addrc = 0;

void setup()
{
    lcd_init();
    onewire_enum_avaliable_devices(&addrc, addrv);
}

void loop()
{
    for (int i = 0; i < addrc; ++i) {
        char str[17] = "";
        onewire_addr_to_str(addrv[i], str);
        lcd_out_text(str, 0, 0, true);
        float t = onewire_get_temperature(addrv[i], C);
        lcd_out_value(": ", t, 4, 1, T, 16, 0, false);
        
        float rh = get_humidity(HIH4000_PIN);
        lcd_out_value("RH: ", rh, 4, 1, RH, 0, 1, false);
        delay(2 * ONE_SEC);
    }
        
}

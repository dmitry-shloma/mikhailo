#include <string.h>

#include "lcdtexthelper.h"
#include "randhelper.h"

#define ONE_SEC 1000
#define UNCONNECTED_PIN 5

void setup()
{
    init_rand(analogRead(UNCONNECTED_PIN));
    
    lcd_init();
    const char *banner = "AQUARIUM";
    lcd_out_text(banner, (24 - strlen(banner)) / 2, 0, true);
    delay(5 * ONE_SEC);
}

void loop()
{
    float t[6] = {0};
    for (uint8_t i = 0; i < 6; ++i) {
        t[i] = frrand(0.0, 99.0);
    };

    lcd_out_value("1: ", t[0], 2, 0, T, 0, 0, true);
    lcd_out_value("2: ", t[1], 2, 0, T, 8, 0, false);
    lcd_out_value("3: ", t[2], 2, 0, T, 16, 0, false);
    lcd_out_value("4: ", t[3], 2, 0, RH, 0, 1, false);
    lcd_out_value("5: ", t[4], 2, 0, RH, 8, 1, false);
    lcd_out_value("6: ", t[5], 2, 0, V, 16, 1, false);
    
    delay(ONE_SEC);
}

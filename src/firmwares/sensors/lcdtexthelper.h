#ifndef LCDTEXTHELPER_H
#define LCDTEXTHELPER_H

#include <stdlib.h>
#include <string.h>

#include <LiquidCrystal.h>

// LCD pin's
#define LCD_RS_PIN  4
#define LCD_E_PIN   6
#define LCD_DB4_PIN 10
#define LCD_DB5_PIN 11
#define LCD_DB6_PIN 12
#define LCD_DB7_PIN 13

// LCD size's
#define LCD_COLS 24
#define LCD_ROWS 2

void lcd_init();
void lcd_out_text(const char *str, uint8_t col, uint8_t row, bool cls);
void lcd_out_char(const unsigned char *ch, uint8_t id, uint8_t col, uint8_t row, bool cls);

enum DIMENSION {NONE, T, RH, V};
void lcd_out_value(const char *msg, float value, char width, uint8_t prec, DIMENSION dim, uint8_t col, uint8_t row, bool cls);
void lcd_clear();

LiquidCrystal lcd(LCD_RS_PIN, LCD_E_PIN, LCD_DB4_PIN, LCD_DB5_PIN, LCD_DB6_PIN, LCD_DB7_PIN);

void lcd_init()
{
    lcd.begin(LCD_COLS, LCD_ROWS);
}

void lcd_out_text(const char *str, uint8_t col, uint8_t row, bool cls)
{
    if (cls) {
        lcd_clear();
    }
    lcd.setCursor(col, row);
    lcd.print(str);
}

void lcd_out_char(const unsigned char *ch, uint8_t id, uint8_t col, uint8_t row, bool cls)
{
    if (cls) {
        lcd_clear();
    }
    unsigned char ch_[8] = {0};
    memcpy(ch_, ch, 8);
    lcd.createChar(id, ch_);
    lcd.setCursor(col, row);
    lcd.write(id);
}

void lcd_out_value(const char *msg, float value, char width, uint8_t prec, DIMENSION dim, uint8_t col, uint8_t row, bool cls)
{
    // INFO: due to some performance reasons %f is not included in the Arduino's implementation of sprintf().
    // A better option would be to use dtostrf(), than used sprintf().
    // https://stackoverflow.com/questions/27651012

    // NOTE: dynamic memory allocation is not always better than static
    char value_str[LCD_COLS] = ""; // the maximum width of, what can be displayed on the screen
    dtostrf(value, width, prec, value_str);

    char buf [LCD_COLS] = ""; // the maximum width of, what can be displayed on the screen
    if (dim == T) {
        sprintf(buf, "%s%s C", msg, value_str);
    } else if (dim == RH) {
        sprintf(buf, "%s%s%%", msg, value_str);
    } else if (dim == V) {
        sprintf(buf, "%s%s m/s", msg, value_str);
    }
    
    lcd_out_text(buf, col, row, cls);
    
    if (dim == T) {
        const unsigned char degree[8] = {0x07, 0x05, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00}; // degree symbol
        lcd_out_char(degree, 0, col + strlen(buf) - 2, row, false);
    }
}

void lcd_clear()
{
    lcd.clear();
}

#endif // LCDTEXTHELPER_H


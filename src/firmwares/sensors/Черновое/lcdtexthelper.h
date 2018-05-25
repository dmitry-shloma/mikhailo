/****************************************************************************
**
** Copyright (C) 2017 Dmitry Shloma
** Contact: http://www.cpp-training.ru
**
** This file is part of the Mikhailo's project and wraps from 
** LiquidCrystal's library the following functions : LiquidCrystal(), begin(), 
** clear(), write() in use with createChar() , print(), createChar(). 
** To the other functions, you can access using the object lcd_
****************************************************************************/

// TODO: Implement the function, that wraps the write() for uses with Serial.read()

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

static unsigned char lcd_cols_ = 0;
static unsigned char lcd_rows_ = 0;

LiquidCrystal lcd_(LCD_RS_PIN, LCD_E_PIN, LCD_DB4_PIN, LCD_DB5_PIN, LCD_DB6_PIN, LCD_DB7_PIN);

/**
 * @brief lcd_init function for initializing the lcd
 * @param lcd_cols columns count
 * @param lcd_rows rows count
 */
void lcd_init(uint8_t lcd_cols, uint8_t lcd_rows) {
    static bool is_init = false;
    if (!is_init) {
        lcd_cols_ = lcd_cols;
        lcd_rows_ = lcd_rows;
        lcd_.begin(lcd_cols_, lcd_rows_);
        is_init = true;
    }
}

/**
 * @brief lcd_out_text function for output text to lcd
 * @param col column's id for output (from 0 to lcd's columns)
 * @param row row's id for output (from 0 to lcd's rows)
 */
void lcd_out_text(const char *str, uint8_t col, uint8_t row) {
    lcd_.setCursor(col, row);
    lcd_.print(str);
}

/**
 * @brief lcd_out_custom_char function for output custom char to lcd
 * @param custom_ch custom char
 * @param id for a custom character (from 0 to 7)
 * @param col column's id for output (from 0 to lcd's columns)
 * @param row row's id for output (from 0 to lcd's rows)
 */
void lcd_out_custom_char(const unsigned char *custom_ch, uint8_t id, uint8_t col, uint8_t row) {
    unsigned char custom_ch_[8] = {0};
    memcpy(custom_ch_, custom_ch, 8);
    lcd_.createChar(id, custom_ch_);
    lcd_.setCursor(col, row);
    lcd_.write(id);
}

/**
 * @brief lcd_out_value
 * @param pref text before output value
 * @param value value for output
 * @param width
 * @param prec precision, i.e. the number of digits after the decimal point (0 is no digit)
 * @param suf text after output value. Allowable values: "NONE" or "" is empty, "DEGREE_C" is degree symbol 
 * of Celsius, "DEGREE_F" is degree symbol of Fahrenheit, "DEGREE" is only degree symbol, "RH" is % for 
 * relative humidity or use any value. e.g. "m/s"
 * @param col column's id for output (from 0 to lcd's columns)
 * @param row row's id for output (from 0 to lcd's rows)
 */
void lcd_out_value(const char *pref, float value, char width, uint8_t prec, const char *suf, uint8_t col, uint8_t row) {
    // INFO: due to some performance reasons %f is not included in the Arduino's implementation of sprintf().
    // A better option would be to use dtostrf(), than used sprintf().
    // https://stackoverflow.com/questions/27651012

    // NOTE: dynamic memory allocation is not always better than static :)
    char value_str[lcd_cols_] = ""; // the maximum width of, what can be displayed on the screen
    dtostrf(value, width, prec, value_str);

    bool is_degree = false;
    char buf [lcd_cols_] = ""; // the maximum width of, what can be displayed on the screen
    if (strcmp(suf, "DEGREE_C") == 0) {
        is_degree = true;
        sprintf(buf, "%s%s C", pref, value_str);
    } else if (strcmp(suf, "DEGREE_F") == 0) {
        is_degree = true;
        sprintf(buf, "%s%s F", pref, value_str);
    } else if (strcmp(suf, "DEGREE") == 0) {
        is_degree = true;
        sprintf(buf, "%s%s  ", pref, value_str); // two spaces in this "%s%s  " are very important
    } else if (strcmp(suf, "RH") == 0) {
        sprintf(buf, "%s%s%%", pref, value_str);
    } else if (strcmp(suf, "NONE") == 0 || strcmp(suf, "") == 0) {
        sprintf(buf, "%s%s", pref, value_str);
    } else {
        sprintf(buf, "%s%s%s", pref, value_str, suf);
    }
    
    lcd_out_text(buf, col, row);
    
    if (is_degree) {
        const unsigned char degree[8] = {0x07, 0x05, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00}; // degree symbol
        lcd_out_custom_char(degree, 0, col + strlen(buf) - 2, row);
    }
}

/**
 * @brief lcd_clear clear lcd
 */
void lcd_clear() {
    lcd_.clear();
}

#endif // LCDTEXTHELPER_H


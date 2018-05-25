#include <LiquidCrystal.h>

/*
  Rotate
 Demonstrates analog input by reading an analog sensor on analog pin 0 and
 turning on and off a light emitting diode(LED)  connected to digital pin 13. 
 The amount of time the LED will be on and off depends on
 the value obtained by analogRead(). 
 
 The circuit:
 * Potentiometer attached to analog input 0
 * center pin of the potentiometer to the analog pin
 * one side pin (either one) to ground
 * the other side pin to +5V
 * LED anode (long leg) attached to digital output 13
 * LED cathode (short leg) attached to ground
 
 * Note: because most Arduinos have a built-in LED attached 
 to pin 13 on the board, the LED is optional.
 
 
 Created by Dmitry Shloma
 17 May 2013
 
 This example code is in the public domain.
 
 http://arduino.cc/en/Tutorial/AnalogInput
 
 */

int inPin = A0;        // select the input pin for the potentiometer
int value = 0;         // variable to store the value coming from the sensor
long revol = 0;        // revolutions
long revol_l = 0;      // revolution at last display

//LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

void setup() {
  Serial.begin(9600);
//  lcd.begin(8, 2);
}

void loop() {
  // read the value from the sensor
  value = analogRead(inPin);
  Serial.println(value);
}

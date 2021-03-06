#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GrayOLED.h>
#include <SPI.h>

#define ONE_WIRE_BUS 9
#define SDA_PIN A4
#define SCL_PIN A5

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float temp;
uint8_t cycles = 20;

Adafruit_7segment matrix = Adafruit_7segment();

void setup() {
  sensors.begin();

  // DISPLAY
  matrix.begin(0x70);
  // print a floating point 
  matrix.writeDisplay();
  for(uint8_t ii = 0; ii < 5; ii++) {
    matrix.writeDigitRaw(ii,0b01100011);
    matrix.writeDisplay();
    delay(250);
  }
  matrix.clear();
}

void loop() {

  for(uint16_t i = 0; i < cycles; i++) {
    sensors.requestTemperatures();
    temp = temp + sensors.getTempCByIndex(0);
    delay(100);
  }

  float intint = (temp/cycles)*10;
  intint = round(intint);
  intint = intint/10;
  matrix.print(intint);
  matrix.writeDigitRaw(4,0b01100011);
  matrix.writeDisplay();

  temp = 0;
  delay(500);
}
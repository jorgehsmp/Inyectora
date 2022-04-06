#include <Adafruit_MAX31865.h>
#include "PID_v1.h"

// Use software SPI: CS, DI, DO, CLK
Adafruit_MAX31865 pt_ext = Adafruit_MAX31865(8, 11, 12, 13);
Adafruit_MAX31865 pt_med = Adafruit_MAX31865(9, 11, 12, 13);

#define HEAT_EXT 15
#define HEAT_MED 14



long measureTime;
short state = 0;
bool list = false, working = false;

void setup() 
{
  pinMode(HEAT_EXT, OUTPUT);
  pinMode(HEAT_MED, OUTPUT);
  
  Serial.begin(115200);
  Serial.println("TFM INYECTORA USAL");

  pt_ext.begin(MAX31865_3WIRE);
  pt_med.begin(MAX31865_3WIRE);
  menu();
}


void loop() 
{
    leerSerial();
    if (working && (millis() > measureTime))
    {
      temperatureControl();
      measureTime = millis() + 1000;
    }

}

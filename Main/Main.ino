#include <Adafruit_MAX31865.h>
#include "PID_v1.h"

// Use software SPI: CS, DI, DO, CLK
Adafruit_MAX31865 pt_ext = Adafruit_MAX31865(8, 11, 12, 13);
Adafruit_MAX31865 pt_med = Adafruit_MAX31865(9, 11, 12, 13);

#define HEAT_EXT  15
#define HEAT_MED  14
#define PWM_pin   2
#define DIR_pin   3
#define OpenEndStop_pin  16
#define CloseEndStop_pin 17
#define Open_pin  6
#define Close_pin 5

long measureTime;
bool purge = false;
int state = 0;

void setup() 
{
  //HEATING RESISTORS
  pinMode(HEAT_EXT, OUTPUT);
  pinMode(HEAT_MED, OUTPUT);

  //HBS57
  pinMode(PWM_pin, OUTPUT);
  pinMode(DIR_pin, OUTPUT);

  //Clamping
  pinMode(OpenEndStop_pin, INPUT);
  pinMode(CloseEndStop_pin, INPUT);
  pinMode(Open_pin, OUTPUT);
  pinMode(Close_pin, OUTPUT);
  digitalWrite(Open_pin, HIGH);
  digitalWrite(Close_pin, HIGH);
  
  Serial.begin(115200);
  Serial.println("TFM INYECTORA USAL");

}


void loop() 
{
  StateMachine();
    /*leerSerial();
    if (working && (millis() > measureTime))
    {
      temperatureControl();
      measureTime = millis() + 1000;
    }*/

}

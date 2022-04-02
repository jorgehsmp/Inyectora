#include <Adafruit_MAX31865.h>
#include "PID_v1.h"

// Use software SPI: CS, DI, DO, CLK
Adafruit_MAX31865 pt_ext = Adafruit_MAX31865(8, 11, 12, 13);
Adafruit_MAX31865 pt_med = Adafruit_MAX31865(9, 11, 12, 13);

#define RREF      430.0
#define RNOMINAL  100.0

#define HEAT_EXT 15
#define HEAT_MED 14

double Setpoint_PText = 25, Input_PText, Output_PText;
double Setpoint_PTmed = 24, Input_PTmed, Output_PTmed;

double Kp1=2, Ki1=5, Kd1=1;
double Kp2=2, Ki2=5, Kd2=1;
PID PText_PID(&Input_PText, &Output_PText, &Setpoint_PText, Kp1, Ki1, Kd1, DIRECT);
PID PTmed_PID(&Input_PTmed, &Output_PTmed, &Setpoint_PTmed, Kp2, Ki2, Kd2, DIRECT);

void setup() 
{
  pinMode(HEAT_EXT, OUTPUT);
  pinMode(HEAT_MED, OUTPUT);
  
  Serial.begin(115200);
  Serial.println("PT100 Sensors Test!");

  pt_ext.begin(MAX31865_3WIRE);
  pt_med.begin(MAX31865_3WIRE);

  PText_PID.SetMode(AUTOMATIC);
  PTmed_PID.SetMode(AUTOMATIC);
}


void loop() 
{
  Input_PText = pt_ext.temperature(RNOMINAL, RREF);
  Serial.print("Temperatura Extrusor = "); Serial.println(Input_PText);
  PText_PID.Compute();
  digitalWrite(HEAT_EXT, Output_PText);

  uint8_t fault_ext = pt_ext.readFault();
  if (fault_ext) {
    Serial.print("Fault 0x"); Serial.println(fault_ext, HEX);
    if (fault_ext & MAX31865_FAULT_HIGHTHRESH) {
      Serial.println("RTD High Threshold"); 
    }
    if (fault_ext & MAX31865_FAULT_LOWTHRESH) {
      Serial.println("RTD Low Threshold"); 
    }
    if (fault_ext & MAX31865_FAULT_REFINLOW) {
      Serial.println("REFIN- > 0.85 x Bias"); 
    }
    if (fault_ext & MAX31865_FAULT_REFINHIGH) {
      Serial.println("REFIN- < 0.85 x Bias - FORCE- open"); 
    }
    if (fault_ext & MAX31865_FAULT_RTDINLOW) {
      Serial.println("RTDIN- < 0.85 x Bias - FORCE- open"); 
    }
    if (fault_ext & MAX31865_FAULT_OVUV) {
      Serial.println("Under/Over voltage"); 
    }
    pt_ext.clearFault();
  }

  Input_PTmed = pt_med.temperature(RNOMINAL, RREF);
  Serial.print("Temperatura Barril = "); Serial.println(Input_PTmed);
  PTmed_PID.Compute();
  digitalWrite(HEAT_MED, Output_PTmed);

    uint8_t fault_med = pt_med.readFault();
  if (fault_med) {
    Serial.print("Fault 0x"); Serial.println(fault_med, HEX);
    if (fault_med & MAX31865_FAULT_HIGHTHRESH) {
      Serial.println("RTD High Threshold"); 
    }
    if (fault_med & MAX31865_FAULT_LOWTHRESH) {
      Serial.println("RTD Low Threshold"); 
    }
    if (fault_med & MAX31865_FAULT_REFINLOW) {
      Serial.println("REFIN- > 0.85 x Bias"); 
    }
    if (fault_med & MAX31865_FAULT_REFINHIGH) {
      Serial.println("REFIN- < 0.85 x Bias - FORCE- open"); 
    }
    if (fault_med & MAX31865_FAULT_RTDINLOW) {
      Serial.println("RTDIN- < 0.85 x Bias - FORCE- open"); 
    }
    if (fault_med & MAX31865_FAULT_OVUV) {
      Serial.println("Under/Over voltage"); 
    }
    pt_med.clearFault();
  }
  Serial.println();
  
  delay(1000);
}

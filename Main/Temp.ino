#define RREF      430.0
#define RNOMINAL  100.0
#define timeMeasureInterval   5000

bool TempPhase2 = false;

unsigned long lastMeasure;

double Setpoint_PText, Input_PText, Output_PText;
double Setpoint_PTmed, Input_PTmed, Output_PTmed;

double Kp1=10, Ki1=1, Kd1=0.1;
double Kp2=10, Ki2=1, Kd2=0.1;

PID PText_PID(&Input_PText, &Output_PText, &Setpoint_PText, Kp1, Ki1, Kd1, DIRECT);
PID PTmed_PID(&Input_PTmed, &Output_PTmed, &Setpoint_PTmed, Kp2, Ki2, Kd2, DIRECT);

int PTinit()
{
  int fail = 2;
  fail -= pt_ext.begin(MAX31865_3WIRE);
  fail -= pt_med.begin(MAX31865_3WIRE);

  return fail;
}

void tempInjUnit1_EN()
{
  Setpoint_PText = 175;
  
  PText_PID.SetMode(AUTOMATIC);
  
  Serial.print(F("\n\nTemperatura Objetivo del EXTRUSOR: "));Serial.println(Setpoint_PText);
}

void tempInjUnit2_EN()
{
  Setpoint_PTmed = 135;
    
  PTmed_PID.SetMode(AUTOMATIC);

  Serial.print(F("Temperatura Objetivo del BARRIL: "));Serial.println(Setpoint_PTmed);
}

void tempInjUnitDIS()
{
  Setpoint_PText = 22.5;
  Setpoint_PTmed = 22.5;

  Serial.print(F("\n\nTemperatura Objetivo del EXTRUSOR: "));Serial.print(Setpoint_PText);
  Serial.print(F("\n\nTemperatura Objetivo del BARRIL: "));Serial.println(Setpoint_PTmed);
  Serial.println();

  PText_PID.SetMode(AUTOMATIC);
  PTmed_PID.SetMode(AUTOMATIC);

  TempPhase2 = false;
}

void temperatureControl()
{
  if (millis() - lastMeasure > timeMeasureInterval)
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

    if (state == 3 && (Input_PText > (Setpoint_PText * 0.75)) && TempPhase2 == false)
    {
      Serial.println("Iniciando segunda fase del calentamiento");
      tempInjUnit2_EN();
      TempPhase2 = true;
    }
    if (TempPhase2)
    {
      heatingMaterial();
      
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
    }
    
    Serial.println();
    lastMeasure = millis();
  }
  
  if (state == 4 && (Input_PTmed > (Setpoint_PTmed)))
  {
    temperatureControl();
  }
}

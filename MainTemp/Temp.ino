#define RREF      430.0
#define RNOMINAL  100.0
#define timeMeasureInterval   250

bool TempPhase2 = false;

unsigned long lastMeasure;

double Setpoint_PText, Input_PText, Output_PText;
double Setpoint_PTmed, Input_PTmed, Output_PTmed;

double Kp1=10, Ki1=5, Kd1=1;
double Kp2=10, Ki2=5, Kd2=1;

PID PText_PID(&Input_PText, &Output_PText, &Setpoint_PText, Kp1, Ki1, Kd1, DIRECT);
PID PTmed_PID(&Input_PTmed, &Output_PTmed, &Setpoint_PTmed, Kp2, Ki2, Kd2, DIRECT);


void tempInjUnit1_EN()
{
  PText_PID.SetMode(AUTOMATIC);
  
  Setpoint_PText = 50;
  
  Serial.print(F("\n\nTemp. objetivo EXTRUSOR: "));Serial.println(Setpoint_PText);
}

void tempInjUnit2_EN()
{
  PTmed_PID.SetMode(AUTOMATIC);

  Setpoint_PTmed = 40;

  Serial.print(F("Temp. objetivo BARRIL: "));Serial.println(Setpoint_PTmed);
}

void tempInjUnitDIS()
{
  Setpoint_PText = 22.5;
  Setpoint_PTmed = 22.5;

  Serial.print(F("\n\nTemp. objetivo EXTRUSOR: "));Serial.print(Setpoint_PText);
  Serial.print(F("\n\nTemp. objetivo BARRIL: "));Serial.println(Setpoint_PTmed);
  Serial.println();

  PText_PID.SetMode(AUTOMATIC);
  PTmed_PID.SetMode(AUTOMATIC);
  
  TempPhase2 == false;
}

void temperatureControl()
{
  Input_PText = pt_ext.temperature(RNOMINAL, RREF);
  PText_PID.Compute();
  digitalWrite(HEAT_EXT, Output_PText);
  
  Input_PTmed = pt_med.temperature(RNOMINAL, RREF);
  PTmed_PID.Compute();
  digitalWrite(HEAT_MED, Output_PTmed);
  
  if (millis() - lastMeasure > timeMeasureInterval)
  {
    Serial.print("Temp. EXTRUSOR = "); Serial.println(Input_PText);
    Serial.print(F("\n\nCuando Temp. objetivo: "));Serial.println(Setpoint_PText);

    Serial.print("Temp. BARRIL = "); Serial.println(Input_PTmed);
    Serial.print(F("\n\nCuando Temp. objetivo: "));Serial.println(Setpoint_PTmed);

    if ((Input_PText > (Setpoint_PText * 0.75)) && TempPhase2 == false)
    {
      Serial.print("Iniciando segunda fase del calentamiento");
      tempInjUnit2_EN();
      TempPhase2 == true;
    }
    
    Serial.println();
    lastMeasure = millis();
  }
}

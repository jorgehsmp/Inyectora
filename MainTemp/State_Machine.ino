void State_Stop ();
void State_Run();

bool enM_rep = false;
bool disM_rep = false;

void StateMachine ()
{
    switch (state) 
    {
      case 0:         //Estado: inicio
        State_Stop();
        break;
        
      case 1:         //Estado: comprobación
        State_Run(); 
        break;

      default:
        break;
    }
}

void State_Stop()
{
  if (!disM_rep)
  {
    Serial.print(F("\n\tDesactivando control de temperatura..."));
    delay(2000);
    tempInjUnitDIS();
    disM_rep = true;
  }
  temperatureControl();
  menu();
  leerSerial();
}

void State_Run()
{
  if (!enM_rep)
  {
      Serial.print(F("\n\tActivando control de temperatura..."));
      delay(2000);
      tempInjUnit1_EN();
      enM_rep = true;
  }

  temperatureControl();
  menu();
  leerSerial();
}

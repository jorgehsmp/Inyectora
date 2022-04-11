void State_Init ();
void State_Check();
void State_EnableMachine();
void State_enableInjUnit();
void State_disableInjUnit();
void State_purge();
void State_InjCycle();
void State_Close();
void State_Inj();
void State_Open();
void State_Withdraw();

bool w_rep = false;
bool enM_rep = false;
bool disM_rep = false;

void StateMachine ()
{
    switch (state) 
    {
      case 0:         //Estado: inicio
        State_Init();
        break;
        
      case 1:         //Estado: comprobación
        State_Check(); 
        break;
        
      case 2:         //Estado: máquina activa
        State_EnableMachine();
        break;
        
      case 3:         //Estado: activar unidad de inyeción
        State_enableInjUnit();
        break;
        
      case 4:         //Estado: desactivar unidad de inyeción
        State_disableInjUnit();
        break;
        
      case 5:         //Estado: purgar unidad de inyección
        State_purge();
        break;

      case 6:         //Estado: ciclo de inyección
        State_InjCycle();
        break;

      case 7:         //Estado: cerrar molde
        State_Close();
        break;

      case 8:         //Estado: inyectar
        State_Inj();
        break;

      case 9:         //Estado: abrir molde
        State_Open();
        break;

      case 10:         //Estado: retirar pieza
        State_Withdraw();
        break;
        
      default:
        break;
    }
}

void State_Init()
{
  menu();
  leerSerial();
}

void State_Check()
{
  int fail = 0;
  Serial.print(F("\n\tComprobando los periféricos..."));
  delay(2000);
  fail += PTinit();
  fail += clampingInit();
  screwInit();
  
  if (!fail)
  {
    state = 2;
    m_rep = false;
  }
  else{
    Serial.print(F("\n\tFALLO EN LA COMPROBACIÓN DE PERIFERICOS..."));
    delay(1000);
    Serial.print(F("\n\tDESARMANDO..."));
    delay(2000);
    state = 0;
    m_rep = false;
  }
}

void State_EnableMachine()
{
  menu();
  leerSerial();
}

void State_enableInjUnit()
{
  if (!enM_rep)
  {
      tempInjUnit1_EN();
      enM_rep = true;
  }

  temperatureControl();
  menu();
  leerSerial();
}

void State_disableInjUnit()
{
  if (!disM_rep)
  {
    Serial.print(F("\n\tDesactivando unidad de inyección..."));
    delay(2000);
    tempInjUnitDIS();
    disM_rep = true;
  }
  temperatureControl();       // Estando en el estado 4, solo sale de tempCntrl cuando la temp del barril es inferior a la temp objetivo

  disM_rep = false;
  purge = false;
  m_rep = false;
  enM_rep = false;
  state = 2;

}

void State_purge()
{
  Serial.print(F("\n\tPurgando unidad de inyección..."));
  delay(2000);
  purgeBarrel();
  purge = true;
  m_rep = false;
  state = 3;
}

void State_InjCycle()
{
  Serial.print(F("\n\tIniciando ciclo de inyección..."));
  delay(2000);
  state = 7;
}

void State_Close()
{
  int fail = 0;
  
  Serial.print(F("\n\tCerrando molde..."));
  delay(2000);
  fail = closeInjUnit();
  if (fail)
  {
    //Parada de emergencia
    Serial.print(F("\n\tPARADA DE EMERGENCIA"));
    delay(1000);
    Serial.print(F("\n\tDESARMANDO..."));
    delay(2000);
    m_rep = false;
    state = 0;
    return;
  }
  Serial.print(F(" Molde cerrado"));
  state = 8;
}

void State_Inj()
{
  Serial.print(F("\n\tInyectando material..."));
  delay(2000);
  injectingMaterial();
  Serial.print(F("\n\tEnfriando el molde..."));
  delay(2000);
  state = 9;
}

void State_Open()
{
  int fail = 0;
  
  Serial.print(F("\n\tAbriendo el molde..."));
  delay(2000);
  fail = openInjUnit();
  if (fail)
  {
    //Parada de emergencia
    Serial.print(F("\n\tPARADA DE EMERGENCIA"));
    delay(1000);
    Serial.print(F("\n\tDESARMANDO..."));
    delay(2000);
    m_rep = false;
    state = 0;
    return;
  }
  Serial.print(F(" Molde abierto"));
  state = 10;
}

void State_Withdraw()
{
  if (Serial.available()) 
  {
    char withdrawConfirmation = Serial.read();
    if (!w_rep)
    {
      Serial.print(F("\n\tConfirme la extracción de la pieza (y)..."));
      w_rep = true;
    }
    switch (withdrawConfirmation) 
    {
      case 'y':
        Serial.println(F("\n\tExtracción de la pieza confirmada..."));
        delay(2000);
        m_rep = false;
        w_rep = false;
        state = 3;
        break;
      default:
        Serial.print(F("\n\tOpción incorrecta..."));
        break;
    }
  }
}

bool m_rep = false;

void menu() 
{
  if (!m_rep)
  {
    Serial.print(F("\n\tMENU PRUEBA DE PROGRAMA DE TEMPERATURA"));
    
    switch (state)
    {
      case 0:
        Serial.print(F("\n\t1 - INICIAR"));
        break;
        
      case 1:
        Serial.print(F("\n\t0 - FINALIZAR"));
        break;
        
      default:
        break;
    }
    Serial.println();
    Serial.print(F("\n\nPulse tecla + INTRO\n"));
    Serial.flush();
    m_rep = true;
  }
}

void leerSerial() 
{
  if (Serial.available()) 
  {
    char desireState = Serial.read();
  
    switch (desireState) 
    {
      case '0':
        if (state == 1)
        {
          Serial.print(F("\n\nOpción escogida: FINALIZAR\n"));
          state = 0;
          m_rep = false;
        }
        else{
          Serial.print(F("\n\nEstado deseado incorrecto\n"));
        }
        break;
        
      case '1':
        if (state == 0)
        {
          Serial.print(F("\n\nOpción escogida: INICIAR\n"));
          state = 1;
          m_rep = false;
        }
        else{
          Serial.print(F("\n\nEstado deseado incorrecto\n"));
        }
        break;
 
      default:
        Serial.print(F("\n\nEstado deseado incorrecto\n"));
        break;
    }
  }
}

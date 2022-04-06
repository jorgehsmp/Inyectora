
bool injState = false, Lista = false, checked = false;

bool menu() 
{
  Serial.print(F("\n\t0 - Comprobar periféricos"));
  if ( checked == true )
  {
    Serial.print(F("\n\t1 - Activar/Desactivar unidad de inyección"));
    Serial.print(F("\n\t2 - Purgar barril de inyección"));
    Serial.print(F("\n\t3 - Comenzar ciclo de inyección"));
  }
  Serial.println();
  Serial.print(F("\n\ta - Abrir molde"));
  Serial.print(F("\n\tc - Cerrar molde"));
  Serial.println();
  Serial.print(F("\n\tm - Mostrar Menu"));
  Serial.println();
  Serial.print(F("\n\nPulse tecla + INTRO\n"));
  Serial.flush();

  return true;
}

void leerSerial() 
{
  if (Serial.available()) 
  {
    char c = Serial.read();
  
    switch (c) 
    {
      case '0':
        Serial.print(F("\n\nCOMPROBANDO PERIFERICOS...\n"));
        working = false;
        checked = true;
        menu();
        break;
        
      case '1':
        if (checked != false)
        {
          if (injState == false)
          {
            Serial.print(F("\n\nACTIVANDO UNIDAD DE INYECCIÓN...\n"));
            injUnitEN();
            injState = true;
          }
          else{
            Serial.print(F("\n\nDESACTIVANDO UNIDAD DE INYECCIÓN...\n"));
            injUnitDIS();
            injState = false;
          }
          working = true;
        }
        break;
        
      case '2':
        if (checked != false)
        {
          Serial.print(F("\n\nPURGANDO BARRIL DE INYECCIÓN...\n"));
          working = true;
        }
        break;
        
      case '3':
        if (checked != false)
        {
          Serial.print(F("\n\nCOMENZANDO CICLO DE INYECCIÓN...\n"));
          working = true;
        }
        break;
        
      case 'a':
        Serial.print(F("\n\nABRIENDO EL MOLDE...\n"));
        working = false;
        break;
        
      case 'c':
        Serial.print(F("\n\nCERRANDO EL MOLDE...\n"));
        working = false;
        break;

      case 'm':
        menu();
        break;
        
      default:
        break;
    }
  }
}

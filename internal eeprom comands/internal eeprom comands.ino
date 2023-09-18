#include <EEPROM.h>

void setup()
{ Serial.begin( 9600 );
  for (int i = 0; i < 255; i++)//address, value
    EEPROM.write(i, i+i/10+3);
  for (int i = 0; i < 255; i++){
    Serial.print(i);
    Serial.print(" - ");
    Serial.println(EEPROM.read(i));
  }
// EEPROM.length()
// val = EEPROM[ 44 ];
 

}

void loop()
{
}
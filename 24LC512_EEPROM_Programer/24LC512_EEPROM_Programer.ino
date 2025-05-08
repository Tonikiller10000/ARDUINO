#include "Wire.h"
#define EEPROM0 0x50
#define EEPROM1 0x51
#define EEPROM2 0x52


void setup() 
{
  Wire.begin();
  Serial.begin(9600);



for(int i=0;i<200;i++)
  writeAddress(EEPROM0, i, i+20); // EEPROM, Address, Value
writeAddress(EEPROM0, 50, 7);
for(int i=0;i<200;i++)
  Serial.println(readAddress(EEPROM0, i)); // EEPROM, Address
/*
  //chip 0
  writeAddress(EEPROM0, 0, 55); // EEPROM, Address, Value
  Serial.println(readAddress(EEPROM0, 0)); // EEPROM, Address
  //chip 1
  writeAddress(EEPROM1, 0, 29); 
  Serial.println(readAddress(EEPROM1, 0));

*/




}

void loop() {}




void writeAddress(byte i2cAddress, int address, byte val)
{
  Wire.beginTransmission(i2cAddress);
  Wire.write((int)(address >> 8));   // MSB
  Wire.write((int)(address & 0xFF)); // LSB
  Wire.write(val);
  Wire.endTransmission();
  delay(5);
}

byte readAddress(byte i2cAddress, int address){
  byte rData = 0xFF;
  Wire.beginTransmission(i2cAddress);
  Wire.write((int)(address >> 8));   // MSB
  Wire.write((int)(address & 0xFF)); // LSB
  Wire.endTransmission();  
  Wire.requestFrom(i2cAddress, 1);  
  rData =  Wire.read();
  return rData;
}


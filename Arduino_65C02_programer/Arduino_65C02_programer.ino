int DATA_BITS=[6,7,8,9,10,11,12,13];
int code = [
0xA9, 0x42,       // lda #$42
0x8D, 0x00, 0x60  // sta $6000
];


void EEPROM_Write(int addr, int data){}
int EEPROM_Read(int addr){return DATA_BITS[2];}

void setup() {
    Serial.begin(9600);
    for(int i=0;i<=32768;i++)
      EEPROM_Write(i, 0xea);
    // EEPROM_Write(7ffc, 0x00);
    // EEPROM_Write(7ffd, 0x80);
    for(int i=0;i<code.len;i++)
      EEPROM_Write(i, code[i]);



}

void loop() {
  

}

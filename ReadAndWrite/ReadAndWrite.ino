/*         
 * SPI MOSI    MOSI         11 / ICSP-4  
 * SPI MISO    MISO         12 / ICSP-1   
 * SPI SCK     SCK          13 / ICSP-3   
 * More here: https://github.com/miguelbalboa/rfid#pin-layout */
 
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9          
#define SS_PIN  10         

MFRC522 mfrc522(SS_PIN, RST_PIN);  
MFRC522::MIFARE_Key key;

void setup() {
    Serial.begin(9600); while (!Serial); SPI.begin(); mfrc522.PCD_Init(); //INIT
    for (byte i = 0; i < 6; i++) {key.keyByte[i] = 0xFF;}// Prepare the default key FFFFFFFFFFFFh for A and B
    Serial.print(F("Using key (for A and B):")); dump_byte_array(key.keyByte, MFRC522::MF_KEY_SIZE); Serial.println();
}






void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) {return;}//reset loop if no new card detected
  if ( ! mfrc522.PICC_ReadCardSerial()) {return;}
  
    // Show details
    Serial.print(F("Card UID:"));
    dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
    Serial.println();
    Serial.print(F("PICC type: "));
    MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
    Serial.println(mfrc522.PICC_GetTypeName(piccType));

    byte sector = 1;
    byte blockAddr = 4, trailerBlock = 7;//from block 4 to 7
    byte dataBlock[] = { 0x01, 0x02, 0x03, 0x04,    0x05, 0x06, 0x07, 0x08,    0x09, 0x0a, 0xff, 0x0b,     0x0c, 0x0d, 0x0e, 0x0f };
    
    MFRC522::StatusCode status;
    byte buffer[18];
    byte size = sizeof(buffer);

    // Authenticate using key A
    Serial.println(F("Authenticating using key A..."));
    status = (MFRC522::StatusCode) mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("PCD_Authenticate() failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }

    // Show the whole sector as it currently is
    Serial.println(F("Current data in sector:"));
    mfrc522.PICC_DumpMifareClassicSectorToSerial(&(mfrc522.uid), &key, sector);
    Serial.println();

//READ
    status = (MFRC522::StatusCode) mfrc522.MIFARE_Read(blockAddr, buffer, &size);
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("MIFARE_Read() failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
    }

    // Authenticate using key B
    Serial.println(F("Authenticating again using key B..."));
    status = (MFRC522::StatusCode) mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_B, trailerBlock, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("PCD_Authenticate() failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }

    // Write data to the block
    Serial.print(F("Writing data into block ")); Serial.print(blockAddr);
    Serial.println(F(" ..."));
    dump_byte_array(dataBlock, 16); Serial.println();
    status = (MFRC522::StatusCode) mfrc522.MIFARE_Write(blockAddr, dataBlock, 16);
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("MIFARE_Write() failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
    }
    Serial.println();

    Serial.print(F("Data in block ")); Serial.print(blockAddr); Serial.println(F(":"));
    dump_byte_array(buffer, 16); Serial.println();
    
    byte count = 0;
    for (byte i = 0; i < 16; i++) {
        if (buffer[i] == dataBlock[i])
            count++;}
    Serial.print(F("Number of bytes that match = ")); Serial.println(count);

    //READ SECTOR
    mfrc522.PICC_DumpMifareClassicSectorToSerial(&(mfrc522.uid), &key, sector);
    Serial.println();

    mfrc522.PICC_HaltA();// Halt PICC
    mfrc522.PCD_StopCrypto1();// Stop encryption on PCD
}






void dump_byte_array(byte *buffer, byte bufferSize) {//reading 
    for (byte i = 0; i < bufferSize; i++) {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], HEX);}}

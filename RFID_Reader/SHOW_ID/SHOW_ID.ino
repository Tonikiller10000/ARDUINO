/*
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 *
 * More pin layouts for other boards can be found here: https://github.com/miguelbalboa/rfid#pin-layout
 */
#include "U8glib.h" 
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
 
 
char LOGS[10][10] ={
"53C221AA", "ADMIN1",
"533DCAA9", "ADMIN2",
"1F1C348D", "UNKNOWN",
"33C4841F", "USER1",
"638F821F", "USER2",};


int COUNTER=0;
char CT[5];
char ID[30] = "----";
char NAME[10]= "-";
U8GLIB_SH1106_128X64 u8g(6,5,4,3); // SCK, SDA, CS, DC(PWM) {RESET to ARDUINO RESET PIN}
void draw(void) { 
   
  u8g.setFont(u8g_font_unifont); 
  u8g.drawStr( 0, 12, "ID: "); 
  u8g.drawStr( 30, 12, ID);
  u8g.drawStr( 0, 26, "NAME: "); 
  u8g.drawStr( 40, 26, NAME ); 
  u8g.drawStr( 0, 40, "COUNTER: "); 
  itoa(COUNTER, CT, 10);
  u8g.drawStr( 65, 40, CT ); 
  u8g.drawStr( 0, 54, "OTHER: "); 



  } 

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key; 
byte nuidPICC[4];

void setup() { 
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 

  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) 
    u8g.setColorIndex(255);     // white 
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) 
    u8g.setColorIndex(3);         // max intensity 
  else if ( u8g.getMode() == U8G_MODE_BW ) 
    u8g.setColorIndex(1);         // pixel on 
     

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }}
 
void loop() {

  if ( ! rfid.PICC_IsNewCardPresent())  // Reset the loop if no new card present on the sensor
    return;
  COUNTER +=1;
  if ( ! rfid.PICC_ReadCardSerial())  // Verify if the NUID has been readed
    return;

  if (rfid.uid.uidByte[0] != nuidPICC[0] || 
    rfid.uid.uidByte[1] != nuidPICC[1] || 
    rfid.uid.uidByte[2] != nuidPICC[2] || 
    rfid.uid.uidByte[3] != nuidPICC[3] ) {
    Serial.println(F("A new card has been detected."));

    // Store NUID into nuidPICC array
    for (byte i = 0; i < 4; i++) {   
      nuidPICC[i] = rfid.uid.uidByte[i]; 
      int h1 = rfid.uid.uidByte[i]/16;
      int h2 = rfid.uid.uidByte[i]%16;
      if(h1<10)
        h1=h1+48;      
      else 
        h1=h1+55;  
      if(h2<10)
        h2=h2+48;      
      else 
        h2=h2+55;  
        ID[2*i]=h1;
        ID[2*i+1]=h2;
     
     
    }

   for(int i=0;i<5;i++){
     int v=0;

    for(int j=0;j<8;j++) 
      if(ID[j]!=LOGS[2*i][j])
        v=1;



    if(v==0) 
      for(int j=0;j<10;j++)    
        NAME[j]=LOGS[2*i+1][j];
    else
      v=0;


      
     
   } 



   
    Serial.println(F("The NUID tag is:"));
    Serial.print(F("In hex: "));
    printHex(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
    Serial.print(F("In dec: "));
    printDec(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
  }
  else Serial.println(F("Card read previously."));

    u8g.firstPage();   
    do { 
    
      draw(); 
  
    } while( u8g.nextPage()); 
    delay(50); 


  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }}

void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }}

/*
-------------HEATING PLATE--------------

LINKS
https://www.tme.eu/Document/f9d2f5e38227fc1c7d979e546ff51768/NTCM-100K-B3950.pdf
*/

#define TempRead_Pin A0
#define Fan_Pin 12
#define HeatingPlate_Pin 13
#define SW1_Pin 9
#define SW2_Pin 10
#define ENCODER_Pin1 10 // ok
#define ENCODER_Pin2 8  // not good
#define ENCODER_Pin3 6  // not good
#define Buzzer_Pin 2
#define Display_SCL 5  // not good
#define Display_SDA 4  // not good

// 9,10,12,13,14,15,2,4,5 + UART(2) + BOOT(1) + A0
// 9,10,14,15,4,5 

int SerialMonitor_Enable = 1;
float TempRead_Val = 0, temp;    
float R = 100000, R2, logR2;
//float TH_A = 0.00064437585, TH_B = 0.0002277425318, TH_C = 0.00000005744251435;
int ENC_Pos = 0, ENC_State, ENC_LastState; 
unsigned long Time, prev_time, elapsed_time, set_time = 120 * 1000; 
int heating = 0;

void BEEP(int time){
  digitalWrite(Buzzer_Pin, 1);
  delay(time);
  digitalWrite(Buzzer_Pin, 0);}
void ENCODER_UPDATE(){// NOT WORKING
  /*
  ENC_State = digitalRead(ENCODER_Pin1); 
  if (ENC_State != ENC_LastState) //pulse has occured   
  {
    if (digitalRead(ENCODER_Pin3) != ENC_State) //clockwise
    {
      ENC_Pos ++;
    }
    else 
    {
      ENC_Pos --;
    }  
  }
  ENC_LastState = ENC_State;
  */}
void TEMPERATURE_UPDATE() {// Check temperature update accuracy
  TempRead_Val = analogRead(TempRead_Pin);
  R2 = R * (1023.0 / (float)TempRead_Val - 1.0);
  logR2 = log(R2);
  temp = (1.0 / (TH_A + TH_B*logR2 + TH_C*logR2*logR2*logR2)) - 273.15;}
void Heat(float set_temp, float temp_tolerance){
  unsigned long currentMillis = millis();
  temp = TEMPERATURE_UPDATE();
  
  if(SerialMonitor_Enable){
    Serial.print(currentMillis);
    Serial.print(": Temp=");
    Serial.print(temp);
    Serial.print(" task:")
  }
  // if it is heating and it didn't reached the target temperature, keep heating
  if (heating == 1 && temp < set_temp + temp_tolerance)
  {
    heating = 1;
    digitalWrite(HeatingPlate_Pin, 1);
    analogWrite(Fan_Pin, 0);
  }
  // if it is heating and the temperature overshoot the tolerance, start cooling
  if (heating == 1 && temp > set_temp + temp_tolerance)
  {
    heating = -1;
    digitalWrite(HeatingPlate_Pin, 0);
    analogWrite(Fan_Pin, 255);
  }
  // if it is cooling and temperature is lower than upper tolerance, stop cooling
  if (heating == -1 && temp < set_temp + temp_tolerance)
  {
    heating = 0;
    digitalWrite(HeatingPlate_Pin, 0);
    analogWrite(Fan_Pin, 0);
    BEEP(500); 
  }
  // if the temperature falls under the lower tolerance, start heating
  if (heating == 0 && temp < set_temp - temp_tolerance)
    heating = 1;
  
  
  if(SerialMonitor_Enable)
  {
    if (heating == -1)
      Serial.println("Cooling...");
    else if (heating == 1)
      Serial.println("Heating...");
    else
      Serial.println("Wait...");
  }}


void setup() {
  pinMode(Fan_Pin, OUTPUT);
  pinMode(HeatingPlate_Pin, OUTPUT);
  pinMode(Buzzer_Pin, OUTPUT);
  //pinMode(TempRead_Pin, INPUT);
  pinMode(SW1_Pin, INPUT);
  pinMode(ENCODER_Pin1, INPUT);
  //pinMode(ENCODER_Pin2, OUTPUT);
  //digitalWrite(ENCODER_Pin2, 0);// GND
  //pinMode(ENCODER_Pin3, INPUT);
  //ENC_LastState = digitalRead(ENCODER_Pin1); 
  prev_time = millis();
  // ***Testing***:
  //digitalWrite(HeatingPlate_Pin, 1);
  //digitalWrite(Fan_Pin,1);
  Serial.begin(9600);
}

void loop() 
{

  Heat(30,2);
}





/*
Datasheet: https://components101.com/sites/default/files/2021-09/ESP12E-Datasheet.pdf

(PIN NR) | PIN ID | Alternate function | (observations)
(1)   HW_RESET 
(2)   ADC0
(3)   HW_EN              
(4)   GPIO 16/WAKE      
(5)   GPIO 14      
(6)   *GPIO 12      
(7)   *GPIO 13
(8)   VCC   
(9)   CS0 
(10)  MISO       
(11)  GPIO 9      
(12)  GPIO 10      
(13)  MOSI        
(14)  SCLK 
(15)  GND     
(16)  *GPIO 15 (Pulled Down)
(17)  GPIO 2/TXD1  (BuiltIn Led)    
(18)  GPIO 0/FLASH (BOOT)
(19)  GPIO 4       
(20)  GPIO 5       
(21)  GPIO 3/RXD0       
(22)  GPIO 1/TXD0   

*-PWM
*/







/*
#include <ESP32Time.h>

ESP32Time rtc(3600);  // offset in seconds GMT+2

void setup() {
  Serial.begin(115200);
  rtc.setTime(30, 24, 12, 1, 3, 2025);  // ss,mm,hh,dd,mm,yy => 1st Mar 2025 12:24:30
  rtc.offset = 7200; // change offset value


//  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
//  struct tm timeinfo;
//  if (getLocalTime(&timeinfo)){
//    rtc.setTimeStruct(timeinfo); 
//  }
}

void loop() {

//  Serial.println(rtc.getDateTime(True));      //  (String) Sun, Jan 17 2021 15:24:38
//  Serial.println(rtc.getMicros());        //  (long)    723546
//  Serial.println(rtc.getEpoch());         //  (long)    1609459200
//  Serial.println(rtc.getHour(true));      //  (int)     15    (0-23)
//  Serial.println(rtc.getDayofWeek());     //  (int)     0     (0-6)

  Serial.println(rtc.getTime("%A, %B %d %Y %H:%M:%S"));   // formating options at  http://www.cplusplus.com/reference/ctime/strftime/
  delay(1000);
}
*/

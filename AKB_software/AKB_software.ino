//AKB code
#define Led1_Pin 12 // NOT WORKING   go to GPIO 12 or 13
#define Led2_Pin 10  // NOT WORKING   go to GPIO 10
#define Spk_Pin 9
//#define Btn1_Pin 16 // good?
//#define Btn2_Pin 4


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);//GPIO 2
  pinMode(Led1_Pin, OUTPUT);
  pinMode(Led2_Pin, OUTPUT);
  pinMode(Spk_Pin, OUTPUT);
  //pinMode(Btn1_Pin, INPUT);
  //pinMode(Btn2_Pin, INPUT);
}

void loop() {
  //if(digitalRead(Btn2_Pin))
    //digitalWrite(Led1_Pin, 0);
  //else
    //digitalWrite(Led1_Pin, 1);

  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(Led2_Pin, LOW);
  digitalWrite(Spk_Pin, LOW);
  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(Led2_Pin, HIGH);
  digitalWrite(Spk_Pin, HIGH);
  delay(1000);
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




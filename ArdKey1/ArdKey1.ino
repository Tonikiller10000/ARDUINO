/*
#define KEY_LEFT_CTRL	0x01
#define KEY_LEFT_SHIFT	0x02
#define KEY_RIGHT_CTRL	0x10
#define KEY_RIGHT_SHIFT	0x20

uint8_t buf[8] = {  0 }; 	

#define PIN_COPY 5
#define PIN_CUT 6
#define PIN_PASTE 7

void setup() 
{
  Serial.begin(9600);

  pinMode(PIN_COPY, INPUT);
  pinMode(PIN_CUT, INPUT);
  pinMode(PIN_PASTE, INPUT);
 
  // Enable internal pull-ups
  //digitalWrite(PIN_COPY, 1); 
  //digitalWrite(PIN_CUT, 1);
  //digitalWrite(PIN_PASTE, 1); 

  delay(200);
}

void loop() 
{
  if (digitalRead(PIN_CUT) == HIGH) {
    buf[0] = KEY_LEFT_CTRL; 	// Ctrl
    buf[2] = 27;    // Letter X
    // buf[2] = 123;	  // Cut key: Less portable
    Serial.write(buf, 8);	// Ssend keypress
    releaseKey();
  } 

  if (digitalRead(PIN_COPY) == HIGH) {
    buf[0] = KEY_LEFT_CTRL; 	// Ctrl
    buf[2] = 6;    // Letter C
    // buf[2] = 124;	  // Copy key: Less portable
    Serial.write(buf, 8);	// Send keypress
    releaseKey();
  } 

  if (digitalRead(PIN_PASTE) == HIGH) {
    buf[0] = KEY_LEFT_CTRL; 	// Ctrl
    buf[2] = 25;    // Letter V
    // buf[2] = 125;	  // Paste key: Less portable
    Serial.write(buf, 8);	// Send keypress
    releaseKey();
  } 
}

void releaseKey() 
{
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8);	// Release key  
  delay(100);
}

*/









/*

if(digitalRead(Push0) && Push0_State == 0){
    Serial.println("apasat");
    Push0_State = 1;}
else if(digitalRead(Push0) && Push0_State == 1)
    Serial.println("tinut"); 
else if(!digitalRead(Push0) && Push0_State == 1){
    Serial.println("eliberat");
    Push0_State = 0;}


if(digitalRead(Push0) && Push0_State == 0){
    Serial.println("apasat");
    Push0_State = 1;
    t0=time;}
else if(digitalRead(Push0) && Push0_State == 1){
    Serial.println("tinut"); 
    if (t1 - t0 >= delay) {
        Serial.println("continuare");        
    }      
    }
else if(!digitalRead(Push0) && Push0_State == 1){
    Serial.println("eliberat");
    Push0_State = 0;}

*/


char message[] = "Your Message\n";


#define SHIFT 0x80
const uint8_t _asciimap[128] = 
{
  0x00,             // NUL
  0x00,             // SOH
  0x00,             // STX
  0x00,             // ETX
  0x00,             // EOT
  0x00,             // ENQ
  0x00,             // ACK  
  0x00,             // BEL
  0x2a,             // BS Backspace
  0x2b,             // TAB  Tab
  0x28,             // LF Enter
  0x00,             // VT 
  0x00,             // FF 
  0x00,             // CR 
  0x00,             // SO 
  0x00,             // SI 
  0x00,             // DEL
  0x00,             // DC1
  0x00,             // DC2
  0x00,             // DC3
  0x00,             // DC4
  0x00,             // NAK
  0x00,             // SYN
  0x00,             // ETB
  0x00,             // CAN
  0x00,             // EM 
  0x00,             // SUB
  0x00,             // ESC
  0x00,             // FS 
  0x00,             // GS 
  0x00,             // RS 
  0x00,             // US 
  0x2c,          //  ' '
  0x1e|SHIFT,    // !
  0x34|SHIFT,    // "
  0x20|SHIFT,    // #
  0x21|SHIFT,    // $
  0x22|SHIFT,    // %
  0x24|SHIFT,    // &
  0x34,          // '
  0x26|SHIFT,    // (
  0x27|SHIFT,    // )
  0x25|SHIFT,    // *
  0x2e|SHIFT,    // +
  0x36,          // ,
  0x2d,          // -
  0x37,          // .
  0x38,          // /
  0x27,          // 0
  0x1e,          // 1
  0x1f,          // 2
  0x20,          // 3
  0x21,          // 4
  0x22,          // 5
  0x23,          // 6
  0x24,          // 7
  0x25,          // 8
  0x26,          // 9
  0x33|SHIFT,      // :
  0x33,            // ;
  0x36|SHIFT,      // <
  0x2e,            // =
  0x37|SHIFT,      // >
  0x38|SHIFT,      // ?
  0x1f|SHIFT,      // @
  0x04|SHIFT,      // A
  0x05|SHIFT,      // B
  0x06|SHIFT,      // C
  0x07|SHIFT,      // D
  0x08|SHIFT,      // E
  0x09|SHIFT,      // F
  0x0a|SHIFT,      // G
  0x0b|SHIFT,      // H
  0x0c|SHIFT,      // I
  0x0d|SHIFT,      // J
  0x0e|SHIFT,      // K
  0x0f|SHIFT,      // L
  0x10|SHIFT,      // M
  0x11|SHIFT,      // N
  0x12|SHIFT,      // O
  0x13|SHIFT,      // P
  0x14|SHIFT,      // Q
  0x15|SHIFT,      // R
  0x16|SHIFT,      // S
  0x17|SHIFT,      // T
  0x18|SHIFT,      // U
  0x19|SHIFT,      // V
  0x1a|SHIFT,      // W
  0x1b|SHIFT,      // X
  0x1c|SHIFT,      // Y
  0x1d|SHIFT,      // Z
  0x2f,          // [
  0x31,          // bslash
  0x30,          // ]
  0x23|SHIFT,    // ^
  0x2d|SHIFT,    // _
  0x35,          // `
  0x04,          // a
  0x05,          // b
  0x06,          // c
  0x07,          // d
  0x08,          // e
  0x09,          // f
  0x0a,          // g
  0x0b,          // h
  0x0c,          // i
  0x0d,          // j
  0x0e,          // k
  0x0f,          // l
  0x10,          // m
  0x11,          // n
  0x12,          // o
  0x13,          // p
  0x14,          // q
  0x15,          // r
  0x16,          // s
  0x17,          // t
  0x18,          // u
  0x19,          // v
  0x1a,          // w
  0x1b,          // x
  0x1c,          // y
  0x1d,          // z
  0x2f|SHIFT,    // {
  0x31|SHIFT,    // |
  0x30|SHIFT,    // }
  0x35|SHIFT,    // ~
  0       // DEL
};

uint8_t buf[8] = {0,0,0,0,0,0,0,0}; 

void setup(){
  Serial.begin(9600);
} 

void loop(){
  delay(1000);
  buf[0] = 0;
  
  for (char i : message) {
    delay(5);
    if (_asciimap[i] & SHIFT) { 
      buf[0] = B10; // If so, make the first digit of buf a shift (2)
      buf[2] = _asciimap[i] & 0x7F; 
    }
    else 
    { 
      buf[0] = 0; 
      buf[2] = _asciimap[i]; 
    }
    Serial.write(buf, 8); 
    releaseKey(); 
  }
  
}

void releaseKey() 
{
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8);	// Release key  
  delay(100);
}


  // buf[2] = 26; W   
  // buf[2] = 4;  A 
  // buf[2] = 22; S
  // buf[2] = 7;  D

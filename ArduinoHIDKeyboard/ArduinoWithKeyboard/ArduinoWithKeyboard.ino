//https://www.pjrc.com/teensy/td_libs_PS2Keyboard.html
#include <PS2Keyboard.h>
#include <LiquidCrystal.h>

char text[]="Hello world!!";
int CursorState = 0, DisplayState = 1, ScrollState=0, CursorX=1, CursorY=1; // CursorX 0-40
const int rs = 12, en = 11, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int IRQpin =  2, DataPin = 3;
PS2Keyboard keyboard;

void ChangeCursor(){
if(CursorState==0){
  lcd.cursor();
  CursorState = 1;}
else if(CursorState==1) {
  lcd.blink();
  CursorState = 2;}
else if(CursorState==2) {
  lcd.noCursor();
  CursorState = 3;}
else {
  lcd.noBlink();
  CursorState = 0;}

}
void ChangeVision(){
if(DisplayState == 0){
  DisplayState = 1;
  lcd.display();}
else {
  DisplayState = 0;
  lcd.noDisplay();}
}
void ChangeScroll(){
if(ScrollState == 0){
  ScrollState = 1;
  lcd.autoscroll();}
else {
  ScrollState = 0;
  lcd.noAutoscroll();}
}
void Backspace(){
  lcd.setCursor(CursorX-1, CursorY);
  lcd.print(" ");
  lcd.setCursor(CursorX-1, CursorY);
  CursorX-=1;}

void ChangeRow(){
if (CursorY==1)
CursorY=0;
else
 CursorY=1;
lcd.setCursor(CursorX-1, CursorY);

}





void setup() {
  delay(1000);
  lcd.begin(16, 2);
  lcd.print(text);
  lcd.setCursor(CursorX, CursorY);
  keyboard.begin(DataPin, IRQpin);
  Serial.begin(9600);
  Serial.println("Keyboard Test:");
}

void loop() {
  if (keyboard.available()) {
     char c = keyboard.read();
     if (c == PS2_ENTER) ChangeRow();
     else if (c == PS2_TAB) ChangeCursor();
     else if (c == PS2_ESC) lcd.clear();
     else if (c == '~') ChangeVision();
     else if (c == '`') ChangeScroll();
     else if (c == PS2_LEFTARROW) {CursorX-=2; lcd.setCursor(CursorX, CursorY);}
     else if (c == PS2_RIGHTARROW) { lcd.setCursor(CursorX+1, CursorY);}
     else if (c == PS2_UPARROW) lcd.scrollDisplayLeft();
     else if (c == PS2_DOWNARROW) lcd.scrollDisplayRight();
     else if (c == PS2_BACKSPACE) Backspace(); 
     else if (c == PS2_DELETE) Backspace(); 
     else lcd.print(c);
     CursorX+=1;
  }
}











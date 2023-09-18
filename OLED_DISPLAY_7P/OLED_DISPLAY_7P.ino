#include "U8glib.h" 
char ID[30] = "11 22 33 44 55 66";
U8GLIB_SH1106_128X64 u8g(13, 11, 10, 9); // SCK, SDA, CS, DC(PWM) {RESET to ARDUINO RESET PIN}
void draw(void) { 
   
  u8g.setFont(u8g_font_unifont); 
  u8g.drawStr( 0, 12, "ID: "); 
  u8g.drawStr( 0, 30, ID);    
} 
void setup(void) { 
 // u8g.setRot180();// flip screen, if required 


  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) 
    u8g.setColorIndex(255);     // white 
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) 
    u8g.setColorIndex(3);         // max intensity 
  else if ( u8g.getMode() == U8G_MODE_BW ) 
    u8g.setColorIndex(1);         // pixel on 
     }

    
void loop(void) { 
  u8g.firstPage();   
  do { 
    
    draw(); 
  
  } while( u8g.nextPage()); 
  delay(50); 
}

 // display.fillScreen(BLUE);
 // display.drawRect(0,0,96,64,WHITE);
 // display.fillRect(10,40, 75, 20, RED);





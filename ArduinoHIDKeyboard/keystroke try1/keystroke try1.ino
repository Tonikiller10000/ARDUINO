#include <Keyboard.h> // The main library for sending keystrokes.

void setup() 
{
 Keyboard.begin();  // Initialise the library.
}

// Loop around waiting for a button press on pin 2.
// When the button is pressed, go to the function triggerAutomation.
void loop() 
{
  if(digitalRead(2) == HIGH)
  {
    triggerAutomation();    
  }
}

void triggerAutomation()
{
  Keyboard.press(KEY_LEFT_GUI);     // Press and hold the Windows key.
  Keyboard.press('r');              // Press and hold the 'r' key.
  delay(100);                       // Wait for the computer to register the press.
  Keyboard.releaseAll();            // Release both of the above keys.
  delay(1000);                      // Wait for the Windows Run Dialog to open.
  Keyboard.print("Notepad");        // Type "Notepad".
  Keyboard.press(KEY_RETURN);       // Press the Enter key.
  delay(100);                       // Wait for the computer to register the press.
  Keyboard.releaseAll();            // Release the Enter key.

}
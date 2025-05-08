#include <ESP8266WiFi.h>
#include <SPI.h>
#include <MFRC522.h>


constexpr uint8_t RST_PIN = 0;   
constexpr uint8_t SS_PIN = 2;  
MFRC522 rfid(SS_PIN, RST_PIN); 
MFRC522::MIFARE_Key key;
String tag;




const char* ssid     = "FA";
const char* password = "1234567890";

WiFiServer server(80);
String header;

String output5State = "off";
String output4State = "off";

const int output5 = 5, output4 = 4;


unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  
  SPI.begin(); 
  rfid.PCD_Init(); 
  
  pinMode(output5, OUTPUT);
  pinMode(output4, OUTPUT);
  digitalWrite(output5, LOW);
  digitalWrite(output4, LOW);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);Serial.print(".");}
  
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){




if (rfid.PICC_IsNewCardPresent())
  if (rfid.PICC_ReadCardSerial()) {
    for (byte i = 0; i < 4; i++)  tag += rfid.uid.uidByte[i];
    Serial.println("cod: ----------------------- ");
    Serial.println(tag);
    
    if(tag == "13132130169")
          Serial.println("id deteted");

    
    
    tag = "";
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }











//13132130169
//2431554633





  
  WiFiClient client = server.available();   

  if (client) {                             
    Serial.println("New Client.");          
    String currentLine = "";               
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { 
      currentTime = millis();         






      
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close\n");

            
            if (header.indexOf("GET /5/on") >= 0) {
              Serial.println("GPIO 5 on");
              output5State = "on";
              digitalWrite(output5, HIGH);
            } else if (header.indexOf("GET /5/off") >= 0) {
              Serial.println("GPIO 5 off");
              output5State = "off";
              digitalWrite(output5, LOW);
            } else if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("GPIO 4 on");
              output4State = "on";
              digitalWrite(output4, HIGH);
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("GPIO 4 off");
              output4State = "off";
              digitalWrite(output4, LOW);
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");
            
            
            client.println("<body><h1>ESP8266 Web Server</h1>"); 
            client.println("<p>GPIO 5 - State " + output5State + "</p>");      
            if (output5State=="off") { client.println("<p><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>");}
            else {client.println("<p><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>");} 
               
            client.println("<p>GPIO 4 - State " + output4State + "</p>");      
            if (output4State=="off") {client.println("<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>");}
            else {client.println("<p><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>");}
            client.println("</body></html>\n");

            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}

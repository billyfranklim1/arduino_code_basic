/* 
Node MCU -> RC552 wiring diagram
3V3 ->  3.3v
GND ->  GND
D7  ->  MOSI
D6  ->  MISO
D5  ->  SCK
D2  ->  SDA
D1  ->  RST
*/



#include <ESP8266WiFi.h>

#include "MFRC522.h"
#define RST_PIN  5 // RST-PIN for RC522 - RFID - SPI - Modul GPIO5 
#define SS_PIN  2 // SDA-PIN for RC522 - RFID - SPI - Modul GPIO4 
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance

//Debug (Comment what you don't need...)
#define serialDebug       //Activate to use any debug
#define wifiDebug
#define cardDebug
#define requestDebug
//#define rawResponseDebug  //Exclusive or
#define responseDebug     //Exclusive or
#define perfomanceDebug
#define authorizeDebug

#define relay 15          //Port to use relay module
#define delayAuthorized 3000
#define delayNAuthorized 1000


//Wifi + requisition parameters
const char* ssid     = "SKY_052031";
const char* password = "BOIZ4915";
const char* host = "192.168.100.4";
const char* page = "/php/add_acesso.php";
const String authorize = "Acesso autenticado";//String to authorize acess

//Data used on request
#define labId 3
#define lockId 117
String cardUID = "";
String POSTData = "";//Temp variable to POST data
String POSTResponse = "";//Temp variable to POST response



void setup() {
  #ifdef serialDebug
  Serial.begin(115200);
  #endif

  pinMode(relay, OUTPUT);

  //Initialize RFID module
  SPI.begin();           // Init SPI bus
  mfrc522.PCD_Init();    // Init MFRC522

  // We start by connecting to a WiFi network
  #ifdef wifiDebug
  Serial.print("\n\nConnecting to ");
  Serial.println(ssid);
  #endif
  
  WiFi.begin(ssid, password);
  
  #ifdef wifiDebug
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nWiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  #endif
}



void loop() {
  if(checkCard(mfrc522.uid.uidByte, mfrc522.uid.size, cardUID)){
    #ifdef cardDebug
    Serial.println("Card UID: " + cardUID);
    #endif

    #ifdef wifiDebug
    Serial.print("connecting to ");
    Serial.println(host);
    #endif
    
    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 8095;
    if (!client.connect(host, httpPort)) {
      #ifdef wifiDebug
      Serial.println("connection failed");
      #endif
      return;
    }
    
    //Request
    POSTData = "id_cartao=" + cardUID +"&id_lab=" + labId + "&id_porta=" + lockId;

    //Print request
    #ifdef requestDebug
    Serial.println("\n====  Request to server  ====");
    Serial.printf("Requesting URL: %s\n", page);
    Serial.println("POST data: " + POSTData);
    Serial.printf("POST data size: %d bytes\n", POSTData.length());
    #endif

    //Mesaure request + response time
    #ifdef perfomanceDebug
    unsigned long reqTime = millis();
    #endif
    
    //Send request to server
    client.println("POST " + String(page) + " HTTP/1.1");
    client.println("Host: "+ String(host));
    client.println("Cache-Control: no-cache");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.println(POSTData.length());
    client.println();
    client.println(POSTData);

    //Kill connection if take more than 5 secs to receive a response
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
        #ifdef wifiDebug
        Serial.println(">>> Client Timeout !");
        #endif
        client.stop();
        return;
      }
    }
    
    //Measure only response time
    #ifdef perfomanceDebug
    unsigned long resTime = millis();
    #endif

    #ifdef responseDebug
    Serial.println("\n====  Response from server  ====");
    #endif

    while(client.available()){
      //Read all the lines of the reply from server and print them to serial
      #ifdef rawResponseDebug
      String line = client.readStringUntil('\r');
      Serial.print(line);
      #endif

      //Read <data> and print them to serial
      #ifndef rawResponseDebug
      client.readStringUntil('<');
      POSTResponse = client.readStringUntil('>');
      client.readStringUntil('\r');
      #endif

      #ifdef responseDebug
      Serial.println(POSTResponse);
      #endif
    }

    #ifdef perfomanceDebug
    Serial.println("\n====  Performance measurement  ====");
    Serial.printf("Response received in %d ms\nTotal time is %d ms\n", (millis() - resTime), (millis() - reqTime));
    #endif

    #ifdef wifiDebug
    Serial.println("\nclosing connection");
    #endif

    //Check if authenticated
    if(POSTResponse.equals(authorize)){
      POSTResponse = "";
      #ifdef authorizeDebug
      Serial.println("Acess granted");
      #endif
      digitalWrite(relay, HIGH);
      delay(delayAuthorized);
      digitalWrite(relay, LOW);
    }
    else{
      #ifdef authorizeDebug
      Serial.println("Invalid credentials");
      #endif
      delay(delayNAuthorized);
    }
  }
}








//Auxiliary function to dump RFID card UID to a variable
void readTag(byte *buffer, byte bufferSize, String& cardUID) {
  cardUID = "";//Overwrite previous readed tag (if any)
  for (byte i = 0; i < bufferSize; i++) {
    cardUID.concat(String(buffer[i] < 0x10 ? "0" : ""));
    cardUID.concat(String(buffer[i], HEX));
  }
  cardUID.toUpperCase();
}

//Complete function to detect and read an RFID card UID
bool checkCard(byte *buffer, byte bufferSize, String& cardUID){
  if (mfrc522.PICC_IsNewCardPresent()){
    if (mfrc522.PICC_ReadCardSerial()){
      readTag(mfrc522.uid.uidByte, mfrc522.uid.size, cardUID);
      return true;
    }
  }
  return false;
}


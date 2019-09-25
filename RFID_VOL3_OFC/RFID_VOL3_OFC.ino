/*
   LIGAÇÃO RFID
    SDA - D4(2)
    SCK - D5(14)
    MOSI - D7(13)
    MISO - D6(12)
    RST - D3(0)

    LIGAÇÃO LCD
    SCL - D2
    SDA - D3

*/

#define SS_PIN 2  //D2
#define RST_PIN 0 //D1

#include <SPI.h>
#include <MFRC522.h>


// Set the LCD address to 0x27 for a 16 chars and 2 line display


MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int statuss = 0;
int out = 0;
void setup()
{

  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  mensageminicial();
}
void loop()
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  //Show UID on serial monitor
  Serial.println();
  Serial.print(" UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println();
  if (content.substring(1) == "82 30 53 73") //change UID of the card that you want to give access
  {
    Serial.println(" Access Granted ");
    Serial.println(" Welcome Mr.Circuit ");

    delay(1000);
    Serial.println(" Have FUN ");
    Serial.println();
    statuss = 1;
    mensageminicial();
  }

  else   {
    Serial.println(" Access Denied ");

    delay(3000);

  }
}

void mensageminicial()
{

}

#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 53
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.
int vezes =0 ;
 
char st[20];
 
void setup() 
{
  Serial.begin(9600); // Inicia a serial
  SPI.begin();    // Inicia  SPI bus
  mfrc522.PCD_Init(); // Inicia MFRC522
  Serial.println("Aproxime o seu cartao do leitor...");
  Serial.println();
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
  //Mostra UID na serial
  Serial.print("UID da tag :");
  String conteudo= "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Mensagem : ");
  conteudo.toUpperCase();
  //if ( vezes <= 1){
    if (conteudo.substring(1) == "7D 84 51 6F" or conteudo.substring(1) == "51 84 CE 94" or vezes <= 1) //UID 1 - Chaveiro
    {
      vezes ++ ;
      if (conteudo.substring(1) == "7D 84 51 6F")
      {
      Serial.println("Billyfranklim A. Pereira ");
      Serial.println();
      Serial.println("Presente no dia 07/09/2017");
      Serial.println();
      Serial.println(vezes);
      delay(3000);}
      
      if (conteudo.substring(1) == "51 84 CE 94" )
      {
       Serial.println("Giselly A. Pereira");
      Serial.println();
      Serial.println("Presente no dia 07/09/2017");
      Serial.println();
      Serial.println(vezes);
      delay(3000);}
   
      if (vezes == 3)
      {
      Serial.println("limite de presença exedido");
      //break
      }
     else if  (vezes == 3)
     {
      close;
      }
} 
} 


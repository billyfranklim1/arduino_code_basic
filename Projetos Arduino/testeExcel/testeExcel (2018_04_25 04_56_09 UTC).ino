#include <MFRC522.h>
#include <SPI.h>
#define SS_PIN 53
#define RST_PIN 51
MFRC522 mfrc522(SS_PIN, RST_PIN);
String nome = "Billyfranklim Avelino Pereira"; 
int linha = 0;
int pro = 0;
String prof = "Kenio";
String ru = "Billyfranklim Avelino Pereira";
String old =  "Fulano";
String neww = "Franklim Pereira";
String gi = "Giselly Avelino";
 
void setup() {

 Serial.begin(9600);
 SPI.begin();
 mfrc522.PCD_Init();
 Serial.println("CLEARDATA"); // Reset da comunicação serial
 Serial.println("LABEL,Entrada, Nome, Status"); // Nomeia ascolunas

 

}
void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  String conteudo = "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  conteudo.toUpperCase();
 if (conteudo.substring(1) == "70 B9 B8 46")
  { 
    Serial.print("DATA,TIME,"); //inicia a impressão de dados, sempre iniciando
    Serial.print(ru);
    Serial.print(",");
    Serial.println("Presente");
    
    delay(1500);
    
}

else if (conteudo.substring(1) == "7D 84 51 6F")
{
    Serial.print("DATA,TIME,"); //inicia a impressão de dados, sempre iniciando
    Serial.print(old);
    Serial.print(",");
    Serial.println("Presente");
    delay(1500);
  }

  
else if (conteudo.substring(1) == "82 30 53 73")
{
    Serial.print("DATA,TIME,"); //inicia a impressão de dados, sempre iniciando
    Serial.print(neww);
    Serial.print(",");
    Serial.println("Presente");
    delay(1500);
  }
  else if (conteudo.substring(1) == "51 84 CE 94")
{
    Serial.print("DATA,TIME,"); //inicia a impressão de dados, sempre iniciando
    Serial.print(gi);
    Serial.print(",");
    Serial.println("Presente");
    delay(1500);
  }
  else {
    Serial.println("desconhecido");
    }
}


#include <SPI.h>
#include <MFRC522.h>
#include <TimeLib.h>

#define SS_PIN 53
#define RST_PIN 5
MFRC522 mfrc522(SS_PIN, RST_PIN);

char st[20];
String nome = "Billyfranklim" ;
String giselly = "Giselly" ;
String ru = "CAU : Billyfranklim" ;
String billy = "Billy" ;

void setup()
{


  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Aproxime o seu cartao do leitor...");
  Serial.println();
}
void loop()
{
  // Aguarda a aproximacao do cartao
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Seleciona um dos cartoes
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  // Mostra UID na serial
  Serial.println();
  Serial.print("UID da tag :");
  String conteudo = "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX); //printa a udi da tag
    conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

    conteudo.toUpperCase();
  teste("82 30 53 73", "Nomeee");
}

void teste(char udi, String nome);
{
  if (conteudo.substring(1) == udi)
  {
    Serial.println();
    Serial.print("Seja Bem-Vindo ");
    Serial.println(nome);
    Serial.print("Entrada: ");
    delay(1500);
  }
}


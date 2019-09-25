#include <SPI.h>
#include <MFRC522.h>
#include <TimeLib.h>

#define SS_PIN 53
#define RST_PIN 5
// Definicoes pino modulo RC522
MFRC522 mfrc522(SS_PIN, RST_PIN);

char st[20];
String nome = "Billyfranklim" ;


void setup()
{


  Serial.begin(9600);
  // Inicia  SPI bus
  SPI.begin();
  // Inicia MFRC522
  mfrc522.PCD_Init();
  // Mensagens iniciais no serial monitor
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
  Serial.println();
  Serial.print("Mensagem : ");
  conteudo.toUpperCase();

  // Testa se o cartao1 foi lido
  if (conteudo.substring(1) == "82 30 53 73")
  {
    // Levanta a cancela e acende o led verde
    Serial.print("Seja Bem-Vindo ");
    Serial.println(nome);
    Serial.println();
    digitalClockDisplay();
    Serial.println();
    delay(3000);
  }

  // Testa se o cartao2 foi lido
  if (conteudo.substring(1) == "87 4B DC 8A")
  {
    Serial.println("Cartao2 - Acesso negado !!");
    Serial.println();
    // Pisca o led vermelho
    for (int i = 1; i < 5 ; i++)
    {
      delay(200);
    }
  }
  delay(1000);
}
void digitalClockDisplay(){
  // digital clock display of the time
  Serial.print(hour());
  Serial.println(" horas ");
  Serial.print(minute());
  Serial.println(" minutos ");
  Serial.print(second());
  Serial.println(" segundos ");
  Serial.print(day());
  Serial.println(" dia ");
  Serial.print(month());
  Serial.println(" Mês");
  Serial.print(year(47)); 
  Serial.println(" Ano"); 
//  Serial.print(time_t t = now ( )) ;
  //Serial.println("hora certa");
//  Serial.print(time);
}

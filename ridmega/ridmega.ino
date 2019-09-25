//Programa : RFID - Controle de Acesso leitor RFID
//Autor : FILIPEFLOP
 
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
 
#define SS_PIN 53
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.
 
LiquidCrystal lcd(6, 7, 5, 4, 3, 2); 
 
char st[20];
 
void setup() 
{
  Serial.begin(9600); // Inicia a serial
  SPI.begin();    // Inicia  SPI bus
  mfrc522.PCD_Init(); // Inicia MFRC522
  Serial.println("Aproxime o seu cartao do leitor...");
  Serial.println();
  //Define o número de colunas e linhas do LCD:  
  lcd.begin(16, 2);  
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
  if (conteudo.substring(1) == "7D 84 51 6F") //UID 1 - Chaveiro
  {
    Serial.println("Carteira antiga billy !,UID: 7D 84 51 6F ");
    Serial.println();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Ola FILIPEFLOP !");
    lcd.setCursor(0,1);
    lcd.print("Acesso liberado!");
    delay(3000);
    mensageminicial();
  }
 
  if (conteudo.substring(1) == "51 84 CE 94") //UID 2 - Cartao
  {
    Serial.println("carteira giselly ! UID: 51 84 CE 94");
    Serial.println();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Ola Cartao !");
    lcd.setCursor(0,1);
    lcd.print("Acesso Negado !");
    delay(3000);
    mensageminicial();
  }

    if (conteudo.substring(1) == "70 B9 B8 46") //UID 2 - Cartao
  {
    Serial.println("carteira RU ! UID: 70 B9 B8 46");
    Serial.println();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Ola Cartao !");
    lcd.setCursor(0,1);
    lcd.print("Acesso Negado !");
    delay(3000);
    mensageminicial();
  }

   if (conteudo.substring(1) == "82 30 53 73") //UID 2 - Cartao
  {
    Serial.println("carteira estudante atual ! UID: 82 30 53 73");
    Serial.println();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Ola Cartao !");
    lcd.setCursor(0,1);
    lcd.print("Acesso Negado !");
    delay(3000);
    mensageminicial();
  }
} 
 
void mensageminicial()
{
  lcd.clear();
  lcd.print(" Aproxime o seu");  
  lcd.setCursor(0,1);
  lcd.print("cartao do leitor");  
}

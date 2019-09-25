#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         5           // Configurable, see typical pin layout above
#define SS_PIN          53          // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
MFRC522::MIFARE_Key key;
const int ledVermelho = 46; //Pino que irá acender o led
const int ledVerde = 47; //Pino que irá acender o led

void setup() 
{
    Serial.begin(9600); // Inicializar a comunicação serial com o PC
    SPI.begin();        // Inicia o SPI bus
    mfrc522.PCD_Init(); // Inicia o MFRC522 card
    pinMode(ledVermelho,OUTPUT);
    pinMode(ledVerde,OUTPUT);
    mensageminicial();
}

void loop() 
{
    // Procure novos cartões
    if ( ! mfrc522.PICC_IsNewCardPresent())
        return;

    // Seleccionar um dos cartões
    if ( ! mfrc522.PICC_ReadCardSerial())
        return;

//Mostra UID na serial
    
    //Serial.print("UID da tag:"); mostra a UID da tag comentado abaixo
    String conteudo= "";
    byte letra;
    for (byte i = 0; i < mfrc522.uid.size; i++) 
    {
       Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
       //Serial.print(mfrc522.uid.uidByte[i], HEX); // pega a UID da tag exibir acima
       conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
       conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    Serial.println();
    //Serial.print("");
    conteudo.toUpperCase();
      
      
      //leitura das TAGS
      if (conteudo.substring(1) == "11 2E E5 2B" or conteudo.substring(1) == "11 2E E5 2B" ) //UID 1 - Chaveiro
      {
        digitalWrite(ledVerde,HIGH);
        Serial.println("Ola Klayton M C de Paiva");
        Serial.println("TORRE: 10, BL: 28, AP: 03");
        Serial.println("GARAGEM: 462");
        Serial.println("STATUS DA GARAGEM: VAGA");
        Serial.println();
        Serial.println("Acesso Liberado!");
        delay(3000);
        digitalWrite(ledVerde,LOW);
        Serial.println();
        Serial.println();
        delay(1000);
        mensageminicial();
      }
      else if (conteudo.substring(1) == "ED 78 03 CA") //UID 2 - Chaveiro
      {
        digitalWrite(ledVerde,HIGH);
        Serial.println("Ola USUARIO");
        Serial.println("TORRE: 10, BL: 28, AP: 03");
        Serial.println("GARAGEM: 462");
        Serial.println("STATUS DA GARAGEM: VAGA");
        Serial.println();
        Serial.println("Acesso Liberado!");
        delay(3000);
        digitalWrite(ledVerde,LOW);
        Serial.println();
        Serial.println();
        delay(1000);
        mensageminicial();
      }
      else if (conteudo.substring(1) == "FD 78 03 CA") //UID 3 - Chaveiro
      {
        digitalWrite(ledVerde,HIGH);        
        Serial.println("Ola USUARIO");
        Serial.println("TORRE: , BL: , AP: ");
        Serial.println("GARAGEM: ");
        Serial.println("STATUS DA GARAGEM: VAGA");
        Serial.println();
        Serial.println("Acesso Liberado!");
        delay(3000);
        digitalWrite(ledVerde,LOW);
        Serial.println();
        Serial.println();
        delay(1000);
        mensageminicial();
      }
      else 
      {
        digitalWrite(ledVermelho,HIGH);
        Serial.println("Ola usuario");
        Serial.println();
        Serial.println("ACESSO NAO PERMITIDO!");
        delay(3000);
        digitalWrite(ledVermelho,LOW);
        Serial.println();
        Serial.println();
        delay(1000);
        mensageminicial();
      }
} 
   // dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
     
     void mensageminicial()
     {
      Serial.print("APROXIME O SEU CARTAO DO LEITOR...");
      Serial.println();  
     }

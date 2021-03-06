int segundo, minuto, hora, dia, mes, ano;
unsigned long UtlTime;
#include <SPI.h>
#include <MFRC522.h>
#include <TimeLib.h>

#define SS_PIN 53
#define RST_PIN 5
// Definicoes pino modulo RC522
MFRC522 mfrc522(SS_PIN, RST_PIN);

char st[20];
String nome = "Billyfranklim" ;
String giselly = "Giselly" ;
String ru = "CAU : Billyfranklim" ;
String billy = "Billy" ;
int teste = 0;
String turno ;
String turma;
String M;
String T;
String N;

void setup()
{

Serial.begin(9600);
// Inicia  SPI bus
SPI.begin();
// Inicia MFRC522
mfrc522.PCD_Init();
// Mensagens iniciais no serial monitor
Serial.print("Aproxime o seu cartao do leitor...");
Serial.print();

UtlTime = 0;
minuto = 36;
hora = 20;
dia = 8;
mes = 9;
ano = 2017;
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
  //Serial.print("Cartão não cadastrado");
  //delay (2000);
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


  // Testa se o cartao1 foi lido

  if (conteudo.substring(1) == "82 30 53 73")
  {
    teste ++;
    Serial.println();
    Serial.print("Seja Bem-Vindo ");
    Serial.println(nome);
    Serial.print("Entrada: ");
    horacerta();
    delay(1500);
  }

  else if (conteudo.substring(1) == "7D 84 51 6F")
  {
    Serial.println();
    Serial.print("Seja Bem-Vindo ");
    Serial.println(billy);
    Serial.print("Entrada: ");
    horacerta();
    delay(1500);
  }


  else if (conteudo.substring(1) == "51 84 CE 94")
  {
    Serial.println();
    Serial.print("Seja Bem-Vindo ");
    Serial.println(giselly);
    Serial.print("Entrada: ");
    horacerta();
    delay(1500);
  }

  else
  {
    Serial.println();
    Serial.print("Cartão não cadastrado");
    Serial.println();
    delay(1500);
  }

}


void horacerta()
{
  if (millis() - UtlTime < 0)
  {
    UtlTime = millis();
  } else
  {
    segundo = int((millis() - UtlTime) / 1000);
  }
  if (segundo > 59)
  {
    segundo = 0;
    minuto++;

    UtlTime = millis();
    if (minuto > 59)
    {
      hora++;
      minuto = 0;
      if (hora > 23)
      {
        dia++;
        hora = 0;
        if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12)
        {
          if (dia > 31)
          {
            dia = 1;
            mes++;
            if (mes > 12)
            {
              ano++;
              mes = 1;
            }
          }
        }
        else if (mes == 2)
        {
          if (ano % 400 == 0)
          {
            if (dia > 29)
            {
              dia = 1;
              mes++;
            }
          }
          else if ((ano % 4 == 0) && (ano % 100 != 0))
          {
            if (dia > 29)
            {
              dia = 1;
              mes++;
            }
          }
          else
          {
            if (dia > 28)
            {
              dia = 1;
              mes++;
            }
          }
        }
        else
        {
          if (dia > 30)
          {
            dia = 1;
            mes++;
          }
        }
      }
    }
  }
  Serial.print(dia);
  Serial.print("/");
  Serial.print(mes);
  Serial.print("/");
  Serial.print(ano);
  Serial.print(" ");
  Serial.print(hora);
  Serial.print(":");
  Serial.print(minuto);
  Serial.print(":");
  Serial.print(segundo);
  Serial.print("\n");
  //delay(500);
}



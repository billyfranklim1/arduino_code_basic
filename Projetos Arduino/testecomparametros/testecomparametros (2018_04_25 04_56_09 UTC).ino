int segundo, minuto, hora, dia, mes, ano;
unsigned long UtlTime;
#include <SPI.h>
#include <MFRC522.h>
#include <TimeLib.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define red 18
#define gre 19
#define SS_PIN 53
#define RST_PIN 51
// Definicoes pino modulo RC522
MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
char st[20];
String nome = "Franklim Oliveira" ;
String giselly = "Giselly Avelino" ;
String ru = "Professor Fulano de Tal" ;
String billy = "Billyfranklim Pereira" ;
String prof = "Professor Fulano de Tal";
int teste = 0 ;
int teste1 = 0;
int teste2 = 0;
int pro = 0;
static nome="";

void setup()
{
  pinMode(red, OUTPUT);
  pinMode(gre, OUTPUT);
  Serial.begin(9600);
  // Inicia  SPI bus
  SPI.begin();
  // Inicia MFRC522
  mfrc522.PCD_Init();
  // Mensagens iniciais no serial monitor
  lcd.setBacklight(HIGH);
  lcd.setCursor(0, 0);
  lcd.print("Aproxime o seu ");
  lcd.setCursor(0, 1);
  lcd.print("cartao do leitor...");


  Serial.print("Aproxime o seu cartao do leitor...");
  Serial.println();
  lcd.begin (16, 2);

  UtlTime = 0;
  minuto = 06;
  hora = 21;
  dia = 21;
  mes = 9;
  ano = 2017;
}

void loop()
{
  lcd.setBacklight(HIGH);
  lcd.setCursor(0, 0);
  lcd.print("Aprox. o cartao ");
  horacertalcd();
  proo();

}

void horacertalcd()
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

  lcd.setBacklight(HIGH);
  lcd.setCursor(0, 1);
  lcd.print("    ");
  lcd.print(hora);
  lcd.print(":");
  lcd.print(minuto);
  lcd.print(":");
  lcd.print(segundo);
  lcd.print("    ");
  delay (1000);

  lcd.setBacklight(HIGH);
  lcd.setCursor(0, 1);
  lcd.print("    ");
  lcd.print(dia);
  lcd.print("/");
  lcd.print(mes);
  lcd.print("/");
  lcd.print(ano);
  lcd.print("    ");
  delay(1000);
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
  delay (1000);
}

void proo() {
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
  if (conteudo.substring(1) == "70 B9 B8 46")
  {
    if (pro == 0 ) {
      
  entrada('Teste');
  
    }

    pro ++;

      if (pro > 1) {
        saida();
    }
  }
  }
  else {
    Serial.println();
    Serial.print("Cartão não cadastrado");
    Serial.println();


    lcd.setBacklight(HIGH);
    lcd.setCursor(0, 0);
    lcd.print("  Cartao nao    ");
    lcd.setCursor(0, 1);
    lcd.print("    cadastrado    ");

    reed();
    // adicionar a função de não cadastrado
  }
}
void reed() {
  digitalWrite(red, HIGH);
  delay(250);
  digitalWrite(red, LOW);
  delay(250);
  digitalWrite(red, HIGH);
  delay(250);
  digitalWrite(red, LOW);

}

void gree() {
  digitalWrite(gre, HIGH);
  delay(250);
  digitalWrite(gre, LOW);
  delay(250);
  digitalWrite(gre, HIGH);
  delay(250);
  digitalWrite(gre, LOW);

}

char entrada(char[16] nome){
       lcd.setBacklight(HIGH);
      lcd.setCursor(0, 0);
      lcd.print("   Bem-Vindo   ");
      lcd.setCursor(0, 1);
      lcd.print(nome);

      gree();

      Serial.println();
      Serial.print("Seja Bem-Vindo Professor ");
      Serial.println(nome);
      Serial.print("Entrada: ");
      horacerta();
  }

  char saida (char[16] nome){
         lcd.setBacklight(HIGH);
      lcd.setCursor(0, 0);
      lcd.print("  Ate logo !!!!");
      lcd.setCursor(0, 1);
      lcd.print(prof);

      gree();


      Serial.println();
      Serial.print("Ate mais Professor !! ");
      Serial.println(prof);
      Serial.print("Saida: ");
      horacerta();
      pro = 0;
    }


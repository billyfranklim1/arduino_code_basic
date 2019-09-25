int segundo, minuto, hora, dia, mes, ano;
unsigned long UtlTime;
#include <Keypad.h>

#include <SPI.h>
#include <SD.h>
#include <MFRC522.h>
#include <TimeLib.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define red 48
#define gre 46
#define SS_PIN 53
#define RST_PIN 51


File myFile;


// Definicoes pino modulo RC522
MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
char st[20];
String nome = "Franklim Oliveira" ;
String giselly = "Giselly Avelino" ;
String ru = "Professor Fulano de Tal" ;
String billy = "Billyfranklim Pereira" ;
String prof = "MATEUS E DE +   ";
int teste = 0 ;
int teste1 = 0;
int teste2 = 0;
int pro = 0;

void setup()
{
  UtlTime = 0;
  minuto = 16;
  hora = 19;
  dia = 9;
  mes = 10;
  ano = 2017;


  byte pinosLinhas[]  = {10, 5, 6, 8};

  byte pinosColunas[] = {9, 11, 7};

  char teclas[4][3] = {{'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
  };

  Keypad teclado1 = Keypad( makeKeymap(teclas), pinosLinhas, pinosColunas, 4, 3);

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


  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");


  myFile = SD.open("chamada.csv", FILE_WRITE);

  // re-open the file for reading:
  // myFile = SD.open("pre.csv");



  myFile.println();
  myFile.print("Nome");
  myFile.print(";");
  myFile.print("Saida");
  myFile.print(";");
  myFile.print("Status");
  myFile.print(";");
  myFile.print("Data:");
  myFile.print(dia);
  myFile.print("/");
  myFile.print(mes);
  myFile.print("/");
  myFile.print(ano);
  myFile.print(";");
  myFile.print("Hora:");
  myFile.print(hora);
  myFile.print(":");
  myFile.print(minuto);
  myFile.print(":");
  myFile.println(segundo);


  ///digitalWrite(gre, LOW);
  //digitalWrite(red, LOW);


}

void loop()
{
  /*lcd.setBacklight(HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Aprox. o cartao ");*/
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
  lcd.setCursor(0, 0);
  lcd.print("     ");
  lcd.print(hora);
  lcd.print(":");
  lcd.print(minuto);
  lcd.print(":");
  lcd.print(segundo);
  lcd.print("    ");
  //delay (1000);

  lcd.setBacklight(HIGH);
  lcd.setCursor(0, 1);
  lcd.print("     ");
  lcd.print(dia);
  lcd.print("/");
  lcd.print(mes);
  lcd.print("/");
  lcd.print(ano);
  lcd.print("    ");
  //delay(1000);
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
  //Serial.print("CartÃ£o nÃ£o cadastrado");
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

      lcd.setBacklight(HIGH);
      lcd.setCursor(0, 0);
      lcd.print("   Bem-Vindo   ");
      lcd.setCursor(0, 1);
      lcd.print(prof);
      delay(3000);

      lcd.setBacklight(HIGH);
      lcd.setCursor(0, 0);
      lcd.println("Aguardando ");
      lcd.setCursor(0, 1);
      lcd.print("a ecolha da turma");
      
          if (tecla_pressionada)
      {
        lcd.setBacklight(HIGH);
        lcd.setCursor(0, 0);
        lcd.print("Turma selecionada : ");
        lcd.setCursor(0, 1);
        lcd.println(tecla_pressionada);

        if (tecla_pressionada == 1)
      {
           if (conteudo.substring(1) == "82 30 53 73" or conteudo.substring(1) == "51 84 CE 94" or conteudo.substring(1) == "7D 84 51 6F") {
      if (conteudo.substring(1) == "82 30 53 73")
      {
        if (teste < 1) {
          lcd.setBacklight(HIGH);
          lcd.setCursor(0, 0);
          lcd.print("  Bem-Vindo    ");
          lcd.setCursor(0, 1);
          lcd.print(nome);

          gree();


          teste ++;
          Serial.println(teste);
          Serial.println();
          Serial.print("Seja Bem-Vindo ");
          Serial.println(nome);
          Serial.print("Entrada: ");
          horacerta();
        }

        else {
          if (myFile) {
            myFile.print(nome);
            myFile.print(";");
            myFile.print(hora);
            myFile.print(":");
            myFile.print(minuto);
            myFile.print(":");
            myFile.print(segundo);
            myFile.print(";");
            myFile.println("Presente");
          }
          lcd.setBacklight(HIGH);
          lcd.setCursor(0, 0);
          lcd.print("  Ate logo !!!!");
          lcd.setCursor(0, 1);
          lcd.print(nome);

          Serial.println();
          Serial.print("AtÃ© mais!! ");
          Serial.println(nome);
          Serial.print("Saida: ");
          horacerta();
          teste = 0;
        }
      }

      else if (conteudo.substring(1) == "51 84 CE 94") {
        if (teste1 < 1) {

          lcd.setBacklight(HIGH);
          lcd.setCursor(0, 0);
          lcd.print("  Bem-Vindo    ");
          lcd.setCursor(0, 1);
          lcd.print(giselly);


          gree();
          teste1 ++;
          Serial.println(giselly);
          Serial.println();
          Serial.print("Seja Bem-Vindo ");
          Serial.println(giselly);
          Serial.print("Entrada: ");
          horacerta();
        }

        else {

          lcd.setBacklight(HIGH);
          lcd.setCursor(0, 0);
          lcd.print("  Ate logo !!!!");
          lcd.setCursor(0, 1);
          lcd.print(giselly);

          if (myFile) {
            myFile.print(giselly);
            myFile.print(";");
            myFile.print(hora);
            myFile.print(":");
            myFile.print(minuto);
            myFile.print(":");
            myFile.print(segundo);
            myFile.print(";");
            myFile.println("Presente");
          }
          gree();
          Serial.println();
          Serial.print("AtÃ© mais!! ");
          Serial.println(giselly);
          Serial.print("Saida: ");
          horacerta();
          teste1 = 0;
        }
      }
      else if (conteudo.substring(1) == "7D 84 51 6F") {
        if (teste2 < 1) {

          lcd.setBacklight(HIGH);
          lcd.setCursor(0, 0);
          lcd.print("    Bem-Vindo  ");
          lcd.setCursor(0, 1);
          lcd.print(billy);


          gree();


          teste2 ++;
          Serial.println(billy);
          Serial.println();
          Serial.print("Seja Bem-Vindo ");
          Serial.println(billy);
          Serial.print("Entrada: ");
          horacerta();
        }

        else {

          if (myFile) {
            myFile.print(billy);
            myFile.print(";");
            myFile.print(hora);
            myFile.print(":");
            myFile.print(minuto);
            myFile.print(":");
            myFile.print(segundo);
            myFile.print(";");
            myFile.println("Presente");
          }
          lcd.setBacklight(HIGH);
          lcd.setCursor(0, 0);
          lcd.print("  Ate logo !!!!");
          lcd.setCursor(0, 1);
          lcd.print(billy);

          Serial.println();
          Serial.print("AtÃ© mais!! ");
          Serial.println(billy);
          Serial.print("Saida: ");
          horacerta();
          teste2 = 0;
        }
      }

    }
    else {
      neg();
    }
  }
      }
        
     
      }


      gree();

      Serial.println();
      Serial.print("Seja Bem-Vindo Professor ");
      Serial.println(prof);
      Serial.print("Entrada: ");
      horacerta();
    }

    pro ++;

    if (pro > 1) {
      lcd.setBacklight(HIGH);
      lcd.setCursor(0, 0);
      lcd.print("  Ate logo !!!!");
      lcd.setCursor(0, 1);
      lcd.print(prof);

      if (myFile) {

        myFile.print(prof);
        myFile.print(";");
        myFile.print(hora);
        myFile.print(":");
        myFile.print(minuto);
        myFile.print(":");
        myFile.print(segundo);
        myFile.print(";");
        myFile.println("Presente");
        myFile.close();

      }

      // close the file:

      gree();


      Serial.println();
      Serial.print("Ate mais Professor !! ");
      Serial.println(prof);
      Serial.print("Saida: ");
      horacerta();
      pro = 0;
    }
  }
 /* else if (pro == 1) {
    if (conteudo.substring(1) == "82 30 53 73" or conteudo.substring(1) == "51 84 CE 94" or conteudo.substring(1) == "7D 84 51 6F") {
      if (conteudo.substring(1) == "82 30 53 73")
      {
        if (teste < 1) {
          lcd.setBacklight(HIGH);
          lcd.setCursor(0, 0);
          lcd.print("  Bem-Vindo    ");
          lcd.setCursor(0, 1);
          lcd.print(nome);

          gree();


          teste ++;
          Serial.println(teste);
          Serial.println();
          Serial.print("Seja Bem-Vindo ");
          Serial.println(nome);
          Serial.print("Entrada: ");
          horacerta();
        }

        else {
          if (myFile) {
            myFile.print(nome);
            myFile.print(";");
            myFile.print(hora);
            myFile.print(":");
            myFile.print(minuto);
            myFile.print(":");
            myFile.print(segundo);
            myFile.print(";");
            myFile.println("Presente");
          }
          lcd.setBacklight(HIGH);
          lcd.setCursor(0, 0);
          lcd.print("  Ate logo !!!!");
          lcd.setCursor(0, 1);
          lcd.print(nome);

          Serial.println();
          Serial.print("AtÃ© mais!! ");
          Serial.println(nome);
          Serial.print("Saida: ");
          horacerta();
          teste = 0;
        }
      }

      else if (conteudo.substring(1) == "51 84 CE 94") {
        if (teste1 < 1) {

          lcd.setBacklight(HIGH);
          lcd.setCursor(0, 0);
          lcd.print("  Bem-Vindo    ");
          lcd.setCursor(0, 1);
          lcd.print(giselly);


          gree();
          teste1 ++;
          Serial.println(giselly);
          Serial.println();
          Serial.print("Seja Bem-Vindo ");
          Serial.println(giselly);
          Serial.print("Entrada: ");
          horacerta();
        }

        else {

          lcd.setBacklight(HIGH);
          lcd.setCursor(0, 0);
          lcd.print("  Ate logo !!!!");
          lcd.setCursor(0, 1);
          lcd.print(giselly);

          if (myFile) {
            myFile.print(giselly);
            myFile.print(";");
            myFile.print(hora);
            myFile.print(":");
            myFile.print(minuto);
            myFile.print(":");
            myFile.print(segundo);
            myFile.print(";");
            myFile.println("Presente");
          }
          gree();
          Serial.println();
          Serial.print("AtÃ© mais!! ");
          Serial.println(giselly);
          Serial.print("Saida: ");
          horacerta();
          teste1 = 0;
        }
      }
      else if (conteudo.substring(1) == "7D 84 51 6F") {
        if (teste2 < 1) {

          lcd.setBacklight(HIGH);
          lcd.setCursor(0, 0);
          lcd.print("    Bem-Vindo  ");
          lcd.setCursor(0, 1);
          lcd.print(billy);


          gree();


          teste2 ++;
          Serial.println(billy);
          Serial.println();
          Serial.print("Seja Bem-Vindo ");
          Serial.println(billy);
          Serial.print("Entrada: ");
          horacerta();
        }

        else {

          if (myFile) {
            myFile.print(billy);
            myFile.print(";");
            myFile.print(hora);
            myFile.print(":");
            myFile.print(minuto);
            myFile.print(":");
            myFile.print(segundo);
            myFile.print(";");
            myFile.println("Presente");
          }
          lcd.setBacklight(HIGH);
          lcd.setCursor(0, 0);
          lcd.print("  Ate logo !!!!");
          lcd.setCursor(0, 1);
          lcd.print(billy);

          Serial.println();
          Serial.print("AtÃ© mais!! ");
          Serial.println(billy);
          Serial.print("Saida: ");
          horacerta();
          teste2 = 0;
        }
      }

    }
    else {
      neg();
    }
  }*/
  else {
    neg();
    // adicionar a funÃ§Ã£o de nÃ£o cadastrado
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
  delay(250);
  digitalWrite(red, HIGH);

}

void gree() {
  digitalWrite(gre, HIGH);
  delay(250);
  digitalWrite(gre, LOW);
  delay(250);
  digitalWrite(gre, HIGH);
  delay(250);
  digitalWrite(gre, LOW);
  delay(250);
  digitalWrite(gre, HIGH);

}
void neg() {
  Serial.println();
  Serial.print("CartÃ£o nÃ£o cadastrado");
  Serial.println();
  lcd.setBacklight(HIGH);
  lcd.setCursor(0, 0);
  lcd.print("  Cartao nao    ");
  lcd.setCursor(0, 1);
  lcd.print("    cadastrado    ");

  reed();
}


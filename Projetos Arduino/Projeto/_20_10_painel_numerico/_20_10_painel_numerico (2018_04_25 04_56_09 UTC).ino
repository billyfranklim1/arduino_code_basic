#include <Keypad.h>
#include <SPI.h>
#include <SD.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include <DS1307.h>

#define red 48
#define gre 46
#define SS_PIN 53
#define RST_PIN 51

DS1307 rtc(A4, A5);
File myFile;


// Definicoes pino modulo RC522
MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
char st[20];
String nome = "Franklim Oliveira" ;
String giselly = "Giselly Avelino" ;
String ru = "Professor Fulano de Tal" ;
String billy = "Billyfranklim Pereira" ;
String prof = "Professor Fulano";
int teste = 0 ;
int teste1 = 0;
int teste2 = 0;
int pro = 0;
int cont = 0;
byte pinosLinhas[]  = {10,5,6,8};

byte pinosColunas[] = {9,11,7};

char teclas[4][3] = {{'1','2','3'},
                     {'4','5','6'},
                     {'7','8','9'},
                     {'*','0','#'}};

Keypad teclado1 = Keypad( makeKeymap(teclas), pinosLinhas, pinosColunas, 4, 3);  

void setup()
{
  pinMode(red, OUTPUT);
  pinMode(gre, OUTPUT);
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.begin (16, 2);


  rtc.halt(false);
  rtc.setDOW(THURSDAY);      //Define o dia da semana Thursday

  rtc.setTime(13, 41, 0);     //Define o horario
  rtc.setDate(20, 10, 2017);   //Define o dia, mes e ano
  rtc.setSQWRate(SQW_RATE_1);
  rtc.enableSQW(true);

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
  myFile.print(rtc.getDateStr(FORMAT_SHORT));
  myFile.print(";");
  myFile.print("Hora:");
  myFile.println(rtc.getTimeStr());


  ///digitalWrite(gre, LOW);
  //digitalWrite(red, LOW);


}

void loop()
{
  horacertalcd();
  proo();

}

void horacertalcd()
{



  lcd.setCursor(0, 0);
  lcd.print("Hora: ");

  lcd.print(rtc.getTimeStr());

  lcd.setCursor(0, 1);
  lcd.print("Data: ");

  lcd.setCursor(6, 1);
  lcd.print(rtc.getDateStr());

  delay (1000);
}

void horacerta()
{
  Serial.print("Hora : ");
  Serial.print(rtc.getTimeStr());
  Serial.print(" ");
  Serial.print("Data : ");
  Serial.print(rtc.getDateStr(FORMAT_SHORT));
  Serial.print(" ");
  Serial.println(rtc.getDOWStr(FORMAT_SHORT));
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
      lcd.print(prof);[

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
        myFile.print(rtc.getTimeStr());
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
  else if (pro == 1) {
    if (conteudo.substring(1) == "82 30 53 73" or conteudo.substring(1) == "51 84 CE 94" or conteudo.substring(1) == "7D 84 51 6F") {
      if (conteudo.substring(1) == "82 30 53 73") {

        cadastro("Billyfranklim Avelino Pereira");

      }


      else if (conteudo.substring(1) == "51 84 CE 94") {
        cadastro("Giselly Pereira Oliveira");
      }


      else if (conteudo.substring(1) == "7D 84 51 6F") {
        cadastro("Franklim Oliverira Silva");
      }
      }
      
    else {
      neg();
    }
  }
  else {
    neg();
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

void matricula (String nome) {

  lcd.setBacklight(HIGH);
  lcd.setCursor(0, 0);
  lcd.print("  Bem-Vindo    ");
  lcd.setCursor(0, 1);
  lcd.print(nome);

  gree();

  Serial.println(teste);
  Serial.println();
  Serial.print("Seja Bem-Vindo ");
  Serial.println(nome);
  Serial.print("Entrada: ");
  horacerta();
}
void saida (String nome) {

  lcd.setBacklight(HIGH);
  lcd.setCursor(0, 0);
  lcd.print("  Ate logo !!!!");
  lcd.setCursor(0, 1);
  lcd.print(nome);

  if (myFile) {

    myFile.print(nome);
    myFile.print(";");
    myFile.print(rtc.getTimeStr());
    myFile.print(";");
    myFile.println("Presente");

  }
  gree();
  Serial.println();
  Serial.print("AtÃ© mais!! ");
  Serial.println(nome);
  Serial.print("Saida: ");
  horacerta();
}

void cadastro (String nomee) {
  if (cont == 0) {

    matricula(nomee);
    cont++;
  }
  else {
    saida(nomee);
    cont = 0;

  }
}


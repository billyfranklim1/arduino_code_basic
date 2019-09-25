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
char turma = 0;
int t ;
String prof = "Professor Fulano";
int pro = 0;
int cont = 0;
int contador = 0;
int com = 0;
byte pinosLinhas[]  = {10, 5, 6, 8};
byte pinosColunas[] = {9, 11, 7};
char teclas[4][3] = {{'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

Keypad teclado1 = Keypad( makeKeymap(teclas), pinosLinhas, pinosColunas, 4, 3);


void setup()
{
  pinMode(red, OUTPUT);
  pinMode(gre, OUTPUT);
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.begin (16, 2);

  //--------------------------------------------------------------------
  rtc.halt(false);
  rtc.setDOW(THURSDAY);      //Define o dia da semana Thursday

  rtc.setTime(15, 53, 0);     //Define o horario
  rtc.setDate(23, 10, 2017);   //Define o dia, mes e ano
  rtc.setSQWRate(SQW_RATE_1);
  rtc.enableSQW(true);
  //-------------------------------------------------------------------
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("inicializando o cartão SD...");

  if (!SD.begin(4)) {
    Serial.println("inicialização mal sucedida");
    return;
  }
  Serial.println("inicialização feita.");


  myFile = SD.open("chamada.csv", FILE_WRITE);

  // re-open the file for reading:
  // myFile = SD.open("pre.csv");
  //--------------------------------------------


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

  //------------------------------------------------------
  ///digitalWrite(gre, LOW);
  //digitalWrite(red, LOW);
  char tecla_pressionada = teclado1.getKey();

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

void proo()
{
  char tecla_pressionada = teclado1.getKey();
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
  teste("conteudo.substring(1)", "70 B9 B8 46", "Professor fulano ");


}

void teste (String info, char udi, String nome)
{
  if (info == udi)
  { 
    Serial.println();
    Serial.print("   Bem-Vindo   ");
    Serial.print(nome);
    delay(1500);
  }
}






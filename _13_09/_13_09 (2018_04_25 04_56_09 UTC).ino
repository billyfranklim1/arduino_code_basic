#include <Keypad.h>
#include <SPI.h>
#include <SD.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include <DS1307.h>

#define red 47
#define gre 48
#define SS_PIN 53
#define RST_PIN 51

DS1307 rtc(A4, A5);
File myFile;


// Definicoes pino modulo RC522
MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
char st[20];
char turma ;

String stts[2] = {"PRESENTE", "AUSENTE"};
String situacao;
String nomeDiciplina[3] = {"Fundamentos da Computacao", "Laboratorio de Programacao", "Banco de Dados"};
String professores[3] = {"Prof.Dr.Paulo Rogerio", "Prof.Dr.Janieyde", "Prof.Dr.Jose Renato"};
//↑↓
int passou[60] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int passouP[3] = {0, 0, 0}; //, 0, 0, 0, 0, 0, 0, 0, 0, 0};//, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};



int contador = 0;


byte pinosLinhas[]  = {10, 5, 6, 8};
byte pinosColunas[] = {9, 11, 7};
char teclas[4][3] =
{ {'1', '2', '3'},
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


  rtc.halt(false);
  rtc.setDOW(THURSDAY);      //Define o dia da semana Thursday

  rtc.setTime(15, 53, 0);     //Define o horario
  rtc.setDate(23, 10, 2017);   //Define o dia, mes e ano
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


  //  myFile = SD.open("chamada.csv", FILE_WRITE);

  // re-open the file for reading:
  // myFile = SD.open("pre.csv");



  myFile.println();
  myFile.print("Nome");
  myFile.print(";");
  myFile.print("Saida");
  myFile.print(";");
  myFile.print("Status");
  myFile.print(";");
  myFile.print("Turma");
  myFile.print(";");
  myFile.print("Data:");
  myFile.print(rtc.getDateStr(FORMAT_SHORT));
  myFile.print(";");
  myFile.print("Hora:");
  myFile.println(rtc.getTimeStr());





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

  //void cadPro (String infoP, String udiP, String nomeP, int pp(contadora do professor))

  //  cadPro (conteudo.substring(1), "70 B9 B8 46", "Professor Fulano de Tal", 0);

  // info = , udi=, t=nº da turma do aluno, pp = nº do Professor, aa = n do aluno
  //  void cadAl (String info, String udi, String nome, char t, int pp, int aa)

  //void CadTurma (String infoP, String udiP, String nomeP, int posiP,char sala, String diciplina)

  CadTurma (conteudo.substring(1), "70 B9 B8 46", professores[0], 0, '1', nomeDiciplina[0]);
  cadAl (conteudo.substring(1), "82 30 53 73", "Franklim Pereira", '1', 0, 0, nomeDiciplina[0]);
  cadAl (conteudo.substring(1), "7D 84 51 6F", "Billyfrankm Avelino", '1',0, 1, nomeDiciplina[0]);
  cadAl (conteudo.substring(1), "51 84 CE 94", "Giselly Pereira", '1', 0 ,2, nomeDiciplina[0]);

  /*
    cadAl (conteudo.substring(1), "82 30 53 73", "Billy Turma 2", '2',0,0);
    cadAl (conteudo.substring(1), "7D 84 51 6F", "Franklim Turma 2", '2',0,1);
    cadAl (conteudo.substring(1), "51 84 CE 94", "Giselly Turma 2", '2',0,2);
  */
  
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

  //  printLcd("  Cartao nao    ", "    cadastrado    ", 3000);

  lcd.setBacklight(HIGH);
  lcd.setCursor(0, 0);
  lcd.print("  Cartao nao    ");
  lcd.setCursor(0, 1);
  lcd.print("    cadastrado    ");
  //  delay(200)
  reed();
}


void teclado() {

  //  printLcd("Digite a Turma", "Aguarde 3 segundos", 3000);
  lcd.setBacklight(HIGH);
  lcd.setCursor(0, 0);
  lcd.print("Digite o numero");
  lcd.setCursor(0, 1);
  lcd.print("   da  Turma  ");
  delay(2000);

  lcd.setCursor(0, 0);
  lcd.print(" Aguarde 3 seg   ");
  lcd.setCursor(0, 1);
  lcd.print(" Aguarde 3 seg   ");
  delay(1000);

  lcd.setCursor(0, 0);
  lcd.print(" Aguarde 2 seg   ");
  lcd.setCursor(0, 1);
  lcd.print(" Aguarde 2 seg   ");
  delay(1000);

  lcd.setCursor(0, 0);
  lcd.print(" Aguarde 1 seg   ");
  lcd.setCursor(0, 1);
  lcd.print(" Aguarde 1 seg   ");
  delay(1000);
  lcd.clear();

  char tecla_pressionada = teclado1.getKey();

  while (contador == NO_KEY)
  {
    char tecla_pressionada = teclado1.getKey();
    if (tecla_pressionada )
    {
      lcd.setBacklight(HIGH);
      lcd.setCursor(0, 0);
      lcd.print("      TURMA       ");
      lcd.setCursor(0, 1);
      lcd.print(tecla_pressionada);
      delay(1000);


      Serial.println(tecla_pressionada);
      contador ++;
      turma = 0 + tecla_pressionada;
      Serial.print(turma);
      lcd.clear();

    }
  }
}

void printLcd (String msg1, String msg2, int tempo)
{
  lcd.setBacklight(HIGH);
  lcd.setCursor(0, 0);
  lcd.print(msg1);
  lcd.setCursor(0, 1);
  lcd.print(msg2);
  delay(tempo);
  lcd.clear();

}

void cadPro (String infoP, String udiP, String nomeP, int posiP)
{

  if (infoP == udiP)
  {

    if (passouP[posiP] == 0)
    {
      myFile = SD.open("chamada.csv", FILE_WRITE);
      myFile.println();
      myFile.print("Nome");
      myFile.print(";");
      myFile.print("Saida");
      myFile.print(";");
      myFile.print("Status");
      myFile.print(";");
      myFile.print("Turma:");
      //      myFile.print(t[0]);
      myFile.print(";");
      myFile.print("Data:");
      myFile.print(rtc.getDateStr(FORMAT_SHORT));
      myFile.print(";");
      myFile.print("Hora:");
      myFile.println(rtc.getTimeStr());
      myFile.print(";");


      lcd.setBacklight(HIGH);
      lcd.setCursor(0, 0);
      lcd.print("  Bem-Vindo    ");
      lcd.setCursor(0, 1);
      lcd.print(nomeP);
      delay(1500);

      gree();
      teclado();


      passouP[posiP] = 1;
    }
    else if (passouP[0] == 1)
    {

      lcd.setBacklight(HIGH);
      lcd.setCursor(0, 0);
      lcd.print("  Ate logo !!!!");
      lcd.setCursor(0, 1);
      lcd.print(nomeP);
      delay(2000);


      if (myFile)
      {

        myFile.print(nomeP);
        myFile.print(";");
        myFile.print(rtc.getTimeStr());
        myFile.println();
        myFile.close();
      }
      gree();
      contador = 0;
      passouP[posiP] = 0;


    }
  }
}
void cadAl (String info, String udi, String nome, char sala, int posiP, int posiA,String diciplina)
// info = , udi=, t=nº da turma do aluno, pp = nº do Professor, aa = n do aluno
{
  if (info == udi)
  {
    if (passouP[posiP] == 0)
    {
      neg(); // aluno sem permisao do professor
    }
    else if (passouP[posiP] == 1)
    {
      /*------------------------------------------*/
      if (turma = sala)
      {
        if (passou[posiA] == 0)
        {
          lcd.setBacklight(HIGH);
          lcd.setCursor(0, 0);
          lcd.print("  Bem-Vindo    ");
          lcd.setCursor(0, 1);
          lcd.print(nome);
          passou[posiA] = 1;
          delay(2000);
        }
        else if (passou[posiA] == 1)
        {
          lcd.setBacklight(HIGH);
          lcd.setCursor(0, 0);
          lcd.print("  Ate logo !!!!");
          lcd.setCursor(0, 1);
          lcd.print(nome);
          passou[posiA] = 2;

          if (passou[posiA] == 2)
          {
            situacao = stts[0];
            //            String stts[2] = {"PRESENTE", "AUSENTE"};
          }


          if (myFile)
          {
            myFile.print(nome);
            myFile.print(";");
            myFile.print(rtc.getTimeStr());
            myFile.print(";");
            myFile.print(situacao);
            myFile.print(";");
            myFile.println(diciplina);
          }
          passou[posiA] = 0;
          delay(2000);
        }
      }
      /*--------------------------------------------------*/
    }
  }
}

void verifP ()
{

}


void CadTurma (String infoP, String udiP, String nomeP, int posiP, char sala, String diciplina)
{
  //  void cadAl (String info, String udi, String nome, char sala, int posiP, int posiA)


  if (infoP == udiP)
  {

    if (passouP[posiP] == 0)
    {
      myFile = SD.open("chamada.csv", FILE_WRITE);
      myFile.println();
      myFile.print("Nome");
      myFile.print(";");
      myFile.print("Saida");
      myFile.print(";");
      myFile.print("Status");
      myFile.print(";");
      myFile.print("Turma");
      //      myFile.print(diciplina);
      myFile.print(";");
      myFile.print("Data:");
      myFile.print(rtc.getDateStr(FORMAT_SHORT));
      myFile.print(";");
      myFile.print("Hora:");
      myFile.println(rtc.getTimeStr());
//      myFile.print(";");


      lcd.setBacklight(HIGH);
      lcd.setCursor(0, 0);
      lcd.print("  Bem-Vindo    ");
      lcd.setCursor(0, 1);
      lcd.print(nomeP);
      delay(1500);

      gree();
      teclado();


      passouP[posiP] = 1;
    }
    else if (passouP[0] == 1)
    {

      lcd.setBacklight(HIGH);
      lcd.setCursor(0, 0);
      lcd.print("  Ate logo !!!!");
      lcd.setCursor(0, 1);
      lcd.print(nomeP);
      delay(2000);


      if (myFile)
      {

        myFile.print(nomeP);
        myFile.print(";");
        myFile.print(rtc.getTimeStr());
        myFile.println();
        myFile.close();
      }
      gree();
      contador = 0;
      passouP[posiP] = 0;


    }
  }





  //  cadPro (conteudo.substring(1), "70 B9 B8 46", "Professor Fulano de Tal", 0);

  // info = , udi=, t=nº da turma do aluno, pp = nº do Professor, aa = n do aluno
  //  void cadAl (String info, String udi, String nome, char t, int pp, int aa)


  //  cadAl (conteudo.substring(1), "82 30 53 73", "Franklim Pereira", '1', 0, 0);
}



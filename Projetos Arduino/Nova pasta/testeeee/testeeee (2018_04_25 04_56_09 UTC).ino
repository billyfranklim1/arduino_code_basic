int segundo, minuto, hora, dia, mes, ano;
unsigned long UtlTime;
#include <SPI.h>
#include <MFRC522.h>
#include <TimeLib.h>
#define SS_PIN 53
#define RST_PIN 51
MFRC522 mfrc522(SS_PIN, RST_PIN);
char st[20];
String nome = "Billyfranklim" ;
int teste = 0 ;


int pinoSensor = 0; //pino que está ligado o terminal central do LM35 (portaanalogica 0)
int valorLido = 0; //valor lido na entrada analogica
float temperatura = 0; //valorLido convertido para temperatura
int linha = 0; // variavel que se refere as linhas do excel
short int Conta_Pulso;
short int Tanque_Vazio = 0; //variável referente ao volume
int pro = 0 ;
String  prof ="Kenio";

void setup() {


  
 Serial.begin(9600); //Inicializa comunicação Serial
 Serial.println("CLEARDATA"); // Reset da comunicação serial
 Serial.println("LABEL,Nome,Entrada, saida, status"); // Nomeia ascolunas
 SPI.begin();
 mfrc522.PCD_Init();
 Serial.print("Aproxime o seu cartao do leitor...");
 Serial.println();

  UtlTime = 0;
  minuto = 28;
  hora = 16;
  dia = 9;
  mes = 9;
  ano = 2017;


 
}
void loop() {
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
      Serial.println();
      Serial.print("Seja Bem-Vindo Professor ");
      Serial.println(prof);
      Serial.print("Entrada: ");
      Serial.print("DATA,TIME,");
      delay(1500);
    }

    pro ++;

    if (pro > 1) {
      Serial.println();
      Serial.print("Até mais Professor !! ");
      Serial.println(prof);
      Serial.print("Saida: ");
      Serial.print("DATA,TIME,");
      pro = 0;
      delay(1500);
    }
  }
}


 /*Serial.print("DATA,TIME,"); //inicia a impressão de dados, sempre iniciando
 Serial.print(temperatura);
 Serial.print(",");
 Serial.print(Tanque_Vazio);
 Serial.print(",");
 Serial.println(linha);
*/
 



#include <MFRC522.h>
#include <SPI.h>
#define SS_PIN 53
#define RST_PIN 51
MFRC522 mfrc522(SS_PIN, RST_PIN);
String nome = "Billyfranklim Avelino Pereira"; 
int linha = 0; 


void setup() {

 Serial.begin(9600);
 SPI.begin();
 mfrc522.PCD_Init();
 Serial.println("CLEARDATA"); // Reset da comunicação serial
 Serial.println("LABEL,Entrada,Nome, linha"); // Nomeia ascolunas


}
void loop() {

 linha++; // incrementa a linha do excel para que a leitura pule de linha em linha
 Serial.print("DATA,TIME,"); //inicia a impressão de dados, sempre iniciando
 Serial.print(nome);
 Serial.print(",");
 Serial.println(linha);

 if (linha > 100) //laço para limitar a quantidade de dados
{
 linha = 0;
 Serial.println("ROW,SET,2"); // alimentação das linhas com os dados sempreiniciando
}
 delay(5000); //espera 5 segundos para fazer nova leitura
}

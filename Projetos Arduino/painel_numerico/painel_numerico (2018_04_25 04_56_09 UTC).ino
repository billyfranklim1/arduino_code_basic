//Programa : Teclado matricial 4x3 - Biblioteca Keypad
//Autor : Arduino e Cia
//Baseado no programa original de Alexander Brevig

//Carrega a biblioteca Keypad
#include <Keypad.h>

//Definicao da quantidade de linhas e colunas
const byte LINHAS = 4;
const byte COLUNAS = 3;

//Matriz de caracteres
char matriz_teclas[LINHAS][COLUNAS] = 
{
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

//Definicao dos pinos das linhas
byte PinosLinhas[LINHAS] = {4, 5, 6, 7};
//Definicao dos pinos das colunas
byte PinosColunas[COLUNAS] = {8, 9, 10};

//Inicializa o teclado
Keypad meuteclado = Keypad( makeKeymap(matriz_teclas), PinosLinhas, 
                            PinosColunas, LINHAS, COLUNAS); 

void setup()
{
  Serial.begin(9600);
  Serial.println("Teclado 4x3 - Exemplo biblioteca Keypad");
  Serial.println("Aguardando acionamento das teclas...");
  Serial.println();
}
  
void loop()
{
  //Verifica se alguma tecla foi pressionada
  char tecla_pressionada = meuteclado.getKey();
  
  //Mostra no serial monitor o caracter da matriz,
  //referente a tecla que foi pressionada
  if (tecla_pressionada)
  {
    Serial.print("Tecla pressionada : ");
    Serial.println(tecla_pressionada);
  }
}

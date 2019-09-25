#include <Keypad.h>

byte pinosLinhas[]  = {10,5,6,8};

byte pinosColunas[] = {9,11,7};

char teclas[4][3] = {{'1','2','3'},
                     {'4','5','6'},
                     {'7','8','9'},
                     {'*','0','#'}};

Keypad teclado1 = Keypad( makeKeymap(teclas), pinosLinhas, pinosColunas, 4, 3);  

void setup() {
  Serial.begin(9600);
  Serial.println("Teclado 4x4 com Biblioteca Keypad");
  Serial.println("Aguardando acionamento das teclas...");
  Serial.println();
}

void loop() {
  //Verifica se alguma tecla foi pressionada
  char tecla_pressionada = teclado1.getKey();
  
  //Mostra no serial monitor o caracter da matriz,
  //referente a tecla que foi pressionada
  if (tecla_pressionada)
  {
    Serial.print("Tecla: ");
    Serial.println(tecla_pressionada);
  } 
}

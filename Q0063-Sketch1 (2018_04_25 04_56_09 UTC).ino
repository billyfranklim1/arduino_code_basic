//**********************************************************
// Sketch: Teclado matricial 4x4 Arduino
// Autor : Brincando com Ideias
//**********************************************************

int pinosLinhas[]  = {11,10,9,8};
int pinosColunas[] = {7,6,5,4};
char teclas[4][4] = {{'1','2','3','A'},
                     {'4','5','6','B'},
                     {'7','8','9','C'},
                     {'*','0','#','D'}};

void setup()
{
  for (int nL = 0; nL <= 3; nL++) {
     pinMode(pinosLinhas[nL], OUTPUT);
     digitalWrite(pinosLinhas[nL], HIGH);
  }

  for (int nC = 0; nC <= 3; nC++) {
     pinMode(pinosColunas[nC], INPUT_PULLUP);
  } 
   
  Serial.begin(9600);
  Serial.println("Teclado 4x4");
  Serial.println("Aguardando acionamento das teclas...");
  Serial.println();
}
 
void loop()
{
    //faz varredura em todas as linhas, desligando uma de cada vez
    for (int nL = 0; nL <= 3; nL++)
    {
      digitalWrite(pinosLinhas[nL], LOW);
      
      //faz varredura em todas as colunas verificando se tem algum botao apertado
      for (int nC = 0; nC <= 3; nC++) {
        if (digitalRead(pinosColunas[nC]) == LOW)
        {
          Serial.print("Tecla: ");
          Serial.println(teclas[nL][nC]);
          while(digitalRead(pinosColunas[nC]) == LOW){}
        }
      }

      digitalWrite(pinosLinhas[nL], HIGH);
    }
   delay(10);
}
 

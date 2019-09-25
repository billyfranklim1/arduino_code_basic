#define red 47 
#define gre 46
void setup() 
{
  // Configura o pino d13 como saída 
  pinMode(red, OUTPUT);
   pinMode(gre, OUTPUT);
}

void loop() 
{
 digitalWrite(gre, HIGH);
  delay(250);
  digitalWrite(gre, LOW);
  delay(250);
  digitalWrite(gre, HIGH);
  delay(250);
  digitalWrite(gre, LOW);

}

/*
int ledAzul = 47;         
int potenciometro = 7;
int tempoDeEspera = 0;
 
void setup() {
  pinMode(ledAzul,OUTPUT);  
}
 
void loop() {
  //Leitura do valor do potenciômetro que é usada como delay
  tempoDeEspera = analogRead(potenciometro);
   
  digitalWrite(ledAzul, HIGH);
  delay(tempoDeEspera);
  digitalWrite(ledAzul, LOW);
  delay(tempoDeEspera);
 
              
          
}

#define potPin 0   // Define o pino analógico em que o potenciômetro vai ser conectado 
#define ledPin 47   // Define o pino que terá um LED e um resistência ligada ao terra 

int valPot = 0; //Variável que armazena o valor da leitura do potenciômetro 

void setup() { 

pinMode(ledPin,OUTPUT); // Configura o pino do LED como saída 

} 

void loop() {    

valPot =  analogRead(potPin); //Faz a leitura analógica do pino em que o potenciômetro esta ligado 
valPot = map(valPot,0,1023,0,255); //Utilizando a função map() para transformar uma escala de 0-1023 em uma escala 0 a 255 
analogWrite(ledPin,valPot ); // Aciona o LED proporcionalmente ao valor da leitura analógica 

}*/

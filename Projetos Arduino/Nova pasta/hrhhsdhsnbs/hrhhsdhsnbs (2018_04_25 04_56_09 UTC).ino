int pinoSensor = 0; //pino que está ligado o terminal central do LM35 (portaanalogica 0)
int valorLido = 0; //valor lido na entrada analogica
float temperatura = 0; //valorLido convertido para temperatura
int linha = 0; // variavel que se refere as linhas do excel
short int Conta_Pulso;
short int Tanque_Vazio = 0; //variável referente ao volume
void setup() {
 Serial.begin(9600); //Inicializa comunicação Serial
 Serial.println("CLEARDATA"); // Reset da comunicação serial
 Serial.println("LABEL,Hora,Temperatura, Volume, linha"); // Nomeia ascolunas
 pinMode(2, INPUT);
 pinMode(8, OUTPUT);
 attachInterrupt(0, incpulso, RISING); //Configura o pino 2(Interrupção 0) paratrabalhar como interrupção
Figura 5.13 – Montagem do circuito
37
}
void loop() {
 valorLido = analogRead(pinoSensor);
 temperatura = (valorLido * 0.00488); // 5V / 1023 = 0.00488 (precisão do A/D)
 temperatura = temperatura * 100; //Converte milivolts para graus celSius,lembrando que a cada 10mV equivalem a 1 grau celSius
 linha++; // incrementa a linha do excel para que a leitura pule de linha em linha
 Serial.print("DATA,TIME,"); //inicia a impressão de dados, sempre iniciando
 Serial.print(temperatura);
 Serial.print(",");
 Serial.print(Tanque_Vazio);
 Serial.print(",");
 Serial.println(linha);

 if (linha > 100) //laço para limitar a quantidade de dados
{
 linha = 0;
 Serial.println("ROW,SET,2"); // alimentação das linhas com os dados sempre
iniciando
}
 delay(5000); //espera 5 segundos para fazer nova leitura
}
void incpulso ()
{
 Conta_Pulso++;
 Tanque_Vazio = Conta_Pulso * 0.972+6.36;
int pinoSensor = 0; //pino que está ligado o terminal central do LM35 (portaanalogica 0)
int valorLido = 0; //valor lido na entrada analogica
float temperatura = 0; //valorLido convertido para temperatura
int linha = 0; // variavel que se refere as linhas do excel
short int Conta_Pulso;
short int Tanque_Vazio = 0; //variável referente ao volume
void setup() {
 Serial.begin(9600); //Inicializa comunicação Serial
 Serial.println("CLEARDATA"); // Reset da comunicação serial
 Serial.println("LABEL,Hora,Temperatura, Volume, linha"); // Nomeia as
colunas
 pinMode(2, INPUT);
 pinMode(8, OUTPUT);
 attachInterrupt(0, incpulso, RISING); //Configura o pino 2(Interrupção 0) paratrabalhar como interrupçãoFigura 5.13 – Montagem do circuito
37
}
void loop() {
 valorLido = analogRead(pinoSensor);
 temperatura = (valorLido * 0.00488); // 5V / 1023 = 0.00488 (precisão do A/D)
 temperatura = temperatura * 100; //Converte milivolts para graus celSius,lembrando que a cada 10mV equivalem a 1 grau celSius
 linha++; // incrementa a linha do excel para que a leitura pule de linha em linha
 Serial.print("DATA,TIME,"); //inicia a impressão de dados, sempre iniciando
 Serial.print(temperatura);
 Serial.print(",");
 Serial.print(Tanque_Vazio);
 Serial.print(",");
 Serial.println(linha);

 if (linha > 100) //laço para limitar a quantidade de dados
{
 linha = 0;
 Serial.println("ROW,SET,2"); // alimentação das linhas com os dados sempreiniciando
}
 delay(5000); //espera 5 segundos para fazer nova leitura
}
void incpulso ()
{
 Conta_Pulso++;
 Tanque_Vazio = Conta_Pulso * 0.972+6.36;
}
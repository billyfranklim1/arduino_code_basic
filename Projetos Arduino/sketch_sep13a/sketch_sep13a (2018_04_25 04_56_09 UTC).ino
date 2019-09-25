int nome = "Billyfranklim Avelino Pereira"; 

void setup() {
 Serial.begin(9600);
 Serial.println("CLEARDATA"); // Reset da comunicação serial
 Serial.println("LABEL,Nome,Entrada"); // Nomeia ascolunas

}

void loop() {
Serial.println(nome);
Serial.println("DATA,TIME,");
delay(1000);
}

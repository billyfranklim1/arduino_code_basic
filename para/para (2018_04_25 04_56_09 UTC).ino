void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  teste ("Billy");
  teste2 ("gjas");
}

void teste(String nome) {
  Serial.println();
  Serial.print("Seja Bem-Vindo Professor ");
  Serial.println(nome);
  Serial.print("Entrada: ");

  delay(3000);
}

void teste2 (String nome) {

  Serial.println();
  Serial.print("Ate mais Professor !! ");
  Serial.println(nome);
  Serial.print("Saida: ");

}

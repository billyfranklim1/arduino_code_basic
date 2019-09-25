
String turno ;
String turma;
String M;
String T;
String N;

void setup() {
  turno == 0;
  Serial.print("\nEntre com o turno:");
  while (turno == 0)

    if (Serial.available() > 0) {

      turno = Serial.parseInt();
      if (turno == M) {

        Serial.print("Turno escolhido foi manhã");
        turma = Serial.parseInt();
        Serial.print("Escolha uma turma");
        if (turma == 1) {
          Serial.print("Você escolheu a turma 1") ;
        }
        else if (turma == 2 ) {
          Serial.print("Você escolheu a turma 2");
        }
        else {
          Serial.print("Escolha uma turma valida : 1 ou 2");
        }
      }
    }
    else if (turno = T) {
      Serial.print("Turno escolhido foi Tarde");
      turma = Serial.parseInt();
      Serial.print("Escolha uma turma");
      if (turma == 1) {
        Serial.print("Você escolheu a turma 1");
      }
      else if (turma == 2 ) {
        Serial.print("Você escolheu a turma 2");
      }
      else {
        Serial.print("Escolha uma turma valida : 1 ou 2");
      }

    }

    else if (turno = N) {
      Serial.print("Turno escolhido foi Noite");
      turma = Serial.parseInt();
      Serial.print("Escolha uma turma");
      if (turma == 1) {
        Serial.print("Você escolheu a turma 1");
      }
      else if (turma == 2 ) {
        Serial.print("Você escolheu a turma 2");
      }
      else {
        Serial.print("Escolha uma turma valida : 1 ou 2");
      }
 
    }
else {
  Serial.print("Escolha um turno vailido M,T ou N");
}
}


void loop() {
  // put your main code here, to run repeatedly:

}

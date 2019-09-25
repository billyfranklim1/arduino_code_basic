String a=(" FULANO DE TAL");
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);
int rele=13;

void setup() 
{

 Serial.begin(9600);
 
 pinMode(rele, OUTPUT);
 lcd.begin (16,2);
 
}

void loop()
{
  char leitura = Serial.read();

  if ( leitura == '1' )
  {
    lcd.setBacklight(HIGH);
    lcd.setCursor(0,0);
    lcd.print("Ligado com Sucesso");
    lcd.setCursor(0,1);
    lcd.print(a);
  }
  else if (leitura == '0')
  {
    lcd.setBacklight(HIGH);
    lcd.setCursor(0,0);
    lcd.print ("Desligado com Suceso");
    lcd.setCursor(0,1);
    lcd.print(a);
  }
}

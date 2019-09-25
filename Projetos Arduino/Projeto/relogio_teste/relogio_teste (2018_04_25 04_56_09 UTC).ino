#include <DS1307.h>
#include <LiquidCrystal_I2C.h>

 
DS1307 rtc(A4, A5);
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup()
{
  rtc.halt(false);
  rtc.setDOW(THURSDAY);      //Define o dia da semana Thursday

  rtc.setTime(13, 41, 0);     //Define o horario
  rtc.setDate(20, 10, 2017);   //Define o dia, mes e ano
  rtc.setSQWRate(SQW_RATE_1);
  rtc.enableSQW(true);
  lcd.begin (16, 2);
  Serial.begin(9600);
}
 
void loop()
{
  //Mostra as informações no Serial Monitor
  Serial.print("Hora : ");
  Serial.print(rtc.getTimeStr());
  Serial.print(" ");
  Serial.print("Data : ");
  Serial.print(rtc.getDateStr(FORMAT_SHORT));
  Serial.print(" ");
  Serial.println(rtc.getDOWStr(FORMAT_SHORT));
  //Mostra as informações no Serial Monitor
  /* lcd.setBacklight(HIGH);
  lcd.setCursor(0, 0);
  lcd.print("Hora : ");
  lcd.print(rtc.getTimeStr());
  
  lcd.setCursor(0, 1);
  lcd.print("Data : ");
  lcd.print(rtc.getDateStr(FORMAT_SHORT));
  
  //Aguarda 1 segundo e repete o processo
  delay (1000);*/
   lcd.setCursor(4, 0);
  lcd.print(rtc.getTimeStr());
  
  // Display abbreviated Day-of-Week in the lower left corner
  lcd.setCursor(0, 1);
  lcd.print(rtc.getDOWStr(FORMAT_SHORT));
  
  // Display date in the lower right corner
  lcd.setCursor(6, 1);
  lcd.print(rtc.getDateStr());

  // Wait one second before repeating :)
  delay (1000);
  
}

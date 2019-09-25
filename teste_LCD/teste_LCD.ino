//Tony Emerson Marim em 15/06/2017.
/** mecatronizando@gmail.com **/
// Baseado no programa original de Nishant Arora 
/** Display LCD_2 **/

#include <Wire.h>  //INCLUSÃO DE BIBLIOTECA
#include <LiquidCrystal_I2C.h> //INCLUSÃO DE BIBLIOTECA

LiquidCrystal_I2C lcd(0x3F, 16, 2); //FUNÇÃO DO TIPO "LiquidCrystal_I2C"
 
//line1 = TEXTO DA ROLAGEM SUPERIOR
String line1 = "Mecatronizando: www.mecatronizando.com.br/ curta / inscreva-se / compartilhe"; 
 
//line2 = TEXTO DA LINHA INFERIOR  
String line2 = "-MECATRONIZANDO-";  
   
// REFERENCE FLAGS 
int stringStart, stringStop = 0;  
int scrollCursor = 16;  
int tamanho =0;  
   
void setup() 
{  
  lcd.init();   // INICIALIZA O DISPLAY LCD
  lcd.backlight(); // HABILITA O BACKLIGHT (LUZ DE FUNDO)   
}  
   
void loop() 
{  
  lcd.setCursor(scrollCursor, 0);  
  lcd.print(line1.substring(stringStart,stringStop));  
  lcd.setCursor(0, 1);  
  lcd.print(line2);  
 
  delay(200); //TEMPO DE TRANSPOSIÇÃO DA ROLAGEM 
  scroll_sup(); //ROTINA DA ROLAGEM

  //VERIFICA TAMANHO DA STRING 
  tamanho = line1.length();  
  if (stringStart == tamanho)  
  {  
    stringStart = 0;  
    stringStop = 0;  
  }  
}  
//ROTINA DE ROLAGEM 
void scroll_sup()  
{  
  lcd.clear();  
  if(stringStart == 0 && scrollCursor > 0)
  {  
    scrollCursor--;  
    stringStop++;  
  } else if (stringStart == stringStop){  
    stringStart = stringStop = 0;  
    scrollCursor = 16;  
  } else if (stringStop == line1.length() && scrollCursor == 0) {  
    stringStart++;  
  } else {  
    stringStart++;  
    stringStop++;  
  }  
}

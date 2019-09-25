#include <LiquidCrystal_I2C.h>
#include <DS1307.h>

// Init the DS1307
DS1307 rtc(4, 5);

// Init the LCD
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup()
{
  // Initialize the rtc object
// rtc.begin();
  
  // Set the clock to run-mode
  rtc.halt(false);
  
  // Setup LCD to 16x2 characters
  lcd.begin(16, 2);

  // The following lines can be commented out to use the values already stored in the DS1307
  rtc.setDOW(SUNDAY);        // Set Day-of-Week to SUNDAY
  rtc.setTime(14, 40, 0);     // Set the time to 12:00:00 (24hr format)
  rtc.setDate(12, 10, 2017);   // Set the date to October 3th, 2010

  // Set SQW/Out rate to 1Hz, and enable SQW
  rtc.setSQWRate(SQW_RATE_1);
  rtc.enableSQW(true);
}

void loop()
{
  // Display time centered on the upper line
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

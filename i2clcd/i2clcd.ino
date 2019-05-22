#include <LiquidCrystal_I2C.h>

#define LCD_COLS 16
#define LCD_ROWS 2

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
uint8_t row = 0;
uint8_t col = 0;

void setup()
{
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  lcd.cursor();
  lcd.setCursor(0,0);
}


void loop()
{
  if (Serial.available()) {
    if (col == LCD_COLS) {
      row++;
      col = 0;

      if (row == LCD_ROWS) {
        row = 0;
        lcd.clear();
      }
    }

    uint8_t c = Serial.read();
    switch (c) {
      case 0x1B:
        col = 0;
        row = 0;
        lcd.setCursor(0,0);
        lcd.clear();
        break;

      case 0x8:
        col--;
        lcd.setCursor(col, row);
        lcd.print(' ');
        lcd.setCursor(col, row);
        break;

      default:
        lcd.setCursor(col, row);
        lcd.print((char)c);
        col++;
        break;

    }

  }
}

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LCD_COLS 16
#define LCD_ROWS 2

uint8_t left_empty   [8] = { 0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F };
uint8_t left_full    [8] = { 0x1F, 0x10, 0x17, 0x17, 0x17, 0x10, 0x1F };
uint8_t middle_empty [8] = { 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F };
uint8_t middle_full  [8] = { 0x1F, 0x00, 0x1F, 0x1F, 0x1F, 0x00, 0x1F };
uint8_t right_empty  [8] = { 0x1F, 0x01, 0x01, 0x01, 0x01, 0x01, 0x1F };
uint8_t right_full   [8] = { 0x1F, 0x01, 0x1D, 0x1D, 0x1D, 0x01, 0x1F };

LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void lcd_setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();

  lcd.createChar(0, left_empty);
  lcd.createChar(1, left_full );
  lcd.createChar(2, middle_empty);
  lcd.createChar(3, middle_full);
  lcd.createChar(4, right_empty);
  lcd.createChar(5, right_full);
  lcd.home();

}

void lcd_print_progress(uint8_t percent) {
  uint8_t barlen = map(percent, 0, 100, 0, 16);

  barlen > 0  && lcd.write(0x101) || lcd.write(0x100);
  barlen > 1  && lcd.write(0x103) || lcd.write(0x102);
  barlen > 2  && lcd.write(0x103) || lcd.write(0x102);
  barlen > 3  && lcd.write(0x103) || lcd.write(0x102);
  barlen > 4  && lcd.write(0x103) || lcd.write(0x102);
  barlen > 5  && lcd.write(0x103) || lcd.write(0x102);
  barlen > 6  && lcd.write(0x103) || lcd.write(0x102);
  barlen > 7  && lcd.write(0x103) || lcd.write(0x102);
  barlen > 8  && lcd.write(0x103) || lcd.write(0x102);
  barlen > 9  && lcd.write(0x103) || lcd.write(0x102);
  barlen > 10 && lcd.write(0x103) || lcd.write(0x102);
  barlen > 11 && lcd.write(0x103) || lcd.write(0x102);
  barlen > 12 && lcd.write(0x103) || lcd.write(0x102);
  barlen > 13 && lcd.write(0x103) || lcd.write(0x102);
  barlen > 14 && lcd.write(0x103) || lcd.write(0x102);
  barlen > 15 && lcd.write(0x105) || lcd.write(0x104);
}

void lcd_print_ml(long ml) {
  char padded[6];
  sprintf(padded, "%05d", ml);
  lcd.print(padded);
  lcd.print("mL");
}

void update_lcd_closed(uint8_t dispense_ml) {

  lcd.home();
  lcd.print("CLOSED");

  lcd.setCursor(9, 0);
  lcd_print_ml(dispense_ml);
}

void update_lcd_open(uint8_t dispense_ml, uint8_t totalMilliLitres) {
  lcd.home();
  lcd_print_ml(totalMilliLitres);

  lcd.setCursor(9, 0);
  lcd_print_ml(dispense_ml);


  lcd.setCursor(0, 1);
  lcd_print_progress(
    (uint8_t)(((float) totalMilliLitres / (float) dispense_ml) * 100)
  );
}

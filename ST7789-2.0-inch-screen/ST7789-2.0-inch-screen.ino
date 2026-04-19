#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

#define TFT_BL 1   // Backlight control (PWM). Controls screen brightness via LED backlight driver
#define TFT_CS 2   // Chip Select (SPI). Pull LOW to talk to the display, HIGH to ignore it
#define TFT_DC 3   // Data/Command select. LOW = command, HIGH = pixel/data stream
#define TFT_MOSI 9 // SPI MOSI (Master Out Slave In). Data sent from ESP32 → display
#define TFT_SCLK 7 // SPI Clock. Synchronizes data transfer on MOSI line
#define TFT_RST 4  // Hardware reset. Pull LOW briefly to reset the display controller

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

float p = 3.1415926;
char *lorem = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt feugiat. Maecenas enim massa, fringilla sed malesuada et, malesuada sit amet turpis. Sed porttitor neque ut ante pretium vitae malesuada nunc bibendum. Nullam aliquet ultrices massa eu hendrerit. Ut sed nisi lorem. In vestibulum purus a tortor imperdiet posuere.";

void setup(void)
{
  ledcAttach(TFT_BL, 5000, 8); // pin, freq, resolution
  ledcWrite(TFT_BL, 127);      // duty (0–255)
  tft.init(240, 320);          // can't flip this
  tft.setRotation(0);          // pins down
}

void loop()
{
  testdrawtext(lorem, ST77XX_WHITE);
  delay(1000);
  tftPrintTest();
  delay(4000);
}

void testdrawtext(char *text, uint16_t color)
{
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

void tftPrintTest()
{
  tft.setTextWrap(false);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 30);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(2);
  tft.println("Hello World!");
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(3);
  tft.println("Hello World!");
  tft.setTextColor(ST77XX_BLUE);
  tft.setTextSize(4);
  tft.print(1234.567);
  delay(1500);
  tft.setCursor(0, 0);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(0);
  tft.println("Hello World!");
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_GREEN);
  tft.print(p, 6);
  tft.println(" Want pi?");
  tft.println(" ");
  tft.print(8675309, HEX); // print 8,675,309 out in HEX!
  tft.println(" Print HEX!");
  tft.println(" ");
  tft.setTextColor(ST77XX_WHITE);
  tft.println("Sketch has been");
  tft.println("running for: ");
  tft.setTextColor(ST77XX_MAGENTA);
  tft.print(millis() / 1000);
  tft.setTextColor(ST77XX_WHITE);
  tft.print(" seconds.");
}

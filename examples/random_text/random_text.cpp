/*

    Raspberry Pi Pico pico-sdk LCD ILI9341 font print Library (C++)
    print_GFX demo program random_text.cpp
                                      https://twitter.com/yama23238

*/

#include <stdio.h>
#include "pico/stdlib.h"
#include "print_GFX_ILI9341.h"
#include "glcdfont.h"
#include "glcdfont_tt14.h"
#include "glcdfont_tt24.h"
#include "glcdfont_tt32.h"

#define MOSI 19
#define SCK  18
#define CS   17
#define MISO 16

#define RST  22
#define DC   20

#define SPI_PORT  spi0



print_GFX_ILI9341 tft = print_GFX_ILI9341(SPI_PORT, DC, RST, CS);

// フォントの宣言
glcdfont glcdfont01 = glcdfont();
glcdfont_tt14 glcdfont_tt14_01 = glcdfont_tt14();
glcdfont_tt24 glcdfont_tt24_01 = glcdfont_tt24();
glcdfont_tt32 glcdfont_tt32_01 = glcdfont_tt32();



void loop01(void);

int main() {

  stdio_init_all();

  spi_init(SPI_PORT, 10000000);
  gpio_set_function(MISO, GPIO_FUNC_SPI);
  gpio_set_function(SCK, GPIO_FUNC_SPI);
  gpio_set_function(MOSI, GPIO_FUNC_SPI);
  gpio_pull_up(MISO);
  gpio_pull_up(SCK);
  gpio_pull_up(MOSI);
  spi_set_format(SPI_PORT, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);   // SPI MODE0, MSBFIRST

  tft.tft_setup();
  tft.fillScreen(ILI9341_BLACK);
  printf("ILI9341 Test!\r\n"); 
  tft.setRotation(3);
  tft.set_font_back_ground_fill(false);

  while (1) {
    loop01();
  }
  return 0;
}


int rnd(int a);

void loop01(void) {

  tft.fillScreen(ILI9341_BLACK);

  for (int i = 0; i < 6000; i++) {
      int colr, colg, colb, font01, x, y;

      colr = rnd(255);
      colg = rnd(255);
      colb = rnd(255);
      font01 = rnd(1000) % 4;
      x = rnd(300);
      y = rnd(220);

      switch (font01) {
          case 0:
              tft.set_font(&glcdfont01);
              break;
          case 1:
              tft.set_font(&glcdfont_tt14_01);
              break;
          case 2:
              tft.set_font(&glcdfont_tt24_01);
              break;
          case 3:
              tft.set_font(&glcdfont_tt32_01);
              break;
      }
      tft.set_font_color(tft.color565(colr, colg, colb), tft.color565(0, 0, 0));
      tft.chars("TEXT", x, y);
      sleep_ms(10);
  }
}

int rnd(int a) {
    return (rand() % a);
}

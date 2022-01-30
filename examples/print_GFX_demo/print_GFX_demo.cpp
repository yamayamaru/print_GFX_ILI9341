/*

    Raspberry Pi Pico pico-sdk LCD ILI9341 font print Library (C++)
    Demo Program
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
void loop02_setup(void);
void loop02(void);

int main() {

  stdio_init_all();

  spi_init(SPI_PORT, 10000000);    // 40000000まで動作はすることは確認
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

  while (1) {
    loop01();
    loop02_setup();
    loop02();
  }
  return 0;
}

void loop01(void) {
  static int r = 0;

  tft.setRotation(r);
  tft.set_font_back_ground_fill(false);

  tft.set_font(&glcdfont_tt14_01);
  tft.set_font_color(tft.color565(128, 255, 255), tft.color565(0, 0, 0));
  tft.set_font_pos(0,  0);
  tft.fillScreen(ILI9341_BLACK);
  const char c[] = "ARM architecture (Jan.25,2022,20:57 UTC). In Wikipedia: The Free Encyclopedia. Retrieved from https://en.wikipedia.org/wiki/ARM_architecture";
  tft.word_print(c);
  sleep_ms(3000);



  tft.set_font(&glcdfont01);
  tft.set_font_color(tft.color565(255, 255, 255), tft.color565(0, 0, 0));
  tft.set_font_pos(0,  0);
  tft.fillScreen(ILI9341_BLACK);
  const char a[] = "ARM (stylised in lowercase as arm, formerly an acronym for Advanced RISC Machines and originally Acorn RISC Machine) is a family of reduced instruction set computer (RISC) architectures for computer processors, configured for various environments. Arm Ltd. develops the architecture and licenses it to other companies, who design their own products that implement one or more of those architectures, including system on a chip (SoC) and system on module (SoM) designs, that incorporate different components such as memory, interfaces, and radios. It also designs cores that implement these instruction set architectures and licenses these designs to many companies that incorporate those core designs into their own products. ";
  char b[2048];
  strcpy(b, a);
  tft.word_print(b);
  sleep_ms(3000);

  tft.set_font(&glcdfont01);
  tft.set_font_color(tft.color565(255, 255, 255), tft.color565(0, 0, 0));
  tft.set_font_pos(0,  0);
  tft.fillScreen(ILI9341_BLACK);
  tft.print(b);
  sleep_ms(3000);



  tft.set_font(&glcdfont01);
  tft.set_font_color(tft.color565(0, 255, 255), tft.color565(0, 0, 0));
  tft.set_font_pos(0,  0);
  tft.fillScreen(ILI9341_BLACK);
  tft.word_printf("color = 0x%04x,  %s\n", tft.color565(0, 255, 255), "ARM (stylised in lowercase as arm, formerly an acronym for Advanced RISC Machines and originally Acorn RISC Machine) is a family of reduced instruction set computer (RISC) architectures for computer processors, configured for various environments. Arm Ltd. develops the architecture and licenses it to other companies, who design their own products that implement one or more of those architectures, including system on a chip (SoC) and system on module (SoM) designs, that incorporate different components such as memory, interfaces, and radios. It also designs cores that implement these instruction set architectures and licenses these designs to many companies that incorporate those core designs into their own products. ");
  sleep_ms(3000);

  tft.set_font(&glcdfont_tt14_01);
  tft.set_font_pos(0, 0);
  tft.fillScreen(ILI9341_BLACK);
  tft.word_printf("color = 0x%04x,  %s\n", tft.color565(0, 255, 255), "ARM (stylised in lowercase as arm, formerly an acronym for Advanced RISC Machines and originally Acorn RISC Machine) is a family of reduced instruction set computer (RISC) architectures for computer processors, configured for various environments. Arm Ltd. develops the architecture and licenses it to other companies, who design their own products that implement one or more of those architectures, including system on a chip (SoC) and system on module (SoM) designs, that incorporate different components such as memory, interfaces, and radios. It also designs cores that implement these instruction set architectures and licenses these designs to many companies that incorporate those core designs into their own products. ");
  sleep_ms(3000);

  tft.set_font(&glcdfont_tt24_01);
  tft.set_font_pos(0, 0);
  tft.fillScreen(ILI9341_BLACK);
  tft.word_printf("color = 0x%04x,  %s\n", tft.color565(0, 255, 255), "ARM (stylised in lowercase as arm, formerly an acronym for Advanced RISC Machines and originally Acorn RISC Machine) is a family of reduced instruction set computer (RISC) architectures for computer processors, configured for various environments. \n");
  sleep_ms(3000);

  tft.set_font(&glcdfont_tt32_01);
  tft.set_font_pos(0, 0);
  tft.fillScreen(ILI9341_BLACK);
  tft.word_printf("color = 0x%04x,  %s\n", tft.color565(0, 255, 255), "ARM (stylised in lowercase as arm, formerly an acronym for Advanced RISC Machines and originally Acorn RISC Machine) is a family of reduced instruction set computer (RISC) architectures for computer processors, configured for various environments. \n");
  sleep_ms(3000);



  tft.set_font(&glcdfont01);
  tft.set_font_color(tft.color565(0, 0, 255), tft.color565(0, 0, 0));
  tft.set_font_pos(0,  0);
  tft.fillScreen(ILI9341_BLACK);
  tft.printf("color = 0x%04x,  %s\n", tft.color565(0, 0, 255), "ARM (stylised in lowercase as arm, formerly an acronym for Advanced RISC Machines and originally Acorn RISC Machine) is a family of reduced instruction set computer (RISC) architectures for computer processors, configured for various environments. Arm Ltd. develops the architecture and licenses it to other companies, who design their own products that implement one or more of those architectures, including system on a chip (SoC) and system on module (SoM) designs, that incorporate different components such as memory, interfaces, and radios. It also designs cores that implement these instruction set architectures and licenses these designs to many companies that incorporate those core designs into their own products. ");
  sleep_ms(3000);

  tft.set_font(&glcdfont_tt14_01);
  tft.set_font_pos(0, 0);
  tft.fillScreen(ILI9341_BLACK);
  tft.printf("color = 0x%04x,  %s\n", tft.color565(0, 0, 255), "ARM (stylised in lowercase as arm, formerly an acronym for Advanced RISC Machines and originally Acorn RISC Machine) is a family of reduced instruction set computer (RISC) architectures for computer processors, configured for various environments. Arm Ltd. develops the architecture and licenses it to other companies, who design their own products that implement one or more of those architectures, including system on a chip (SoC) and system on module (SoM) designs, that incorporate different components such as memory, interfaces, and radios. It also designs cores that implement these instruction set architectures and licenses these designs to many companies that incorporate those core designs into their own products. ");
  sleep_ms(3000);

  tft.set_font(&glcdfont_tt24_01);
  tft.set_font_pos(0, 0);
  tft.fillScreen(ILI9341_BLACK);
  tft.printf("color = 0x%04x,  %s\n", tft.color565(0, 0, 255), "ARM (stylised in lowercase as arm, formerly an acronym for Advanced RISC Machines and originally Acorn RISC Machine) is a family of reduced instruction set computer (RISC) architectures for computer processors, configured for various environments.\n");
  sleep_ms(3000);

  tft.set_font(&glcdfont_tt32_01);
  tft.set_font_pos(0, 0);
  tft.fillScreen(ILI9341_BLACK);
  tft.printf("color = 0x%04x,  %s\n", tft.color565(0, 0, 255), "ARM (stylised in lowercase as arm, formerly an acronym for Advanced RISC Machines and originally Acorn RISC Machine) is a family of reduced instruction set computer (RISC) architectures for computer processors, configured for various environments.\n");
  sleep_ms(3000);



  tft.set_font(&glcdfont01);
  tft.set_font_color(tft.color565(0, 255, 0), tft.color565(0, 0, 0));
  tft.set_font_pos(0,  0);
  tft.fillScreen(ILI9341_BLACK);
  tft.word_print("ARM (stylised in lowercase as arm, formerly an acronym for Advanced RISC Machines and originally Acorn RISC Machine) is a family of reduced instruction set computer (RISC) architectures for computer processors, configured for various environments. Arm Ltd. develops the architecture and licenses it to other companies, who design their own products that implement one or more of those architectures, including system on a chip (SoC) and system on module (SoM) designs, that incorporate different components such as memory, interfaces, and radios. It also designs cores that implement these instruction set architectures and licenses these designs to many companies that incorporate those core designs into their own products. \n");
  sleep_ms(3000);

  tft.set_font(&glcdfont_tt14_01);
  tft.set_font_pos(0, 0);
  tft.fillScreen(ILI9341_BLACK);
  tft.word_print("ARM (stylised in lowercase as arm, formerly an acronym for Advanced RISC Machines and originally Acorn RISC Machine) is a family of reduced instruction set computer (RISC) architectures for computer processors, configured for various environments. Arm Ltd. develops the architecture and licenses it to other companies, who design their own products that implement one or more of those architectures, including system on a chip (SoC) and system on module (SoM) designs, that incorporate different components such as memory, interfaces, and radios. It also designs cores that implement these instruction set architectures and licenses these designs to many companies that incorporate those core designs into their own products. \n");
  sleep_ms(3000);

  tft.set_font(&glcdfont_tt24_01);
  tft.set_font_pos(0, 0);
  tft.fillScreen(ILI9341_BLACK);
  tft.word_print("ARM (stylised in lowercase as arm, formerly an acronym for Advanced RISC Machines and originally Acorn RISC Machine) is a family of reduced instruction set computer (RISC) architectures for computer processors, configured for various environments. \n");
  sleep_ms(3000);

  tft.set_font(&glcdfont_tt32_01);
  tft.set_font_pos(0, 0);
  tft.fillScreen(ILI9341_BLACK);
  tft.word_print("ARM (stylised in lowercase as arm, formerly an acronym for Advanced RISC Machines and originally Acorn RISC Machine) is a family of reduced instruction set computer (RISC) architectures for computer processors, configured for various environments. ");
  sleep_ms(3000);



  tft.set_font(&glcdfont01);
  tft.set_font_color(tft.color565(255, 0, 255), tft.color565(0, 0, 0));
  tft.set_font_pos(0,  0);
  tft.fillScreen(ILI9341_BLACK);
  tft.print("ARM (stylised in lowercase as arm, formerly an acronym for Advanced RISC Machines and originally Acorn RISC Machine) is a family of reduced instruction set computer (RISC) architectures for computer processors, configured for various environments. Arm Ltd. develops the architecture and licenses it to other companies, who design their own products that implement one or more of those architectures, including system on a chip (SoC) and system on module (SoM) designs, that incorporate different components such as memory, interfaces, and radios. It also designs cores that implement these instruction set architectures and licenses these designs to many companies that incorporate those core designs into their own products. \n");
  sleep_ms(3000);

  tft.set_font(&glcdfont_tt14_01);
  tft.set_font_pos(0, 0);
  tft.fillScreen(ILI9341_BLACK);
  tft.print("ARM (stylised in lowercase as arm, formerly an acronym for Advanced RISC Machines and originally Acorn RISC Machine) is a family of reduced instruction set computer (RISC) architectures for computer processors, configured for various environments. Arm Ltd. develops the architecture and licenses it to other companies, who design their own products that implement one or more of those architectures, including system on a chip (SoC) and system on module (SoM) designs, that incorporate different components such as memory, interfaces, and radios. It also designs cores that implement these instruction set architectures and licenses these designs to many companies that incorporate those core designs into their own products. \n");
  sleep_ms(3000);

  tft.set_font(&glcdfont_tt24_01);
  tft.set_font_pos(0, 0);
  tft.fillScreen(ILI9341_BLACK);
  tft.print("ARM (stylised in lowercase as arm, formerly an acronym for Advanced RISC Machines and originally Acorn RISC Machine) is a family of reduced instruction set computer (RISC) architectures for computer processors, configured for various environments. \n");
  sleep_ms(3000);

  tft.set_font(&glcdfont_tt32_01);
  tft.set_font_pos(0, 0);
  tft.fillScreen(ILI9341_BLACK);
  tft.print("ARM (stylised in lowercase as arm, formerly an acronym for Advanced RISC Machines and originally Acorn RISC Machine) is a family of reduced instruction set computer (RISC) architectures for computer processors, configured for various environments.\n");
  sleep_ms(3000);

  r++;
  if (r >= 4) r = 0;
}




#include "print_GFX_GFXcanvas16.h"

#define CIRCLE_N   80
#define RDX         5
#define RDY         5

print_GFX_GFXcanvas16 canvas01 = print_GFX_GFXcanvas16(ILI9341_TFTWIDTH, ILI9341_TFTHEIGHT);
    // print_GFX_GFXcanvas16はメモリ上の確保したフレームバッファ上に描画するクラスです。
    // print_GFX_GFXcanvas16でメモリ上に書き込んだうえで
    // print_GFX_ILI9341もしくはyama_2_GFX_ILI9341のdrawRGBBitmap()で
    // 実際にILI9341のLCDにフレームバッファのメモリの内容を
    // 一度に書き込むことで高速に描画ができます。
    // print_GFX_GFXcanvas16を使う場合はCMakeLists.txtのadd_executableに
    // print_GFX_GFXcanvas16.cppを追加するのを忘れないようにしてください


void random_circle(void);
void loop02(void) {

    int n = 100;
    for (int i = 0; i < n; i++) {
        random_circle();
    }
}

int rnd(int max);

struct {
    int    x;
    int    y;
    int    dx;
    int    dy;
    int    signx;
    int    signy;
    int    r;
    int    c;
} circle01[CIRCLE_N];

void loop02_setup(void) {
    static int r = 0;

    tft.setRotation(0);
    canvas01.setRotation(r);
    canvas01.set_font(&glcdfont_tt24_01);
    canvas01.set_font_color(ILI9341_MAGENTA, ILI9341_BLACK);
    canvas01.set_font_pos(0,  0);

    for (int i = 0; i < CIRCLE_N; i++) {
        circle01[i].x = rnd(canvas01.width());
        circle01[i].y = rnd(canvas01.height());
        circle01[i].r = rnd(10) + 5;
        circle01[i].c = rnd(65534) + 1;
        circle01[i].dx = rnd(RDX) + 1;
        circle01[i].dy = rnd(RDY) + 1;
        circle01[i].signx = rnd(2) ? 1 : -1;
        circle01[i].signy = rnd(2) ? 1 : -1;
    }

    
    r++;
    if (r >=4) r = 0;
}

void random_circle(void) {

    int temp1, temp2;
    canvas01.fillScreen(ILI9341_BLACK);
    for (int i = 0; i < CIRCLE_N; i++ ) {
        temp1 = circle01[i].dx * circle01[i].signx;
        temp2 = circle01[i].x + temp1;
        if (temp2 > canvas01.width()) {
            circle01[i].signx = -1;
            circle01[i].dx = rnd(RDX) + 1;
            circle01[i].x = canvas01.width() + circle01[i].signx * circle01[i].dx;
        } else if (temp2 < 0 ) {
            circle01[i].signx = 1;
            circle01[i].dx = rnd(RDX) + 1;
            circle01[i].x = 0 + circle01[i].signx * circle01[i].dx;
        } else {
            circle01[i].x = circle01[i].x + temp1;
        } 
        temp1 = circle01[i].dy * circle01[i].signy;
        temp2 = circle01[i].y + temp1;
        if (temp2 > canvas01.height()) {
            circle01[i].signy = -1;
            circle01[i].dy = rnd(RDY) + 1;
            circle01[i].y = canvas01.height() + circle01[i].signy * circle01[i].dy;
        } else if (temp2 < 0 ) {
            circle01[i].signy = 1;
            circle01[i].dy = rnd(RDY) + 1;
            circle01[i].y = 0 + circle01[i].signy * circle01[i].dy;
        } else {
            circle01[i].y = circle01[i].y + temp1;
        }

        // フレームバッファ上に円を描画
        canvas01.fillCircle( circle01[i].x, circle01[i].y + 15, circle01[i].r, circle01[i].c);
    }

    // フレームバッファ上に文字を表示
    canvas01.chars("Raspberry Pi Pico", 0, 0);

    // フレームバッファのメモリの内容を実際にILI9341のLCDに書き込む
    tft.drawRGBBitmap(0, 0, canvas01.getBuffer(), ILI9341_TFTWIDTH, ILI9341_TFTHEIGHT); 
    sleep_ms(10);
}

int rnd(int a) {
    return (rand() % a);
}

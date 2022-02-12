/*

    Raspberry Pi Pico pico-sdk LCD ILI9341 font print Library (C++)
    print_GFX demo program random_raspberry_64px_GFXcanvas1.cpp
                                      https://twitter.com/yama23238

*/

#include <stdio.h>
#include "pico/stdlib.h"
#include "print_GFX_ILI9341.h"

#define MOSI 19
#define SCK  18
#define CS   17
#define MISO 16

#define RST  22
#define DC   20

#define SPI_PORT  spi0

print_GFX_ILI9341 tft = print_GFX_ILI9341(SPI_PORT, DC, RST, CS);


extern const uint8_t bitmap01[];
extern const uint8_t bitmap_mask01[];

#define RASPBERRY_N  40
#define RDX        5
#define RDY        5

void random_raspberry(void);
void setup();
void loop();
int main() {
    stdio_init_all();

    spi_init(SPI_PORT, 40000000);
    gpio_set_function(MISO, GPIO_FUNC_SPI);
    gpio_set_function(SCK, GPIO_FUNC_SPI);
    gpio_set_function(MOSI, GPIO_FUNC_SPI);
    gpio_pull_up(MISO);
    gpio_pull_up(SCK);
    gpio_pull_up(MOSI);
    spi_set_format(SPI_PORT, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);   // SPI MODE0, MSBFIRST

    sleep_ms(100); 
    printf("\nReset:");


    tft.tft_setup();
    tft.setRotation(0);
    tft.fillScreen(ILI9341_BLACK);

    while (1) {
        setup();
        for (int i = 0; i < 200; i++) {
            loop();
        }
    }

    return 0;
}

void loop() {
    random_raspberry();
}

// print_GFX_GFXcanvas1のインクルード
#include "print_GFX_GFXcanvas1.h"
// fontデータのインクルード
#include "glcdfont_tt24.h"

print_GFX_GFXcanvas1 canvas01 = print_GFX_GFXcanvas1(ILI9341_TFTWIDTH, ILI9341_TFTHEIGHT);
    // print_GFX_GFXcanvas1はメモリ上の確保したフレームバッファ上に描画するクラスです。
    // print_GFX_GFXcanvas1でメモリ上に書き込んだうえで
    // print_GFX_ILI9341もしくはyama_2_GFX_ILI9341のdrawBitmap()で
    // 実際にILI9341のLCDにフレームバッファのメモリの内容を
    // 一度に書き込むことで高速に描画ができます。
    // print_GFX_GFXcanvas1を使う場合はCMakeLists.txtのadd_executableに
    // print_GFX_GFXcanvas1.cppを追加するのを忘れないようにしてください

// fontの宣言
glcdfont_tt24 glcdfont_tt24_01 = glcdfont_tt24();

int rnd(int max);

struct {
    int    x;
    int    y;
    int    dx;
    int    dy;
    int    signx;
    int    signy;
    int    c;
} raspberry_data01[RASPBERRY_N];

void setup(void){
    static int r = 3;

    canvas01.setRotation(r);
    canvas01.set_font(&glcdfont_tt24_01);
    canvas01.set_font_color(1, 0);
    canvas01.set_font_pos(0,  0);

    for (int i = 0; i < RASPBERRY_N; i++) {
        raspberry_data01[i].x = rnd(canvas01.width());
        raspberry_data01[i].y = rnd(canvas01.height());
        raspberry_data01[i].dx = rnd(RDX) + 1;
        raspberry_data01[i].dy = rnd(RDY) + 1;
        raspberry_data01[i].signx = rnd(2) ? 1 : -1;
        raspberry_data01[i].signy = rnd(2) ? 1 : -1;
    }

    r++;
    if (r >= 4) r = 0;
}

void random_raspberry(void) {

    int temp1, temp2;
    canvas01.fillScreen(0);
    for (int i = 0; i < RASPBERRY_N; i++ ) {
        temp1 = raspberry_data01[i].dx * raspberry_data01[i].signx;
        temp2 = raspberry_data01[i].x + temp1;
        if (temp2 > canvas01.width()) {
            raspberry_data01[i].signx = -1;
            raspberry_data01[i].dx = rnd(RDX) + 1;
            raspberry_data01[i].x = canvas01.width() + raspberry_data01[i].signx * raspberry_data01[i].dx;
        } else if (temp2 < 0 ) {
            raspberry_data01[i].signx = 1;
            raspberry_data01[i].dx = rnd(RDX) + 1;
            raspberry_data01[i].x = 0 + raspberry_data01[i].signx * raspberry_data01[i].dx;
        } else {
            raspberry_data01[i].x = raspberry_data01[i].x + temp1;
        } 
        temp1 = raspberry_data01[i].dy * raspberry_data01[i].signy;
        temp2 = raspberry_data01[i].y + temp1;
        if (temp2 > canvas01.height()) {
            raspberry_data01[i].signy = -1;
            raspberry_data01[i].dy = rnd(RDY) + 1;
            raspberry_data01[i].y = canvas01.height() + raspberry_data01[i].signy * raspberry_data01[i].dy;
        } else if (temp2 < 0 ) {
            raspberry_data01[i].signy = 1;
            raspberry_data01[i].dy = rnd(RDY) + 1;
            raspberry_data01[i].y = 0 + raspberry_data01[i].signy * raspberry_data01[i].dy;
        } else {
            raspberry_data01[i].y = raspberry_data01[i].y + temp1;
        }

        // GFXcanvas1のバッファにラズベリーのアイコンの描画
        canvas01.drawBitmap( raspberry_data01[i].x, raspberry_data01[i].y, bitmap01, bitmap_mask01, 64, 64, 1, 0);
    }
    // GFXcanvas1のバッファの座標x=0、y=0に文字を表示
    canvas01.set_font_pos(0,0);
    canvas01.word_print("Raspberry Pi Pico");

    // GFXcanvas1のバッファの内容を実際にILI9341のLCDに書き込む
    tft.drawBitmap(0, 0, canvas01.getBuffer(), ILI9341_TFTWIDTH, ILI9341_TFTHEIGHT, ILI9341_RED, ILI9341_BLACK); 
    sleep_ms(10);
}

int rnd(int a) {
    return (rand() % a);
}

const uint8_t bitmap_mask01[] = {      // 64x64の1bitモノクロ画像マスクデータ
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x40,0x00,0x00,
    0x00,0x00,0x7f,0xf8,0x1f,0xfe,0x00,0x00,0x00,0x01,0xff,0xfc,0x3f,0xff,0x80,0x00,
    0x00,0x03,0xff,0xfe,0x7f,0xff,0xc0,0x00,0x00,0x03,0xff,0xff,0xff,0xff,0xc0,0x00,
    0x00,0x03,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0x03,0xff,0xff,0xff,0xff,0xc0,0x00,
    0x00,0x03,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0x03,0xff,0xff,0xff,0xff,0xc0,0x00,
    0x00,0x01,0xff,0xff,0xff,0xff,0x80,0x00,0x00,0x01,0xff,0xff,0xff,0xff,0x80,0x00,
    0x00,0x00,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x7f,0xff,0xff,0xfe,0x00,0x00,
    0x00,0x00,0x3f,0xff,0xff,0xfc,0x00,0x00,0x00,0x00,0x1f,0xff,0xff,0xf8,0x00,0x00,
    0x00,0x00,0x1f,0xff,0xff,0xf8,0x00,0x00,0x00,0x00,0x3f,0xff,0xff,0xfc,0x00,0x00,
    0x00,0x00,0x7f,0xff,0xff,0xfe,0x00,0x00,0x00,0x00,0x7f,0xff,0xff,0xfe,0x00,0x00,
    0x00,0x00,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0x00,0x00,
    0x00,0x00,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x01,0xff,0xff,0xff,0xff,0x80,0x00,
    0x00,0x01,0xff,0xff,0xff,0xff,0x80,0x00,0x00,0x03,0xff,0xff,0xff,0xff,0xc0,0x00,
    0x00,0x07,0xff,0xff,0xff,0xff,0xe0,0x00,0x00,0x07,0xff,0xff,0xff,0xff,0xe0,0x00,
    0x00,0x0f,0xff,0xff,0xff,0xff,0xf0,0x00,0x00,0x0f,0xff,0xff,0xff,0xff,0xf0,0x00,
    0x00,0x0f,0xff,0xff,0xff,0xff,0xf0,0x00,0x00,0x0f,0xff,0xff,0xff,0xff,0xf0,0x00,
    0x00,0x07,0xff,0xff,0xff,0xff,0xe0,0x00,0x00,0x07,0xff,0xff,0xff,0xff,0xe0,0x00,
    0x00,0x03,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0x03,0xff,0xff,0xff,0xff,0xc0,0x00,
    0x00,0x03,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0x01,0xff,0xff,0xff,0xff,0x80,0x00,
    0x00,0x01,0xff,0xff,0xff,0xff,0x80,0x00,0x00,0x01,0xff,0xff,0xff,0xff,0x80,0x00,
    0x00,0x00,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0x00,0x00,
    0x00,0x00,0x7f,0xff,0xff,0xfe,0x00,0x00,0x00,0x00,0x3f,0xff,0xff,0xfc,0x00,0x00,
    0x00,0x00,0x1f,0xff,0xff,0xf8,0x00,0x00,0x00,0x00,0x07,0xff,0xff,0xe0,0x00,0x00,
    0x00,0x00,0x03,0xff,0xff,0xc0,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0x00,0x00,0x00,
    0x00,0x00,0x00,0x3f,0xfc,0x00,0x00,0x00,0x00,0x00,0x00,0x1f,0xf8,0x00,0x00,0x00,
    0x00,0x00,0x00,0x03,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

const uint8_t bitmap01[] = {    // 64x64の1bitモノクロ画像データ
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x40,0x00,0x00,
    0x00,0x00,0x7f,0xf8,0x1f,0xfe,0x00,0x00,0x00,0x01,0xfd,0xbc,0x3d,0xbf,0x80,0x00,
    0x00,0x03,0xc0,0x0e,0x70,0x03,0xc0,0x00,0x00,0x03,0x00,0x07,0xe0,0x00,0xc0,0x00,
    0x00,0x03,0x80,0x03,0xc0,0x01,0xc0,0x00,0x00,0x03,0x01,0x01,0x80,0x80,0xc0,0x00,
    0x00,0x03,0x80,0x81,0x81,0x01,0xc0,0x00,0x00,0x03,0xc0,0x41,0x82,0x03,0xc0,0x00,
    0x00,0x01,0xc0,0x33,0xcc,0x03,0x80,0x00,0x00,0x01,0xe0,0x1f,0xf8,0x07,0x80,0x00,
    0x00,0x00,0xe0,0x0f,0xf0,0x07,0x00,0x00,0x00,0x00,0x70,0x0f,0xf0,0x0e,0x00,0x00,
    0x00,0x00,0x38,0x3f,0xf8,0x3c,0x00,0x00,0x00,0x00,0x1f,0xfc,0x3f,0xf8,0x00,0x00,
    0x00,0x00,0x1c,0x70,0x0e,0x38,0x00,0x00,0x00,0x00,0x30,0x20,0x04,0x0c,0x00,0x00,
    0x00,0x00,0x60,0x20,0x04,0x06,0x00,0x00,0x00,0x00,0x40,0x60,0x06,0x02,0x00,0x00,
    0x00,0x00,0xc0,0xf0,0x07,0x03,0x00,0x00,0x00,0x00,0xc1,0xfc,0x3f,0x83,0x00,0x00,
    0x00,0x00,0xc6,0x07,0xe0,0x63,0x00,0x00,0x00,0x01,0xcc,0x03,0xc0,0x33,0x80,0x00,
    0x00,0x01,0xf8,0x03,0xc0,0x1f,0x80,0x00,0x00,0x03,0x18,0x01,0x80,0x18,0xc0,0x00,
    0x00,0x06,0x10,0x01,0x80,0x08,0x60,0x00,0x00,0x06,0x10,0x01,0x80,0x08,0x60,0x00,
    0x00,0x0c,0x10,0x01,0x80,0x08,0x30,0x00,0x00,0x0c,0x10,0x03,0xc0,0x08,0x30,0x00,
    0x00,0x0c,0x18,0x03,0xc0,0x18,0x30,0x00,0x00,0x0c,0x18,0x07,0xe0,0x18,0x30,0x00,
    0x00,0x06,0x3e,0x1c,0x38,0x7c,0x60,0x00,0x00,0x06,0x3f,0xf0,0x0f,0xfc,0x60,0x00,
    0x00,0x03,0x67,0xe0,0x07,0xe6,0xc0,0x00,0x00,0x03,0xc1,0xc0,0x03,0x83,0xc0,0x00,
    0x00,0x03,0x80,0xc0,0x03,0x01,0xc0,0x00,0x00,0x01,0x80,0xc0,0x03,0x01,0x80,0x00,
    0x00,0x01,0x80,0x40,0x02,0x01,0x80,0x00,0x00,0x01,0x80,0x40,0x02,0x01,0x80,0x00,
    0x00,0x00,0xc0,0x60,0x06,0x03,0x00,0x00,0x00,0x00,0xe0,0x30,0x0c,0x07,0x00,0x00,
    0x00,0x00,0x70,0x3c,0x3c,0x0e,0x00,0x00,0x00,0x00,0x38,0x7f,0xfe,0x1c,0x00,0x00,
    0x00,0x00,0x1f,0xe0,0x07,0xf8,0x00,0x00,0x00,0x00,0x07,0xc0,0x03,0xe0,0x00,0x00,
    0x00,0x00,0x03,0xc0,0x03,0xc0,0x00,0x00,0x00,0x00,0x00,0xe0,0x07,0x00,0x00,0x00,
    0x00,0x00,0x00,0x38,0x1c,0x00,0x00,0x00,0x00,0x00,0x00,0x1f,0xf8,0x00,0x00,0x00,
    0x00,0x00,0x00,0x03,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

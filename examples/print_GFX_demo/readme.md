# examples print_GFX_demo
  
このプログラムはpico-sdk用ですpico-sdkを使ってビルドしてください。
ビルドするにはyama_2_GFX、print_GFX_ILI9341が必要になります。  
https://github.com/yamayamaru/yama_2_GFX  
https://github.com/yamayamaru/print_GFX_ILI9341  

  
CMakeLists.txt  
print_GFX_demo.cpp  
font_class.h  
glcdfont.h  
glcdfont_tt14.h  
glcdfont_tt24.h  
glcdfont_tt32.h  
print_GFX_GFXcanvas16.h  
print_GFX_GFXcanvas16.cpp  
print_GFX_ILI9341.h  
print_GFX_ILI9341.cpp  
yama_2_GFX.h  
yama_2_GFX.cpp  
  
上記ファイルを同じディレクトリに入れてビルドしてください。  
  
CMakeLists.txtでpico-sdkのprintfの出力がUART0になっています。  
USBシリアルに出力したい場合はCMakeLists.txtの最後の方の3行を下記のように変更してください。  
  
    pico_enable_stdio_usb(mandelbrot_set 1)
    pico_enable_stdio_uart(mandelbrot_set 0)
    
    pico_add_extra_outputs(mandelbrot_set)

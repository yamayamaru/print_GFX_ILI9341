# print_GFX_ILI9341
  
print_GFX_ILI9341はRaspberry Pi PicoのC/C++開発ツールのpico-sdk用のグラフィックスライブラリであるyama_2_GFXに簡易的な文字表示機能を付け加えるライブラリです。  
print_GFX_ILI9341を使うためにはyama_2_GFXが必要になります。  
https://github.com/yamayamaru/yama_2_GFX  
プログラム全体がC++で書かれていてC++用のライブラリになります。  
  
print_GFX_ILI9341はMicroPython用のライブラリであるmicropython-ili9341を参考にして作成しました  
https://github.com/jeffmer/micropython-ili9341  
  
print_GFX_ILI9341はyama_2_GFX_ILI9341を継承していて直接ILI9341に文字を描画するためのライブラリです。  
  
print_GFX_GFXcanvas16はyama_2_GFXのGFXcanvas16を継承していてメモリに確保したバッファに文字を描画するためのライブラリです。
  
print_GFX_ILI9341はyama_2_GFX_ILI9341を継承していてyama_2_GFX_ILI9341の全機能が使用できます。  
  
print_GFX_GFXcanvas16はGFXcanvas16を継承していてGFXcanvas16の全機能が使用できます。  
print_GFX_GFXcanvas16に描画しておき、yama_2_GFX_ILI9341やprint_GFX_ILI9341のdrawRGBBitmapでprint_GFX_GFXcanvas16のバッファの内容をLCDに書き込むことでフレームバッファのように扱えます。  

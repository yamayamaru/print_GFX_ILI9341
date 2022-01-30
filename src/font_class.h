// font_class.h
//
//    print_GFX_ILI9341 LCD ILI9341 font print Library (C++)
//                                   https://twitter.com/yama23238
//

#ifndef _FONT_CLASS01_H
#define _FONT_CLASS01_H

class font_class01 {
public:
    font_class01() {}
    virtual int32_t height() {}
    virtual int32_t max_width() {}
    virtual bool hmap() {}
    virtual bool reverse() {}
    virtual bool monospaced() {}
    virtual int32_t min_ch() {}
    virtual int32_t max_ch() {}
    virtual int32_t get_width(const char *str, int32_t size) {}
    virtual void get_ch(char ch, uint8_t **buf) {}
    virtual int32_t get_ch_char_w(char ch) {}
};

#endif // _FONT_CLASS01_H

#ifndef _GLCDFONT_DUMMY_H
#define _GLCDFONT_DUMMY_H

class glcdfont_dummy : public font_class01 {

public:
    glcdfont_dummy() {}
    ~glcdfont_dummy() {}
    int32_t height() {
        return 8;
    }

    int32_t max_width() {
        return 6;
    }

    bool hmap() {
        return false;
    }

    bool reverse() {
        return false;
    }

    bool monospaced() {
        return true;
    }

    int32_t min_ch() {
        return 0;
    }

    int32_t max_ch() {
        return 255;
    }

    int32_t get_width(const char *str, int32_t size) {
        return (strnlen(str, size) * 6);
    }

    int32_t get_ch_char_w(char ch) {
        return 6;
    }

    void get_ch(char ch, uint8_t **buf) {
        for (int i = 0; i < 6; i++) {
            (*buf)[i] = 0xff;
        }
    }
};

#endif  // _GLCDFONT_DUMMY_H
#ifndef __font_h__
#define __font_h__

#include "tool.hpp"
#include "truetype.h"
#include "photo.hpp"

#define wchar s32
#define wchar_to_str(wc) ((char *)(wc))

#define getA(c) ((c>> 0)&0x000000ff)
#define getR(c) ((c>> 8)&0x000000ff)
#define getG(c) ((c>>16)&0x000000ff)
#define getB(c) ((c>>24)&0x000000ff)

#define color u32
#define getColor(a, b, c, d) (a|b<<8|c<<16|d<<24)

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef char s8;
typedef short s16;
typedef int s32;
typedef long long s64;

// typedef struct stbtt_fontinfo
// {
//    void           * userdata;
//    unsigned char  * data;              // pointer to .ttf file
//    int              fontstart;         // offset of start of font
//    int numGlyphs;                     // number of glyphs, needed for range checking
//    int loca,head,glyf,hhea,hmtx,kern; // table locations as offset from start of .ttf
//    int index_map;                     // a cmap mapping for our chosen character encoding
//    int indexToLocFormat;              // format needed to map from glyph index to glyph
// } stbtt_fontinfo;

typedef struct{
	u32 height;
	u32 width;
	u32 byteperpixel;
	u8 *map;
}bitmap;

typedef struct{
	stbtt_fontinfo *info;
	u8 *buffer;
	float scale;
}font;

u32 wstrlen(wchar *ws);
wchar *utf8_to_ucs2(char *code);


// extern int stbtt_InitFont(stbtt_fontinfo *info, const unsigned char *data, int offset);
// // Given an offset into the file that defines a font, this function builds
// // the necessary cached info for the rest of the system. You must allocate
// // the stbtt_fontinfo yourself, and stbtt_InitFont will fill it out. You don't
// // need to do anything special to free it, because the contents are pure
// // value data with no additional data structures. Returns 0 on failure.



// int stbtt_FindGlyphIndex(const stbtt_fontinfo *info, int unicode_codepoint);
// float stbtt_ScaleForPixelHeight(const stbtt_fontinfo *info, float pixels);
// float stbtt_ScaleForMappingEmToPixels(const stbtt_fontinfo *info, float pixels);
// void stbtt_GetFontVMetrics(const stbtt_fontinfo *info, int *ascent, int *descent, int *lineGap);
// void stbtt_GetFontBoundingBox(const stbtt_fontinfo *info, int *x0, int *y0, int *x1, int *y1);
// void stbtt_GetCodepointHMetrics(const stbtt_fontinfo *info, int codepoint, int *advanceWidth, int *leftSideBearing);
// int  stbtt_GetCodepointKernAdvance(const stbtt_fontinfo *info, int ch1, int ch2);
// int stbtt_GetCodepointBox(const stbtt_fontinfo *info, int codepoint, int *x0, int *y0, int *x1, int *y1);
// void stbtt_GetGlyphHMetrics(const stbtt_fontinfo *info, int glyph_index, int *advanceWidth, int *leftSideBearing);
// int  stbtt_GetGlyphKernAdvance(const stbtt_fontinfo *info, int glyph1, int glyph2);
// int  stbtt_GetGlyphBox(const stbtt_fontinfo *info, int glyph_index, int *x0, int *y0, int *x1, int *y1);
// void stbtt_GetCodepointBitmapBox(const stbtt_fontinfo *font, int codepoint, float scale_x, float scale_y, int *ix0, int *iy0, int *ix1, int *iy1);
// void stbtt_GetCodepointBitmapBoxSubpixel(const stbtt_fontinfo *font, int codepoint, float scale_x, float scale_y, float shift_x, float shift_y, int *ix0, int *iy0, int *ix1, int *iy1);
// void stbtt_MakeCodepointBitmap(const stbtt_fontinfo *info, unsigned char *output, int out_w, int out_h, int out_stride, float scale_x, float scale_y, int codepoint);

color getPixel(bitmap *bm, u32 x, u32 y);
void setPixel(bitmap *bm, u32 x, u32 y, color c);

using namespace std;

class Font
{
public:
   Font(){}
   Font(const string &fontPath);
   ~Font();
   //1.初始化字库 
   void fontLoad(const string &fontPath);

   //2.设置字体的大小 
   void fontSetSize(s32 pixels);

   //3.设置字体输出框的大小
   void createBitmap(u32 width, u32 height, u32 byteperpixel);

   //可以指定输出框的颜色
   //参数:u32 width, u32 height宽高,  byteperpixel-一个像素占用字节数, c区域初始化颜色
   void createBitmapWithInit(u32 width, u32 height, u32 byteperpixel, color c);

   //4.把字体输出到输出框中
   //参数 f-字库, screen-绘制文字区域, x, y位置, text要绘制的文字, c文字颜色, maxwidth文字最大宽度默认0自动识别字大小
   void fontPrint(bitmap *screen, s32 x, s32 y, const char *text, color c, s32 maxWidth);
   
   //返回字库的指针
   font *Show_F();

   //返回输出框指针
   bitmap *Show_Bm();

   //贴合输出框和图片对应颜色
   void Fit(int x,int y,BitMap *bmp);

   // 关闭字体库
   void fontUnload();

   // 关闭bitmap
   void destroyBitmap();

protected:
   bitmap * bm;//用来接收背景指针
   font *f;//存储字库指针

};



#endif

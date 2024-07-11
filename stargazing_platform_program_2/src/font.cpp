#include "font.hpp"

using namespace std;
Font::Font(const string &fontPath)
{
	fontLoad(fontPath);
}
Font::~Font()
{
   destroyBitmap();
   fontUnload();
}

void Font::createBitmap(u32 width, u32 height, u32 byteperpixel){
	this->bm = new bitmap[sizeof(bitmap)]();
	this->bm->height = height;
	this->bm->width = width;
	this->bm->byteperpixel = byteperpixel;
	this->bm->map = new u8[width*height*byteperpixel]();
}

void Font:: destroyBitmap(){
	delete []this->bm->map;
	delete []this->bm;
}
bitmap * Font::Show_Bm()
{
	return this->bm;
}

//获取指定位置像素的颜色
color getPixel(bitmap *bm, u32 x, u32 y){
	if(bm->byteperpixel == 3){
		u8 r = *(bm->map + y*bm->width*bm->byteperpixel + x*bm->byteperpixel + 0);
		u8 g = *(bm->map + y*bm->width*bm->byteperpixel + x*bm->byteperpixel + 1);
		u8 b = *(bm->map + y*bm->width*bm->byteperpixel + x*bm->byteperpixel + 2);
		return getColor(0, r, g, b);
	}else if(bm->byteperpixel == 4){
		u8 r = *(bm->map + y*bm->width*bm->byteperpixel + x*bm->byteperpixel + 0);
		u8 g = *(bm->map + y*bm->width*bm->byteperpixel + x*bm->byteperpixel + 1);
		u8 b = *(bm->map + y*bm->width*bm->byteperpixel + x*bm->byteperpixel + 2);
		u8 a = *(bm->map + y*bm->width*bm->byteperpixel + x*bm->byteperpixel + 3);
		return getColor(a, r, g, b);
	}
	return 0;
}

//设置指定位置像素的颜色
void setPixel(bitmap *bm, u32 x, u32 y, color c){
	if(bm->byteperpixel == 3){
		*(bm->map + y*bm->width*bm->byteperpixel + x*bm->byteperpixel + 0) = getR(c);
		*(bm->map + y*bm->width*bm->byteperpixel + x*bm->byteperpixel + 1) = getG(c);
		*(bm->map + y*bm->width*bm->byteperpixel + x*bm->byteperpixel + 2) = getB(c);
	}else if(bm->byteperpixel == 4){
		*(bm->map + y*bm->width*bm->byteperpixel + x*bm->byteperpixel + 0) = getR(c);
		*(bm->map + y*bm->width*bm->byteperpixel + x*bm->byteperpixel + 1) = getG(c);
		*(bm->map + y*bm->width*bm->byteperpixel + x*bm->byteperpixel + 2) = getB(c);
		*(bm->map + y*bm->width*bm->byteperpixel + x*bm->byteperpixel + 3) = getA(c);
	}
}

void Font::createBitmapWithInit(u32 width, u32 height, u32 byteperpixel, color c){
	this->createBitmap(width, height, byteperpixel);
	u32 x, y;
	for(y=0; y<height; y++){
		for(x=0; x<width; x++){
			setPixel(this->bm, x, y, c);
		}
	}
}

u32 wstrlen(wchar *ws){
	u32 len = 0;
	while(*(ws+len)!='\0')
		len++;
	return len;
}


wchar *utf8_to_ucs2(const char *code){
	wchar *ucs2 = (wchar *)malloc((strlen(code)+2)*sizeof(wchar));
	bzero(ucs2, (strlen(code)+2)*sizeof(wchar));
	s16 com = 1<<7;
	u32 x;
	for(x=0; x<=strlen(code); x++){
		char utf = code[x];
		u32 size = 0;
		u32 i = 0;
		u32 index = (utf&com) != 0;
		u16 binary[16];
		if(index == 0){///0xxxxxxx ==> 00000000 0xxxxxxxx
			for(; i < 8; ++i){
				binary[i] = 0;
			}
			for(; i < 16; ++i){
				binary[i] = (utf & 1 << (15 - i)) != 0;
			}
		}else if(utf&(1 << 5) == 0){// 110xxxxx 10yyyyyy ==> 00000xxx xxyyyyyy
			for(; i < 5; ++i){
				binary[i] = 0;
			}
			for(; i < 10; ++i){
				binary[i] = (utf&(1 << (9 - i))) != 0;
			}
			x += 1;
			utf = code[x];
			for(; i < 16; ++i){
				binary[i] = (utf&(1 << (15 - i))) != 0;
			}
		}else{//1110xxxx 10yyyyyy 10zzzzzz ==> xxxxyyyy yyzzzzzz
			for(; i < 4; ++i){
				binary[i] = (utf & 1 << (3 - i)) != 0;
			}
			x += 1;
			utf = code[x];
			for(; i < 10; ++i){
				binary[i] = (utf & 1 << (9 - i)) != 0;
			}
			x += 1;
			utf = code[x];
			for(; i < 16; ++i){
				binary[i] = (utf & 1 << (15 - i)) != 0;
			}
		}
		wchar ch = 0;
		for(i=0; i <16; i++){
			ch <<= 1;
			ch |= binary[i];
		}
		u32 len = wstrlen(ucs2);
		ucs2[len] = ch;
		ucs2[len+1] = 0;
	}
	return ucs2;
}

void Font::fontPrint(bitmap *screen, s32 x, s32 y, const char *text, color c, s32 maxWidth){
	wchar *wText = utf8_to_ucs2(text);
	u8 *charRaster = NULL;
	s32 bx, by, bw, bh;
	s32 ascent, descent, lineGap;
	s32 sx = 0, sy = 0;
	stbtt_GetFontVMetrics(this->f->info, &ascent, &descent, &lineGap);

	ascent *= this->f->scale;
	descent *= this->f->scale;
	lineGap *= this->f->scale;

	u32 i;
	for(i=0; i<wstrlen(wText); i++){
		if(wText[i] == '\n'){
			sy += ascent - descent + lineGap;
			sx = 0;
			continue;
		}

		stbtt_GetCodepointBitmapBox(this->f->info, wText[i], this->f->scale, this->f->scale, &bx, &by, &bw, &bh);

		s32 charWidth = bw - bx;
		s32 charHeight = bh - by;
		s32 oy = ascent + by;

		if(maxWidth > 0 && sx + charWidth > maxWidth) {
			sy += ascent - descent + lineGap;
			sx = 0;
		}

		charRaster = (u8 *)realloc(charRaster, charWidth*charHeight);
		
		stbtt_MakeCodepointBitmap(this->f->info, charRaster, charWidth, charHeight, charWidth, this->f->scale, this->f->scale, wText[i]);


		
		s32 advance;
		stbtt_GetCodepointHMetrics(this->f->info, wText[i], &advance, 0);
		s32 kerning = stbtt_GetCodepointKernAdvance(this->f->info, wText[i], wText[i+1]);
		s32 printLength = advance * this->f->scale + kerning * this->f->scale;
		
		s32 mx;
		for(mx=0; mx<printLength; mx++){
			if(charWidth+mx < printLength-mx){
				continue;
			}
			break;
		}
		
		s32 ix, iy;
		for(iy=0; iy<charHeight; iy++){
			for(ix=0; ix<charWidth; ix++){
				s32 xpos = x + sx + ix + mx;// + (printLength-charWidth)/2;
				s32 ypos = (y + sy + oy + iy) - 1;
				if(charRaster[ix+iy*charWidth]!=0 && xpos<screen->width && ypos<screen->height){
					u32 alpha = charRaster[ix+iy*charWidth];
					u32 invAlpha = 255 - alpha;
					color bgc = getPixel(screen, xpos, ypos);
					u8 bgr = getR(bgc);
					u8 bgg = getG(bgc);
					u8 bgb = getB(bgc);

					u8 r = (alpha * getR(c) + invAlpha * bgr) >> 8;
					u8 g = (alpha * getG(c) + invAlpha * bgg) >> 8;
					u8 b = (alpha * getB(c) + invAlpha * bgb) >> 8;

					setPixel(screen, xpos, ypos, getColor(0, r, g, b));
				}
			}
		}
		
		bzero(charRaster, charWidth*charHeight);
	
		sx += printLength;
	}
	free(charRaster);
	free(wText);
}

void Font::fontSetSize(s32 pixels){
	this->f->scale = stbtt_ScaleForPixelHeight(this->f->info, pixels);
}

void Font::fontLoad(const string &fontPath){
	// 打开字体文件并读取
	s32 fd = open(fontPath.c_str(), O_RDONLY);
	if(fd==-1)
	{
		cerr<<"open ..."<<endl;
		return ;
	}
		
	u32 bufferSize = lseek(fd, 0, SEEK_END);
	u8 *buffer = (u8 *)malloc(bufferSize);
	lseek(fd, 0, SEEK_SET);
	read(fd, buffer, bufferSize);
	close(fd);

	// 从内存读取
	this->f = new font[sizeof(font)]();
	this->f->info = new stbtt_fontinfo[sizeof(stbtt_fontinfo)];
	if(!buffer || bufferSize==0)
	{
		cerr<<"buffer .."<<endl;
		return ;
	}
	if(stbtt_InitFont(this->f->info, buffer, 0) != 1)
		return ;
	this->f->buffer = buffer;
	this->f->scale = stbtt_ScaleForPixelHeight(this->f->info, 16);

}

font *Font::Show_F()
{
	return this->f;
}

void Font::fontUnload(){
    delete []this->f->info;
	delete []this->f->buffer;
	delete []this->f;
}


void Font::Fit(int x, int y, BitMap *bmp)
{
    if (this->bm == nullptr) {
        std::cerr << "bm pointers should not be null!" << std::endl;
        return;
    }
	if (bmp == nullptr) {
        std::cerr << "bmp pointers should not be null!" << std::endl;
        return;
    }

    for(int i = 0; i < this->bm->width; i++)
    {
        for(int j = 0; j < this->bm->height; j++)
        {
            if ((i + x) >= bmp->w || (j + y) >= bmp->h)
			{
				cout<<"地址越界了"<<endl;
                continue;
			}

            *(this->bm->map + j * this->bm->width * this->bm->byteperpixel + i * this->bm->byteperpixel + 0) = *(bmp->data + (j + y) * bmp->w * bmp->bytepix + (i + x) * bmp->bytepix + 0);
            *(this->bm->map + j * this->bm->width * this->bm->byteperpixel + i * this->bm->byteperpixel + 1) = *(bmp->data + (j + y) * bmp->w * bmp->bytepix + (i + x) * bmp->bytepix + 1);
            *(this->bm->map + j * this->bm->width * this->bm->byteperpixel + i * this->bm->byteperpixel + 2) = *(bmp->data + (j + y) * bmp->w * bmp->bytepix + (i + x) * bmp->bytepix + 2);       
        }
    }
}


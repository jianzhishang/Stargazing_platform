#ifndef _PHOTO_
#define _PHOTO_
#include "tool.hpp"

extern "C"
{
    #include "jpeglib.h"
}

using namespace std;

//设计图片结构体
struct BitMap{
    int w, h, bytepix;
    unsigned char *data;
};

struct bitmap_header
{
	int16_t type;
	int32_t size; // 图像文件大小
	int16_t reserved1;
	int16_t reserved2;
	int32_t offbits; // bmp图像数据偏移量

	int32_t tsize;   // 本结构大小	
	int32_t width;  // 图像宽
	int32_t height; // 图像高
	int16_t planes;

	int16_t bit_count; // 色深
	int32_t compression;
	int32_t size_img; // bmp数据大小，必须是4的整数倍
	int32_t X_pel;
	int32_t Y_pel;
	int32_t clrused;
	int32_t clrImportant;
}__attribute__((packed));

class Photo_Resolution
{
public:
    map<string,string> weather;//存储天气名称和天气名称对应图片路径
    Photo_Resolution();
    ~Photo_Resolution();
    //创建一个图片
    void createBitMap(const string &picname);
    //缩放图片
    void zoomBitMap(int w,int h); 
    //图片显示
    struct BitMap *Show_Photo();

    //将天气图片的路径和天气名称的文本数据存储到字典中
	void Storage();
protected:
struct BitMap *bmp;
};

#endif
#ifndef _LCDDEVICE_H
#define _LCDDEVICE_H

#include "tool.hpp"
using namespace std;
//设计lcd结构体

class Lcd
{
public:
    Lcd(){}
    Lcd(const string &lcdname);
    ~Lcd();

    // 绘制一个像素点
    void drawPoint(int x,int y, unsigned int &color);
    // 设置当前缓冲区
    void setCurrentFb(int n); 

    // 在指定的区域绘制图片数据
    void drawBitMap(int x, int y, int w, int h, unsigned char *data);

    //创建Lcd设备
    void createLcd(const string &lcdname);

    //销毁函数
    void destroyLcd(); 

private:
    int fd;//保存lcd设备文件描述符
    int rw, rh; //保存lcd的可见宽和高
    int vw, vh; //保存虚拟区域宽高
    int bytepix; //一个像素占用的字节数
    void* mptr; //保存映射空间的首地址
    void** fbmptr; //保存缓冲区首地址
    int currentfb; //保存当前缓冲区编号
    int fbnumber;//保存缓冲区数量
};





#endif//_LCDDEVICE_H
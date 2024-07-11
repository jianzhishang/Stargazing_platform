#include "lcddevice.hpp"
using namespace std;

Lcd ::Lcd(const string &lcdname)
{
    createLcd(lcdname);
}

Lcd ::~Lcd()
{
    destroyLcd();
}

// 绘制一个像素点
void Lcd::drawPoint(int x, int y, unsigned int &color)
{
    unsigned int *ptr = (unsigned int *)this->mptr;
    ptr[y * this->vw + x] = color;
}
// 设置当前缓冲区
void Lcd::setCurrentFb(int n)
{
    if (n >= this->fbnumber)
        return;
    this->currentfb = n;

    struct fb_var_screeninfo vinfo;                 // 显卡设备的可变属性结构体
    ioctl(this->fd, FBIOGET_VSCREENINFO, &vinfo); // 获取可变属性
    vinfo.xoffset = 0;
    vinfo.yoffset = this->rh * this->currentfb;
    ioctl(this->fd, FBIOPAN_DISPLAY, &vinfo);
}

// 在指定的区域绘制图片数据
void Lcd::drawBitMap(int x,int y, int w, int h, unsigned char *data)
{
    unsigned int *ptr = (unsigned int *)this->mptr + y * this->vw + x;
    // 联合体 把一个3字节的图片像素转换lcd4字节像素
    union color
    {
        unsigned int c;
        unsigned char d[3];
    } cr;
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            // memcpy(cr.d, data+j*3, 3);
            cr.d[0] = data[j * 3 + 2];
            cr.d[1] = data[j * 3 + 1];
            cr.d[2] = data[j * 3 + 0];
            ptr[j] = cr.c;
        }
        ptr += this->vw; // 移动到下一行
        data += w * 3;     // 图片数据移动到下一行
    }
}

// 创建Lcd设备
void Lcd::createLcd(const string &lcdname)
{
    // 初始化
    this->fd = open(lcdname.c_str(), O_RDWR);
    if (this->fd < 0)
    {
        cerr<<"lcdopen..."<<endl;
    }

    // 从驱动获取宽高色深
    struct fb_var_screeninfo vinfo;                 // 显卡设备的可变属性结构体
    ioctl(this->fd, FBIOGET_VSCREENINFO, &vinfo); // 获取可变属性
    this->rw = vinfo.xres;
    this->rh = vinfo.yres;
    this->vw = vinfo.xres_virtual;
    this->vh = vinfo.yres_virtual;
    this->bytepix = vinfo.bits_per_pixel / 8;

    cout<<"rw:"<<this->rw<<","<<"rh:"<<this->rh<<","<<"vw:"<<this->vw<<","<<"vh:"<<this->vh<<endl;
   
    // 映射
    this->mptr = mmap(NULL,
                        this->vw * this->vh * this->bytepix,
                        PROT_READ | PROT_WRITE, MAP_SHARED,
                        this->fd, 0);
    if (this->mptr == MAP_FAILED)
    {
        perror("mmap error");
        goto mmaperror;
    }
    // 计算缓冲区个数
    this->fbnumber = this->vh / this->rh;

    // 根据缓冲区个数申请空间存储每个缓冲区首地址
    this->fbmptr = new void*[sizeof(void *) * this->fbnumber];
    for (int i = 0; i < this->fbnumber; i++)
    {
        this->fbmptr[i] = ((unsigned int *)this->mptr) + this->rw * this->rh * i;
    }

    // 设置当前缓冲区编号为0；
    this->currentfb = 0;

    mmaperror:
        close(this->fd);
        return ;
}

// 销毁函数
void Lcd::destroyLcd()
{
    if (this->mptr != MAP_FAILED)
    {
        // 释放映射
        munmap(this->mptr, this->vw * this->vh * this->bytepix);
    }
    // 释放保存缓冲区首地址
    delete []this->fbmptr;
    // 关闭设备
    close(this->fd);
}



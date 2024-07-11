#ifndef _BUTTON_
#define _BUTTON_

#include "tool.hpp"

class Button
{
public:
   Button();
   ~Button();
   void Run_Get_x_y();//获取触摸屏数据
   int button_fd;//触摸屏文件描述符
   int button_x;//触摸屏x坐标
   int button_y;//触摸屏y坐标
};


#endif 
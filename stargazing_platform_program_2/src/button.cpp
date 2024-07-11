#include "button.hpp"
using namespace std;

Button::Button():button_x(0),button_y(0)
{
    this->button_fd = open("/dev/input/event0",O_RDWR|O_NONBLOCK);
    if(button_fd<0) cerr<<"open ... "<<endl;
}
Button::~Button()
{
    close(button_fd);
}
void Button::Run_Get_x_y()
{
    int ret = 0;
    struct input_event ievt;//读取触摸屏数据

    int x = -1;
    int y = -1;
    while(1)
    {
        read(this->button_fd,&ievt,sizeof(ievt));
        //if(ret<0) break;
        // if(ievt.type == EV_KEY&&ievt.code == BTN_TOUCH &&ievt.value>0)
        // {     
        // }
        if(ievt.type == EV_ABS && ievt.code == ABS_X)
        {
            x = ievt.value*800/1024;
            // this->button_x = ievt.value*800/1024;
            // cout<<"x"<<this->button_x<<endl;
        }
        if(ievt.type == EV_ABS &&ievt.code == ABS_Y)
        {
            y = ievt.value*480/600; 
            // this->button_y = ievt.value*480/600;   
            // cout<<"y"<<this->button_y<<endl;  
        }

        if(ievt.type == EV_KEY && ievt.code == BTN_TOUCH&&ievt.value == 0 )
        {
            if(x !=-1&& y!=-1) 
            {
                this->button_x = x;
                x = -1;
                this->button_y = y;
                y = -1;
                cout<<"x"<<this->button_x<<endl;
                cout<<"y"<<this->button_y<<endl;
                
            }
        }
    }
}

// int main()
// {
//     Button *button = new Button;
//     thread t1(&Button::Run_Get_x_y,button);
//     while(1)
//     {
//         // cout<<button->button_x<<endl;
//         // cout<<button->button_y<<endl;
//         // sleep(1);
//     }
//     return 0;
// }

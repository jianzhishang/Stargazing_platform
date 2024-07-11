#include "scence.hpp"
using namespace std;

#define key key=c7f086cf2b926afdaf99dd0141b93a80&extensions  //key值可以在高德开发平台上申请


Scence::Scence()
{
    // 创建连接服务器的客户端的类，进行服务器信息获取
    HttpSocket *httpsock = new HttpSocket;
    // 存储http域名
    string hostname = "restapi.amap.com";

    // 解析域名，并自动获取ip地址
    httpsock->Getaddrinfo(hostname);

    // 连接服务器
    httpsock->Connect();

    // 判断是否连接成功
    if (httpsock->is_connected())
    {
        // 发送请求，获取服务器天气信息,key值可以在高德开发平台上申请
        httpsock->get("/v3/weather/weatherInfo?city=440100&key&extensions=all");

        // 将来自服务器的天气信息存储到文件中
        httpsock->WeatherFile();
    }
    // 将从文本中获取天气信息并存储到字典容器中
    this->weather_info = httpsock->GetWeather();
    this->province = httpsock->province;
    this->city = httpsock->city;

    delete httpsock;

    // 将天气名称和对应路径存入字典容器中
    Climatic_photo = new Photo_Resolution;
    Climatic_photo->Storage();

    this->lcd = new Lcd("/dev/fb0");    // 开启lcd
    this->address_table = new Location; // 初始化地址检索表

    // 初始化字库
    this->APP = new Font("./simfang.ttf");                 // 显示应用
    this->PROVINCE = new Font("./simfang.ttf");            // 显示省份区域
    this->CITY = new Font("./simfang.ttf");                // 显示城市区域
    this->CURRENT_TEMPERATURE = new Font("./simfang.ttf"); // 显示实时温度
    this->CELSIUS = new Font("./simfang.ttf");             // 摄氏度
    this->CURRENT_CLIMATIC = new Font("./simfang.ttf");    // 实时气象


    // 事件触发信号初始化
    for (int i = 0; i < 4; i++)
    {
        this->sign[i] = false;
    }
}
Scence::~Scence()
{
    delete lcd;
    delete background;
    delete PROVINCE;
    delete CITY;
    delete address_table;
    delete Address_Slection;
    delete Return;
    delete quit;


}
// 进行字显示区域初始化
vector<Font *> Scence::Area(vector<Font *> area, int num)
{
    area.clear();
    while (num--)
    {
        area.push_back(new Font("./simfang.ttf"));

    }
    return area;
}

// 天气信息背景初始化
void Scence::Background_Init()
{
    this->background = new Photo_Resolution;
    this->background->createBitMap("./button-picture/background.jpg");
    this->background->zoomBitMap(800, 480);

    this->background_screen = this->background->Show_Photo();

    this->Return = new Photo_Resolution;
    this->Return->createBitMap("./button-picture/return.jpg");
    this->Return->zoomBitMap(50, 50);

    // 地址选择图片
    this->Address_Slection = new Photo_Resolution;
    this->Address_Slection->createBitMap("./button-picture/address_select.jpg");
    this->Address_Slection->zoomBitMap(50, 50);

    // 退出图片
    this->quit = new Photo_Resolution;
    this->quit->createBitMap("./button-picture/quit.jpg");
    this->quit->zoomBitMap(50, 50);
}

// 天气信息展示
void Scence::Weather_Show()
{
    // 显示日期
    this->DATE = this->Area(this->DATE, 4);

    // 显示周
    this->WEEK = this->Area(this->WEEK, 4);

    // 显示温度
    this->TEMPERATURE = this->Area(this->TEMPERATURE, 4);

    // 显示气象
    this->CLIMATIC = this->Area(this->CLIMATIC, 4);

    // 显示风向
    this->WIND = this->Area(this->WIND, 4);

    // 显示风力
    this->WIND_POWER = this->Area(this->WIND_POWER, 4);

    this->button_x = 0;
    this->button_y = 0;

    this->sign[0] = true;

    // 指定输出框大小
    this->DATE[0]->createBitmap(200, 40, 3);
    this->WEEK[0]->createBitmap(100, 40, 3);
    this->TEMPERATURE[0]->createBitmap(350, 50, 3);
    this->CLIMATIC[0]->createBitmap(350, 50, 3);
    this->WIND[0]->createBitmap(350, 50, 3);
    this->WIND_POWER[0]->createBitmap(350, 50, 3);

    this->CURRENT_TEMPERATURE->createBitmap(120, 60, 3);
    this->CELSIUS->createBitmap(50, 30, 3);
    this->CURRENT_CLIMATIC->createBitmap(150, 30, 3);

    this->PROVINCE->createBitmap(100, 40, 3);
    this->CITY->createBitmap(100, 40, 3);
    for (int i = 1; i < 4; i++)
    {
        this->DATE[i]->createBitmap(150, 50, 3);
        this->WEEK[i]->createBitmap(150, 50, 3);
        this->TEMPERATURE[i]->createBitmap(150, 50, 3);
        this->CLIMATIC[i]->createBitmap(150, 50, 3);
        this->WIND[i]->createBitmap(150, 50, 3);
        this->WIND_POWER[i]->createBitmap(150, 50, 3);
    }

    // 等待后，我们占有锁
    // 将图片数据颜色赋值到输出框中
    this->DATE[0]->Fit(0, 0, this->background_screen);
    this->WEEK[0]->Fit(300, 0, this->background_screen);
    this->TEMPERATURE[0]->Fit(0, 280, this->background_screen);
    this->CLIMATIC[0]->Fit(0, 330, this->background_screen);
    this->WIND[0]->Fit(0, 380, this->background_screen);
    this->WIND_POWER[0]->Fit(0, 430, this->background_screen);

    this->CURRENT_TEMPERATURE->Fit(0, 150, this->background_screen);
    this->CELSIUS->Fit(120, 160, this->background_screen);
    this->CURRENT_CLIMATIC->Fit(120, 190, this->background_screen);

    this->PROVINCE->Fit(500, 0, this->background_screen);
    this->CITY->Fit(700, 0, this->background_screen);

    for (int i = 1, lcd_x = 0; i < 4; i++)
    {
        this->DATE[i]->Fit(350 + lcd_x, 90, this->background_screen);
        this->WEEK[i]->Fit(350 + lcd_x, 40, this->background_screen);
        this->TEMPERATURE[i]->Fit(350 + lcd_x, 280, this->background_screen);
        this->CLIMATIC[i]->Fit(350 + lcd_x, 330, this->background_screen);
        this->WIND[i]->Fit(350 + lcd_x, 380, this->background_screen);
        this->WIND_POWER[i]->Fit(350 + lcd_x, 430, this->background_screen);
        lcd_x += 150;
    }

    // 设置字体大小
    this->DATE[0]->fontSetSize(32);
    this->WEEK[0]->fontSetSize(32);
    this->TEMPERATURE[0]->fontSetSize(20);
    this->CLIMATIC[0]->fontSetSize(20);
    this->WIND[0]->fontSetSize(20);
    this->WIND_POWER[0]->fontSetSize(20);

    this->CURRENT_TEMPERATURE->fontSetSize(70);
    this->CELSIUS->fontSetSize(20);
    this->CURRENT_CLIMATIC->fontSetSize(20);

    this->PROVINCE->fontSetSize(32);
    this->CITY->fontSetSize(32);

    for (int i = 1; i < 4; i++)
    {
        this->DATE[i]->fontSetSize(20);
        this->WEEK[i]->fontSetSize(20);
        this->TEMPERATURE[i]->fontSetSize(20);
        this->CLIMATIC[i]->fontSetSize(20);
        this->WIND[i]->fontSetSize(20);
        this->WIND_POWER[i]->fontSetSize(20);
    }

    // 返回指定区域指针

    this->current_temperature_screen = this->CURRENT_TEMPERATURE->Show_Bm();
    this->celsius_screen = this->CELSIUS->Show_Bm();
    this->current_climatic_screen = this->CURRENT_CLIMATIC->Show_Bm();

    this->province_screen = this->PROVINCE->Show_Bm();
    this->city_screen = this->CITY->Show_Bm();

    for (int i = 0; i < 4; i++)
    {
        this->date_screen[i] = this->DATE[i]->Show_Bm(); // 返回对应的区域指针
        this->week_screen[i] = this->WEEK[i]->Show_Bm();
        this->temperature_screen[i] = this->TEMPERATURE[i]->Show_Bm();
        this->climatic_screen[i] = this->CLIMATIC[i]->Show_Bm();
        this->wind_screen[i] = this->WIND[i]->Show_Bm();
        this->wind_power_screen[i] = this->WIND_POWER[i]->Show_Bm();
    }

    // 初始化输入字体
    for (int i = 0; i < 4; i++)
    {
        temperature[i] = weather_info[i].daytemp + "℃" + "-" + weather_info[i].nighttemp + "℃";
        if (weather_info[i].dayweather == weather_info[i].nightweather)
            climatic[i] = weather_info[i].dayweather;
        else
            climatic[i] = weather_info[i].dayweather + " 转 " + weather_info[i].nightweather;
        if (weather_info[i].daywind == weather_info[i].nightwind)
            wind[i] = weather_info[i].daywind + "风";
        else
            wind[i] = weather_info[i].daywind + "风" + " 转 " + weather_info[i].nightwind + "风";
        if (weather_info[i].daypower == weather_info[i].nightpower)
            wind_power[i] = weather_info[i].daypower + "级";
        else
            wind_power[i] = weather_info[i].daypower + "-" + weather_info[i].nightpower;
    }

    for (int i = 0; i < 3; i++)
    {
        predict_date[i].assign(weather_info[i + 1].data, weather_info[i + 1].data.find("-") + 1, 5);
        predict_week[i] = weather_info[i + 1].week;
    }

    string current_temperature = this->weather_info[0].daytemp;
    string celsius = "℃";
    string current_climatic = this->weather_info[0].dayweather + "（实时）";

    // 将字体输入到输出框中
    this->DATE[0]->fontPrint(this->date_screen[0], 15, 6, this->weather_info[0].data.c_str(), 0xffffffff, 0);
    this->WEEK[0]->fontPrint(this->week_screen[0], 20, 6, this->weather_info[0].week.c_str(), 0xffffffff, 0);
    this->TEMPERATURE[0]->fontPrint(this->temperature_screen[0], 80, 15, this->temperature[0].c_str(), 0xffffffff, 0);
    this->CLIMATIC[0]->fontPrint(this->climatic_screen[0], 80, 15, this->climatic[0].c_str(), 0xffffffff, 0);
    this->WIND[0]->fontPrint(this->wind_screen[0], 80, 15, this->wind[0].c_str(), 0xffffffff, 0);
    this->WIND_POWER[0]->fontPrint(this->wind_power_screen[0], 80, 15, this->wind_power[0].c_str(), 0xffffffff, 0);

    this->CURRENT_TEMPERATURE->fontPrint(this->current_temperature_screen, 40, 0, current_temperature.c_str(), 0xffffffff, 0);
    this->CELSIUS->fontPrint(this->celsius_screen, 0, 0, celsius.c_str(), 0xffffffff, 0);
    this->CURRENT_CLIMATIC->fontPrint(this->current_climatic_screen, 0, 0, current_climatic.c_str(), 0xffffffff, 0);

    this->PROVINCE->fontPrint(this->province_screen, 5, 6, this->province.c_str(), 0xffffffff, 0);
    this->CITY->fontPrint(this->city_screen, 5, 6, this->city.c_str(), 0xffffffff, 0);

    for (int i = 1; i < 4; i++)
    {
        this->TEMPERATURE[i]->fontPrint(temperature_screen[i], 0, 15, this->temperature[i].c_str(), 0xffffffff, 0);
        this->CLIMATIC[i]->fontPrint(climatic_screen[i], 5, 15, this->climatic[i].c_str(), 0xffffffff, 0);
        this->WIND[i]->fontPrint(wind_screen[i], 5, 15, this->wind[i].c_str(), 0xffffffff, 0);
        this->WIND_POWER[i]->fontPrint(wind_power_screen[i], 5, 15, this->wind_power[i].c_str(), 0xffffffff, 0);
    }
    for (int i = 0; i < 3; i++)
    {
        this->DATE[i + 1]->fontPrint(date_screen[i + 1], 5, 10, this->predict_date[i].c_str(), 0xffffffff, 0);
        this->WEEK[i + 1]->fontPrint(week_screen[i + 1], 5, 10, this->predict_week[i].c_str(), 0xffffffff, 0);
    }
    // 返回天气图片
    string weatherPath;

    // 打开退出图片
    this->quit_screen = this->quit->Show_Photo();

    weatherPath = Climatic_photo->weather[weather_info[0].dayweather];
    Climatic_photo->createBitMap(weatherPath);
    Climatic_photo->zoomBitMap(100, 80);
    this->climatic_photo[0] = *Climatic_photo->Show_Photo();

    for (int i = 1; i < 4; i++)
    {
        weatherPath = Climatic_photo->weather[weather_info[i].dayweather];
        Climatic_photo->createBitMap(weatherPath);
        Climatic_photo->zoomBitMap(140, 100);
        this->climatic_photo[i] = *Climatic_photo->Show_Photo();
    }

    // 图像显示
    this->Show_Background();
    this->Show_Current_Time();
    this->Show_Current_Weather();
    this->Show_Predict_Weather(1, 350);
    this->Show_Predict_Weather(2, 500);
    this->Show_Predict_Weather(3, 650);
    this->lcd->drawBitMap(0, 430, this->quit_screen->w, this->quit_screen->h, this->quit_screen->data);
    this->lcd->drawBitMap(0, 370, this->Address_Slection->Show_Photo()->w, this->Address_Slection->Show_Photo()->h, this->Address_Slection->Show_Photo()->data);

    while (this->Event_Sign())
    {
    }

    Destroy(DATE);
    Destroy(WEEK);
    Destroy(TEMPERATURE);
    Destroy(CLIMATIC);
    Destroy(WIND);
    Destroy(WIND_POWER);



}

// 显示背景
void Scence::Show_Background()
{
    this->lcd->setCurrentFb(0);
    this->lcd->drawBitMap(0, 0, this->background_screen->w, this->background_screen->h, this->background_screen->data);
}

// 显示当天的日期、城市
void Scence::Show_Current_Time()
{
    this->lcd->drawBitMap(0, 0, this->date_screen[0]->width, this->date_screen[0]->height, this->date_screen[0]->map);
    this->lcd->drawBitMap(300, 0, this->week_screen[0]->width, this->week_screen[0]->height, this->week_screen[0]->map);
    this->lcd->drawBitMap(500, 0, this->province_screen->width, this->province_screen->height, this->province_screen->map);
    this->lcd->drawBitMap(700, 0, this->city_screen->width, this->city_screen->height, this->city_screen->map);
}
// 显示当天的天气信息
void Scence::Show_Current_Weather()
{

    this->lcd->drawBitMap(90, 50, this->climatic_photo[0].w, this->climatic_photo[0].h, this->climatic_photo[0].data);
    this->lcd->drawBitMap(0, 280, this->temperature_screen[0]->width, this->temperature_screen[0]->height, this->temperature_screen[0]->map);
    this->lcd->drawBitMap(0, 330, this->climatic_screen[0]->width, this->climatic_screen[0]->height, this->climatic_screen[0]->map);
    this->lcd->drawBitMap(0, 380, this->wind_screen[0]->width, this->wind_screen[0]->height, this->wind_screen[0]->map);
    this->lcd->drawBitMap(0, 430, this->wind_power_screen[0]->width, this->wind_power_screen[0]->height, this->wind_power_screen[0]->map);
}

// 显示后三天的天气信息和日期
void Scence::Show_Predict_Weather(int i, int lcd_x)
{

    this->lcd->drawBitMap(lcd_x, 90, this->date_screen[i]->width, this->date_screen[i]->height, this->date_screen[i]->map);
    this->lcd->drawBitMap(lcd_x, 40, this->week_screen[i]->width, this->week_screen[i]->height, this->week_screen[i]->map);
    this->lcd->drawBitMap(lcd_x - 15, 140, this->climatic_photo[i].w, this->climatic_photo[i].h, this->climatic_photo[i].data);
    this->lcd->drawBitMap(lcd_x, 280, this->temperature_screen[i]->width, this->temperature_screen[i]->height, this->temperature_screen[i]->map);
    this->lcd->drawBitMap(lcd_x, 330, this->climatic_screen[i]->width, this->climatic_screen[i]->height, this->climatic_screen[i]->map);
    this->lcd->drawBitMap(lcd_x, 380, this->wind_screen[i]->width, this->wind_screen[i]->height, this->wind_screen[i]->map);
    this->lcd->drawBitMap(lcd_x, 430, this->wind_power_screen[i]->width, this->wind_power_screen[i]->height, this->wind_power_screen[i]->map);
}
void Scence::App_Show()
{
    this->button_x = 0;
    this->button_y = 0;
    this->sign[1] = true;
    // 打开桌面背景图片
    Photo_Resolution *interface = new Photo_Resolution;
    interface->createBitMap("./button-picture/interface.jpg");
    interface->zoomBitMap(800, 480);
    BitMap interface_screen = *(interface->Show_Photo());

    // 打开应用图片
    interface->createBitMap("./button-picture/stargazing_platform.jpg");

    // 缩放图片
    interface->zoomBitMap(80, 80);
    BitMap app = *(interface->Show_Photo());

    // 应用名称
    this->APP->createBitmap(60, 60, 3);

    // 位置填充
    this->APP->Fit(15, 90, &interface_screen);
    bitmap *app_screen = this->APP->Show_Bm();
    // 设置字大小
    this->APP->fontSetSize(20);

    string app_name = "观星台";

    // 将字写入区域中
    this->APP->fontPrint(app_screen, 4, 4, app_name.c_str(), 0x00000000, 0);

    // 显示图片
    this->lcd->drawBitMap(0, 0, interface_screen.w, interface_screen.h, interface_screen.data);
    this->lcd->drawBitMap(10, 10, app.w, app.h, app.data);
    this->lcd->drawBitMap(15, 90, app_screen->width, app_screen->height, app_screen->map);

    // 退出判断
    while (this->Event_Sign())
    {
        // if ((this->button_x > 0 && this->button_x <= 150) && (this->button_y > 0 && this->button_y <= 150))
        // {
        //     this->flag = 1;

        //     break;
        // }
        // if(this->Event_Sign()) break;
    }
    delete interface;
    // this->flag = 0;
}

void Scence::Re_Gethttp(string City)
{
    this->button_x = 0;
    this->button_y = 0;
    // 创建连接服务器的客户端的类，进行服务器信息获取
    HttpSocket *httpsock = new HttpSocket;
    // 存储http域名
    string hostname = "restapi.amap.com";

    // 解析域名，并自动获取ip地址
    httpsock->Getaddrinfo(hostname);

    // 连接服务器
    httpsock->Connect();

    // 判断是否连接成功
    if (httpsock->is_connected())
    {
        // 发送请求，获取服务器天气信息
        httpsock->get("/v3/weather/weatherInfo?city=" + City + "&key=c7f086cf2b926afdaf99dd0141b93a80&extensions=all");

        // 将来自服务器的天气信息存储到文件中
        httpsock->WeatherFile();
    }
    // 将从文本中获取天气信息并存储到字典容器中
    this->weather_info = httpsock->GetWeather();
    this->province = httpsock->province;
    this->city = httpsock->city;

    delete httpsock;
}

// 显示可以查看天气的省份
void Scence::Province_Show()
{
    // 显示省份
    this->PROVINCE_TABLE = this->Area(this->PROVINCE_TABLE, this->address_table->Province_Sum());

    this->button_x = 0;
    this->button_y = 0;
    touch_province.clear();
    this->sign[2] = true;
    // 设置省份显示的区域大小
    for (int i = 0; i < this->address_table->Province_Sum(); i++)
    {
        this->PROVINCE_TABLE[i]->createBitmapWithInit(90, 60, 3, 0x80808080);
    }

    // 设置字体大小
    for (int i = 0; i < this->address_table->Province_Sum(); i++)
    {
        this->PROVINCE_TABLE[i]->fontSetSize(20);
    }

    // 将字体放入框中
    auto it = this->address_table->address_correspondence.begin();
    for (int i = 0; i < this->address_table->Province_Sum(); i++)
    {
        this->PROVINCE_TABLE[i]->fontPrint(this->PROVINCE_TABLE[i]->Show_Bm(), 15, 15, it->first.c_str(), 0xffffffff, 0);
        this->touch_province.push_back(it->first);
        it++;
    }

    this->lcd->drawBitMap(0, 0, this->background_screen->w, this->background_screen->h, this->background_screen->data);
    this->lcd->drawBitMap(0, 0, this->Return->Show_Photo()->w, this->Return->Show_Photo()->h, this->Return->Show_Photo()->data);

    // 省份显示
    for (int i = 0, lcd_x = 100, lcd_y = 10, num = 1; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            this->lcd->drawBitMap(lcd_x, lcd_y, this->PROVINCE_TABLE[num - 1]->Show_Bm()->width, this->PROVINCE_TABLE[num - 1]->Show_Bm()->height, this->PROVINCE_TABLE[num - 1]->Show_Bm()->map);
            lcd_x += 100;
            num++;
            if (num == this->address_table->Province_Sum())
                break;
        }
        lcd_x = 100;
        lcd_y += 80;
        if (num == this->address_table->Province_Sum())
                break;
    }
        this->Destroy(PROVINCE_TABLE);

    string temp_province;
    while (this->sign[2])
    {
        // 返回当前地址天气显示界面
        if ((this->button_x > 0 && this->button_x <= 80) && (this->button_y > 0 && this->button_y <= 80))
        {
            thread t4(&Scence::Weather_Show, this);
            t4.detach();
            this->sign[2] = false;
        }
        if ((this->button_x >= 100 && this->button_x <= 700) && (this->button_y > 0 && this->button_y <= 480))
        {
            for (int i = 0, lcd_x = 100, lcd_y = 10,num = 0; i < 6; i++)
            {
                for (int j = 0; j < 6; j++)
                {
    
                    if ((this->button_x > lcd_x && this->button_x < (lcd_x + 100)) && (this->button_y > lcd_y && this->button_y < (lcd_y + 80)))
                    {
                        
                        temp_province = this->touch_province[num];
                        thread t5([this, temp_province]()
                                    { City_Show(temp_province); });
                        t5.detach();

                        this->sign[2] = false;
                    }
                    num++;
                    lcd_x += 100;
                    if(num==this->address_table->Province_Sum()-1) break;
                }
                lcd_x = 100;
                lcd_y += 80;
                if(num==this->address_table->Province_Sum()-1) break;
            }
        }
    }

    
}

// 显示可以查看的城市
void Scence::City_Show(string sort_province)
{
    this->button_x = 0;
    this->button_y = 0;


    touch_city.clear();
    this->sign[3] = true;
    vector<Font *> CITY_TABLE;  

    CITY_TABLE = this->Area(CITY_TABLE, this->address_table->City_Sum(sort_province)); 

    // 设置省份显示的区域大小
    for (int i = 0; i < this->address_table->City_Sum(sort_province); i++)
    {
        CITY_TABLE[i]->createBitmapWithInit(90, 60, 3, 0x80808080);
    }

    // 设置字体大小
    for (int i = 0; i < this->address_table->City_Sum(sort_province); i++)
    {
        CITY_TABLE[i]->fontSetSize(15);
    }




    // 将字体放入框中
    auto city_map = this->address_table->address_correspondence.find(sort_province);
    auto it = city_map->second.begin();

    for (int i = 0; i < this->address_table->City_Sum(sort_province); i++)
    {
        CITY_TABLE[i]->fontPrint(CITY_TABLE[i]->Show_Bm(), 15, 15, it->first.c_str(), 0xffffffff, 0);
        this->touch_city.push_back(it->first);
        cout<<touch_city[0]<<endl;
        it++;
    }

    this->lcd->drawBitMap(0, 0, this->background_screen->w, this->background_screen->h, this->background_screen->data);
    this->lcd->drawBitMap(0, 0, this->Return->Show_Photo()->w, this->Return->Show_Photo()->h, this->Return->Show_Photo()->data);


    // 城市显示
    for (int i = 0, lcd_x = 100, lcd_y = 10, num = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            this->lcd->drawBitMap(lcd_x, lcd_y, CITY_TABLE[num ]->Show_Bm()->width, CITY_TABLE[num ]->Show_Bm()->height, CITY_TABLE[num ]->Show_Bm()->map);                
            lcd_x += 100;
            num++;
            if (num == this->address_table->City_Sum(sort_province))
            {
                break;
            }
            cout<<num<<endl;
        }
        lcd_x = 100;
        lcd_y += 80;

        if (num == this->address_table->City_Sum(sort_province))
        {
            break;
        }
    }
    this->Destroy(CITY_TABLE);

    while (this->sign[3])
    {
            // 返回省份选择界面
        if ((this->button_x > 0 && this->button_x <= 80) && (this->button_y > 0 && this->button_y <= 80))
        {
            //this->sign[3] = false;
            thread t6(&Scence::Province_Show, this);
            t6.detach();
            this->sign[3] = false;
        }
        if ((this->button_x >= 100 && this->button_x <= 700) && (this->button_y > 0 && this->button_y <= 480))
        {


            for (int i = 0, lcd_x = 100, lcd_y = 10,num = 0; i < 6; i++)
            {
                for (int j = 0; j < 6; j++)
                {
                            
                    if ((this->button_x > lcd_x && this->button_x < (lcd_x + 100)) && (this->button_y > lcd_y && this->button_y < (lcd_y + 80)))
                    {
            
                        string temp_city_code = this->address_table->City_Sort(sort_province,this->touch_city[num]);
                        this->Re_Gethttp(temp_city_code);
                        thread t7(&Scence::Weather_Show, this);
                        t7.detach();
                        this->button_x = 0;
                        this->button_y = 0; 
                        this->sign[3] = false;;
                    }
                    lcd_x += 100;
                    num++;
                    if (num == this->address_table->City_Sum(sort_province)-1)
                    {
                        break;
                    }
                }
                lcd_x = 100;
                lcd_y += 80;
            
                if (num == this->address_table->City_Sum(sort_province)-1)
                {
                    break;
                }
            }
        }
    }

}

// 触发线程切换信号事件
bool Scence::Event_Sign()
{
    string temp_province; // 存储临时省份
    // 判断是否退出天气显示界面
    if (this->sign[0])
    {
        // 退出天气显示
        if ((this->button_x > 0 && this->button_x <= 50) && (this->button_y <= 480 && this->button_y >= 430))
        {
            this->sign[0] = false;
            thread t1(&Scence::App_Show, this);
            t1.detach();
            return this->sign[0];
        }
        // 选择其他地址天气
        if ((this->button_x > 0 && this->button_x <= 50) && (this->button_y <= 420 && this->button_y >= 370))
        {
            this->sign[0] = false;
            thread t2(&Scence::Province_Show, this);
            t2.detach();
            return this->sign[0];
        }
    }

    // 判断是否进入应用
    if (this->sign[1])
    {
        // 进入应用
        if ((this->button_x > 0 && this->button_x <= 150) && (this->button_y > 0 && this->button_y <= 150))
        {
            this->sign[1] = false;
            thread t3(&Scence::Weather_Show, this);
            t3.detach();
            return this->sign[1];
        }
    }

}
// 程序运行
void Scence::Run()
{
    thread t1(&Button::Run_Get_x_y, this);
    t1.detach();
    this->Background_Init();
    this->App_Show();
    while (1)
        ;
}
void Scence::Destroy(vector<Font *> TEMP)
{
    for (Font *font : TEMP)
    {
        delete font;
    }
}


#include "http.hpp"
#include "photo.hpp"
#include "tool.hpp"
#include "lcddevice.hpp"
#include "font.hpp"
#include "button.hpp"
#include "location.hpp"

using namespace std;


class Scence : public Button
{
public:
    Scence();
    ~Scence();
    // 进行字显示区域初始化
    vector<Font *> Area(vector<Font *> area, int num);

    // 天气信息背景初始化
    void Background_Init();

    // 天气信息展示
    void Weather_Show();

    // 显示背景
    void Show_Background();

    // 显示当天的日期、城市
    void Show_Current_Time();

    // 显示当天的天气信息
    void Show_Current_Weather();

    // 显示后三天的天气信息和日期
    void Show_Predict_Weather(int i, int lcd_x);

    //进行app显示
    void App_Show();
    
    //重新获取天气信息
    void Re_Gethttp(string City);

    // 显示可以查看天气的省份
    void Province_Show();

    // 显示可以查看的城市
    void City_Show(string sort_province);

    // 触发线程切换信号事件
    bool Event_Sign();

    // 程序运行
    void Run();

    //进行字库区域资源回收
    void Destroy(vector<Font *> TEMP);

private:
    Photo_Resolution *background;       // 显示背景
    Photo_Resolution *Climatic_photo;   // 气象图片
    Lcd *lcd;                           // 显示lcd
    Location *address_table;            // 存储地址对应表
    Photo_Resolution *Return;           // 返回图片
    Photo_Resolution *Address_Slection; // 地址选择图片
    Photo_Resolution *quit;             // 打开退出图片

    vector<Font *> DATE;           // 显示日期字库
    vector<Font *> WEEK;           // 显示周字库
    vector<Font *> PROVINCE_TABLE; // 显示省份
    Font *APP;                     // 显示应用
    Font *PROVINCE;                // 显示省份字库
    Font *CITY;                    // 显示城市字库
    Font *CURRENT_TEMPERATURE;     // 实时温度
    Font *CELSIUS;                 // 摄氏度
    Font *CURRENT_CLIMATIC;        // 实时气象
    map<int, WI> weather_info;     // 天气信息
    string province;               // 省份
    string city;                   // 城市
    BitMap *background_screen;     // 背景指针
    vector<Font *> TEMPERATURE;    // 温度
    vector<Font *> CLIMATIC;       // 气象
    vector<Font *> WIND;           // 风向
    vector<Font *> WIND_POWER;     // 风力
    string temperature[4];         // 温度
    string wind[4];                // 风向
    string climatic[4];            // 气象
    string wind_power[4];          // 风力
    string predict_date[3];        // 预测天气
    string predict_week[3];        // 预测周

    bool sign[4]; // 进行线程间的切换信号

    // 返回指定区域指针
    bitmap *date_screen[4];
    bitmap *week_screen[4];
    bitmap *temperature_screen[4];
    bitmap *climatic_screen[4];
    bitmap *wind_screen[4];
    bitmap *wind_power_screen[4];
    bitmap *current_temperature_screen;
    bitmap *celsius_screen;
    bitmap *current_climatic_screen;
    bitmap *province_screen;
    bitmap *city_screen;

    BitMap *quit_screen;
    BitMap climatic_photo[4];

    vector<string> touch_province;     //查询身份
    vector<string> touch_city;         //查询城市
};

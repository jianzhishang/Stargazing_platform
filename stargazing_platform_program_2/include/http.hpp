#ifndef _HTTP_
#define _HTTP_

#include "json.hpp"
#include "tool.hpp"

using namespace std;
#define _WEATHER_INFO_ "./configure-text/weather_data.txt"

typedef struct WeatherInfo
{
    string data;//日期
    string week;//星期
    string dayweather;//白天天气气象
    string nightweather;//晚上天气气象
    string daytemp;//白天温度
    string nighttemp;//晚上温度
    string daywind;//白天风向
    string nightwind;//晚上风向
    string daypower;//白天风力
    string nightpower;//晚上风力
}WI;

class HttpSocket
{
    public:
    //构造函数创建对象时，顺便创建套接字
    HttpSocket();
    ~HttpSocket();
    //自动获取地址信息链表
    void Getaddrinfo(string hostname);
    //连接服务器
    void Connect();
    //http发送请求函数
    void get(string url);
    //打开文件以写入响应数据
    void WeatherFile();
    bool is_connected()const;//要求函数数据不改变
    //读取天气数据并进行解析存储到字典容器中
    map<int,WI> GetWeather();
    
protected:
    struct addrinfo *res;//存储地址信息链表
    struct addrinfo *p;//存储临时地址信息链表
    int sockfd;//创建套接字
    string ip;//存储ip地址
    string port;//存储端口号
    bool isOpen;//存储当前开启状态
    bool isConnected;//存储当前连接状态
    map<int,WI> weather_info;//存储四天天气信息

public:
    string province;
    string city;


};

#endif
#include "http.hpp"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

//构造函数创建对象时，顺便创建套接字
HttpSocket::HttpSocket():port("80")
{
    this->isConnected = false;//标志是否连接状态
    this->isOpen = false;//标志是否开启状态
    this->sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(this->sockfd < 0)
    {
        cout<<"socket erro"<<endl;
    }else isOpen = true;
}
HttpSocket::~HttpSocket()
{
    close(this->sockfd);
}
     
//自动获取地址信息链表
 void HttpSocket:: Getaddrinfo(string hostname)
    {
        struct addrinfo hints;//存储地址信息
        memset(&hints,0,sizeof(hints));
        hints.ai_family = AF_UNSPEC;//不限定IPV4或IPV6
        hints.ai_socktype = SOCK_STREAM;//TCP传输协议

        //获取地址信息
        int status = getaddrinfo(hostname.c_str(),this->port.c_str(),&hints,&this->res);
        if(status !=0)
        {
            cerr << "getaddrinf:"<<gai_strerror(status)<<endl;
        }     
    }
//连接服务器
void HttpSocket::Connect()
    {
        //遍历结果列表并进行连接
        for(this->p = this->res;this->p != NULL; this->p = this->p->ai_next)
        {
            if((this->sockfd = socket(this->p->ai_family,this->p->ai_socktype, this->p->ai_protocol)) == -1)
            {
                cerr<<"socket"<<endl;
                continue;
            }
            if(connect(sockfd,this->p->ai_addr,this->p->ai_addrlen) == -1)
            {
                cerr<<"connect"<<endl;
                close(sockfd);
                continue;
            }
            break;//成功连接
        }
        if(this->p == 0)
        {
            cerr<<"Failed to connect"<< endl;
        }
        else
        {
            isConnected = true;//表明连接成功
        }

        freeaddrinfo(res);//释放地址信息链表

    }
    
//http发送请求函数
void HttpSocket::get(string url)
    {
        char buffer[1024] = {0};//存储信息缓存区
        sprintf(buffer, "GET %s HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", url.c_str(), "restapi.amap.com");//将http请求标注信息格式进行拼接并存储再buffer中
        int ret = write(this->sockfd,buffer,strlen(buffer));
    }

//打开文件以写入响应数据
void HttpSocket::WeatherFile()
    {
        ofstream outfile(_WEATHER_INFO_);
        if(!outfile.is_open())
        {
            cerr << "Eroor opening file for writing"<<endl;
            close(sockfd);
        }
        char buffer[4096];
        ssize_t bytes_received;
        while((bytes_received = recv(this->sockfd,buffer,sizeof(buffer) - 1, 0)) > 0)
        {
            buffer[bytes_received] = '\0';
            outfile<<buffer;//缓存区输入到文件描述符中
        }

        if(bytes_received == -1 )
        {
            cerr<<"recv"<<endl;
        }

        outfile.close();
    }
    
// //读取请求获取的数据
    // void Read(char *buffer,int size)
    // {
    //     read(this->sockfd,buffer,size);
    // }

bool HttpSocket::is_connected()const//要求函数数据不改变
{
    return isConnected;
}

//读取天气数据并进行解析存储到字典容器中
map<int,WI> HttpSocket::GetWeather()
{
    ifstream infile(_WEATHER_INFO_);
    int day=0;
    weather_info.clear();
    if(!infile.is_open())
    {
        cerr << "Eroor opening file for outing";
    }
    char buffer[4096];
    while(1)
    {
        infile.getline(buffer,sizeof(buffer));
        if(buffer[0] == '{') break;
    }

    json obj = json::parse(string(buffer));

    //这是c++中引入的范围内遍历，它用于遍历一个容器或范围。在这种情况下，'obj["forecasts"]'是一个JSON数组，'for(const auto& forecast:obj["forecast"])'循环将遍历数组中的每一个JSON元素
    /*
    const:表示循环变量forecast是一个常量，不能被修改，这保证了在循环体内不会意外修改元素的值
    auto:编译器会自动推断forecast的类型，对于nlohmann::json库
    obj["forecasts"]的元素类型是json对象，所以forecast的类型是json
    &：表示forecast是一个引用，避免在每次迭代时复制元素，提高效率。

    obj["forecasts"]:
    obj 是一个json对象，obj["forecast"]是该对象的一个键，值是有一个JSON数组
    */

    ////提取四天天数据存储到容器中
    for(const auto&forecast : obj["forecasts"])
    {
        this->province = forecast["province"];
        this->city     = forecast["city"];
        for(const auto&cast : forecast["casts"])
        {
            weather_info[day] = {cast["date"],cast["week"],cast["dayweather"],cast["nightweather"],
                                    cast["daytemp"],cast["nighttemp"],cast["daywind"],
                                    cast["nightwind"],cast["daypower"],cast["nightpower"]};
            day++;
        }
    }
    infile.close();
    string temp1[7] = {"1","2","3","4","5","6","7"};
    string temp2[7] = {"周一","周二","周三","周四","周五","周六","周日"};
    for(int n=0;n<4;n++)
    {
        for(int i=0;i<7;i++)
        {
            if(this->weather_info[n].week == temp1[i])
            {
                this->weather_info[n].week = temp2[i];
            }
        }
    }

    this->province += "省";

    return weather_info;
}


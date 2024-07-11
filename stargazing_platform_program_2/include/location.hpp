#pragma once

#include "json.hpp"
#include "tool.hpp"

using namespace std;

class Location
{
    public:
    Location();
    ~Location();

    map<string,map<string,string>> address_correspondence;//省份对应表

    string City_Sort(string province,string city);//查找对应城市编码
    //解析地址代码文件存入字典中
    void Address_correspondence();
    //返回省份数
    int Province_Sum();
    //返回城市数
    int City_Sum(string province);
};
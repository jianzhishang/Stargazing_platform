#include "location.hpp"

using namespace std;
using json = nlohmann::json;

Location::Location()
{
    Address_correspondence();
}
Location::~Location(){}

void Location::Address_correspondence()
{
    ifstream infile("./configure-text/city_acode.txt");
    address_correspondence.clear();
    if(!infile.is_open())
    {
        cerr<<"open ... ";
    }

    //读取文件内容到字符串
    string buffer((istreambuf_iterator<char>(infile)),istreambuf_iterator<char>());

    // cout<<buffer<<endl;
    
    //JSON格式解析
    json address = json::parse(buffer);

    for (const auto& acode : address) {
        std::string province = acode["provice"];

        //contains判断是否存在该键值，is_array判断是否存在数组
        if (acode.contains("city") && acode["city"].is_array()) {
            for (const auto& city : acode["city"]) {
                if (city.contains("name") && city.contains("adcode")) {
                    std::string city_name = city["name"];
                    std::string city_adcode = city["adcode"];
                    address_correspondence[province].insert({city_name, city_adcode});//插入字典键值
                } else {
                    //std::cerr << "Error: 'name' or 'acode' field missing for city in province " << province << std::endl;
                    continue; // 跳过当前城市的处理
                }
    
            }
        } else {
            std::cerr << "Error: 'city' field is not an array or missing for province " << province << std::endl;
            continue; // 跳过当前省份的处理
        }
    }

}

string Location::City_Sort(string province,string city)
{
    string result;
    auto it = address_correspondence.find(province);
    auto it2 = it->second.find(city);
    result = it2->second;
    return result;
    
}

//返回省份数
int Location::Province_Sum()
{
    return this->address_correspondence.size();
}

//返回对应省份的城市数
int Location::City_Sum(string province)
{
    int count=0;
    auto it = address_correspondence.find(province);
    count = it->second.size();
    return count;
}


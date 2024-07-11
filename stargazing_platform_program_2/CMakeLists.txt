cmake_minimum_required(VERSION 3.5)

# 设置编译器和编译选项
set(CMAKE_CXX_COMPILER arm-linux-g++)
set(CMAKE_CXX_STANDARD 11) # 使用标准方法指定C++11
set(CMAKE_CXX_STANDARD_REQUIRED ON) # 强制要求使用指定的C++标准
set(CMAKE_CXX_EXTENSIONS OFF) # 禁用GNU扩展

# 指定项目名称和支持的语言
project(Stargazing_platform LANGUAGES CXX C)

# 指定头文件路径
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/jpeg-arm/include)


# 添加子目录
add_subdirectory(src)


# 指定可执行文件
add_executable(Stargazing_platform main.cpp scence.cpp)

# 可执行文件链接lib库
target_link_libraries(Stargazing_platform font button http location photo lcddevice pthread)

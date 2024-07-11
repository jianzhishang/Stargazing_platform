cmake_minimum_required(VERSION 3.5) #指定cmake最低版本

# 设置编译选项
set(CMAKE_CXX_COMPILER arm-linux-g++)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#include_directories(${PROJECT_SOURCE_DIR}/jpeg-arm/include)
# 指定头文件路径${CMAKE_SOURCE_DIR}表示顶级源目录
#include_directories(${CMAKE_SOURCE_DIR}/include)
#include_directories(${CMAKE_SOURCE_DIR}/jpeg-arm/include)

# 查找 libjpeg 库
#find_library(JPEG_LIB jpeg PATHS ${CMAKE_SOURCE_DIR}/jpeg-arm/lib REQUIRED)


# 如果需要，也可以指定包含目录
# find_path(JPEG_INCLUDE_DIR jpeglib.h)

# 包含 libjpeg 的头文件路径（如果需要）
# include_directories(${JPEG_INCLUDE_DIR})

# 添加库文件路径（使用绝对路径）
set(JPEG_LIB_PATH /mnt/hgfs/gongxiang/code/myproject/Stargazing_Platform/stargazing_platform_program/jpeg-arm/lib)

add_library(font font.cpp truetype.cpp) #添加库文件
add_library(button button.cpp) #添加库文件
add_library(http http.cpp)
add_library(location location.cpp)
add_library(photo photo.cpp)
add_library(lcddevice lcddevice.cpp)

# 链接库文件到 photo 库
target_link_libraries(photo ${JPEG_LIB_PATH}/libjpeg.so)#因为photo动态库中包含libjpeg.so的动态库，因此需要进行链接

# 链接 libjpeg 库到 photo 库
#target_link_libraries(photo ${JPEG_LIB})

# 如果使用静态库
# target_link_libraries(photo ${JPEG_LIB_PATH}/libjpeg.a)
#如果需要链接多个库，可以这样做：
#target_link_libraries(photo ${JPEG_LIB_PATH}/libjpeg.so ${OTHER_LIB_PATH}/libother.so)

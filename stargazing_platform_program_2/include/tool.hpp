#ifndef _TOOL_
#define _TOOL_

#include <iostream>
#include <cstring>
#include <cstdio>
#include <memory>
#include <cstdlib>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <chrono>
#include <iostream>
#include <thread>
#include <utility>
#include <mutex>
#include <condition_variable>

extern "C"
{
    #include <unistd.h>
    #include <netdb.h>
    #include <arpa/inet.h>
    #include <sys/socket.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <sys/mman.h>
    #include <linux/fb.h>
    #include <sys/ioctl.h>
    #include <string.h>
    #include <pthread.h>
    #include <linux/input.h> // 系统定义输入设备操作的API
    #include <stdbool.h>
    #include <errno.h>
    //#include "json.hpp"
    
}
#endif

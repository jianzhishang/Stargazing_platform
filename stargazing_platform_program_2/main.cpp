#include "scence.hpp"
using namespace std;

int main(void)
{
    //创建场景类对象
    Scence *scence = new Scence;
    //运行场景类
    scence->Run();

    while (1);

    delete scence;

    return 0;
}

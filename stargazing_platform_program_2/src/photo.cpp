#include "photo.hpp"


using namespace std;

Photo_Resolution::Photo_Resolution()
{
    bmp = new struct BitMap;//初始化一个bmp图片
}
Photo_Resolution::~Photo_Resolution()
{
    delete []bmp->data;
    delete bmp;
}
//创建一个图片
void Photo_Resolution::createBitMap(const string &picname)
{
    int flag = 0;
    if(picname.find(".jpg")||picname.find(".jpeg"))
    {
        flag = 1;
    }
    else if(picname.find(".bmp")||picname.find(".BMP"))
    {
        flag = 2;
    }//辨认是BMP还是jpg图片
    if(flag == 1)
    {
        struct jpeg_decompress_struct cinfo;
        struct jpeg_error_mgr mgr;

        FILE * infile; /* 源文件 */
        if ((infile = fopen(picname.c_str(), "rb")) == NULL) {
            fprintf(stderr, "can't open %s\n", picname.c_str());
        }

        /* 步骤 1：分配并初始化 JPEG 解压缩对象 */
        cinfo.err = jpeg_std_error(&mgr);

        /* 现在我们可以初始化 JPEG 解压缩对象。*/
        jpeg_create_decompress(&cinfo);
        /* 第二步：指定数据源（例如文件） */
        jpeg_stdio_src(&cinfo, infile);
        /* 第 3 步：使用 jpeg_read_header() 读取文件参数 */
        jpeg_read_header(&cinfo, TRUE);

        /* 第 4 步：设置解压缩参数 */
        /* 第 5 步：启动解压程序 */
        jpeg_start_decompress(&cinfo);



        //计算一行像素占用的字节数
        int row_stride = cinfo.output_width * cinfo.output_components;
        /* 制作一个单行高的采样数组，处理完图像后就会消失 */
        unsigned char *buffer = new unsigned char[row_stride];

        //图片结构体信息 w, h, bytepix
        bmp->w = cinfo.output_width;
        bmp->h = cinfo.output_height;
        bmp->bytepix = cinfo.output_components;
        bmp->data = new unsigned char [row_stride*bmp->h];


        /* 第 6 步：循环解压一行一行解*/
        while (cinfo.output_scanline < cinfo.output_height) {
            jpeg_read_scanlines(&cinfo, &buffer, 1);
            //拷贝一行到data中
            memcpy(bmp->data+row_stride*(cinfo.output_scanline-1), buffer, row_stride);
        }
        delete []buffer;

        /* 第 7 步：完成解压缩 */
        jpeg_finish_decompress(&cinfo);

        /* 第 8 步：释放 JPEG 解压缩对象 */
        jpeg_destroy_decompress(&cinfo);

        fclose(infile);
    }else if(flag == 2)
    {
        //打开图片
        FILE *file = fopen(picname.c_str(), "r");
        if(file == NULL) cerr<<"fopen ..."<<endl;

        //读取图片头
        struct bitmap_header header;
        size_t ret = fread(&header, 54, 1, file);
        if(ret < 0) 
        {
            fclose(file);

        }
        //初始化
        
        bmp->w = header.width;
        bmp->h = header.height;
        bmp->bytepix = header.bit_count/8;

        //申请存储像素数据的空间
        bmp->data = new unsigned char[bmp->w*bmp->h*bmp->bytepix];
        //定义一行像素占用的空间（包含填充字节）;
        int pad = ((4-( bmp->w * bmp->bytepix ) % 4)) % 4;
        unsigned char linebuffer[bmp->w*bmp->bytepix+pad];
        
        //一行一行的读取图片数据
        for(int i=0; i<bmp->h; i++){
            fread(linebuffer, sizeof(linebuffer), 1, file);
            memcpy(bmp->data+i*(bmp->w*bmp->bytepix), linebuffer,bmp->w*bmp->bytepix);
        }

        //把像素调换rgb--》bgr
        unsigned char *tptr = bmp->data;
        for(int i=0; i<bmp->h*bmp->w; i++){
            unsigned char t=tptr[0];
            tptr[0] =tptr[2]  ;
            tptr[2] = t;
            tptr += 3;
        }

        //按行调换
        for(int i=0; i<bmp->h/2; i++)
        {
            memcpy(linebuffer, bmp->data+i*bmp->w*bmp->bytepix, bmp->w*bmp->bytepix);
            memcpy(bmp->data+i*bmp->w*bmp->bytepix, bmp->data+((bmp->h-1-i)*bmp->w*bmp->bytepix), bmp->w*bmp->bytepix);
            memcpy(bmp->data+((bmp->h-1-i)*bmp->w*bmp->bytepix), linebuffer, bmp->w*bmp->bytepix);
        }


        fclose(file);

        
    }
}

//缩放图片
void Photo_Resolution::zoomBitMap(int w,int h)
{
    if(bmp == (struct BitMap *)nullptr) return;

    //定义存储缩放后的数据空间
    unsigned char *data = new unsigned char[w*h*bmp->bytepix];

    //宽比例，高比例
    int dx = 100*bmp->w/w;
    int dy = 100*bmp->h/h;

    //按照比例从原图中提取数据存储到目标data中
    for(int i = 0;i<h;i++)
    {
        for(int j = 0;j<w;j++)
        {
            data[j*3+0+i*w*3] = bmp->data[(dx*j)/100*3+0+(dy*i)/100*bmp->w*3];
            data[j*3+1+i*w*3] = bmp->data[(dx*j)/100*3+1+(dy*i)/100*bmp->w*3];
            data[j*3+2+i*w*3] = bmp->data[(dx*j)/100*3+2+(dy*i)/100*bmp->w*3];
        }
    }

    //修改原图里的数据和宽高
    bmp->w = w;
    bmp->h = h;
    delete []bmp->data;
    bmp->data = data;//这样bmp->data就会存储data存储的内存空间
    cout<<"修改成功"<<endl;
    
}

//图片显示
struct BitMap * Photo_Resolution::Show_Photo()
{
    return bmp;
}

//图片存储字典
void Photo_Resolution::Storage()
{
    //定义输入流对象
    ifstream weather_photo("./WeatherPhoto/weather_photo.txt",ios_base::in);//初始化以读方式打开文件
    if(!weather_photo.is_open())
    {
        cerr<<"open ..."<<endl;
    }
    ifstream weather_name("./WeatherPhoto/weather.txt",ios_base::in);
    if(!weather_name.is_open())
    {
        cerr<<"open ..."<<endl;
    }

    //读取缓存区buffer值
    char buffer1[1024] = {0};
    char buffer2[1024] = {0};
    char space =' ';
    
    while(!(weather_name.eof()&&weather_photo.eof()))
    {
        weather_name.getline(buffer1,sizeof(buffer1),space);    
        weather_photo.getline(buffer2,sizeof(buffer2),space);
        this->weather[string(buffer1)] = string(buffer2);
    }
    if(this->weather.empty())
    {
        cout<<"kong"<<endl;
    }

    weather_name.close();
    weather_photo.close();
} 


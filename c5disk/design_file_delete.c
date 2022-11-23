#include <windows.h>
#include <stdio.h>

#define MINFileSize (1<<15)
#define MAXFileSize (1<<20)
//1 0000 0000 0000 0000 0000
double clockperiods = 0;//删除文件的时钟周期数差之和,初始化为零
void Remove(char filename[]) {
    LARGE_INTEGER start_t, stop_t;
    QueryPerformanceCounter(&start_t);
     FILE * fp;//文件指针
    if((fp=fopen(filename,"r"))==NULL) //只读文件形式打开文件
    {
        printf("无法打开文件\n");//如果打开出错，就输出“无法打开文件”的信息
        exit(0);//终止程序
    }
    fclose(fp);
    int booll=remove(filename);
    //printf("%d\n",booll);
    QueryPerformanceCounter(&stop_t);
    clockperiods+=(stop_t.QuadPart-start_t.QuadPart);//累加每一次读取的文件的时钟周期数差
}
int main()
{
    int filenums,filesize=MINFileSize; //要生成文件的数量，大小单位为kb
    double filesizes=0;
    int nums=0;//总文件大小
    while(filesize<=MINFileSize) {
        //int size=filesize/1024;
        filenums = 1024*1024/filesize;
        //printf("MINFileSize:%d\n",MINFileSize);
        //printf("filenums:%d\n",filenums);
        char chars[13];//储存文件后面大小的名字 （sizekb.txt）
        itoa(filesize,chars,10);
        char filesuffixname[20]="sizeis";//文件后面的名字
        strcat(chars,"kb.txt");//字符串拼接函数
        strcat(filesuffixname,chars);
        int i;
        for(i =0 ; i<filenums; i++) ////循环写入filenums次文件
        {
            char chars1[20];//文件后半部分的名字
            itoa(i,chars1,10);
            char filename[100] = "E:\\实验2学生\\coasepv2\\coasep\\c5disk\\temporary_files\\";//修改为本机目录
            //char filename[100] = "E:\\计组\\C5disk\\temporary_files\\";//修改为本机目录
            //E:\实验2学生\coasepv2\coasep\c5disk\temporary_files\0sizeis1048576kb.txt
            //E:\实验2学生\coasepv2\coasep\c5disk\temporary_files
            strcat(filename,chars1);//字符串拼接函数
            strcat(filename,filesuffixname);
             //printf("filename:%s\n",filename);
            Remove(filename);//调用写文件方法
            printf("filename:%s删除成功！\n",filename);
        }
        printf("-------------\n");
        filesizes+=(double)filenums*filesize/1024;
        nums+=filenums;
        filesize<<=1;
    }
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    double exe_time;//读文件时间
    exe_time = 1e3*(clockperiods)/freq.QuadPart;
    //删除文件数度 ；计算公式 全部文件大小 / 读文件用时 * 1000 因为数度以MB/S为单位 写文件用时单位为ms 1s=1000ms
    double v = filesizes/exe_time*1000;
    printf( "%d个文件删除成功\t共计:%fMB\t读用时:%fms.\n",nums,filesizes,exe_time);
    printf("删除速度为:%.2fMB/s",v);

    return 0;
}

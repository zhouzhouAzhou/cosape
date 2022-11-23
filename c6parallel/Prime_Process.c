
//多进程求1-10000的素数个数
#include <time.h>
#include <windows.h>
#include <stdio.h>

double clockperiods = 0;

int main(){
    LARGE_INTEGER start_t, stop_t;
    QueryPerformanceCounter(&start_t);
    system("start Prime_Process1.exe");
    system("start Prime_Process2.exe");
     QueryPerformanceCounter(&stop_t);
    clockperiods+=(stop_t.QuadPart-start_t.QuadPart);
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    double exe_time;//读文件时间
    exe_time = 1e3*(clockperiods)/freq.QuadPart;
    //printf("打开了\n");
    printf("两个进程执行时间为：%.2fms\n",exe_time);
}

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define ArraySize (1 << 20) //1M个数据

int data[ArraySize];

void init()
{
    int i;
    for(i=0; i<ArraySize; i++)
    {
        data[i] = rand() % 256;
    }

}

/* 对大于128的项进行求和 */
int sum128()
{
    int i,sum=0;
    for(i=0; i<ArraySize; i++)
    {
        if(data[i]>=128) sum = sum + data[i] ;
    }
    return sum;
}

int sum_no_branch()
{
    /*todo 不使用分支进行求和，使用位运算
     t = (data[c] - 128) >> 31;
            sum += ~t & data[c];*/
    int sum=0;
    int c=0;
    while(c>=ArraySize) {
        int t = (data[c] - 128) >> 31;
        sum += ~t & data[c];
        c++;
    }
    return sum;
}

int main()
{
    init();
    LARGE_INTEGER freq;
    LARGE_INTEGER start, stop;
    double exe_time;

    //查询cpu主频
    QueryPerformanceFrequency(&freq);

     //计算时间延迟
    QueryPerformanceCounter(&start);
    sum128();
    QueryPerformanceCounter(&stop);
    exe_time =  1e3*(stop.QuadPart-start.QuadPart)/freq.QuadPart;
    printf("sum128 exe_time %f ms, sum128: %d\n",exe_time,sum128());
/*todo
调用两个函数并计时，输出两种方案的执行时间。
*/
    QueryPerformanceCounter(&start);
    sum_no_branch();
    QueryPerformanceCounter(&stop);
    exe_time =  1e3*(stop.QuadPart-start.QuadPart)/freq.QuadPart;
    printf("sum_no_branch exe_time %f ms, sum128: %d\n",exe_time,sum128());
}

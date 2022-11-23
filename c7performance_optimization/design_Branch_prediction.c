#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define ArraySize (1 << 20) //1M������

int data[ArraySize];

void init()
{
    int i;
    for(i=0; i<ArraySize; i++)
    {
        data[i] = rand() % 256;
    }

}

/* �Դ���128���������� */
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
    /*todo ��ʹ�÷�֧������ͣ�ʹ��λ����
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

    //��ѯcpu��Ƶ
    QueryPerformanceFrequency(&freq);

     //����ʱ���ӳ�
    QueryPerformanceCounter(&start);
    sum128();
    QueryPerformanceCounter(&stop);
    exe_time =  1e3*(stop.QuadPart-start.QuadPart)/freq.QuadPart;
    printf("sum128 exe_time %f ms, sum128: %d\n",exe_time,sum128());
/*todo
����������������ʱ��������ַ�����ִ��ʱ�䡣
*/
    QueryPerformanceCounter(&start);
    sum_no_branch();
    QueryPerformanceCounter(&stop);
    exe_time =  1e3*(stop.QuadPart-start.QuadPart)/freq.QuadPart;
    printf("sum_no_branch exe_time %f ms, sum128: %d\n",exe_time,sum128());
}

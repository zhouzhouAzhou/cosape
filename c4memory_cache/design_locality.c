#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "QPC_time_4locality.h"

#define P 100
int a[P][P][P];

LARGE_INTEGER start, stop;

int sumarray3d(int a[P][P][P])
{
    int i, j, k, sum = 0;
     //����ʱ���ӳ�
    QueryPerformanceCounter(&start);
    for (i = 0; i < P; i++)
    {
        for (j = 0; j < P; j++)
        {
            for (k = 0; k < P; k++)
            {
                sum += a[k][i][j] ;
            }
        }
    }
    QueryPerformanceCounter(&stop);
    return sum;
}

int sumarray3d_1(int a[P][P][P])
{
    int i, j, k, sum = 0;
    //�ֲ���ԭ���Ż���������
    QueryPerformanceCounter(&start);
    for (k = 0; k < P; k++)
    {
        for (i = 0; i < P; i++)
        {
            for (j = 0; j < P; j++)
            {
                sum += a[k][i][j] ;
            }
        }
    }
    QueryPerformanceCounter(&stop);
    return sum;
}

void init()
{
    int i,j,k;
    for (i = 0; i < P; i++)
    {
        for (j = 0; j < P; j++)
        {
            for (k = 0; k < P; k++)
            {
                a[k][i][j]= i+j+k ;
            }
        }
    }
}

int main()
{
    LARGE_INTEGER freq;
    double exe_time;
    //��ѯcpu��Ƶ

    init();

    QueryPerformanceFrequency(&freq);

    printf("sumarray3d���Ϊ��%d",sumarray3d(a));
    exe_time =  1e3*(stop.QuadPart-start.QuadPart)/freq.QuadPart;
    printf("exe_time��%fms\n",exe_time);

    printf("�Ż����sumarray3d_1���Ϊ��%d��",sumarray3d_1(a));
    exe_time =  1e3*(stop.QuadPart-start.QuadPart)/freq.QuadPart;
    printf("exe_time��%fms\n",exe_time);

    return 0;
}

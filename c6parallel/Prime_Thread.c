//��1-10000������
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <windows.h>

int count=0;
pthread_mutex_t lock;
double clockperiods = 0;//�߳̿�ʼ��������ʱ����������֮��,��ʼ��Ϊ��

void *Prime(void *args){
    //printf("!!!");
    int i,j;
    int arr1[2]={2,5000};
    int arr2[2]={5001,10000};
    int *a;
    char *name = (char*)args;
    //printf("%s\n",name);
    if(!strcmp(name,"th1")) {
        a=arr1;
    } else {
        a=arr2;
    }

    //printf("%d %d\n",a[0],a[1]);
    LARGE_INTEGER start_t, stop_t;
    QueryPerformanceCounter(&start_t);
    for(i=a[0];i<=a[1];i++) {
        int flag=0;
        for(j=2;j*j<=i;j++) {
            if(i%j==0) {
                flag=1;
                break;
            }
        }
        if(!flag) {
            pthread_mutex_lock(&lock);
            count++;
            pthread_mutex_unlock(&lock);
        }
    }
     QueryPerformanceCounter(&stop_t);
    clockperiods+=(stop_t.QuadPart-start_t.QuadPart);//�ۼ�ÿһ���̵߳�ʱ����������
    //printf("clockperiods:%f\n",clockperiods);
   /* if(strcmp(name,"th1")) {
        LARGE_INTEGER freq;
        QueryPerformanceFrequency(&freq);
        double exe_time;//���ļ�ʱ��
        exe_time = 1e3*(clockperiods)/freq.QuadPart;
        printf("�����߳�ִ��ʱ��Ϊ��%fs\n",exe_time);
    }*/
    return NULL;
}
int main() {
    pthread_t th1;
    pthread_t th2;

    pthread_mutex_init(&lock,NULL);

    pthread_create(&th1,NULL,Prime,"th1");
    pthread_create(&th2,NULL,Prime,"th2");

    pthread_join(th1,NULL);
    pthread_join(th2,NULL);

    printf("1-10000�������ĸ���count:%d\n",count);
      //printf("clockperiods:%f\n",clockperiods);
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    double exe_time;//���ļ�ʱ��
    exe_time = 1e3*(clockperiods)/freq.QuadPart;
    printf("�����߳�ִ��ʱ��Ϊ��%fms\n",exe_time);
}

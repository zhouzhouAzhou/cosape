#include <windows.h>
#include <stdio.h>

#define MINFileSize (1<<15)
#define MAXFileSize (1<<20)
//1 0000 0000 0000 0000 0000
double clockperiods = 0;//ɾ���ļ���ʱ����������֮��,��ʼ��Ϊ��
void Remove(char filename[]) {
    LARGE_INTEGER start_t, stop_t;
    QueryPerformanceCounter(&start_t);
     FILE * fp;//�ļ�ָ��
    if((fp=fopen(filename,"r"))==NULL) //ֻ���ļ���ʽ���ļ�
    {
        printf("�޷����ļ�\n");//����򿪳�����������޷����ļ�������Ϣ
        exit(0);//��ֹ����
    }
    fclose(fp);
    int booll=remove(filename);
    //printf("%d\n",booll);
    QueryPerformanceCounter(&stop_t);
    clockperiods+=(stop_t.QuadPart-start_t.QuadPart);//�ۼ�ÿһ�ζ�ȡ���ļ���ʱ����������
}
int main()
{
    int filenums,filesize=MINFileSize; //Ҫ�����ļ�����������С��λΪkb
    double filesizes=0;
    int nums=0;//���ļ���С
    while(filesize<=MINFileSize) {
        //int size=filesize/1024;
        filenums = 1024*1024/filesize;
        //printf("MINFileSize:%d\n",MINFileSize);
        //printf("filenums:%d\n",filenums);
        char chars[13];//�����ļ������С������ ��sizekb.txt��
        itoa(filesize,chars,10);
        char filesuffixname[20]="sizeis";//�ļ����������
        strcat(chars,"kb.txt");//�ַ���ƴ�Ӻ���
        strcat(filesuffixname,chars);
        int i;
        for(i =0 ; i<filenums; i++) ////ѭ��д��filenums���ļ�
        {
            char chars1[20];//�ļ���벿�ֵ�����
            itoa(i,chars1,10);
            char filename[100] = "E:\\ʵ��2ѧ��\\coasepv2\\coasep\\c5disk\\temporary_files\\";//�޸�Ϊ����Ŀ¼
            //char filename[100] = "E:\\����\\C5disk\\temporary_files\\";//�޸�Ϊ����Ŀ¼
            //E:\ʵ��2ѧ��\coasepv2\coasep\c5disk\temporary_files\0sizeis1048576kb.txt
            //E:\ʵ��2ѧ��\coasepv2\coasep\c5disk\temporary_files
            strcat(filename,chars1);//�ַ���ƴ�Ӻ���
            strcat(filename,filesuffixname);
             //printf("filename:%s\n",filename);
            Remove(filename);//����д�ļ�����
            printf("filename:%sɾ���ɹ���\n",filename);
        }
        printf("-------------\n");
        filesizes+=(double)filenums*filesize/1024;
        nums+=filenums;
        filesize<<=1;
    }
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    double exe_time;//���ļ�ʱ��
    exe_time = 1e3*(clockperiods)/freq.QuadPart;
    //ɾ���ļ����� �����㹫ʽ ȫ���ļ���С / ���ļ���ʱ * 1000 ��Ϊ������MB/SΪ��λ д�ļ���ʱ��λΪms 1s=1000ms
    double v = filesizes/exe_time*1000;
    printf( "%d���ļ�ɾ���ɹ�\t����:%fMB\t����ʱ:%fms.\n",nums,filesizes,exe_time);
    printf("ɾ���ٶ�Ϊ:%.2fMB/s",v);

    return 0;
}

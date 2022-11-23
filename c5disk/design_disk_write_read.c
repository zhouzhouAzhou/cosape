#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <windows.h>

#define MINFileSize (1<<15)
#define MAXFileSize (1<<20)

double clockperiods = 0,clockperiods1 = 0;//д���ļ���ʱ����������֮��,��ʼ��Ϊ��
char str[1024];//1kb��С���ַ���
//д�ļ����� filename :�ļ��� �� size �ļ���С ��kb��
void save(char filename[],int size)
{
    LARGE_INTEGER start_t, stop_t;
    QueryPerformanceCounter(&start_t);
    FILE * fp;//�ļ�ָ��
    if((fp=fopen(filename,"w"))==NULL) //д�ļ���ʽ���ļ�
    {
        printf("�޷����ļ�\n");//����򿪳�����������޷����ļ�������Ϣ
        exit(0);//��ֹ����
    }
    int i;
    for(i =0; i<size; i++) //ѭ��дsize1��kb��С������
    {
        fputs(str,fp);
    }
    fclose(fp);//�ر�����ļ�
    QueryPerformanceCounter(&stop_t);
    clockperiods+=(stop_t.QuadPart-start_t.QuadPart);//�ۼ�ÿһ�ζ�ȡ���ļ���ʱ����������
}
void read(char filename[])
{
    LARGE_INTEGER start_t, stop_t;
    QueryPerformanceCounter(&start_t);
    FILE * fp;//�ļ�ָ��
    if((fp=fopen(filename,"r"))==NULL) //ֻ���ļ���ʽ���ļ�
    {
        printf("�޷����ļ�\n");//����򿪳�����������޷����ļ�������Ϣ
        exit(0);//��ֹ����
    }

    char str[1024];
    while(fgets(str,1024,fp)!=NULL) //һ���Զ�ȡ1kb�Ĵ�С������
    {

    }

    fclose(fp);//�ر������ļ�
    QueryPerformanceCounter(&stop_t);
    clockperiods1+=(stop_t.QuadPart-start_t.QuadPart);//�ۼ�ÿһ�ζ�ȡ���ļ���ʱ����������
}

/*�ܼ�һ��G����,�ֶ��С�ļ�д�봢��*/

int main()
{
    int length = sizeof(str)/sizeof(char);//str����ĳ���
    //printf("%d %d\n",sizeof(str),sizeof(char));
    length--;//���ȼ�һ��ʹ�ַ��������һ���ǽ�����
    int i;
    for(i = 0; i<length; i++)
    {
        str[i]='a';
    }
    int filenums,filesize=MINFileSize; //Ҫ�����ļ�����������С��λΪkb
    //printf("�������ļ���С��\n");
    //scanf("%d",&filesize);
    printf("д�ļ���С(KB),д�ļ�����(MB/s),���ļ����ȣ�MB/s)\n");
    while(filesize<=MAXFileSize) {
        filenums = 1024*1024/filesize;
         char chars[13];//�����ļ������С������ ��sizekb.txt��
         itoa(filesize,chars,10);
        //printf("%s\n",chars);
        //char *itoa( int value, char *string,int radix); [1]ԭ��˵���� value����ת�������ݡ�
        //string��Ŀ���ַ����ĵ�ַ�� radix��ת����Ľ�������������10���ơ�16���Ƶȡ�
        char filesuffixname[20]="sizeis";//�ļ����������
        strcat(chars,"kb.txt");//�ַ���ƴ�Ӻ���
        strcat(filesuffixname,chars);
        //printf("%s\n",filesuffixname);
        //дfilenums���ļ�
        //printf("%d��%dkb�ļ���ʼд��\n",filenums,filesize);
        clockperiods=0;
        for(i =0 ; i<filenums; i++) ////ѭ��д��filenums���ļ�
        {
            char chars1[20];//�ļ���벿�ֵ�����
            itoa(i,chars1,10);
            //char filename[100] = "C:\\coasep\\coasepv1\\coasep\\c5disk\\";//�޸�Ϊ����Ŀ¼
            char filename[100] = "E:\\ʵ��2ѧ��\\coasepv2\\coasep\\c5disk\\temporary_files\\";//�޸�Ϊ����Ŀ¼
            strcat(filename,chars1);//�ַ���ƴ�Ӻ���
            strcat(filename,filesuffixname);
            //printf("filename:%s\n",filename);
            save(filename,filesize);//����д�ļ�����
        }
        //printf("%d��%dkb�ļ����ɳɹ���\n",filenums,filesize);
        clockperiods1=0;
        for(i =0 ; i<filenums; i++) //ѭ����ȡfilenums���ļ�
       {
            char chars1[20];//�ļ���벿�ֵ�����
            itoa(i,chars1,10);
            char filename[100] = "E:\\ʵ��2ѧ��\\coasepv2\\coasep\\c5disk\\temporary_files\\";//�޸�Ϊ����Ŀ¼
            strcat(filename,chars1);//�ַ���ƴ�Ӻ���
            strcat(filename,filesuffixname);
            read(filename);//���ö��ļ�����
        }
        //д�ļ�����
        LARGE_INTEGER freq;
        QueryPerformanceFrequency(&freq);
        double exe_time;//д�ļ�ʱ��
        exe_time = 1e3*(clockperiods)/freq.QuadPart;
        //ȫ���ļ���С ��ȫ���ļ����㹫ʽ���ļ��� * �����ļ���С / 1024 ��Ϊ���ﵥλ��MB �ļ���С��λΪkb 1MB=1024kb
        double filesizes=filenums/1024.0*filesize;
        //д�ļ����� �����㹫ʽ ȫ���ļ���С / д�ļ���ʱ * 1000 ��Ϊ������MB/SΪ��λ д�ļ���ʱ��λΪms 1s=1000ms
        double v = filesizes/exe_time*1000;

        //���ļ�����
        LARGE_INTEGER freq1;
        QueryPerformanceFrequency(&freq1);
        double exe_time1;//���ļ�ʱ��
        exe_time1 = 1e3*(clockperiods1)/freq.QuadPart;
        //ȫ���ļ����㹫ʽ���ļ��� * �����ļ���С / 1024 ��Ϊ���ﵥλ��MB �ļ���С��λΪkb 1MB=1024kb
        //double filesizes=(double)filenums*filesize/1024;
        //���ļ����� �����㹫ʽ ȫ���ļ���С / ���ļ���ʱ * 1000 ��Ϊ������MB/SΪ��λ д�ļ���ʱ��λΪms 1s=1000ms
        double v1 = filesizes/exe_time1*1000;

        printf( "%d,%f,%f,\n",filesize,v,v1);
        //printf("д�ļ�����:%.2fMB/s",v);
        filesize<<=1;
    }
    return 0;
}

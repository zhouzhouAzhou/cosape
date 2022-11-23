#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ShowValueBin(int bits, int value)
{
    int i;
    //printf("%d�Ķ�����Ϊ:",value);
    for(i = bits-1; i >=0; i--)
    {
        if(value & (1 << i))
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
    }
}

int GetSign(int iNum)//��ȡ����λ
{
    int iSign = iNum >> 31;
    if(iSign)//��λΪ1Ϊ����
        return 1;
    else
        return 0;
}


/*���Ҫ��
-4����ֵ������Ϊ:-100
��ʽ
*/
void True_Code(int iNum)
{
    printf("%d����ֵ��",iNum);
    int iSign = GetSign(iNum);
    if(iSign)//�������ڴ������Բ������ʽ����
    {
         printf("-");
         iNum=-iNum;
    } else {
        printf("+");
    }
    int i;
    //printf("%d�Ķ�����Ϊ:",value);
    for(i = 31; i >=0; i--)
    {
        if(iNum & (1 << i))
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
    }
    puts("\n");
    /*todo*/
}

void Bin(int iNum) {
    printf("%d��ԭ�룺",iNum);
    int iSign = GetSign(iNum);
    if(iSign)//�������ڴ������Բ������ʽ����
    {
         printf("1");
         iNum=-iNum;
    } else {
        printf("0");
    }
    int i;
    //printf("%d�Ķ�����Ϊ:",value);
    for(i = 31; i >=0; i--)
    {
        if(iNum & (1 << i))
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
    }
    puts("\n");
    /*todo*/
}

/*���Ҫ��
-4�ķ��������Ϊ:11111111111111111111111111111011
��ʽ
*/
int Ones_complement_Code(int iNum)//����
{
    /*todo*/
    int iSign = GetSign(iNum);
    if(iSign) {
        iNum-=1;
        /*iNum=~iNum;
        iNum |= 1 << 31;*/
    }
    /*printf("���룺%d\n",iNum);*/
    return iNum;
}

/*���Ҫ��
-4�Ĳ��������Ϊ:11111111111111111111111111111100
��ʽ
*/
int  Complemental_Code(int iNum)//����
{
    /*todo*/
    return iNum;
}


/*���Ҫ��
-4�����������Ϊ:01111111111111111111111111111100
��ʽ
*/
int Frame_Shift(int iNum)//����
{
    /*todo*/
    int iSign = GetSign(iNum);
    if(iSign)
    {
        //�������λȡ��1&0=0
        iNum &= ~(1 << 31);
        return iNum;
    }
    else
    {
        iNum |= 1 << 31;
        return iNum;
    }
}


int main(int argc, char* argv[])
{
    /*****************************************************
    1. ������
    ������ԭ�롢���롢���붼��ͬ��
    2. ������
    ԭ�룺�����ľ���ֵ���������λΪ1��
    ���룺ԭ��ķ���λ���䣬����λ��λȡ����
    ���룺�ڷ���Ļ�����+1��
    3. ���룺
    ��������/�����������ڲ���Ļ����ϣ�����λȡ����
    ******************************************************/


    printf("int �͵ĳ���Ϊ��%dλ\n",sizeof(int)*8);
    printf("���������int��10�������������ֵ��ԭ�롢���롢���롢���롣\n");
    /*todo
    ���������10�������������ֵ��ԭ�롢���롢���롢���롣
    */
    True_Code(4);
    True_Code(-4);

    Bin(4);
    Bin(-4);

    int Complemental_Code1 = Complemental_Code(4);
    int Complemental_Code2 = Complemental_Code(-4);

    int Ones_complement1 = Ones_complement_Code(4);
    int Ones_complement2 = Ones_complement_Code(-4);

    int Frame_Shift1 = Frame_Shift(4);
    int Frame_Shift2 = Frame_Shift(-4);

    /*printf("4����ֵTrue_Code1=");
    ShowValueBin(32, True_Code1);
    printf("\r\n");
    printf("-4����ֵTrue_Code2=");
    ShowValueBin(32, True_Code2);*/
    printf("\r\n");
    printf("4�ķ���Ones_complement1=");
    ShowValueBin(32, Ones_complement1);
    printf("\r\n");
    printf("-4�ķ���Ones_complement2=");
    ShowValueBin(32, Ones_complement2);
    printf("\r\n");

    printf("4�Ĳ���Complemental_Code1=");
    ShowValueBin(32, Complemental_Code1);
    printf("\r\n");
    printf("-4�Ĳ���Complemental_Code2=");
    ShowValueBin(32, Complemental_Code2);
    printf("\r\n");

    printf("4������Frame_Shift1=");
    ShowValueBin(32, Frame_Shift1);
    printf("\r\n");
    printf("-4������Frame_Shift2=");
    ShowValueBin(32, Frame_Shift2);
    printf("\r\n");

    return 0;

}

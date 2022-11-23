#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ShowValueBin(int bits, int value)
{
    int i;
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
int Ones_complement_Code(int iNum)//����
{
    int iSign = GetSign(iNum);
    if(iSign)//Ϊ����
    {
        iNum = ~iNum;
        iNum |= 1 << 31;
        return iNum;
    }
    else
    {
        return iNum;
    }
}
int  Complemental_Code(int iNum)//����
{
    int iSign = GetSign(iNum);
    if(iSign)
    {
        iNum = Ones_complement_Code(iNum)+1;
        return iNum;
    }
    else
    {
        return iNum;
    }
}

int Frame_Shift(int iNum)//����
{
    int iSign = GetSign(iNum);
    if(iSign)
    {
        iNum &= ~(1 << 31);
        return iNum;
    }
    else
    {
        iNum |= 1 << 31;
        return iNum;
    }
}
int True_Code(int iNum)
{
    int iSign = GetSign(iNum);
    if(iSign)//�������ڴ������Բ������ʽ����
    {
        iNum = Complemental_Code(iNum);
        return iNum;
    }
    else
    {
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

    int True_Code1 = True_Code(4);
    int True_Code2 = True_Code(-4);

    int Complemental_Code1 = Complemental_Code(4);
    int Complemental_Code2 = Complemental_Code(-4);

    int Ones_complement1 = Ones_complement_Code(4);
    int Ones_complement2 = Ones_complement_Code(-4);

    int Frame_Shift1 = Frame_Shift(4);
    int Frame_Shift2 = Frame_Shift(-4);

    printf("True_Code1=%d\r\n", True_Code1);
    printf("True_Code2=%d\r\n", True_Code2);

    printf("Complemental_Code1=%d\r\n", Complemental_Code1);
    printf("Complemental_Code2=%d\r\n", Complemental_Code2);

    printf("Ones_complement1=%d\r\n", Ones_complement1);
    printf("Ones_complement2=%d\r\n", Ones_complement2);

    printf("Frame_Shift1=%d\r\n", Frame_Shift1);
    printf("Frame_Shift2=%d\r\n", Frame_Shift2);

    printf("\r\n");
    ShowValueBin(32, 4);
    printf("\r\n");
    ShowValueBin(32, -4);
    printf("\r\n");

    return 0;

}

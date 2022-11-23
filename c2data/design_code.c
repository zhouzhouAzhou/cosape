#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ShowValueBin(int bits, int value)
{
    int i;
    //printf("%d的二进制为:",value);
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

int GetSign(int iNum)//获取符号位
{
    int iSign = iNum >> 31;
    if(iSign)//高位为1为负数
        return 1;
    else
        return 0;
}


/*输出要求
-4的真值二进制为:-100
形式
*/
void True_Code(int iNum)
{
    printf("%d的真值：",iNum);
    int iSign = GetSign(iNum);
    if(iSign)//负数在内存中是以补码的形式存在
    {
         printf("-");
         iNum=-iNum;
    } else {
        printf("+");
    }
    int i;
    //printf("%d的二进制为:",value);
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
    printf("%d的原码：",iNum);
    int iSign = GetSign(iNum);
    if(iSign)//负数在内存中是以补码的形式存在
    {
         printf("1");
         iNum=-iNum;
    } else {
        printf("0");
    }
    int i;
    //printf("%d的二进制为:",value);
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

/*输出要求
-4的反码二进制为:11111111111111111111111111111011
形式
*/
int Ones_complement_Code(int iNum)//反码
{
    /*todo*/
    int iSign = GetSign(iNum);
    if(iSign) {
        iNum-=1;
        /*iNum=~iNum;
        iNum |= 1 << 31;*/
    }
    /*printf("反码：%d\n",iNum);*/
    return iNum;
}

/*输出要求
-4的补码二进制为:11111111111111111111111111111100
形式
*/
int  Complemental_Code(int iNum)//补码
{
    /*todo*/
    return iNum;
}


/*输出要求
-4的移码二进制为:01111111111111111111111111111100
形式
*/
int Frame_Shift(int iNum)//移码
{
    /*todo*/
    int iSign = GetSign(iNum);
    if(iSign)
    {
        //补码符号位取反1&0=0
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
    1. 正数：
    正数的原码、反码、补码都相同。
    2. 负数：
    原码：负数的绝对值，并且最高位为1。
    反码：原码的符号位不变，其他位按位取反。
    补码：在反码的基础上+1。
    3. 移码：
    无论是正/负数，都是在补码的基础上，符号位取反。
    ******************************************************/


    printf("int 型的长度为：%d位\n",sizeof(int)*8);
    printf("接收输入的int型10进制数，输出真值、原码、反码、补码、移码。\n");
    /*todo
    接受输入的10进制数，输出真值、原码、反码、补码、移码。
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

    /*printf("4的真值True_Code1=");
    ShowValueBin(32, True_Code1);
    printf("\r\n");
    printf("-4的真值True_Code2=");
    ShowValueBin(32, True_Code2);*/
    printf("\r\n");
    printf("4的反码Ones_complement1=");
    ShowValueBin(32, Ones_complement1);
    printf("\r\n");
    printf("-4的反码Ones_complement2=");
    ShowValueBin(32, Ones_complement2);
    printf("\r\n");

    printf("4的补码Complemental_Code1=");
    ShowValueBin(32, Complemental_Code1);
    printf("\r\n");
    printf("-4的补码Complemental_Code2=");
    ShowValueBin(32, Complemental_Code2);
    printf("\r\n");

    printf("4的移码Frame_Shift1=");
    ShowValueBin(32, Frame_Shift1);
    printf("\r\n");
    printf("-4的移码Frame_Shift2=");
    ShowValueBin(32, Frame_Shift2);
    printf("\r\n");

    return 0;

}

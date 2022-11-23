#include <stdio.h>
#include<stdlib.h>
#include<string.h>

union {
    int i;
    float f;
} myunion;

int GetValue(char *s)
{
    //printf("%s:\n",s);
    int sum=0,l=strlen(s)-1;
    //printf("%d ",l);
    int i=l;
    while(i>=0) {
        int n=(s[i]-'0')*(1<<(l-i));
        //printf("%d ",s[i]-'0');
        i--;
        sum+=n;
    }
    //puts("\n");
    return sum;

}

int binstr2int(char *s)
{
    int rc;
    for (rc = 0; '\0' != *s; s++) {
        if ('1' == *s) {
            rc = (rc * 2) + 1;
        } else if ('0' == *s) {
            rc *= 2;
        }
       // printf("rc:%d ",rc);
    }
   // printf("\nrc:%d\n",rc);
    return rc;
}

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
    puts("\n");
}

int main(void) {

    // the input binary string (4 bytes)
    char * input = "11000000110110011001100110011010";
    float *output;

    char * input1 = "10111111001001100110011001100110";
    //11000000110110011001100110011010
     int sum=0,l=strlen(input1)-1;
    //printf("%d ",l);
    int i=l;
    while(i>=1) {
        int n=(input1[i]-'0')*(1<<(l-i));
        //printf("%d ",s[i]-'0');
        i--;
        sum+=n;
    }
    //ShowValueBin(32,-sum);
    printf("%d在内存中的原码：\n",-sum);
    ShowValueBin(32,-sum);
    printf("%d实际的原码：\n",-sum);
    printf("%s\n",input1);
    // convert to int, sizeof(int) == sizeof(float) == 4
    int converted = binstr2int(input);

    // strat 1: point memory of float at the int
    output = (float*)&converted; // cast to suppress warning
    printf("%f\n", *output); // -6.8
printf("%d\n", converted);
printf("%d\n",*(float*)&converted);
printf("%d\n", &converted);
   char Echar[9],Mchar[30];
    //int i;
    // input=input+1;
    for(i=1;i<=8;i++) {
        Echar[i-1]=input[i];
        //printf("input:%c\n",input[i]);
        // printf("Echar:%c\n",*input);
    }
    Echar[8]='\0';
    //printf("Echar:%s\n", Echar);
   // printf("Echar：%s\n",Echar);
    for(i=9;i<=strlen(input)-1;i++) {
        Mchar[i-9]=input[i];
    }
    Mchar[23]='\0';
    //int E=GetValue("");
    printf("该浮点数%s的尾数为：%d,阶数%s为：%d\n",Mchar,GetValue(Mchar),Echar,GetValue(Echar));

    // strat 2: use a union to share memory
    //myunion.i = converted;
    //printf("%f\n", myunion.f); // -6.8

    return 0;
}

#include <string.h>

#include "toy_compiler.h"
#include "misc.h"


//变量地址分配表
char var_table[100][8];//可以用于检查变量重名，指令使用未定义变量等情况

//读入高级C保存
char highc_lines[100][20];
char asm_lines[100][20];

int lines_num;
int iasm_lines_length;
int compile_result = 1; //1表示正确，0表示错误，


/*代码格式检查：
1.读取代码，并删除空行；
2.检查 data code output段是否存在
3.输出段检查结果
*/
void read_check(FILE *fp)
{
    int iline=0;
    printf("开始代码格式检查……");

    //读取文件，并删除空行
    while (!feof(fp))//feof其功能是检测流上的文件结束符，如果文件结束，则返回非0值，否则返回0
    {
        fgets(highc_lines[iline],20,fp);
        printf("highc_lines[%d]:%s\n",iline,highc_lines[iline]);
        //空行判读，highc_lines数组只保留非空行
        //blank_flag 0 表示空，1表示非空
        int blank_flag=0,ichar;
        for (ichar=0; ichar<strlen(highc_lines[iline]); ichar++)
        {
            if (0xff & (highc_lines[iline][ichar] > 0x20))
            {
                blank_flag=1;
                break;
            };
        }
        if(blank_flag==1)
            iline++;
    }
    lines_num=iline;
    printf("有效代码共 %d行。\n",lines_num);

    //检查 #data #code #output 是否完整
    int i=0,data_seg_flag=0,code_seg_flag=0,output_seg_flag=0;
    for(i=0; i<lines_num; i++)
    {
        //printf("%s\n",highc_lines[i]);
        if(strcmp(highc_lines[i], "#data\n")==0) data_seg_flag=1;
        if(strcmp(highc_lines[i], "#code\n")==0) code_seg_flag=1;
        if(strcmp(highc_lines[i], "#output\n")==0) output_seg_flag=1;
    }
    if(data_seg_flag==0) printf("**** #data 标记错误。\n");
    if(code_seg_flag==0) printf("**** #code 标记错误。\n");
    if(output_seg_flag==0) printf("**** #output 标记错误。\n");
}

/*标记各段，并逐段编译*/
void seg_compile()
{
    printf("开始逐段编译……\n");
    //处理标志flag，1处理data,2处理code，3处理output
    int i,ivar=0,iasm_line=0,seg_flag=0;
    for(i=0; i<lines_num; i++)
    {
        if(strcmp(highc_lines[i], "#data\n")==0)
        {
            seg_flag = 1;
            strcpy(asm_lines[iasm_line],"#data");
            iasm_line++;
            continue;
        }
        if(strcmp(highc_lines[i], "#code\n")==0)
        {
            seg_flag = 2;
            //存在i++指令的情况下
            sprintf(asm_lines[iasm_line],"%s%s%s","one"," ","1");
            printf("成功加入one\n");
            iasm_line++;
            strcpy(asm_lines[iasm_line],"#code");
            iasm_line++;
            continue;
        }
        if(strcmp(highc_lines[i], "#output\n")==0)
        {
            seg_flag =3;
            strcpy(asm_lines[iasm_line],"#output");
            iasm_line++;
            continue;
        }

        char *revbuf[5] = {0}; // for line_split  misc.c文件中
        int num;               // for line_split
        if(seg_flag==1)  //编译数据段
        {
            num = 0;
            line_split(highc_lines[i]," =;",revbuf,&num);
            //printf("%s,%s %s  %d\n\n",revbuf[0],revbuf[1],revbuf[2],num);
            strcpy(var_table[ivar],revbuf[1]);
            ivar++;
            sprintf(asm_lines[iasm_line],"%s%s%s",revbuf[1]," ",revbuf[2]);
            iasm_line++;
        }
        if(seg_flag==2)  //编译代码段
        {
            /*strstr(str1,str2) 函数用于判断字符串str2是否是str1的子串。
            如果是，则该函数返回 str1字符串从 str2第一次出现的位置开始
            到 str1结尾的字符串；否则，返回NULL。*/
            //添加一段i++指令
            if(strstr(highc_lines[i],"++") != NULL)
            {
                line_split(highc_lines[i]," +;",revbuf,&num);
                 //printf("%s %s %s  %d\n",revbuf[0],revbuf[1],revbuf[2],num);
                sprintf(asm_lines[iasm_line],  "LOAD R1, %s",revbuf[0]);
                sprintf(asm_lines[iasm_line+1],"LOAD R2, %s","one");
                sprintf(asm_lines[iasm_line+2],"ADD R3, R1, R2");
                sprintf(asm_lines[iasm_line+3],"STORE %s, R3",revbuf[0]);
                iasm_line=iasm_line+4;
            }
            if(strstr(highc_lines[i],"+") != NULL)
            {
                num = 0;
                line_split(highc_lines[i]," +=;",revbuf,&num);
                 printf("%s %s %s  %d\n",revbuf[0],revbuf[1],revbuf[2],num);
                sprintf(asm_lines[iasm_line],  "LOAD R1, %s",revbuf[1]);
                sprintf(asm_lines[iasm_line+1],"LOAD R2, %s",revbuf[2]);
                if(num>4) {
                        //printf("%s %s %s %s %d\n",revbuf[0],revbuf[1],revbuf[2],revbuf[3],num);
                    sprintf(asm_lines[iasm_line+2],"ADD R3, R1, R2");
                    sprintf(asm_lines[iasm_line+3],"STORE %s, R3",revbuf[0]);
                    sprintf(asm_lines[iasm_line+4],"LOAD R1, %s",revbuf[0]);
                    sprintf(asm_lines[iasm_line+5],"LOAD R2, %s",revbuf[3]);
                    sprintf(asm_lines[iasm_line+6],"ADD R3, R1, R2");
                    sprintf(asm_lines[iasm_line+7],"STORE %s, R3",revbuf[0]);
                    iasm_line=iasm_line+8;
                }
                else {
                    sprintf(asm_lines[iasm_line+2],"ADD R3, R1, R2");
                    sprintf(asm_lines[iasm_line+3],"STORE %s, R3",revbuf[0]);
                    iasm_line=iasm_line+4;
                }

            }
            if(strstr(highc_lines[i],"-") != NULL)
            {
                num = 0;
                line_split(highc_lines[i]," -=;",revbuf,&num);
                //printf("%s %s %s  %d\n",revbuf[0],revbuf[1],revbuf[2],num);
                sprintf(asm_lines[iasm_line],"LOAD R1, %s",revbuf[1]);
                sprintf(asm_lines[iasm_line+1],"LOAD R2, %s",revbuf[2]);
                sprintf(asm_lines[iasm_line+2],"SUB R3, R1, R2");
                sprintf(asm_lines[iasm_line+3],"STORE %s, R3",revbuf[0]);
                iasm_line=iasm_line+4;
            }
            if(strstr(highc_lines[i],"*") != NULL)
            {
                num = 0;
                line_split(highc_lines[i]," *=;",revbuf,&num);
                //printf("%s %s %s  %d\n",revbuf[0],revbuf[1],revbuf[2],num);
                sprintf(asm_lines[iasm_line],"LOAD R1, %s",revbuf[1]);
                sprintf(asm_lines[iasm_line+1],"LOAD R2, %s",revbuf[2]);
                sprintf(asm_lines[iasm_line+2],"MUL R3, R1, R2");
                sprintf(asm_lines[iasm_line+3],"STORE %s, R3",revbuf[0]);
                iasm_line=iasm_line+4;
            }

            if(strstr(highc_lines[i],"/") != NULL)
            {
                num = 0;
                line_split(highc_lines[i]," /=;",revbuf,&num);
                //printf("%s %s %s  %d\n",revbuf[0],revbuf[1],revbuf[2],num);
                sprintf(asm_lines[iasm_line],"LOAD R1, %s",revbuf[1]);
                sprintf(asm_lines[iasm_line+1],"LOAD R2, %s",revbuf[2]);
                sprintf(asm_lines[iasm_line+2],"DIV R3, R1, R2");
                sprintf(asm_lines[iasm_line+3],"STORE %s, R3",revbuf[0]);
                iasm_line=iasm_line+4;
            }

        }

        if(seg_flag==3) //编译输出段
        {
            num = 0;
            line_split(highc_lines[i],";",revbuf,&num);
            // printf("%s %s %s  %d\n",revbuf[0],revbuf[1],revbuf[2],num);
            sprintf(asm_lines[iasm_line],revbuf[0]);
            iasm_line++;
            //printf("%s\n",revbuf[0]);
        }
    }

    iasm_lines_length = iasm_line;

    if(compile_result)
        printf("编译完成，正确\n");
    else
        printf("编译完成，错误\n");

}


void compiler(char file_c[],char file_asm[])
{
    printf("********开始编译********\n");
    FILE *highC_handler,*asm_handle;
    if((highC_handler=fopen(file_c,"r"))==NULL) //高级语言文件//读文件形式打开文件
    {
        printf("无法打开%s文件\n",file_c);
        exit(0);//终止程序
    }
    if((asm_handle=fopen(file_asm,"w"))==NULL) //汇编语言文件
    {
        printf("无法打开%s文件\n",file_asm);
        exit(0);//终止程序
    }

    read_check(highC_handler);

    seg_compile();

    int i;
    for(i=0; i<iasm_lines_length; i++)
    {
        fputs(asm_lines[i],asm_handle);
        fputs("\n",asm_handle);
    }

    fclose(highC_handler);
    fclose(asm_handle);
    printf("\n");
    printf("\n");
}

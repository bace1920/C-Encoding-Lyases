#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int Mode;
extern char *secretKey;

//临时用参数输入接口
void option_in()
{
    printf("inpun Mode\n");
    scanf("%d",&Mode);
    printf("inpun secret\n");
    scanf("%s",&secretKey);
}

//算法选择接口
void select(char *sourcefile,char *targetFile,char *secretKey,int Mode)
{
    if(Mode==1)
    {
       if(encryptFile(sourcefile,targetFile,secretKey,Mode)){
        return 1;}
    }
    //if(Mode==2)
    //{
       //if(encryptFile(fpSource,fpTarget))
       // return 1;
    //}
}

int encryptFile(char *sourcefile,char *targetFile,char *secretKey,char *Mode)
{FILE *fpSource, *fpTarget;  // 要打开的文件的指针
    char buffer[21];  // 缓冲区，用于存放从文件读取的数据
    int readCount,  // 每次从文件中读取的字节数
        keyLen = strlen(secretKey),  // 密钥的长度
        i;  // 循环次数

    // 以二进制方式读取/写入文件
      fpSource = fopen(sourcefile, "rb");
    if(fpSource==NULL){
        printf("[%s] open failed\n", sourcefile);
        return 0;
    }
    fpTarget = fopen(targetFile, "wb");
    if(fpTarget==NULL){
        printf("文件[%s] write filed\n", fpTarget);
        return 0;
    }
    // 不断地从文件中读取 keyLen 长度的数据，保存到buffer，直到文件结束
    while( (readCount=fread(buffer, 1, keyLen, fpSource)) > 0 ){
        // 对buffer中的数据逐字节进行异或运算
        for(i=0; i<readCount; i++){
            buffer[i] ^= secretKey[i];
        }
        // 将buffer中的数据写入文件
        fwrite(buffer, 1, readCount, fpTarget);
    }

    fclose(fpSource);
    fclose(fpTarget);
    return 1;
}

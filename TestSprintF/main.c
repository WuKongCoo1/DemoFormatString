//
//  main.c
//  TestSprintF
//
//  Created by Jacky Walker on 2019/9/9.
//  Copyright © 2019 Jacky Walker. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define myFormatStringByMacro_ReturnFormatString(format, ...) \
({ \
    int size = snprintf(NULL, 0, format, ##__VA_ARGS__);\
    size++; \
    char *buf = (char *)malloc(size); \
    snprintf(buf, size, format, ##__VA_ARGS__); \
    buf; \
});

#define myFormatStringByMacro_WithoutReturn(format, ...) \
do { \
    int size = snprintf(NULL, 0, format, ##__VA_ARGS__);\
    size++; \
    char *buf = (char *)malloc(size); \
    snprintf(buf, size, format, ##__VA_ARGS__); \
    printf("%s", buf); \
    free(buf); \
} while(0)

#define testMarco(a, b) \
do { \
int _a = a + 1; \
int _b = b + 1; \
printf("\n%d", _a + _b); \
} while(0)


#define Log_Debug(format, ...) \
do { \
int size = snprintf(NULL, 0, format, ##__VA_ARGS__);\
size++; \
char *buf = (char *)malloc(size); \
snprintf(buf, size, format, ##__VA_ARGS__); \
doLog(buf); \
free(buf); \
} while(0)



void test()
{
    if (1 > 0)
        testMarco(1, 2);
}

//#define testMarco2(a, b) \
//int _a = a + 1; \
//int _b = b + 1; \
//printf("\n%d", _a + _b); \
//
//void test2()
//{
//    if (1 > 0)
//        testMarco2(1, 2);
//    else {
//        printf("");
//    }
//}

/**
 
 @param __str 接收格式化结果的指针
 @param __size 接收的size
 @param __format 格式化的字符串
 @param ... 可变参数
 @return 返回格式化后实际上写入的大小a，a <= __size
 */
//int     snprintf(char * __restrict __str, size_t __size, const char * __restrict __format, ...) __printflike(3, 4);

void testSnprintf()
{
    printf("------%s------\n", __FUNCTION__);
    char des[50];
    int size = snprintf(des, 50, "less length %d", 50);
    printf("size:%d\n", size);
}

char *myFormatStringByFun(char *format, ...)
{
    va_list list;
    //1. 先获取格式化后字符串的长度
    va_start(list, format);
    int size = vsnprintf(NULL, 0, format, list);
    va_end(list);
    if(size <= 0) {
        return NULL;
    }
    size++;
    
    //2. 复位va_list，将格式化字符串写入到buf
    va_start(list, format);
    char *buf = (char *)malloc(size);
    vsnprintf(buf, size, format, list);
    va_end(list);
    return buf;
}

/**

 @param __str 目标字符串
 @param __size 要赋值的大小
 @param __format 格式化字符串
 @param va_list 可变参数列表
 @return 返回格式化后实际上写入的大小a，a <= __size
 */
//int     vsnprintf(char * __restrict __str, size_t __size, const char * __restrict __format, va_list) __printflike(3, 0);

#define myFormatStringByFunQuick(format, ...) myFormatStringByFun(format, ##__VA_ARGS__);

//-1表示可变参数结束
void receiveVariadic(int a, ...) {
    va_list list;
    va_start(list, a);
    int arg = a;
    while (arg != -1) {
        arg = va_arg(list, int);
        printf("%d ", arg);
    }
    printf("\n");
    va_end(list);
}

void testByMacro1()
{
    printf("------%s------\n", __FUNCTION__);
    char *a = myFormatStringByMacro_ReturnFormatString("format by macro, %d %s", 123, "well done");
    printf("%s\n", a);
    free(a);
}

void testByMacro2()
{
    printf("------%s------\n", __FUNCTION__);
    myFormatStringByMacro_WithoutReturn("format by macro, %d %s", 123, "well done");
    printf("\n");
}


void testByFun()
{
    printf("------%s------\n", __FUNCTION__);
    char *b = myFormatStringByFun("format by fun %d %s", 321, "nice");
    printf("%s\n", b);
}

void testVari()
{
    printf("------%s------\n", __FUNCTION__);
    //-1表示可变参数结束
    receiveVariadic(1, 2, 3, 4, 5, 6, -1);
}

void testMyFormatStringByFunQuick() {
    printf("------%s------\n", __FUNCTION__);
    char *formatString = myFormatStringByFunQuick("amazing happen, %s", "cool");
    printf("%s\n", formatString);
}

int main(int argc, const char * argv[]) {
    
    testSnprintf();
    
    testVari();
    testByMacro1();
    testByMacro2();
    testByFun();

    testMyFormatStringByFunQuick();
    
    return 0;
}

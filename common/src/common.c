#include <stdio.h>
#include <string.h>
#include <stdarg.h>

/*
 *	本文件使用的宏定义
 */
#define MAX_STR_LENGTH 501

#if 0
/*
 *  名称：calc_fmt_input_size
 *  描述：计算格式化输入的字符总数
 *	输入：fmt:       输入格式
 *        valist: 已经初始化了的va_list类型变量
 *	输出：无
 *	返回：格式化输入的字符总数
 *	作者：DZD，2019.9.7
 *	说明：
 */
int calc_fmt_input_size(const char *fmt, va_list valist)
{
	int num = 0;
	int i;
	for(i = 0; fmt[i] != '\0', i++)
	{
		num++;
		if(fmt[i] == '%' && fmt[i+1] != '\0')
		{
			
		}
	}
}
#endif

/*
 *  名称：sys
 *  描述：格式化输入可变参数来调用system函数
 *	输入：fmt: 输入格式
 *        ...: 可变参数
 *	输出：
 *	返回：
 *	作者：DZD，2019.9.7
 *	说明：注意，格式化之后的字符串总长度不能超过MAX_STR_LENGTH，
 *        不然会导致内存越界
 */
void sys(const char *fmt, ...)
{
	char str[MAX_STR_LENGTH];

	if(strlen(fmt))
	memset(str, 0, MAX_STR_LENGTH);
	va_list valist;
	va_start(valist,fmt);
	vsprintf(str, fmt, valist);
	va_end(valist);
	system(str);
}

void sys_ut(void)
{
	sys("mkdir %s", "test");
}

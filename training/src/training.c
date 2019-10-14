#include <stdio.h>
#include <string.h>

/*
 * 题目1：当前路径和相对路径拼接，输出绝对路径
 * 输入： 一个当前路径和一个相对路径
 * 输出： 拼接后输出一个绝对路径
 * 要求： C/C++ 实现，有比较好的模块化，对输入的当前路径和相对路径
 *        要做有效性检查，路径格式都是linux方式
 * 例如： 输入：/usr/local/bin  ../.././//share/./locale
 *        输出：/usr/share/locale
 *        输入：/user/     .././../var/tmp//
 *        输出：/var/tmp/
 *        输入：/user/     .././.../var/tmp/
 *        输出：目录不存在
 *        输入：avd/user/     ../var/tmp/
 *        输出：目录不存在
 */
void q1_dir_cat(char *dir1, char *dir2, char *des)
{
	strcpy(des, dir1);
	strcat(des, "/");
	strcat(des, dir2);
	strcat(des, "/");
}

void q1_dir_clear(char *str)
{
	char temp[100] = {0};
	char *p_src = str;
	char *p_des = temp;
	int flag = 0;
	
	while(*p_src != '\0')
	{
		if(*p_src == '/')
		{
			if(flag)
			{
				p_src++;
				continue;
			}
			else
			{
				flag = 1;
			}
		}
		else
		{
			flag = 0;
		}
		*p_des = *p_src;
		p_src++;
		p_des++;
	}
	//*p_des = '\0';
	strcpy(str,temp);
}

void q1_dir_gen(char *str)
{
	char *p_front = str;
	char *p_back = str;
	char temp[100] = {0};
	char *p_des = temp;
	int num = 0;
	
	while(*p_back != '\0')
	{
		if(*p_back == '.')
		{
			num ++;
		}
		if(*p_back == '/')
		{
			if(num == 1)
			{
				num = 0;
			}
			else if(num == 0)
			{
				for(p_front; p_front <= p_back; p_front++)
				{
					*(p_des++) = *p_front;
				}
			}
			else if(num == 2)
			{
				p_des = p_des - 2;
				while(*p_des != '/')
				{
					if((p_des - temp) < 0)
					{
						printf("Dir doesn't exist!\n");
						return;
					}
					p_des--;
				}
				num = 0;
				p_des++;
			}
			p_front = p_back + 1;
		}
		p_back++;
	}
	*p_des = '\0';
	strcpy(str, temp);
}

void q1_ut(void)
{
	char dir1[] = "/usr/local/bin";
	char dir2[] = "../.././//share/./locale";
	char des[100] = {0};
	q1_dir_cat(dir1,dir2,des);
	q1_dir_clear(des);
	q1_dir_gen(des);
	printf("%s\n",des);
}


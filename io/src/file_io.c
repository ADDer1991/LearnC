#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "type_def.h"
#include "common.h"
#include "file_io.h"
#include <sys/stat.h>
//#include "commdef.h"

/*
 * 本文件使用的宏定义
 */
#define RWRWRW (S_IRUSR | S_IWUSR | S_IRGRP | S_IRGRP | S_IROTH | S_IWOTH)

/*  
 * 名 称: unbuf_io_exmpl
 * 描 述：不带缓冲的文件I/O close,open,read,write函数用法例子
 * 输 入：
 * 输 出：
 * 返 回：
 * 说 明：
 */
void unbuf_fio_exmpl(void)
{
	const char filename[] = "file.txt";
	char str1[] = "abcdefghij";
	char str2[] = "ABCDE";
	char str3[] = "KLMNOPQRST";
	char str4[] = "pqrst";
	char str5[] = "UVWXYZ";
	char temp;
	int  fd;
	size_t cnt;
	off_t offset;
	struct stat state = {0};
	
	/* 以只写方式打开文件，并将长度截断为0，若不存在则创建 */
	fd = open(filename, O_WRONLY|O_CREAT|O_TRUNC);
	
	JUDGE_OPEN_RESULT_AND_RETURN(fd, filename);
	printf("open(O_WRONLY) %s. \n", filename);
	printf("write \"%s\" on offset:%d\n", str1, 0);
	
	/* 写数据 */
	if(strlen(str1) != write(fd, str1, strlen(str1)))
	{
		printf("write \"%s\" failed! \n", str1);
		return;
	}
	
	/* 以文件头为参照设置偏移 */
	offset = lseek(fd, 0, SEEK_SET);  
	
	write(fd, str2, strlen(str2));
	printf("write \"%s\" on offset:%d\n", str2, (int)offset);

	/* 以文件尾为参照设置偏移 */
	offset = lseek(fd, 0, SEEK_END);  
	
	write(fd, str3, strlen(str3));
	printf("write \"%s\" on offset:%d\n", str3, (int)offset);

	/* 以当前位置为参照设置偏移 */
	offset = lseek(fd, -5, SEEK_CUR);  
	
	write(fd, str4, strlen(str4));
	printf("write \"%s\" on offset:%d\n", str4, (int)offset);
	
	/* 关闭文件 */
	close(fd);
	
	printf("close %s.\n", filename);
	printf("open(O_RDONLY) %s. \n", filename);
	
	/* 以只读方式打开文件 */
	fd = open(filename, O_RDONLY);
	if(-1 == fd)
	{
		printf("open %s failed! chmod u+r+x\n", filename);
		
		/* 获取文件权限 */
		stat(filename, &state);
	
		/* 增加文件权限为用户可读、可写、可执行 */
		chmod(filename, state.st_mode | S_IRUSR | S_IWUSR | S_IXUSR);
		
		system("ls -l file.txt");
		fd = open(filename, O_RDONLY);
	}
		
	/* 读取数据 */
	while(0 != (cnt = read(fd, &temp, 1)))
	{
		if(-1 == cnt){
			printf("read data error!\n");
			return;
		}
		printf("%c", temp);
	}
	printf("\n");
	close(fd);
	printf("close %s. \n", filename);

	/* 已读写方式打开文件，写时追加到末尾 */
	fd = open(filename, O_RDWR|O_APPEND);
	
	printf("open(O_RDWR|O_APPEND) %s. \n", filename);
	system("ls -l file.txt");
	JUDGE_OPEN_RESULT_AND_RETURN(fd, filename);
	write(fd, str5, strlen(str5));
	system("cat file.txt");
	printf("\n");
	
	/* 删除文件 */
	if(-1 == remove(filename))
	{
		printf("can't remove %s\n",filename);
	}
	printf("remove %s\n",filename);
}

/*  
 * 名 称: umask_exmpl
 * 描 述：umask函数以及open函数mode_t参数 用法例子
 * 输 入：
 * 输 出：
 * 返 回：
 * 说 明：
 */
void umask_exmpl(void)
{
	int fd;
	const char filename[] = "file_umask.txt";
	
	/* 设置当前文件模式创建屏蔽字 */
	umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	
	/* 以open函数的mode_t参数创建文件 */
	fd = open(filename, O_CREAT, S_IRUSR);
	JUDGE_OPEN_RESULT_AND_RETURN(fd, filename);
	close(fd);
	sys("ls -l %s", filename);
	remove(filename);

	fd = open(filename, O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	JUDGE_OPEN_RESULT_AND_RETURN(fd, "test/file_umask3.txt");
	close(fd);
	sys("ls -l %s", filename);
	remove(filename);
}


#include <stdio.h>

/*
	宏定义
*/
#define MAX_FILENAME_LEN 100       /* 文件名最大字符长度 */

#define JUDGE_OPEN_RESULT_AND_RETURN_ERROCODE(fd, filename, errorcode) \
if(-1 == fd){ \
	printf("Open \"%s\" failed! \n", filename); \
	return errorcode; \
}
#define JUDGE_OPEN_RESULT_AND_RETURN(fd, filename) \
if(-1 == fd){ \
	printf("Open \"%s\" failed! Locate: %s:%d -- %s\n", filename, __FILE__, __LINE__, __func__);  \
	return; \
}

/*
	函数声明
*/
void unbuf_fio_exmpl(void);



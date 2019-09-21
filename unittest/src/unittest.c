#include <stdio.h>
#include "unittest.h"

/*
 * 宏定义
 */
#define GET_FUNCNUM(file)  (sizeof(file)/sizeof(t_testfunc))

/*
 *	类型定义
 */
typedef void (*fp_testfunc)(void);

typedef struct{
    int          index;
    char*        name;
    fp_testfunc  func;
}t_testfunc;

typedef struct{
	int           index;
	char         *name;
	int           func_num;
	t_testfunc   *func_list;
}t_testfile;

/*
 *	全局变量
 */
t_testfunc g_test_file_io[] = 
{
    {0, "unbuf_fio_exmpl", unbuf_fio_exmpl},
    {0xffff, NULL, NULL}  /*结束标志*/
};
t_testfunc g_test_common[] = 
{
    {0, "sys_ut", sys_ut},
    {0xffff, NULL, NULL}  /*结束标志*/
};
	
/* ut测试文件 */
t_testfile g_test_files[] = 
{
	{0, "file_io.c", GET_FUNCNUM(g_test_file_io), g_test_file_io},
	{1, "common.c",  GET_FUNCNUM(g_test_common),  g_test_common},
	{0xffff, NULL, 0, NULL}  /*结束标志*/
};

/*
 *	名称：ut_entry
 *	描述：ut入口函数
 *	输入：无
 *	输出：无
 *	返回：无
 *	作者：DZD
 *	说明：
 */
int ut_entry(void){
	int file_index;
	int func_index;
	t_testfunc *func_list;
	int file_num = sizeof(g_test_files)/sizeof(t_testfile);
	int func_num;
	
	printf("********************  unittest  ********************\n");
	printf("index         file name\n");
    for(file_index = 0; g_test_files[file_index].index != 0xffff; file_index++){
		printf("%d          %s\n", g_test_files[file_index].index, g_test_files[file_index].name);
	}
SELECT_FILE:
	printf("selsec file:\n");
	scanf("%d", &file_index);
	if(file_index < 0 || file_index > g_test_files[file_num-2].index){
		printf("Input wrong! Please reselect:\n");
		goto SELECT_FILE;
	}
	func_list = g_test_files[file_index].func_list;
	func_num  = g_test_files[file_index].func_num;
	printf("====================  %s  ===================\n",g_test_files[file_index].name);
	printf("index          func name\n");
	for(func_index = 0; 0xffff != func_list[func_index].index; func_index++){
		printf("%d           %s\n", func_list[func_index].index, func_list[func_index].name);
	}
	printf("select func:\n"); 
SELECT_FUNC:
	scanf("%d", &func_index);
	if(func_index < 0 || func_index > func_list[func_num-2].index){
		printf("Input wrong! Please reselect:\n");
		goto SELECT_FUNC;
	}
	/*执行测试函数*/
	printf("--------------------  %s  --------------------\n", func_list[func_index].name);
	func_list[func_index].func();
    return 0;
}
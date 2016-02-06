/*
 * =====================================================================================
 *
 *       Filename:  dict.c
 *
 *    Description:  A Dict for me.
 *
 *        Version:  1.0
 *        Created:  12/23/2015 01:47:17 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Lee Sheen (leesheen@outlook.com), 
 *   Organization:  
 *
 * =====================================================================================
 */

#define _GNU_SOURCE
#include "dict.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#undef _GNU_SOURCE

static void print_help()
{

	printf("Usage: dict [options] [value] ...\n");
	printf("<value> has to be either integral(raw mode) or decimal(percent mode) depending on the specified value mode.\n");
	printf("<options> can be any of the following:\n\n");

	printf("Operations:\n");
	printf("  -H -h:\tPrints this help and exits\n");

	printf("\n 请输出需要查询的关键字，比如\n\n ~ dict example\n");
	printf("\n 如果英文段落中有“'”(单引号)等符号，可以在需要翻译的语句前后加半角双引号，比如\n\n ~ dict \"I'm a programmer.\"\n\n");

	return ;
}

static void print_version()
{

	printf("--------\n\n\n\n\n");
	
}

static DICT_BOOL dict_choose_api(DICT_STR *dict_str_tmp, char *optarg)
{
	int i;
	DICT_BOOL is_print_help = TRUE;
	
	dict_str_tmp->is_vaild = FALSE;

	for (i=0; i<DICT_API_NAME_NUM; i++)
		if (NULL !=	strcasestr(g_dict_api_name_array[i], optarg))
		{
			dict_str_tmp->dict_api = i;
			dict_str_tmp->is_vaild = TRUE;
			is_print_help = FALSE;
		}

	return is_print_help;
}


static DICT_BOOL dict_arg_init(DICT_STR *dict_str_tmp,
		int argc, char *argv[])
{
	int i = 0;
	int opt_res	= 0;
	int content_len = 0;
	DICT_BOOL is_print_version = FALSE;
	DICT_BOOL is_print_help = FALSE;

	/* 可选参数默认选项 */
	dict_str_tmp->is_vaild	=	TRUE;
	dict_str_tmp->dict_api	=	API_YOUDAO;		/* TODO 从配置文件中导入*/
	dict_str_tmp->res_in	=	stdin;
	dict_str_tmp->res_out	=	stdout;

	while (-1 != (opt_res = getopt(argc, argv, DICT_OPTSTRING)))
	{
		switch (opt_res) 
		{
			/* 版本 */
			case 'v':
			{
				dict_str_tmp->is_vaild = FALSE;
				is_print_version = TRUE;
				break;
			}

			/* TODO 输入选项 */
			case 'i':
			{break;}

			/* TODO 输出选项 */
			case 'o':
			{break;}

			/* API选择 <baidu> <youdao> etc...*/
			case 'a':
			{
				is_print_help = dict_choose_api(dict_str_tmp, optarg);
				break;
			}

			/* 测试参数 */
			case 'V':
			{break;}

			/* 帮助 */
			case 'H':
			case 'h':
			default:
			{
				is_print_help = TRUE;
				dict_str_tmp->is_vaild = FALSE;
				break;
			}
		}
	}

	/* 填充content_location */
	if ((optind == argc) && (is_print_version != TRUE))
	{
		is_print_help = TRUE;
		dict_str_tmp->is_vaild = FALSE;
	}
	else
		dict_str_tmp->content_location = optind;

	/* 填充content_len */
	for (i=optind; i<argc; i++)
	{
		content_len += strlen(argv[i]);
		content_len += 1;
	}
	dict_str_tmp->content_len = content_len;


	if (is_print_version == TRUE)
		print_version();
	if (is_print_help == TRUE)
		print_help();
	
	return dict_str_tmp->is_vaild;
}

static DICT_BOOL dict_str_add_content(DICT_STR * dict_str_tmp, 
		int argc, char *argv[])
{
	int i;
	int len			= dict_str_tmp->content_len;
	int location	= dict_str_tmp->content_location;

	unsigned char *content = (unsigned char *)malloc(len);
	if (NULL == content) 
		return FALSE;

	memset(content, 0, len);

	/* Strcat what words needs translate */
	for (i=location; i<argc; i++)
	{
		strncat(content, argv[i], strlen(argv[i]));
		strncat(content, " ", 1);
	}
	content[len-1] = '\0';

	dict_str_tmp->content = content; 

	return TRUE;
}


static int dict_init(DICT_STR **dict_str_pp, int argc, char *argv[])
{
	int ret	= ERRNO_INIT;
	int trans_words_len = 0;

	DICT_STR  dict_str_tmp;

	dict_arg_init(&dict_str_tmp, argc, argv);
	if (dict_str_tmp.is_vaild == FALSE)
	{
		printf("[DICT]%s: DICT_STR is vaild.", __func__);
		return ret;
	}

	if (dict_str_add_content(&dict_str_tmp, argc, argv) == FALSE)
	{
		free(dict_str_tmp.content);

		printf("[DICT]%s: DICT_STR add content error.", __func__);
		return ret;
	}

	if ((*dict_str_pp = (DICT_STR *)malloc(sizeof (DICT_STR))) == NULL)
	{
		free(dict_str_tmp.content);

		printf("[DICT]%s: DICT_STR malloc failed.", __func__);
		return ret;
	}
	memcpy(*dict_str_pp, &dict_str_tmp, sizeof (DICT_STR));

	return (ret = ERRNO_SUCCESS);
}

static int dict_exec(DICT_STR *dict_str_p)
{
	int ret = 0;

	//baidu_translate(resout, trans_chars);
//	youdao_translate(resout, trans_chars);

	return ret;
}

static void dict_free(DICT_STR *dict_str_p)
{
	free(dict_str_p->content);
	free(dict_str_p);
	return ;
}

int main(int argc, char *argv[])
{
	int	ret = 0;
	DICT_STR *my_dict_str = NULL;

	ret = dict_init(&my_dict_str, argc, argv);
	if (ERRNO_INIT == ret)
	{
		/* 如果没有初始化此结构体，说明用户执行 --help ,
		 * 并没有出错，所有此处不打印出错信息，直接返回。
		 * 而对于程序来说，--help或者错误的参数也是程序
		 * 没有正确执行的一部分，所以main仍返回错误。*/
		if (NULL != my_dict_str)
			printf("[DICT]%s: Initialization Failed.", __func__);

		return ret;
	}
	
	ret = dict_exec(my_dict_str);
	if (ERRNO_EXEC == ret)
		printf("[DICT]%s: Execution Failed.", __func__);

	dict_free(my_dict_str);

	return ret;
}


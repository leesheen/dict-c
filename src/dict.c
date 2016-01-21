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
 *	　注： 词典结果只支持中英互译，翻译结果支持英日韩法俄西到中文的翻译以及中文
 *	到英语的翻译
 *	errorCode：
 *	　0 - 正常
 *	　20 - 要翻译的文本过长
 *	　30 - 无法进行有效的翻译
 *	　40 - 不支持的语言类型
 *	　50 - 无效的key
 *	　60 - 无词典结果，仅在获取词典结果生效
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dict.h"


int main(int argc, char *argv[])
{
	FILE	*resout = stdout;
	int		i;
	char 	trans_chars[TRANS_CHARS_BUF] = {0};
	char 	trans_char[TRANS_CHARS_BUF] = {0};

	if (argc < 2)
	{
		for (i=0; i<30; i++)
			printf("-");
		printf("\n 请输出需要查询的关键字，比如\n\n ~ dict example\n");
		printf("\n 如果英文段落中有“'”(单引号)等符号，可以在需要翻译的语句前后加半角双引号，比如\n\n ~ dict \"I'm a programmer.\"\n\n");
		return 0;
	}
	printf("********************************\n\n"); 

	/* Strcat what words needs translate */
	for (i=1; i<argc; i++)
	{
		strcat(trans_chars, argv[i]);
		strcat(trans_chars, " ");
	}
	
	baidu_translate(resout, trans_chars);
	//youdao_translate(resout, trans_chars);

	printf("\n********************************\n"); 

	return 0;
}



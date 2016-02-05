/*
 * =====================================================================================
 *
 *       Filename:  dict.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/23/2015 02:35:52 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef __DICT_H__
#define __DICT_H__

//#define _DEBUG_

#include "errno.h"

#include <stdio.h>

/* URL地址char数组的存储大小 */
#define TRANS_CHARS_BUF	300
#define URL_BUF	1000
#define URL_ENCODE_BUF	800
/* end */

/* 各种API的宏 */
#define NO_YOUDAO	0
#define NO_BAIDU	1
/* end */

/* 执行URL生成文件的存储位置 */
#define URL_FILE_NAME 	"/tmp/url_tmp.no"
#define TMP_FN_SIZE		20

#define GENERATE_FILENAME(filename, useno) \
	sprintf(filename, "%s%d", URL_FILE_NAME, useno)
/* end */

#define DICT_OPTSTRING	"HhVvi:o:a:"

typedef enum DICT_BOOL {
	TRUE = 0,
	FALSE,
} DICT_BOOL;


#define DICT_API_NAME_NUM	3
typedef enum DICT_API {
	API_YOUDAO = 0,
	API_BAIDU,
	API_GOOGLE,
} DICT_API;

typedef struct dict_str {
	DICT_BOOL 		is_vaild;
	DICT_API 		dict_api;
	FILE 			*res_in;
	FILE 			*res_out;

	int 			content_len;
	int 			content_location;
	unsigned char 	*content;
} DICT_STR;


static unsigned char g_dict_api_name_array[DICT_API_NAME_NUM][7] = {"youdao", "baidu", "google"};

extern int url_handle(char *url_addr, int useno); 
extern int xml_analyse(FILE *resout, int useno, char *xpath);
extern int json_analyse(FILE *resout, int useno, char *xpath);

extern int youdao_translate(FILE *resout, char *arg);
extern int baidu_translate(FILE *resout, char *arg);

#endif

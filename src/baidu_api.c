/*
 * =====================================================================================
 *
 *       Filename:  baidu_api.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/17/2016 12:41:14 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <openssl/md5.h>
#include <samba-4.0/libsmbclient.h>

#include "../include/dict.h"
#include "../include/baidu_api.h"


static void generate_md5(char *out_buf, 
						char *appid,
						char *arg, 
						char *salt, 
						char *key)
{
	int i;
	unsigned char buf[URL_BUF] 		= {0};	
	unsigned char md5_buf[36]		= {0};
	unsigned char md5_tmp[16]		= {0};
	unsigned char tmp[3]			= {0};
	
	strcat(buf, appid);
	strcat(buf, arg);
	strcat(buf, salt);
	strcat(buf, key);
	
	MD5(buf, strlen(buf), md5_tmp);
 
	for (i=0; i<16; i++)
	{
		memset(tmp, 0, 3);
		sprintf(tmp,"%02x", md5_tmp[i]);
		strcat(md5_buf, tmp);
	}

	memcpy(out_buf, md5_buf, sizeof(md5_buf));
	
	return ;
}

int baidu_translate(FILE *resout, char *arg)
{
	int ret = 0;

	unsigned char url_buf[URL_BUF] 	= {0};	
	unsigned char q[URL_ENCODE_BUF]	= {0};
	unsigned char salt[12]			= {0};
	unsigned char sign[36]		= {0};

	unsigned char *apiaddr	=	BD_API_ADDR;
	unsigned char *appid	= 	BD_APPID;
	unsigned char *key 		=	BD_KEY;
	unsigned char *from		=	BD_FROM;
	unsigned char *to		=	BD_TO_ZH;

	/* 生成一个随机数 */
	srand((unsigned int)time(NULL));
	sprintf(salt, "%d", rand());

	/* 拼接appid+q+随机数+密钥的字符串取MD5 */
	generate_md5(sign, appid, arg, salt, key);

	/* 对翻译内容应该进行URLEncode编码 */
	smbc_urlencode(q, arg, URL_ENCODE_BUF);

	sprintf(url_buf, 
			"%sq=%s&from=%s&to=%s&appid=%s&salt=%s&sign=%s",
			apiaddr, q, from, to, appid, salt, sign);

	/* 执行URL链接 */
	ret = url_handle(url_buf, NO_BAIDU);
	if (0 != ret)
	{
		printf("url_handle error.\n");
		goto err_url;
	}

err_url:
	return ret;
}


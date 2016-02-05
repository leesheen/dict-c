/*
 * =====================================================================================
 *
 *       Filename:  youdao_api.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/23/2015 10:14:44 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "dict.h"
#include "youdao_api.h"

#include <samba-4.0/libsmbclient.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <unistd.h>


int youdao_translate(FILE *resout, char *arg)
{
	int ret = 0;

	char url_buf[URL_BUF] 	= {0};	/* 126 is calculated for addrs etc.. */
	char q[URL_ENCODE_BUF]	= {0};

	char *apiaddr	=	YD_API_ADDR;
	char *key 		=	YD_KEY;
	char *keyfrom 	=	YD_KEYFROM;
	char *type		=	YD_TYPE;
	char *doctype	=	YD_DOCTYPE;
	char *version	=	YD_VERSION;
	char *only		=	YD_ONLY;

	/* 对翻译内容应该进行URLEncode编码 */
	smbc_urlencode(q, arg, URL_ENCODE_BUF);

	/* 检查错误码用 */
//	strcpy(q, arg);		

	/* 有道词典xml方式查询格式：
	 * http://fanyi.youdao.com/openapi.do?keyfrom=leekeytest&
	 * key=1497748453&type=data&doctype=<doctype>&version=1.1&q=要翻译的文本 */
	sprintf(url_buf, 
			"%skeyfrom=%s&key=%s&type=%s&doctype=%s&version=%s&only=%s&q=%s",
			apiaddr, keyfrom, key, type, doctype, version, only, q);

	/* 执行URL链接 */
	ret = url_handle(url_buf, NO_YOUDAO);
	if (0 != ret)
	{
		printf("url_handle error.\n");
		goto err_url;
	}

#if 0				
	/* 检查翻译结果是否正确 */
	ret = xml_analyse(resout, NO_YOUDAO, YD_XML_NAME(YD_NAME_ERROR));

	/* 显示需要翻译的文字 */
	ret = xml_analyse(resout, NO_YOUDAO, YD_XML_NAME(YD_NAME_TRANSLATION));
	if (0 != ret)
	{
		if (-1 == ret)

		goto err_xml;
	}
#endif

	if (!strcmp(YD_TYPE, "xml"))		/* XML方式解析 */
	{
		/* 显示需要翻译的文字 */
		ret = xml_analyse(resout, NO_YOUDAO, YD_XML_NAME(YD_NAME_QUERY));
		if (0 != ret)
		{
			if (-1 == ret)
				printf("Translation Failed, please check network.\n");
			printf("No results available.\n");
			goto err_xml;
		}

		/* 显示翻译的文字 */
		ret = xml_analyse(resout, NO_YOUDAO, YD_XML_NAME(YD_NAME_TRANSLATE));
		if (0 != ret)
			goto err_xml;
	}
	else 	/* JSON方式解析 */
	{
		ret = json_analyse(resout, NO_YOUDAO, YD_JSON_NAME(YD_NAME_ERROR));
		//ret = json_analyse(resout, NO_YOUDAO, YD_JSON_NAME(YD_NAME_TRANSLATION));
		ret = json_analyse(resout, NO_YOUDAO, YD_JSON_NAME(YD_NAME_BASIC));
	}


#ifdef _DEBUG_
	printf("%s(): %s\n", __func__, url_buf);
	printf("%s(): chars number = %d\n", __func__, strlen(url_buf));
#endif

err_xml:
err_url:
	return ret;
}


/*
 * =====================================================================================
 *
 *       Filename:  youdao_api.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/28/2015 05:32:10 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */


#define YD_API_ADDR		"http://fanyi.youdao.com/openapi.do?"
#define YD_KEY			"1497748453"
#define YD_KEYFROM		"leekeytest"
#define YD_TYPE			"data"		/* 返回结果的类型，固定为data */
#define YD_DOCTYPE		"json"		/* 返回结果的数据格式，xml或json或jsonp */
#define YD_VERSION		"1.1"		/* 版本，当前最新版本为1.1 */
#define YD_ONLY			""			/* 可选参数，dict表示只获取词典数据
								   translate表示只获取翻译数据，默认为都获取*/

#define YD_NAME_ERROR		"errorCode"
#define YD_NAME_QUERY		"query"
#define YD_NAME_TRANSLATE	"paragraph"
#define YD_NAME_TRANSLATION	"translation"
#define YD_NAME_BASIC		"basic"

#define YD_XML_NAME(name) 	strcat("\\", name)
#define YD_JSON_NAME(name) 	name

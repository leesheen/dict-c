/*
 * =====================================================================================
 *
 *       Filename:  json_analyse.h
 *
 *    Description:  json analyse include file
 *
 *        Version:  1.0
 *        Created:  02/12/2016 01:06:09 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Lee Sheen (lee), leesheen@outlook.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __JSON_ANALYSE_H__
#define __JSON_ANALYSE_H__

#include "dict.h"

#define JSON_C_0_10_VERSION ((0<<16) | (10<<8) | 0)

typedef struct json_string_value {
	int num;
	char **string;
	char **value;
} JSON_SV;


extern DICT_BOOL json_init(JSON_SV *json_sv);
extern void json_free(JSON_SV *json_sv);
extern DICT_BOOL json_analyse_form_file(const char *filename, 
		JSON_SV *json_sv);

#endif

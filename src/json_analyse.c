/*
 * =====================================================================================
 *
 *       Filename:  json_analyse.c
 *
 *    Description:  json analyse functions.
 *
 *        Version:  1.0
 *        Created:  12/29/2015 03:25:47 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Lee Sheen (lee), leesheen@outlook.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "json_analyse.h"

#include "dict.h"

#include <json-c/json.h>

#include <stdio.h>
#include <string.h>

static DICT_BOOL json_sv_init(JSON_SV *json_sv_p)
{
	int i;
	int num = json_sv_p->num;

	if ((json_sv_p->string = (char **) malloc(num * sizeof (char *))) == NULL)
	{
		printf("[DICT]%s: alloc sv string error.", __func__);
		return FALSE;
	}
	if ((json_sv_p->value = (char **) malloc(num * sizeof (char *))) == NULL)
	{
		printf("[DICT]%s: alloc sv string error.", __func__);
		return FALSE;
	}

	for (i=0; i<num; i++)
	{
		json_sv_p->string[i] = NULL;
		json_sv_p->value[i] = NULL;
	}

	return TRUE;
}

static void json_sv_free(JSON_SV *json_sv_p)
{
	int i;
	int num = json_sv_p->num;

	for (i=0; i<num; i++)
	{
		free(json_sv_p->string[i]);
		free(json_sv_p->value[i]);
	}

	free(json_sv_p->string);
	free(json_sv_p->value);
}

static char* const json_alloc_string(const char *value, int len)
{
	char *str_p = NULL;

	if (len != strlen(value))
	{
		printf("[DICT]%s: Value error.", __func__);
		return NULL;
	}

	if ((str_p = (char *) malloc(len+1)) == NULL)
	{
		printf("[DICT]%s: String malloc failed.", __func__);
		return NULL;
	}

	memset(str_p, 0, len+1);
	memcpy(str_p, value, len);

	return str_p;
}

static char * const json_get_one_object(json_object *file_object, const char *keyword)
{
	int i;
	char *ret = NULL;

#if (JSON_C_VERSION_NUM >= JSON_C_0_10_VERSION)
	json_bool ct_bool;
#endif

	json_object *ct_object 	= NULL;

	/* JSON object_get changed when version greater than 0.10  */
#if (JSON_C_VERSION_NUM >= JSON_C_0_10_VERSION)
	ct_bool = json_object_object_get_ex(file_object, keyword, &ct_object);
	if (!ct_bool)
#else
	ct_object = json_object_object_get(file_object, keyword);
	if (NULL == ct_object)
#endif
	{
		printf("[DICT]%s: JSON get error.", __func__);
		return NULL;
	}

	ret = json_alloc_string(json_object_get_string(ct_object),
			json_object_get_string_len(ct_object));

	json_object_put(ct_object);

	return ret;
}

static DICT_BOOL json_get_object(JSON_SV *json_sv, json_object *file_object)
{
	DICT_BOOL ret;
	int i;
	int num = json_sv->num;


	for (i=0; i<num; i++)
	{
		if ((json_sv->value[i] = json_get_one_object(file_object, json_sv->string[i])) == NULL)
		{
			printf("[DICT]%s: JSON get object error.", __func__);
			return FALSE;
		}
	}

	return TRUE;
}


DICT_BOOL json_init(JSON_SV *json_sv)
{
	if (json_sv_init(json_sv) == FALSE)
	{
		printf("[DICT]%s: JSON string & value error.", __func__);
		return FALSE;
	}

	return TRUE;
}

void json_free(JSON_SV *json_sv)
{
	json_sv_free(json_sv);
}


DICT_BOOL json_analyse_string_form_file(const char *filename, 
		JSON_SV *json_sv)
{
	DICT_BOOL ret = TRUE;

	json_object *file_object = NULL;
	
	file_object = json_object_from_file(filename);
	if (NULL == file_object)
	{
		printf("[DICT]%s: JSON data error.", __func__);
		return (ret = FALSE);
	}

	ret = json_get_object(json_sv, file_object);

	json_object_put(file_object);

	return ret;
}


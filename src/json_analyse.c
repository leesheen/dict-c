/*
 * =====================================================================================
 *
 *       Filename:  json_analyse.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/29/2015 03:25:47 PM
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
#include <json-c/json.h>

#include "dict.h"

int json_analyse(FILE *resout, int useno, char *xpath)
{
	int 	ret = 0;
	char 	filename[TMP_FN_SIZE]	= {0};

	json_object *file_object = NULL;
	json_object *ct_object 	= NULL;
	
	GENERATE_FILENAME(filename, useno);

	file_object = json_object_from_file(filename);
	if (NULL == file_object)
	{
		printf("JSON Data Error.\n");
		goto err_file;
	}

	ct_object = json_object_object_get(file_object, xpath);
	if (NULL == ct_object)
	{
		printf("JSON Get Error.\n");
		goto err_content;
	}

	printf("%s\n", json_object_to_json_string(ct_object));

	json_object_put(ct_object);

err_content:
	json_object_put(file_object);
err_file:
	return ret;;
}


/*
 * =====================================================================================
 *
 *       Filename:  url_handle.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/26/2015 11:38:08 PM
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
#include <errno.h>
#include <curl/curl.h>

#include "../include/dict.h"

int url_handle(char *url_addr, int useno)
{
	int 		ret	= 0;
	char 		filename[TMP_FN_SIZE] = {0};
	FILE		*fp;

	CURL 		*curl;
	CURLcode 	res;

	GENERATE_FILENAME(filename, useno);

	if (NULL == (fp = fopen(filename , "w")))
	{
		ret = -1;
		perror("url_handle() fopen error");
		goto err_fopen;
	}

	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, url_addr);
		/* URL 的数据存储到临时文件中 */
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		//curl_easy_setopt(curl, CURLOPT_READDATA, fp);
		
		res = curl_easy_perform(curl);
		if (CURLE_OK != res)
		{
			ret = -1;
			printf("url_handle() curl error %d\n", res);
			goto err_curl;
		}
	}


err_curl:
	
	curl_easy_cleanup(curl);
	fclose(fp);

err_fopen:
	
	return 0;
}



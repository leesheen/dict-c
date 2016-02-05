/*
 * =====================================================================================
 *
 *       Filename:  xml_handle.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/27/2015 01:15:16 PM
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

#include <libxml/parser.h>
#include <libxml/xpath.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int xml_analyse(FILE *resout, int useno, char *xpath)
{
	int		i, ret = 0;
	char 	filename[30] = {0};

	xmlChar				*xml_char = (xmlChar *)xpath;
	xmlDocPtr			xml_doc;
	xmlXPathContextPtr	xml_context;
	xmlXPathObjectPtr	xml_object;
	xmlNodeSetPtr		xml_node;

	GENERATE_FILENAME(filename, useno);

	xml_doc = xmlParseFile(filename);
	if (NULL == xml_doc)
	{
		ret = -2;
		printf("XML_TMP file not parsed.\n");
		goto err_file;
	}

	xml_context = xmlXPathNewContext(xml_doc);
	if (NULL == xml_context)
	{
		ret = -2;
		printf("XML context Error.\n");
		goto err_content;
	}

	xml_object = xmlXPathEvalExpression(xml_char, xml_context);
	if (NULL == xml_object)
	{
		ret = -2;
		printf("XML context Error.\n");
		goto err_object;
	}

	xml_node = xml_object->nodesetval;

	if (xmlXPathNodeSetIsEmpty(xml_node))
	{
		ret = -1;
		//printf("XML is Empty.\n");
		goto err_empty;
	}

	if (!strcmp(xpath, YD_XML_NAME(YD_NAME_ERROR)))
		ret = atoi(XML_GET_CONTENT(xml_node->nodeTab[0]->xmlChildrenNode));
	else
	{
		printf("number: %d\n", xml_node->nodeNr);
		for (i=0; i<xml_node->nodeNr; i++)
		{
			fprintf(resout, "%s\t", XML_GET_CONTENT(xml_node->nodeTab[i]->xmlChildrenNode));
		}
		printf("\n");
	}

err_empty:
	xmlXPathFreeObject(xml_object);
err_object:
	xmlXPathFreeContext(xml_context);
err_content:
	xmlFreeDoc(xml_doc);
err_file:

	return ret;
}

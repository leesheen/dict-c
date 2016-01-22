# =====================================================================================
#
#		Filename:		Makefile
#
#		Description:	Main Makefile for C/C++ Programs
#
#		Version:		1.0
#		Created:		12/23/2015 01:47:17 PM
#		Revision:		none
#		Compiler:		GCC
# 
#		Author:			Lee Sheen (leesheen@outlook.com), 
#		Organization: 
#
# =====================================================================================

DIR_BIN = bin
SUB_DIRS = src

INC = 
LIB = -lcurl -lxml2 -lsmbclient -ljson-c -lssl -lcrypto

CC = gcc
CC_FLAG = -Wall

PRG = $(DIR_BIN)/dict

OBJ = dict.o url_handle.o xml_analyse.o youdao_api.o \
	  json_analyse.o baidu_api.o

export INC LIB CC CC_FLAG PRG OBJ DIR_BIN

all: checkdir $(SUB_DIRS)

checkdir:
	@mkdir -p $(DIR_BIN)

$(SUB_DIRS): ECHO
	@make -C $@

ECHO:
	@echo GCC is completing...

.PRONY:clean
clean:
	@echo "Removing linked and compiled files......"
	@rm -f $(SUB_DIRS)/*.o
	@rm -rf $(PRG)
	@echo "OK"

###########################################
# Makefile for simple programs
###########################################
INC =
LIB = -lcurl -lxml2 -lsmbclient -ljson-c -lssl -lcrypto

CC = gcc
CC_FLAG = -Wall

PRG = dict
OBJ = dict.o url_handle.o xml_analyse.o youdao_api.o \
	  json_analyse.o baidu_api.o

$(PRG):$(OBJ)
		$(CC) $(INC) $(LIB) -o $@ $(OBJ)
			
.SUFFIXES: .c .o .cpp
.cpp.o:
	$(CC) $(CC_FLAG) $(INC) -c $*.cpp -o $*.o

.PRONY:clean
clean:
	@echo "Removing linked and compiled files......"
	rm -f $(OBJ) $(PRG)

# =====================================================================================
#
#		Filename:		Makefile
#
#		Description:	Sub Makefile for C/C++ Programs
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

../$(PRG):$(OBJ)
	$(CC) $(INC) $(LIB) -o $@ $(OBJ)
			
.SUFFIXES: .c .o .cpp
.cpp.o:
	$(CC) $(CC_FLAG) $(INC) -c $*.cpp -o $*.o


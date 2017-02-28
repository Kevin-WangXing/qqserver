.SUFFIXEX: .cpp .o

CC = g++

SRCS1 = serverqq.cpp\
		pub.cpp\
		work.cpp

OBJS1 = $(SRCS1: .cpp=.o)

EXEC1 = qqserverd


all:$(OBJS1) 
	$(CC) -o $(EXEC1) $(OBJS1)
	

	@echo '^^^^^^^^^^^^^^^^^^^^^OK^^^^^^^^^^'
	
.cpp .o:
	$(CC) -Wall -g -o $@ -c $<
clean:
	rm -f $(OBJS1) 
	rm -f core*

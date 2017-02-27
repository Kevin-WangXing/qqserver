//============================================================================
// Name        : serverqq.cpp
// Author      : wangxing
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "pub.h"
#include "work.h"

int main(int arg, char *args[])
{
	if(arg < 2)
	{
		printf("usage:qqserverd port\n");
		return -1;
	}
	int iport = atoi(args[1]);//参数转化为整数
	if(iport == 0)
	{
		printf("port %d is invalid\n", iport);
		return -1;
	}

	setdaemon();//将进程设置为daemon状态（即使关闭窗口依旧可以后台工作）
	work w(iport);
	printf("qqserver begin\n");
	return 0;
}

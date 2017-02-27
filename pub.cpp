/*
 * pub.cpp
 *
 *  Created on: 2017-2-27
 *      Author: Administrator
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>


void setdaemon()
{
	pid_t pid, sid;
	pid = fork();//fork一个子进程
	if(pid < 0)
	{
		printf("fork failed %s\n", strerror(errno));
		exit(EXIT_FAILURE);//failure
	}
	if(pid > 0)
	{
		exit(EXIT_SUCCESS);//父进程退出
	}
	if((sid = setsid()) < 0)///子进程调用setsid函数，将进程和控制台脱离关系
	{
		printf("setsid failed %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

int socket_create(int port)//创建参数port指定端口号的server端socket
{
	int st = socket(AF_INET, SOCK_STREAM, 0);//创建TCP socket
	int on = 1;
	if(setsockopt(st, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1)
	{
		printf("setsockopt failed %s\n", strerror(errno));
		return 0;
	}
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(st, (struct sockaddr *)&addr, sizeof(addr)) == -1)
	{
		printf("bind port %d failed %s\n", port, strerror(errno));
		return 0;
	}
	if(listen(st, 300) == -1)
	{
		printf("listen failed %s\n", strerror(errno));
		return 0;
	}
	return st;//返回listen的socket描述符
}
























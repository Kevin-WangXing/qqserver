/*
 * work.cpp
 *
 *  Created on: 2017-2-27
 *      Author: Administrator
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include "work.h"
#include "pub.h"

work::work(int port)
{
	memset(socket_client, 0, sizeof(socket_client));
	listen_st = socket_create(port);//创建server端socket
	if(listen_st == 0)
		exit(-1);//创建socket失败，程序退出
}

work::~work()
{

}

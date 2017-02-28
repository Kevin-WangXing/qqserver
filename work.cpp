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

int work::setnonblocking(int st)//设置socket为非阻塞e
{
	int opts = fcntl(st, F_GETFL);
	if(opts < 0)
	{
		printf("fcntl failed %s\n", strerror(errno));
		return 0;
	}
	opts = opts | O_NONBLOCK;
	if(fcntl(st, F_SETFL, opts) < 0)
	{
		printf("fcntl failed %s\n", strerror(errno));
		return 0;
	}
	return 1;
}

int work::socket_accept()
{
	struct sockaddr_in client_addr;
	socklen_t len = sizeof(client_addr);
	memset(&client_addr, 0, sizeof(client_addr));
	int client_st = accept(listen_st, (struct sockaddr *)&client_addr, &len);//接受来自client的消息

	if(client_st < 0)
		printf("accept failed %s\n", strerror(errno));
	else
		printf("accept by %s\n", inet_ntoa(client_addr.sin_addr));
	return client_st;
}

int work::socket_recv(int st)
{
	return 0;
}

void work::user_logout(int st)//client socket 数据断开
{

}

void work::run()
{
	struct epoll_event ev, events[CLIENTCOUNT];//声明epoll_event结构体的变量，ev用于注册事件，events数组用于回传要处理的事件
	setnonblocking(listen_st);//设置服务端listen的socket为非阻塞
	int epfd = epoll_create(CLIENTCOUNT);
	ev.data.fd = listen_st;//将listen_st放入epoll
	ev.events = EPOLLIN | EPOLLERR | EPOLLHUP;
	epoll_ctl(epfd, EPOLL_CTL_ADD, listen_st, &ev);

	int st = 0;
	while(1)
	{
		//epoll_wait阻塞，直到epoll当中的socket有指定的消息产生
		int nfds = epoll_wait(epfd, events, CLIENTCOUNT, -1);
		if(nfds == -1)
		{
			printf("epoll_wait failed %s\n", strerror(errno));
			break;
		}

		for(int i = 0; i < nfds; i++)//循环处理epoll_wait返回所有出事的socket
		{
			if(events[i].data.fd < 0)
				continue;
			if(events[i].data.fd == listen_st)//代表listen_st收到了来自客户端的connect
			{
				st = socket_accept();
				if(st >= 0)
				{
					setnonblocking(st);
					ev.data.fd = st;
					ev.events = EPOLLIN | EPOLLERR | EPOLLHUP;
					epoll_ctl(epfd, EPOLL_CTL_ADD, st, &ev);
					continue;
				}
			}
			if(events[i].events & EPOLLIN)//有来自client的数据
			{
				st = events[i].data.fd;//得到有数据的socket
				if(socket_recv(st) <= 0)
				{
					user_logout(st);
					events[i].data.fd = -1;
				}
			}

			if(events[i].events & EPOLLERR)//有来自client出错
			{
				st = events[i].data.fd;
				user_logout(st);
				events[i].data.fd = -1;
			}

			if(events[i].events & EPOLLHUP)//有来自client关闭
			{
				st = events[i].data.fd;
				user_logout(st);
				events[i].data.fd = -1;
			}

		}
	}
	close(epfd);
}





















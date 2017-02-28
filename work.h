/*
 * work.h
 *
 *  Created on: 2017-2-27
 *      Author: Administrator
 */

#ifndef WORK_H_
#define WORK_H_

#define CLIENTCOUNT 256   //clientcount
#define BODYBUF 1024

struct msg_t
{
	unsigned char head[4];
	char body[BODYBUF];
};

class work
{
public:
	work(int port);
	~work();

	void run();

private:
	int listen_st;
	int socket_client[CLIENTCOUNT];//声明socket_client数组，管理client的socket链接

	int setnonblocking(int st);//设置socket为非阻塞e
	int socket_accept();
	int socket_recv(int st);
	void user_logout(int st);//client socket连接断开

};

#endif /* WORK_H_ */

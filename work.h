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

private:
	int listen_st;
	int socket_client[CLIENTCOUNT];//声明socket_client数组，管理client的socket链接

};

#endif /* WORK_H_ */

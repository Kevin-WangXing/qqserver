/*
 * pub.h
 *
 *  Created on: 2017-2-27
 *      Author: Administrator
 */

#ifndef PUB_H_
#define PUB_H_


void setdaemon();
int socket_create(int port);

int signal1(int signo, void (*func)(int));
void catch_Signal(int Sign);

#endif /* PUB_H_ */

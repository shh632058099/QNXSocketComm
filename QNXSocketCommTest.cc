#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <fcntl.h>
#include <thread>

#include "CSocketBase.h"
#include "CSocketServer.h"
#include "CSocketImpl.h"


static struct timespec StartTimeStamp;
int send_test(int id)
{
	sleep(1);
	CIPCBase* pObj = GetIPCSingelObject();
	pObj->Create("server_socket", 0);
	pObj->RegisterReceiveDataCallBack([](int appid, char *pData, int len){
		printf("0 Get data From Server:%s\n", pData);
	});
	char buf[32];
	int i = 0;
	while(i<2)
	{
		snprintf(buf, 31, "data[%d]", i++);
		clock_gettime(CLOCK_REALTIME, &StartTimeStamp);
		pObj->Send(buf, sizeof(buf), 0);
		usleep(1000*1000);
	}
	pObj->Destroy();
}


int receive()
{
	CIPCBase* pObj = GetIPCServerSingelObject();
	pObj->Create("server_socket", 0);
}

int main(int argc, char *argv[])
{
	std::cout << "Welcome to the QNX Momentics IDE" << std::endl;
	std::thread([](){

		sleep(1);
		CIPCBase* pObj = new CSocketImpl();
		pObj->Create("server_socket", 1);
		pObj->RegisterReceiveDataCallBack([](int appid, char *pData, int len){
			struct timespec endTimeStamp;
			clock_gettime(CLOCK_REALTIME, &endTimeStamp);
			printf("1 Get data From Server:%s timestamp[%ld ns]\n", pData, (endTimeStamp.tv_nsec - StartTimeStamp.tv_nsec));
		});

		char buf[32];
		int i = 0;
		while(i<2)
		{
			snprintf(buf, 31, "data[%d]", i++);
			clock_gettime(CLOCK_REALTIME, &StartTimeStamp);
			pObj->Send(buf, sizeof(buf), 0);
			usleep(1000*1000);
		}
		pause();


	}
			).detach();


	std::thread([](){

		sleep(1);
		CIPCBase* pObj = new CSocketImpl();
		pObj->Create("server_socket", 2);
		pObj->RegisterReceiveDataCallBack([](int appid, char *pData, int len){
			struct timespec endTimeStamp;
			clock_gettime(CLOCK_REALTIME, &endTimeStamp);
			printf("1 Get data From Server:%s timestamp[%ld ns]\n", pData, (endTimeStamp.tv_nsec - StartTimeStamp.tv_nsec));
		});

		char buf[32];
		int i = 0;
		while(i<2)
		{
			snprintf(buf, 31, "data[%d]", i++);
			clock_gettime(CLOCK_REALTIME, &StartTimeStamp);
			pObj->Send(buf, sizeof(buf), 0);
			usleep(1000*1000);
		}
		pause();

	}
			).detach();

	std::thread([](){

		sleep(1);
		CIPCBase* pObj = new CSocketImpl();
		pObj->Create("server_socket", 3);
		pObj->RegisterReceiveDataCallBack([](int appid, char *pData, int len){
			struct timespec endTimeStamp;
			clock_gettime(CLOCK_REALTIME, &endTimeStamp);
			printf("1 Get data From Server:%s timestamp[%ld ns]\n", pData, (endTimeStamp.tv_nsec - StartTimeStamp.tv_nsec));
		});

		char buf[32];
		int i = 0;
		while(i<2)
		{
			snprintf(buf, 31, "data[%d]", i++);
			clock_gettime(CLOCK_REALTIME, &StartTimeStamp);
			pObj->Send(buf, sizeof(buf), 0);
			usleep(1000*1000);
		}
		pause();

	}
			).detach();


	std::thread([](){

		sleep(1);
		CIPCBase* pObj = new CSocketImpl();
		pObj->Create("server_socket", 4);
		pObj->RegisterReceiveDataCallBack([](int appid, char *pData, int len){
			struct timespec endTimeStamp;
			clock_gettime(CLOCK_REALTIME, &endTimeStamp);
			printf("1 Get data From Server:%s timestamp[%ld ns]\n", pData, (endTimeStamp.tv_nsec - StartTimeStamp.tv_nsec));
		});

		char buf[32];
		int i = 0;
		while(i<2)
		{
			snprintf(buf, 31, "data[%d]", i++);
			clock_gettime(CLOCK_REALTIME, &StartTimeStamp);
			pObj->Send(buf, sizeof(buf), 0);
			usleep(1000*1000);
		}
		pause();

	}
			).detach();


	std::thread([](){

		sleep(1);
		CIPCBase* pObj = new CSocketImpl();
		pObj->Create("server_socket", 5);
		pObj->RegisterReceiveDataCallBack([](int appid, char *pData, int len){
			struct timespec endTimeStamp;
			clock_gettime(CLOCK_REALTIME, &endTimeStamp);
			printf("1 Get data From Server:%s timestamp[%ld ns]\n", pData, (endTimeStamp.tv_nsec - StartTimeStamp.tv_nsec));
		});
		char buf[32];
		int i = 0;
		while(i<2)
		{
			snprintf(buf, 31, "data[%d]", i++);
			clock_gettime(CLOCK_REALTIME, &StartTimeStamp);
			pObj->Send(buf, sizeof(buf), 0);
			usleep(1000*1000);
		}
		pause();

	}
			).detach();


	std::thread([](){

		sleep(1);
		CIPCBase* pObj = new CSocketImpl();
		pObj->Create("server_socket", 6);
		pObj->RegisterReceiveDataCallBack([](int appid, char *pData, int len){
			struct timespec endTimeStamp;
			clock_gettime(CLOCK_REALTIME, &endTimeStamp);
			printf("1 Get data From Server:%s timestamp[%ld ns]\n", pData, (endTimeStamp.tv_nsec - StartTimeStamp.tv_nsec));
		});
		char buf[32];
		int i = 0;
		while(i<2)
		{
			snprintf(buf, 31, "data[%d]", i++);
			clock_gettime(CLOCK_REALTIME, &StartTimeStamp);
			pObj->Send(buf, sizeof(buf), 0);
			usleep(1000*1000);
		}
		pause();

	}
			).detach();


	std::thread([](){

		sleep(1);
		CIPCBase* pObj = new CSocketImpl();
		pObj->Create("server_socket", 7);
		pObj->RegisterReceiveDataCallBack([](int appid, char *pData, int len){
			struct timespec endTimeStamp;
			clock_gettime(CLOCK_REALTIME, &endTimeStamp);
			printf("1 Get data From Server:%s timestamp[%ld ns]\n", pData, (endTimeStamp.tv_nsec - StartTimeStamp.tv_nsec));
		});
		char buf[32];
		int i = 0;
		while(i<2)
		{
			snprintf(buf, 31, "data[%d]", i++);
			clock_gettime(CLOCK_REALTIME, &StartTimeStamp);
			pObj->Send(buf, sizeof(buf), 0);
			usleep(1000*1000);
		}
		pause();

	}
			).detach();

	std::thread([](){
		send_test(1);
	}
			).detach();

	receive();

	pause();
	return EXIT_SUCCESS;
}

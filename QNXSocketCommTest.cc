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

int send_test(int id)
{
	sleep(1);
	CSocketBase* pObj = GetSocketCommSingelObject();
	pObj->Create("server_socket", 0);
	pObj->RegisterReceiveDataCallBack([](int appid, char *pData, int len){
		printf("Get data From Server:%s\n", pData);
	});
	char buf[32];
	int i = 0;
	while(1)
	{
		snprintf(buf, 31, "data[%d]", i++);
		pObj->Send(buf, sizeof(buf), 0);
		sleep(1);
	}
}


int receive()
{
	  /* delete the socket file */
	  unlink("server_socket");

	  /* create a socket */
	  int server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

	  struct sockaddr_un server_addr;
	  server_addr.sun_family = AF_UNIX;
	  strcpy(server_addr.sun_path, "server_socket");

	  /* bind with the local file */
	  bind(server_sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

	  /* listen */
	  listen(server_sockfd, 5);

	  int client_sockfd;
	  struct sockaddr_un client_addr;
	  socklen_t len = sizeof(client_addr);
	  while(1)
	  {
			/* accept a connection */
			client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_addr, &len);
		    printf("server out waiting:\n\n");
			std::thread([client_sockfd](){
				char buf[32];
				T_SM_FIRST_PACKET packet;
				while(1)
				{
					read(client_sockfd, &packet, sizeof(packet));
					read(client_sockfd, buf, packet.dataLen);
					printf("get data from client,data[%s]\n", buf);

					write(client_sockfd, &packet, sizeof(packet));
					write(client_sockfd, buf, packet.dataLen);
				}
			}).detach();
	  }

	  return 0;
}

int main(int argc, char *argv[])
{
	std::cout << "Welcome to the QNX Momentics IDE" << std::endl;
	std::thread([](){
		send_test(0);
	}
			).detach();

	std::thread([](){
		send_test(1);
	}
			).detach();

	receive();
	return EXIT_SUCCESS;
}

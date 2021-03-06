/*
 * CSocketImpl.cpp
 *
 *  Created on: 2017-10-31
 *      Author: win7
 */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <mutex>
#include <thread>

#include "CSocketImpl.h"
#include "SMErrorCode.h"

static std::mutex g_socketclient_mutex;

CSocketImpl::CSocketImpl()
{
	Contructor();
}


CSocketImpl::~CSocketImpl()
{
	// TODO Auto-generated destructor stub
}

int CSocketImpl::Create(const char *path, int nAppId)
{
	return Init(path, nAppId);
}

int CSocketImpl::Send(const void* pData, unsigned int nLen, int nAppId)
{
	if (NULL == pData || nLen < 1)
	{
		printf("Invalid params\n");
		return SMErrorCode_InvalidParam;
	}

	if (-1 == m_nSocketFd)
	{
		printf("Socket has not been inited.\n");
		return SMErrorCode_InvalidCall;
	}

	std::lock_guard<std::mutex> auto_lock(g_socketclient_mutex);

	//send first packet
	T_SM_PACKET_DATA firstPac = { 0 };
	firstPac.appId = m_nAppId;
	firstPac.toAppId = nAppId;
	strncpy(firstPac.msgData.lParam, (char*)pData, MAX_PACKET_DATA_LEN - 1);

	firstPac.msgData.lParam[MAX_PACKET_DATA_LEN - 1] = '\0';

	int nWrite = write(m_nSocketFd, &firstPac, sizeof(firstPac));
	if (-1 == nWrite || (unsigned int)nWrite != sizeof(firstPac))
	{
		printf("send data failed ");
		return GetErrorCode(errno);
	}
	return 0;
}

int CSocketImpl::Receive(void* buf, unsigned int nLen)
{
	return 0;
}

int CSocketImpl::Destroy()
{
	if (m_nSocketFd > 0)
	{
		close(m_nSocketFd);
		m_nSocketFd = -1;
	}

	return 0;
}

std::string CSocketImpl::GetImplementVersion()
{
	return "1.0";
}

CIPCBase* GetIPCSingelObject()
{
	return &Singleton<CSocketImpl>::instance();
}

void CSocketImpl::Contructor()
{
	m_nSocketFd = -1;
	m_nAppId = -1;
}

int CSocketImpl::Init(const char* path, int nAppId)
{
	if (-1 != m_nSocketFd || NULL == path)
	{
		printf("socket has been inited\n");
		return SMErrorCode_InvalidCall;
	}

	std::lock_guard<std::mutex> auto_lock(g_socketclient_mutex);
	if (-1 != m_nSocketFd)
	{
		printf("socket has been inited\n");
		return SMErrorCode_InvalidCall;
	}

	/* create a socket */
	int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (-1 == sockfd)
	{
		printf("Create socket failed:[%s]\n", strerror(errno));
		return GetErrorCode(errno);
	}

	struct sockaddr_un address;
	address.sun_family = AF_UNIX;
	strncpy(address.sun_path, path, sizeof(address.sun_path) - 1); //the max len -1

	/* connect to the server */
	int result = connect(sockfd, (struct sockaddr *)&address, sizeof(address));
	if(result == -1)
	{
		printf("connect failed:[%s]\n", strerror(errno));
		int nRet = GetErrorCode(errno);
		Destroy();
		return nRet;
	}
	m_nSocketFd = sockfd;
	m_nAppId = nAppId;

	T_SM_PACKET_DATA packData = { 0 };
	packData.appId = m_nAppId;
	packData.msgData.msgType =SMMsgType_CONNECT;
	write(m_nSocketFd, &packData, sizeof(packData));

	std::thread([this, &packData](){
		while(m_nSocketFd != -1)
		{
			//read first packet
			int nRead = read(m_nSocketFd, (void*)(&packData), sizeof(packData));
			//只接受给自己的数据
			if (nRead > 0 && m_funDataChangeCB && (packData.toAppId == m_nAppId || 0 == packData.toAppId))
			{
				m_funDataChangeCB(packData.appId, packData.msgData.lParam, packData.msgData.wParam);
			}
		}

	}).detach();  //创建线程

	printf("socket init succeess\n");
	return SMErrorCode_Success;
}

void CSocketImpl::RegisterReceiveDataCallBack(SocketDataChangedCallBackProc cb)
{
	m_funDataChangeCB = cb;
}

int CSocketImpl::GetErrorCode(int nError)
{
	int nErrorCoe = SMErrorCode_Success;
	switch (nError)
	{
	case EACCES:
		nErrorCoe = SMErrorCode_PermissionDeny;
		break;
	case ENOMEM:
		nErrorCoe = SMErrorCode_OutOfMemory;
		break;
	case EPROTONOSUPPORT:
		nErrorCoe = SMErrorCode_UnSupported;
		break;
	case EOK:
		nErrorCoe = SMErrorCode_Success;
		break;
	default:
		nErrorCoe = SMErrorCode_Fail;
		break;
	}

	printf("Error occured.id [%d]:[%s]\n", nError, strerror(nError));
	return nErrorCoe;
}

/*
 * CSocketTest.h
 *
 *  Created on: 2017-10-31
 *      Author: win7
 */

#ifndef CSOCKETTEST_H_
#define CSOCKETTEST_H_

#include "CSocketBase.h"
#include "singleton.h"

class CSocketImpl: public CIPCBase
{
public:
	CSocketImpl();
	virtual ~CSocketImpl();

	virtual int Create(const char *path, int nAppId);
	virtual int Destroy();
	virtual int Send(const void *pData, unsigned int nLen, int nAppId);
	virtual int Receive(void *buf, unsigned int nLen);
	virtual std::string GetImplementVersion();
	virtual void RegisterReceiveDataCallBack(SocketDataChangedCallBackProc cb);
private:
	void Contructor();
	int Init(const char *path, int nAppId);
	int GetErrorCode(int nError); //将系统errno转换为内部error code
private:
	int m_nSocketFd;
	int m_nAppId;
	SocketDataChangedCallBackProc m_funDataChangeCB;
};

extern "C" SMAPI_PORT CIPCBase* SMCALL GetIPCSingelObject();

#endif /* CSOCKETTEST_H_ */

#pragma once

#include "ISocketHandler.h"
#include "ListenerSocket.h"

// MySocket コマンド ターゲット

class MySocket : public CAsyncSocket, public IListnerSocketHandler
{
public:
	MySocket();
	virtual ~MySocket();
protected:
	ListenerSocket m_socListener;
	ISocketHandler* m_pHandler;
	bool m_bRunning;
	ConnectionType m_eConnectionType;
	CString m_sIpAddress;
	int m_nPortNumber;
	byte* m_pReadBuffer;
public:
	void Start(ConnectionType eConnectionType, LPCTSTR pIpAddress, int nPort, ISocketHandler* pHandler);
	void End();
	bool IsRunning() const;
protected:
	void BeginClientSocket();
	void BeginServerSocket();
	void EndSocket();
	void NotifyConnected();
	void NotifyReceived(byte* pReadBuffer, int nReadSize);
	void NotifyError();
	void NotifyDisconnected();
public:
	virtual void OnConnect(int nErrorCode) override;
	virtual void OnReceive(int nErrorCode) override;
	virtual void OnSend(int nErrorCode) override;
	virtual void OnClose(int nErrorCode) override;
	virtual void OnAccept() override;
};

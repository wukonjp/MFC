#pragma once

// ISocketHandler コマンド ターゲット

class ISocketHandler
{
public:
	ISocketHandler();
	virtual ~ISocketHandler();
	virtual void OnConnected() = 0;
	virtual void OnReceived(byte* pReadBuffer, int nReadSize) = 0;
	virtual void OnError() = 0;
	virtual void OnDisconnected() = 0;
};



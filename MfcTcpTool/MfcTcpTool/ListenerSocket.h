#pragma once

#include "IListnerSocketHandler.h"

// ListenerSocket コマンド ターゲット

class ListenerSocket : public CAsyncSocket
{
protected:
	IListnerSocketHandler* m_pHandler;

public:
	ListenerSocket(IListnerSocketHandler* pHandler);
	virtual ~ListenerSocket();

protected:
	virtual void OnAccept(int nErrorCode) override;
};



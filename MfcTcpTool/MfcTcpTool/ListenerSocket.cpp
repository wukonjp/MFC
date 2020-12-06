// ListenerSocket.cpp : 実装ファイル
//

#include "pch.h"
#include "ListenerSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ListenerSocket

ListenerSocket::ListenerSocket(IListnerSocketHandler* pHandler)
{
	m_pHandler = pHandler;
}

ListenerSocket::~ListenerSocket()
{
}


// ListenerSocket のメンバー関数


void ListenerSocket::OnAccept(int /*nErrorCode*/)
{
	// TODO: ここに特定なコードを追加するか、もしくは基底クラスを呼び出してください。

	m_pHandler->OnAccept();
}

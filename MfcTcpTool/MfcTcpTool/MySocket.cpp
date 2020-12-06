// MySocket.cpp : 実装ファイル
//

#include "pch.h"
#include "AppSettings.h"
#include "MySocket.h"
#include "ListenerSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// MySocket

WNDPROC DefStaticProc;

// CSocketWndメッセージの調査用
LRESULT CALLBACK MyWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_SOCKET_NOTIFY:
		TRACE(_T("WM_SOCKET_NOTIFY %d\n"), WSAGETSELECTEVENT(lParam));
		break;
	case WM_SOCKET_DEAD:
		TRACE(_T("WM_SOCKET_DEAD %d\n"), WSAGETSELECTEVENT(lParam));
		break;
	default:
		TRACE(_T("WM_OTHER_NOTIFY %d\n"), WSAGETSELECTEVENT(lParam));
		break;
	}

	return CallWindowProc(DefStaticProc, hwnd, message, wParam, lParam);
}

MySocket::MySocket()
	: m_socListener(this)
{
	m_pHandler = NULL;
	m_bRunning = false;
	m_eConnectionType = ConnectionType::Client;
	m_sIpAddress = _T("");
	m_nPortNumber = 0;
	m_pReadBuffer = new byte[SHORT_MAX];
}

MySocket::~MySocket()
{
	if (m_pReadBuffer != NULL)
	{
		delete m_pReadBuffer;
	}
}

// MySocket のメンバー関数

void MySocket::Start(ConnectionType eConnectionType, LPCTSTR pIpAddress, int nPort, ISocketHandler* pHandler)
{
	m_bRunning = true;
	m_pHandler = pHandler;
	m_eConnectionType = eConnectionType;
	m_sIpAddress = pIpAddress;
	m_nPortNumber = nPort;

	switch (eConnectionType)
	{
	case ConnectionType::Client:
		BeginClientSocket();
		break;
	case ConnectionType::Server:
		BeginServerSocket();
		break;
	default:
		NotifyError();
		EndSocket();
		break;
	}
}

void MySocket::End()
{
	NotifyDisconnected();
	EndSocket();
}

bool MySocket::IsRunning() const
{
	return m_bRunning;
}

void MySocket::BeginClientSocket()
{
	while (true)
	{
		if (Create() == FALSE)
		{
			break;
		}
		if (Connect(m_sIpAddress, m_nPortNumber) == FALSE)
		{
			int error = GetLastError();
			if (error != WSAEWOULDBLOCK)
			{
				break;
			}
		}

		// 正常
		return;
	}

	// CSocketWndメッセージの調査用
	AFX_MODULE_THREAD_STATE* pState = AfxGetModuleThreadState();
	const int GWL_WNDPROC = -4;
	DefStaticProc = (WNDPROC)GetWindowLongPtrW(pState->m_hSocketWindow, GWL_WNDPROC);
	SetWindowLongPtrW(pState->m_hSocketWindow, GWL_WNDPROC, (LONG_PTR)MyWndProc);

	// エラー
	NotifyError();
	EndSocket();
}

void MySocket::BeginServerSocket()
{
	while (true)
	{
		if (m_socListener.Create(m_nPortNumber) == FALSE)
		{
			break;
		}
		if (m_socListener.Listen(1) == FALSE)
		{
			int error = GetLastError();
			if (error != WSAEWOULDBLOCK)
			{
				break;
			}
		}

		// 正常
		return;
	}

	// CSocketWndメッセージの調査用
	AFX_MODULE_THREAD_STATE* pState = AfxGetModuleThreadState();
	const int GWL_WNDPROC = -4;
	DefStaticProc = (WNDPROC)GetWindowLongPtrW(pState->m_hSocketWindow, GWL_WNDPROC);
	SetWindowLongPtrW(pState->m_hSocketWindow, GWL_WNDPROC, (LONG_PTR)MyWndProc);

	// エラー
	NotifyError();
	EndSocket();
}

void MySocket::EndSocket()
{
	m_socListener.ShutDown(CAsyncSocket::both);
	m_socListener.Close();

	ShutDown(CAsyncSocket::both);
	Close();

	// CSocketWndメッセージ調査の後始末
	if (DefStaticProc != NULL)
	{
		AFX_MODULE_THREAD_STATE* pState = AfxGetModuleThreadState();
		const int GWL_WNDPROC = -4;
		SetWindowLongPtrW(pState->m_hSocketWindow, GWL_WNDPROC, (LONG_PTR)DefStaticProc);
		DefStaticProc = NULL;
	}

	m_bRunning = false;
}

// コールバック通知

void MySocket::NotifyConnected()
{
	if (m_pHandler != NULL)
	{
		m_pHandler->OnConnected();
	}
}

void MySocket::NotifyReceived(byte* pReadBlock, int nReadSize)
{
	if (m_pHandler != NULL)
	{
		m_pHandler->OnReceived(pReadBlock, nReadSize);
	}
}

void MySocket::NotifyError()
{
	if (m_pHandler != NULL)
	{
		m_pHandler->OnError();
	}
}

void MySocket::NotifyDisconnected()
{
	if (m_pHandler != NULL)
	{
		m_pHandler->OnDisconnected();
	}
}

/// CAsyncSocketの継承

void MySocket::OnConnect(int nErrorCode)
{
	if (nErrorCode == 0)
	{
		NotifyConnected();
		return;
	}

	NotifyError();
	EndSocket();
}

void MySocket::OnReceive(int nErrorCode)
{
	if (nErrorCode == 0)
	{
		int readSize = Receive(m_pReadBuffer, SHORT_MAX);
		if(readSize != 0)
		{
			NotifyReceived(m_pReadBuffer, readSize);
			return;
		}
	}
	
	NotifyError();
	EndSocket();
}

void MySocket::OnSend(int nErrorCode)
{
	if (nErrorCode == 0)
	{
		return;
	}

	NotifyError();
	EndSocket();
}

void MySocket::OnClose(int nErrorCode)
{
	if (nErrorCode == 0)
	{
		NotifyDisconnected();
		EndSocket();
		return;
	}

	NotifyError();
	EndSocket();
}

// IListnerSocketHandlerの継承

void MySocket::OnAccept()
{
	m_socListener.Accept(*this);
	m_socListener.ShutDown(CAsyncSocket::both);
	m_socListener.Close();

	NotifyConnected();
}

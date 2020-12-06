
// MfcTcpTool.h : MfcTcpTool アプリケーションのメイン ヘッダー ファイル
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"       // メイン シンボル
#include "AppSettings.h"
#include "MySocket.h"
#include "SendDialog.h"

// CMfcTcpToolApp:
// このクラスの実装については、MfcTcpTool.cpp を参照してください
//

class CMfcTcpToolApp : public CWinApp
{
public:
	CMfcTcpToolApp() noexcept;


// オーバーライド
protected:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 実装
	DECLARE_MESSAGE_MAP()
	afx_msg void OnAppAbout();
	afx_msg void OnStart();
	afx_msg void OnSetting();
	afx_msg void OnEnd();

public:
	AppSettings m_cAppSettings;
	MySocket m_cMySocket;
protected:
	SendDialog* m_pdlgSend;

protected:
	afx_msg void OnUpdateStart(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEnd(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSetting(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewSend(CCmdUI* pCmdUI);
	afx_msg void OnFileNew();
	afx_msg void OnViewSend();
};

extern CMfcTcpToolApp theApp;

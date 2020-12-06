// SendDialog.cpp : 実装ファイル
//

#include "pch.h"
#include "MfcTcpToolApp.h"
#include "SendDialog.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// SendDialog ダイアログ

IMPLEMENT_DYNAMIC(SendDialog, CDialog)

SendDialog::SendDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_SEND, pParent)
	, m_sText(_T(""))
{
	Create(IDD_SEND);
}

SendDialog::~SendDialog()
{
}

void SendDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SEND, m_sText);
}


BEGIN_MESSAGE_MAP(SendDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &SendDialog::OnBnClickedButtonSend)
END_MESSAGE_MAP()


// SendDialog メッセージ ハンドラー


void SendDialog::OnBnClickedButtonSend()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。

	UpdateData(TRUE);
	CT2A ascii(m_sText);
	theApp.m_cMySocket.Send(ascii, (int)strlen(ascii));
}

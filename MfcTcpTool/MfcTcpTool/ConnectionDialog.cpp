// ConnectionDialog.cpp : 実装ファイル
//

#include "pch.h"
#include "MfcTcpToolApp.h"
#include "ConnectionDialog.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ConnectionDialog ダイアログ

IMPLEMENT_DYNAMIC(ConnectionDialog, CDialogEx)

ConnectionDialog::ConnectionDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CONNECTION, pParent)
{

}

ConnectionDialog::~ConnectionDialog()
{
}

void ConnectionDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	AppSettings& settings = theApp.m_cAppSettings;
	DDX_Radio(pDX, IDC_RADIO_CLIENT, (int&)settings.m_eConnectionType);
	DDX_Text(pDX, IDC_COMBO_IP, settings.m_sIpAddress);
	DDX_Text(pDX, IDC_EDIT_PORT, settings.m_nPortNumber);
}


BEGIN_MESSAGE_MAP(ConnectionDialog, CDialogEx)
END_MESSAGE_MAP()


// ConnectionDialog メッセージ ハンドラー

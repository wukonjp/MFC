// LogDialog.cpp : 実装ファイル
//

#include "pch.h"
#include "MfcTcpToolApp.h"
#include "LogDialog.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// LogDialog ダイアログ

IMPLEMENT_DYNAMIC(LogDialog, CDialogEx)

LogDialog::LogDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOG, pParent)
{

}

LogDialog::~LogDialog()
{
}

void LogDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	AppSettings& settings = theApp.m_cAppSettings;
	DDX_CBIndex(pDX, IDC_COMBO_DATA_TYPE, (int&)settings.m_eLogType);
}


BEGIN_MESSAGE_MAP(LogDialog, CDialogEx)
END_MESSAGE_MAP()


// LogDialog メッセージ ハンドラー

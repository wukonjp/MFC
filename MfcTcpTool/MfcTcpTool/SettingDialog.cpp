// SettingDialog.cpp : 実装ファイル
//

#include "pch.h"
#include "MfcTcpToolApp.h"
#include "SettingDialog.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// SettingDialog ダイアログ

IMPLEMENT_DYNAMIC(SettingDialog, CDialogEx)

SettingDialog::SettingDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETTING, pParent)
{

}

SettingDialog::~SettingDialog()
{
}

void SettingDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_SETTING, m_tabSetting);
}


BEGIN_MESSAGE_MAP(SettingDialog, CDialogEx)

	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_SETTING, &SettingDialog::OnTcnSelchangeSettingTab)
END_MESSAGE_MAP()


// SettingDialog メッセージ ハンドラー


void SettingDialog::OnTcnSelchangeSettingTab(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。

	int current = m_tabSetting.GetCurSel();
	m_dlgConnection.ShowWindow(current == 0 ? SW_SHOW : SW_HIDE);
	m_dlgLog.ShowWindow(current == 1 ? SW_SHOW : SW_HIDE);

	*pResult = 0;
}


BOOL SettingDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: ここに初期化を追加してください

	// タブヘッダを登録する
	m_tabSetting.InsertItem(0, _T("接続"));
	m_tabSetting.InsertItem(1, _T("ログ"));

	// タブ内容を生成する
	m_dlgConnection.Create(IDD_CONNECTION, &m_tabSetting);
	m_dlgLog.Create(IDD_LOG, &m_tabSetting);

	// タブ内容の表示領域を計算する
	CRect rect;
	m_tabSetting.GetClientRect(&rect);
	rect.left += 2;
	rect.right -= 4;
	rect.top += 22;
	rect.bottom -= 3;

	// タブ内容を配置する
	m_dlgConnection.MoveWindow(&rect);
	m_dlgLog.MoveWindow(&rect);

	// 初期タブを設定する
	m_tabSetting.SetCurSel(0);
	m_dlgConnection.ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}


void SettingDialog::OnOK()
{
	// TODO: ここに特定なコードを追加するか、もしくは基底クラスを呼び出してください。
	m_dlgConnection.UpdateData(TRUE);
	m_dlgLog.UpdateData(TRUE);

	CDialogEx::OnOK();
}

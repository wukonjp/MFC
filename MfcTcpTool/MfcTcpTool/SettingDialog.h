#pragma once

#include "ConnectionDialog.h"
#include "LogDialog.h"

// SettingDialog ダイアログ

class SettingDialog : public CDialogEx
{
	DECLARE_DYNAMIC(SettingDialog)

public:
	SettingDialog(CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~SettingDialog();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchangeSettingTab(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
private:
	CTabCtrl m_tabSetting;
	ConnectionDialog m_dlgConnection;
	LogDialog m_dlgLog;
	virtual void OnOK();
};

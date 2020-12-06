#pragma once


// SendDialog ダイアログ

class SendDialog : public CDialog
{
	DECLARE_DYNAMIC(SendDialog)

public:
	SendDialog(CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~SendDialog();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEND };
#endif

protected:
	CString m_sText;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedButtonSend();
public:
};

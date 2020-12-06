#pragma once


// LogDialog ダイアログ

class LogDialog : public CDialogEx
{
	DECLARE_DYNAMIC(LogDialog)

public:
	LogDialog(CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~LogDialog();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
private:
	CComboBox m_cmbDataType;
};

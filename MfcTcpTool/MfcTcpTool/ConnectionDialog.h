#pragma once


// ConnectionDialog ダイアログ

class ConnectionDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ConnectionDialog)

public:
	ConnectionDialog(CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~ConnectionDialog();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONNECTION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
private:
};

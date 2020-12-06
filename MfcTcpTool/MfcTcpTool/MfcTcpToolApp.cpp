
// MfcTcpTool.cpp : アプリケーションのクラス動作を定義します。
//

#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "MfcTcpToolApp.h"
#include "MainFrame.h"
#include "MfcTcpToolDoc.h"
#include "MfcTcpToolView.h"
#include "SettingDialog.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMfcTcpToolApp

BEGIN_MESSAGE_MAP(CMfcTcpToolApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CMfcTcpToolApp::OnAppAbout)
	// 標準のファイル基本ドキュメント コマンド
	ON_COMMAND(ID_FILE_NEW, &CMfcTcpToolApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// 標準の印刷セットアップ コマンド
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
	ON_COMMAND(ID_START, &CMfcTcpToolApp::OnStart)
	ON_COMMAND(ID_SETTING, &CMfcTcpToolApp::OnSetting)
	ON_COMMAND(ID_END, &CMfcTcpToolApp::OnEnd)

	ON_UPDATE_COMMAND_UI(ID_START, &CMfcTcpToolApp::OnUpdateStart)
	ON_UPDATE_COMMAND_UI(ID_END, &CMfcTcpToolApp::OnUpdateEnd)
	ON_UPDATE_COMMAND_UI(ID_SETTING, &CMfcTcpToolApp::OnUpdateSetting)
	ON_COMMAND(ID_VIEW_SEND, &CMfcTcpToolApp::OnViewSend)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SEND, &CMfcTcpToolApp::OnUpdateViewSend)
END_MESSAGE_MAP()


// CMfcTcpToolApp の構築

CMfcTcpToolApp::CMfcTcpToolApp() noexcept
{
	// 再起動マネージャーをサポートします
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// アプリケーションが共通言語ランタイム サポート (/clr) を使用して作成されている場合:
	//     1) この追加設定は、再起動マネージャー サポートが正常に機能するために必要です。
	//     2) 作成するには、プロジェクトに System.Windows.Forms への参照を追加する必要があります。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 下のアプリケーション ID 文字列を一意の ID 文字列で置換します。推奨される
	// 文字列の形式は CompanyName.ProductName.SubProduct.VersionInformation です
	SetAppID(_T("MfcTcpTool.AppID.NoVersion"));

	// TODO: この位置に構築用コードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
	m_pdlgSend = NULL;
}

// 唯一の CMfcTcpToolApp オブジェクト

CMfcTcpToolApp theApp;


// CMfcTcpToolApp の初期化

BOOL CMfcTcpToolApp::InitInstance()
{
	// アプリケーション マニフェストが visual スタイルを有効にするために、
	// ComCtl32.dll Version 6 以降の使用を指定する場合は、
	// Windows XP に InitCommonControlsEx() が必要です。さもなければ、ウィンドウ作成はすべて失敗します。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// アプリケーションで使用するすべてのコモン コントロール クラスを含めるには、
	// これを設定します。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(_T("ソケットの初期化に失敗しました。"));
		return FALSE;
	}

	EnableTaskbarInteraction(FALSE);

	// RichEdit コントロールを使用するには AfxInitRichEdit2() が必要です
	// AfxInitRichEdit2();

	// 標準初期化
	// これらの機能を使わずに最終的な実行可能ファイルの
	// サイズを縮小したい場合は、以下から不要な初期化
	// ルーチンを削除してください。
	// 設定が格納されているレジストリ キーを変更します。
	// TODO: 会社名または組織名などの適切な文字列に
	// この文字列を変更してください。
//	SetRegistryKey(_T("アプリケーション ウィザードで生成されたローカル アプリケーション"));
	LoadStdProfileSettings(4);  // 標準の INI ファイルのオプションをロードします (MRU を含む)

	// INIファイルのパスを変更
	if (m_pszProfileName)
	{
		TCHAR szPath[MAX_PATH];
		::GetModuleFileName(NULL, szPath, MAX_PATH);	// 実行ファイルのパスを取得
		::PathRenameExtension(szPath, _T(".ini"));		// 拡張子をiniへ変更
		free((void*)m_pszProfileName);					// メモリの解放
		m_pszProfileName = _tcsdup(szPath);				// 新しいパスを設定 
	}

	// INIファイルの読み込み
	AppSettings& settings = this->m_cAppSettings;
	settings.m_eConnectionType = (ConnectionType)GetProfileInt(_T("Connection"), _T("ConnectionType"), 0);
	settings.m_sIpAddress = GetProfileString(_T("Connection"), _T("IPAddress"), _T("127.0.0.1"));
	settings.m_nPortNumber = GetProfileInt(_T("Connection"), _T("PortNumber"), 50000);
	settings.m_eLogType = (LogType)GetProfileInt(_T("Connection"), _T("LogType"), 0);

	// アプリケーション用のドキュメント テンプレートを登録します。ドキュメント テンプレート
	//  はドキュメント、フレーム ウィンドウとビューを結合するために機能します。
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMfcTcpToolDoc),
		RUNTIME_CLASS(CMainFrame),       // メイン SDI フレーム ウィンドウ
		RUNTIME_CLASS(CMfcTcpToolView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// DDE、file open など標準のシェル コマンドのコマンド ラインを解析します。
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// コマンド ラインで指定されたディスパッチ コマンドです。アプリケーションが
	// /RegServer、/Register、/Unregserver または /Unregister で起動された場合、False を返します。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	m_pdlgSend = new SendDialog();

	// メイン ウィンドウが初期化されたので、表示と更新を行います。
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

int CMfcTcpToolApp::ExitInstance()
{
	// TODO: ここに特定なコードを追加するか、もしくは基底クラスを呼び出してください。

	if (m_pdlgSend != NULL)
	{
		delete m_pdlgSend;
	}

	// INIファイルの書き込み
	AppSettings& settings = this->m_cAppSettings;
	WriteProfileInt(_T("Connection"), _T("ConnectionType"), (int)settings.m_eConnectionType);
	WriteProfileString(_T("Connection"), _T("IPAddress"), settings.m_sIpAddress);
	WriteProfileInt(_T("Connection"), _T("PortNumber"), settings.m_nPortNumber);
	WriteProfileInt(_T("Connection"), _T("LogType"), (int)settings.m_eLogType);

	return CWinApp::ExitInstance();
}

CMfcTcpToolDoc& GetDocument()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	return *(CMfcTcpToolDoc*)pFrame->GetActiveDocument();
}

// CMfcTcpToolApp メッセージ ハンドラー

// ダイアログを実行するためのアプリケーション コマンド
void CMfcTcpToolApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

void CMfcTcpToolApp::OnStart()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	CMfcTcpToolDoc& doc = GetDocument();
	doc.AddText(_T("接続開始\r\n"));
	m_cMySocket.Start(
		m_cAppSettings.m_eConnectionType,
		m_cAppSettings.m_sIpAddress,
		m_cAppSettings.m_nPortNumber,
		&doc
	);
}

void CMfcTcpToolApp::OnEnd()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	m_cMySocket.End();
}

void CMfcTcpToolApp::OnSetting()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	SettingDialog  dialog;
	dialog.DoModal();
}

void CMfcTcpToolApp::OnUpdateStart(CCmdUI* pCmdUI)
{
	// TODO:ここにコマンド更新 UI ハンドラー コードを追加します。
	pCmdUI->Enable(!m_cMySocket.IsRunning());
}

void CMfcTcpToolApp::OnUpdateEnd(CCmdUI* pCmdUI)
{
	// TODO:ここにコマンド更新 UI ハンドラー コードを追加します。
	pCmdUI->Enable(m_cMySocket.IsRunning());
}

void CMfcTcpToolApp::OnUpdateSetting(CCmdUI* pCmdUI)
{
	// TODO:ここにコマンド更新 UI ハンドラー コードを追加します。
	pCmdUI->Enable(!m_cMySocket.IsRunning());
}

void CMfcTcpToolApp::OnUpdateViewSend(CCmdUI* pCmdUI)
{
	// TODO:ここにコマンド更新 UI ハンドラー コードを追加します。
	pCmdUI->SetCheck(m_pdlgSend->IsWindowVisible());
}

void CMfcTcpToolApp::OnFileNew()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	OnEnd();

	CWinApp::OnFileNew();
}

void CMfcTcpToolApp::OnViewSend()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。

	if (!m_pdlgSend->IsWindowVisible())
	{
		m_pdlgSend->ShowWindow(SW_SHOW);
	}
	else
	{
		m_pdlgSend->ShowWindow(SW_HIDE);
	}
}

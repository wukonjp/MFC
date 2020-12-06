
// MfcTcpToolDoc.cpp : CMfcTcpToolDoc クラスの実装
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS は、プレビュー、縮小版、および検索フィルター ハンドラーを実装している ATL プロジェクトで定義でき、
// そのプロジェクトとのドキュメント コードの共有を可能にします。
#ifndef SHARED_HANDLERS
#include "MfcTcpToolApp.h"
#endif

#include "MfcTcpToolDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMfcTcpToolDoc

IMPLEMENT_DYNCREATE(CMfcTcpToolDoc, CDocument)

BEGIN_MESSAGE_MAP(CMfcTcpToolDoc, CDocument)
END_MESSAGE_MAP()


// CMfcTcpToolDoc コンストラクション/デストラクション

CMfcTcpToolDoc::CMfcTcpToolDoc() noexcept
{
	// TODO: この位置に 1 度だけ呼ばれる構築用のコードを追加してください。

	m_logText = _T("");
}

CMfcTcpToolDoc::~CMfcTcpToolDoc()
{
}

BOOL CMfcTcpToolDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: この位置に再初期化処理を追加してください。
	// (SDI ドキュメントはこのドキュメントを再利用します。
	m_logText = _T("");

	return TRUE;
}


// CMfcTcpToolDoc のシリアル化

void CMfcTcpToolDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 格納するコードをここに追加してください。
		ar << m_logText;
	}
	else
	{
		// TODO: 読み込むコードをここに追加してください。
	}
}

#ifdef SHARED_HANDLERS

//縮小版のサポート
void CMfcTcpToolDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// このコードを変更してドキュメントのデータを描画します
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 検索ハンドラーのサポート
void CMfcTcpToolDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ドキュメントのデータから検索コンテンツを設定します。
	// コンテンツの各部分は ";" で区切る必要があります

	// 例:      strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMfcTcpToolDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMfcTcpToolDoc の診断

#ifdef _DEBUG
void CMfcTcpToolDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMfcTcpToolDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMfcTcpToolDoc コマンド


void CMfcTcpToolDoc::AddText(LPCTSTR pText)
{
	m_logText += pText;
	UpdateAllViews(NULL);
}


const CString& CMfcTcpToolDoc::GetLogText()
{
	return m_logText;
}

void CMfcTcpToolDoc::OnConnected()
{
	AddText(_T("接続成功\r\n"));
}

void CMfcTcpToolDoc::OnReceived(byte* pReadBuffer, int nReadSize)
{
	CString sText;
	sText.Format(_T("受信サイズ: %d\r\n"), nReadSize);
	AddText(sText);

	if (theApp.m_cAppSettings.m_eLogType == LogType::ASCII)
	{
		size_t size = nReadSize + 3;
		char* pReadText = new char[size];
		memcpy(pReadText, pReadBuffer, nReadSize);
		pReadText[nReadSize + 0] = '\r';
		pReadText[nReadSize + 1] = '\n';
		pReadText[nReadSize + 2] = '\0';
		sText = pReadText;
		delete[] pReadText;
	}
	else
	{
		size_t size = (nReadSize * 3) + 3;
		char* pReadText = new char[size];
		for (int i = 0; i < nReadSize; i++)
		{
			char hex[3];
			sprintf_s(hex, 3, "%02X", pReadBuffer[i]);
			pReadText[(i * 3) + 0] = hex[0];
			pReadText[(i * 3) + 1] = hex[1];
			pReadText[(i * 3) + 2] = ' ';
		}
		pReadText[(nReadSize * 3) + 0] = '\r';
		pReadText[(nReadSize * 3) + 1] = '\n';
		pReadText[(nReadSize * 3) + 2] = '\0';
		sText = pReadText;
		delete[] pReadText;
	}
	AddText(sText);
}

void CMfcTcpToolDoc::OnError()
{
	AddText(_T("接続エラー\r\n"));
}

void CMfcTcpToolDoc::OnDisconnected()
{
	AddText(_T("接続終了\r\n"));
}


// MfcTcpToolView.cpp : CMfcTcpToolView クラスの実装
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS は、プレビュー、縮小版、および検索フィルター ハンドラーを実装している ATL プロジェクトで定義でき、
// そのプロジェクトとのドキュメント コードの共有を可能にします。
#ifndef SHARED_HANDLERS
#include "MfcTcpToolApp.h"
#endif

#include "MfcTcpToolDoc.h"
#include "MfcTcpToolView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMfcTcpToolView

IMPLEMENT_DYNCREATE(CMfcTcpToolView, CEditView)

BEGIN_MESSAGE_MAP(CMfcTcpToolView, CEditView)
	// 標準印刷コマンド
	ON_COMMAND(ID_FILE_PRINT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEditView::OnFilePrintPreview)
	ON_WM_TIMER()
ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()

// CMfcTcpToolView コンストラクション/デストラクション

CMfcTcpToolView::CMfcTcpToolView() noexcept
{
	// TODO: 構築コードをここに追加します。
}

CMfcTcpToolView::~CMfcTcpToolView()
{
}

BOOL CMfcTcpToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CEditView::PreCreateWindow(cs);
}

// CMfcTcpToolView 描画

void CMfcTcpToolView::OnDraw(CDC* pDC)
{
	CMfcTcpToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: この場所にネイティブ データ用の描画コードを追加します。
	CEditView::OnDraw(pDC);
}


// CMfcTcpToolView の印刷

BOOL CMfcTcpToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 既定の印刷準備
	return CEditView::OnPreparePrinting(pInfo);
}

void CMfcTcpToolView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: 印刷前の特別な初期化処理を追加してください。
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CMfcTcpToolView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: 印刷後の後処理を追加してください。
	CEditView::OnEndPrinting(pDC, pInfo);
}


// CMfcTcpToolView の診断

#ifdef _DEBUG
void CMfcTcpToolView::AssertValid() const
{
	CEditView::AssertValid();
}

void CMfcTcpToolView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CMfcTcpToolDoc* CMfcTcpToolView::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMfcTcpToolDoc)));
	return (CMfcTcpToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CMfcTcpToolView メッセージ ハンドラー


void CMfcTcpToolView::OnInitialUpdate()
{
	CEditView::OnInitialUpdate();

	// TODO: ここに特定なコードを追加するか、もしくは基底クラスを呼び出してください。
	CEdit& editCtrl = GetEditCtrl();
	editCtrl.SetReadOnly();

	SetTimer(1, 3000, NULL);
}

void CMfcTcpToolView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	if (nIDEvent == 1)
	{
		if (theApp.m_cMySocket.IsRunning())
		{
			//const char* pBuffer = "ABCDEFGHIJK\r\n";
			//theApp.m_cMySocket.Send(pBuffer, (int)strlen(pBuffer));
		}
	}
}

/// <summary>
/// EditコントロールのWM_CTLCOLORハンドラ
/// </summary>
HBRUSH CMfcTcpToolView::CtlColor(CDC* /*pDC*/, UINT nCtlColor)
{
	// TODO: ここで DC の属性を変更してください。
	if(nCtlColor == CTLCOLOR_STATIC)
	{
		// コントロールの背景に使うブラシ
		return (HBRUSH)::GetStockObject(WHITE_BRUSH);
	}

	// TODO: 親のハンドラーを呼び出せない場合は NULL 以外のブラシを返します。
	return NULL;
}

/// <summary>
/// Viewの更新
/// </summary>
void CMfcTcpToolView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: ここに特定なコードを追加するか、もしくは基底クラスを呼び出してください。
	CEdit& editCtrl = GetEditCtrl();
	CMfcTcpToolDoc* pDoc = GetDocument();
	editCtrl.SetWindowText(pDoc->GetLogText());
	int pos = editCtrl.GetWindowTextLength();
	editCtrl.SetSel(pos, pos);
}

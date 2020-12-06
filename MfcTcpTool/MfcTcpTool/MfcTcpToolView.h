
// MfcTcpToolView.h : CMfcTcpToolView クラスのインターフェイス
//

#pragma once


class CMfcTcpToolView : public CEditView
{
protected: // シリアル化からのみ作成します。
	CMfcTcpToolView() noexcept;
	DECLARE_DYNCREATE(CMfcTcpToolView)

// 属性
public:
	CMfcTcpToolDoc* GetDocument() const;

// 操作
public:

// オーバーライド
public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画するためにオーバーライドされます。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 実装
public:
	virtual ~CMfcTcpToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成された、メッセージ割り当て関数
protected:
	DECLARE_MESSAGE_MAP()
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
};

#ifndef _DEBUG  // MfcTcpToolView.cpp のデバッグ バージョン
inline CMfcTcpToolDoc* CMfcTcpToolView::GetDocument() const
   { return reinterpret_cast<CMfcTcpToolDoc*>(m_pDocument); }
#endif


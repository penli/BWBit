
// tool_BWBit_docView.h : interface of the Ctool_BWBit_docView class
//

#pragma once
           
#define BWBIT_HEAD_LEN          17
#define BWBIT_TAG_LEN            5
#define MAX_BWBit_BUFFER_SZIE  1024

enum{PLANAR,COMPRESSED};
enum{FILE_OPENED,FILE_CLOSED,FILE_INIT};


#define BWBIT_FILE      0
#define UNKNOW_FILE     1
#define ERROR_FILE_SIZE 2

typedef struct BWBit_tag
{
  unsigned int unHeight;
  unsigned int unWidth;
  char cBWBitTag[BWBIT_TAG_LEN];
  unsigned int unCompressFlag; 
}BWBit;

class Ctool_BWBit_docView : public CView
{
protected: // create from serialization only
	Ctool_BWBit_docView();
	DECLARE_DYNCREATE(Ctool_BWBit_docView)

private:
	CString szFileName;
	CStdioFile myFile;
	BWBit mBWBit;
	int mFileStatus;
	unsigned char * mBWBitBuffer;

// Attributes
public:
	Ctool_BWBit_docDoc* GetDocument() const;
	void DrawBits(unsigned int nWidth,unsigned int  nHeight,unsigned char * const BitBuffer);

public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~Ctool_BWBit_docView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	afx_msg void OnFileOpen();

public:
	int BWBitCheck();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnFileNew();
};


#ifndef _DEBUG  // debug version in tool_BWBit_docView.cpp
inline Ctool_BWBit_docDoc* Ctool_BWBit_docView::GetDocument() const
   { return reinterpret_cast<Ctool_BWBit_docDoc*>(m_pDocument); }
#endif


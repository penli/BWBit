
// tool_BWBit_docView.cpp : implementation of the Ctool_BWBit_docView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "tool_BWBit_doc.h"
#endif

#include "tool_BWBit_docDoc.h"
#include "tool_BWBit_docView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ctool_BWBit_docView

IMPLEMENT_DYNCREATE(Ctool_BWBit_docView, CView)

BEGIN_MESSAGE_MAP(Ctool_BWBit_docView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Ctool_BWBit_docView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_FILE_SAVE, &Ctool_BWBit_docView::OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, &Ctool_BWBit_docView::OnFileSaveAs)
	ON_COMMAND(ID_FILE_OPEN, &Ctool_BWBit_docView::OnFileOpen)
//	ON_COMMAND(IDCLOSE, &Ctool_BWBit_docView::OnIdclose)
//	ON_WM_CLOSE()
ON_WM_CLOSE()
ON_WM_DESTROY()
ON_COMMAND(ID_FILE_NEW, &Ctool_BWBit_docView::OnFileNew)
END_MESSAGE_MAP()

// Ctool_BWBit_docView construction/destruction

Ctool_BWBit_docView::Ctool_BWBit_docView()
{
	// TODO: add construction code here
	memset(&mBWBit,0x00,sizeof(mBWBit));
	mFileStatus = FILE_INIT;
	mBWBitBuffer = NULL;
}

Ctool_BWBit_docView::~Ctool_BWBit_docView()
{
}

BOOL Ctool_BWBit_docView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	return CView::PreCreateWindow(cs);
}

void Ctool_BWBit_docView::OnDraw(CDC* /*pDC*/)
{
	Ctool_BWBit_docDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
}


// Ctool_BWBit_docView printing


void Ctool_BWBit_docView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Ctool_BWBit_docView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void Ctool_BWBit_docView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void Ctool_BWBit_docView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void Ctool_BWBit_docView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Ctool_BWBit_docView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Ctool_BWBit_docView diagnostics

#ifdef _DEBUG
void Ctool_BWBit_docView::AssertValid() const
{
	CView::AssertValid();
}

void Ctool_BWBit_docView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Ctool_BWBit_docDoc* Ctool_BWBit_docView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Ctool_BWBit_docDoc)));
	return (Ctool_BWBit_docDoc*)m_pDocument;
}
#endif //_DEBUG

void Ctool_BWBit_docView::OnFileSave()
{
	CFileDialog dlg(FALSE, L"*.bwbit", NULL, NULL, L"*.bwbit|*.bwbit||");
    if(IDOK == dlg.DoModal())
    {
       szFileName = dlg.GetPathName();
    }
}

void Ctool_BWBit_docView::OnFileSaveAs()
{
	CFileDialog dlg(FALSE, L"*.bwbit", NULL, NULL, L"*.bwbit|*.bwbit||");
    if(IDOK == dlg.DoModal())
    {
       szFileName = dlg.GetPathName();
    }
}

int Ctool_BWBit_docView::BWBitCheck()
{
   CFileException fileException;

   if( FALSE == myFile.Open(szFileName, CFile::typeBinary|CFile::modeRead, &fileException) )
   {
      TRACE("Can't open file %s, error = %u/n",szFileName,fileException.m_cause);	  
	  return UNKNOW_FILE;
   }

   if( myFile.GetLength() < sizeof(mBWBit) ) 
   {
	   myFile.Close();
	   return ERROR_FILE_SIZE; 
   }

   myFile.Read(&mBWBit,BWBIT_HEAD_LEN);

   if( strncmp("BWBit",mBWBit.cBWBitTag,strlen("BWBit")) != 0 )
   {
	  myFile.Close();
      return UNKNOW_FILE; 
   }
   
   if( COMPRESSED == mBWBit.unCompressFlag )
   {
      MessageBox(L"CurrentVersion Does't support this format!");
	  myFile.Close();
      return UNKNOW_FILE; 
   }

   unsigned char nBufferLen = ((mBWBit.unWidth+7)/8)*(mBWBit.unHeight);
   mBWBitBuffer = (unsigned char *)malloc(nBufferLen);
   memset(mBWBitBuffer,0x00,nBufferLen);

   myFile.Seek(BWBIT_HEAD_LEN,SEEK_SET);
   myFile.Read(mBWBitBuffer,nBufferLen);

   mFileStatus = FILE_OPENED;
   DrawBits(mBWBit.unWidth,mBWBit.unHeight,mBWBitBuffer);

   return BWBIT_FILE;
}

void Ctool_BWBit_docView::OnFileOpen()
{
	// TODO: Add your command handler code here
    CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,  L"*.bwbit|*.bwbit||");
    if(IDOK == dlg.DoModal())
    {
       szFileName = dlg.GetPathName();
	   BWBitCheck();
    }
}

void Ctool_BWBit_docView::OnClose()
{
	CView::OnClose();
}

void Ctool_BWBit_docView::OnDestroy()
{
	CView::OnDestroy();

	if(FILE_OPENED == mFileStatus)
	{
	   myFile.Close();

	   if(mBWBitBuffer)
		 delete mBWBitBuffer;
   	}	   
}

void Ctool_BWBit_docView::DrawBits(unsigned int nWidth,unsigned int  nHeight,unsigned char * const BitBuffer)
{
   unsigned int xPos=0,yPos=0;

   CClientDC m_dc(this);
   CPen pen;
   CPen * ppen = m_dc.SelectObject(&pen);
     
   COLORREF BColor = RGB(0,0,0);
   unsigned char uaBitMask[8]={0x1,0x2,0x4,0x8,0x10,0x20,0x40,0x80};

   for( yPos=0; yPos<nHeight; yPos++ )
   {
     for( xPos=0; xPos<nWidth; xPos++ )
     {
	    if( (BitBuffer[nWidth/8*yPos+xPos/8] & uaBitMask[xPos%8]) != 0 )
		  m_dc.SetPixel(xPos,yPos,BColor);  
	 }
   }
   m_dc.SelectObject(ppen);
}

void Ctool_BWBit_docView::OnFileNew()
{

}

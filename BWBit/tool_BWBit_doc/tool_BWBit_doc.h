
// tool_BWBit_doc.h : main header file for the tool_BWBit_doc application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// Ctool_BWBit_docApp:
// See tool_BWBit_doc.cpp for the implementation of this class
//

class Ctool_BWBit_docApp : public CWinAppEx
{
public:
	Ctool_BWBit_docApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Ctool_BWBit_docApp theApp;

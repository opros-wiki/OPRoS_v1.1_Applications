
// ImgViewer.h : ImgViewer DLL 
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH this file."
#endif

#include "resource.h"		// 

// CImgViewerApp
// 
//

class CImgViewerApp : public CWinApp
{
public:
	CImgViewerApp();

// 
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
	
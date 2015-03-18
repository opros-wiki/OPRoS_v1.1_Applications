
// ImgViewer.cpp : 
//
#include "stdafx.h"
#include "ImgViewerApp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestMFApp

BEGIN_MESSAGE_MAP(CImgViewerApp, CWinApp)
END_MESSAGE_MAP()

// CImgViewerApp creation

CImgViewerApp::CImgViewerApp()
{
	// 
	// 
}


// unique CImgViewerApp object.

CImgViewerApp theApp;


// initialize CImgViewerApp 

BOOL CImgViewerApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
	
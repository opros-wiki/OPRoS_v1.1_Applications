
// Viewer.cpp : 
//
#include "stdafx.h"
#include "ViewerApp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestMFApp

BEGIN_MESSAGE_MAP(CViewerApp, CWinApp)
END_MESSAGE_MAP()

// CViewerApp creation

CViewerApp::CViewerApp()
{
	// 
	// 
}


// unique CViewerApp object.

CViewerApp theApp;


// initialize CViewerApp 

BOOL CViewerApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
	
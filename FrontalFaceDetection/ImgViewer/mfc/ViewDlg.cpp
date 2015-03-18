// ViewDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImgViewer.h"
#include "ViewDlg.h"
#include "afxdialogex.h"


// ViewDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(ViewDlg, CDialog)

ViewDlg::ViewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ViewDlg::IDD, pParent)
{

}

ViewDlg::~ViewDlg()
{
}

void ViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ViewDlg, CDialog)
END_MESSAGE_MAP()


// ViewDlg 메시지 처리기입니다.

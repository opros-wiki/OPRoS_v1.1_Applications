// ViewerDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImgViewer.h"
#include "ViewerDlg.h"
#include "afxdialogex.h"


// ViewerDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(ViewerDlg, CDialog)

ViewerDlg::ViewerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ViewerDlg::IDD, pParent)
{

}

ViewerDlg::~ViewerDlg()
{
}

void ViewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC, m_pic);
}


BEGIN_MESSAGE_MAP(ViewerDlg, CDialog)
	ON_BN_CLICKED(ID_View, &ViewerDlg::OnBnClickedView)
END_MESSAGE_MAP()


// ViewerDlg 메시지 처리기입니다.


void ViewerDlg::OnBnClickedView()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

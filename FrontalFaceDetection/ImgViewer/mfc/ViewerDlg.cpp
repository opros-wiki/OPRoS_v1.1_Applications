// ViewerDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ImgViewer.h"
#include "ViewerDlg.h"
#include "afxdialogex.h"


// ViewerDlg ��ȭ �����Դϴ�.

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


// ViewerDlg �޽��� ó�����Դϴ�.


void ViewerDlg::OnBnClickedView()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

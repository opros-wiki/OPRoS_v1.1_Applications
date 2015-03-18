// ViewerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Viewer.h"
#include "ViewerDlg.h"

#include <string>


// ViewerDlg dialog

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
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_VIEW, &ViewerDlg::OnBnClickedView)
END_MESSAGE_MAP()


// ViewerDlg message handlers



void ViewerDlg::OnBnClickedView()
{
	// TODO: Add your control notification handler code here

	//------------------------------------------------------
	//	�󱼰���⿡ �Էµ� ��Ʈ�� ���� ���� �ε�
	//------------------------------------------------------
	CDib *pDib = NULL;
	pDib = new CDib(fileName);


	//----------------------------
	//	������ ȭ�� ���	
	//----------------------------
	CDC *pDC = m_pic.GetDC();
	pDC->SelectStockObject(NULL_BRUSH);
	pDib->LoadPaletteImage(pDC);	// ������ �׸���
	delete pDib;

	//pDC->Rectangle(&rt);	// ���⿵�� �׸���

	int arrySize=pRectArray->GetSize();

	if(arrySize>0)
	{
		for(int i = 0; i < arrySize ; i++)
		{
			RECT rt = pRectArray->GetAt(i);
			pDC->Rectangle(&rt);	// ���⿵�� �׸���
		}
			
	}


	ReleaseDC(pDC);

}

void ViewerDlg::setFileName(const char* str)
{
	fileName=str;
}


void ViewerDlg::setRectArray(RectArray *inArray)
{

	pRectArray = inArray;

std::cout<<"[Viewer] set rect array size = "<<pRectArray->GetSize()<<std::endl;

}
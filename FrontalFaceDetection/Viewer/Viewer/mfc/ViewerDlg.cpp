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
	//	얼굴검출기에 입력될 비트맵 정지 영상 로딩
	//------------------------------------------------------
	CDib *pDib = NULL;
	pDib = new CDib(fileName);


	//----------------------------
	//	검출결과 화면 출력	
	//----------------------------
	CDC *pDC = m_pic.GetDC();
	pDC->SelectStockObject(NULL_BRUSH);
	pDib->LoadPaletteImage(pDC);	// 원영상 그리기
	delete pDib;

	//pDC->Rectangle(&rt);	// 검출영역 그리기

	int arrySize=pRectArray->GetSize();

	if(arrySize>0)
	{
		for(int i = 0; i < arrySize ; i++)
		{
			RECT rt = pRectArray->GetAt(i);
			pDC->Rectangle(&rt);	// 검출영역 그리기
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
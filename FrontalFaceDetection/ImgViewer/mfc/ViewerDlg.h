#pragma once
#include "afxwin.h"


// ViewerDlg 대화 상자입니다.

class ViewerDlg : public CDialog
{
	DECLARE_DYNAMIC(ViewerDlg)

public:
	ViewerDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~ViewerDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ViewDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_pic;
	afx_msg void OnBnClickedView();
};

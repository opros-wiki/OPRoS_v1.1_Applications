#pragma once
#include "afxwin.h"


// ViewerDlg ��ȭ �����Դϴ�.

class ViewerDlg : public CDialog
{
	DECLARE_DYNAMIC(ViewerDlg)

public:
	ViewerDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~ViewerDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ViewDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_pic;
	afx_msg void OnBnClickedView();
};

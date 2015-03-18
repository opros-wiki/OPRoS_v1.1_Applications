#pragma once
#include "afxwin.h"

// ViewerDlg dialog

class ViewerDlg : public CDialog
{
	DECLARE_DYNAMIC(ViewerDlg)

public:
	ViewerDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~ViewerDlg();

// Dialog Data
	enum { IDD = IDD_VIEWER_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:

	CStatic m_pic;
	const char* fileName;
	RectArray *pRectArray;

	void setFileName(const char* str);
	void setRectArray(RectArray *inArray);

	afx_msg void OnBnClickedView();
};

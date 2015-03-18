#pragma once


// ViewDlg 대화 상자입니다.

class ViewDlg : public CDialog
{
	DECLARE_DYNAMIC(ViewDlg)

public:
	ViewDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~ViewDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};

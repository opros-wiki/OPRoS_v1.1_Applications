#pragma once


// ViewDlg ��ȭ �����Դϴ�.

class ViewDlg : public CDialog
{
	DECLARE_DYNAMIC(ViewDlg)

public:
	ViewDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~ViewDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

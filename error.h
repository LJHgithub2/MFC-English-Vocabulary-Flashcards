#pragma once


// error ��ȭ �����Դϴ�.

class error : public CDialogEx
{
	DECLARE_DYNAMIC(error)

public:
	error(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~error();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

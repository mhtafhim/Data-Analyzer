#pragma once
#include "afxdialogex.h"


// Tab_Two dialog

class Tab_Two : public CDialogEx
{
	DECLARE_DYNAMIC(Tab_Two)

public:
	Tab_Two(CWnd* pParent = nullptr);   // standard constructor
	virtual ~Tab_Two();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TAB_TWO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};

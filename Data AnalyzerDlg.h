
// Data AnalyzerDlg.h : header file
//
#include <fstream>
#include <sstream>
#include <vector>
#include "Tab_One.h"
#include "Tab_Two.h"
#pragma once


// CDataAnalyzerDlg dialog
class CDataAnalyzerDlg : public CDialogEx
{
// Construction
public:
	CDataAnalyzerDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DATA_ANALYZER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLoadButton();
	bool LoadTextFile(const CString& filePath);
	void InitTable(std::vector<CString> headers, std::vector<std::vector<double>> data);
	void render_tree();
	std::vector<CString> headers;
	std::vector<std::vector<double>> rows;

	
	CListCtrl m_list_table;
	CTreeCtrl m_tree_ctrl;
	CTabCtrl m_tab_ctrl;

	Tab_One m_tab_one;
	Tab_Two m_tab_two;
	afx_msg void OnTcnSelchangeTabCtrl(NMHDR* pNMHDR, LRESULT* pResult);
};

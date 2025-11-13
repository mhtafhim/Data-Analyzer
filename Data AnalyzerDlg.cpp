
// Data AnalyzerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "framework.h"
#include "Data Analyzer.h"
#include "Data AnalyzerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDataAnalyzerDlg dialog



CDataAnalyzerDlg::CDataAnalyzerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DATA_ANALYZER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDataAnalyzerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_TABLE, m_list_table);
	DDX_Control(pDX, IDC_TREE_VIEW, m_tree_ctrl);
	DDX_Control(pDX, IDC_TAB_CTRL, m_tab_ctrl);
}

BEGIN_MESSAGE_MAP(CDataAnalyzerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LOAD_BUTTON, &CDataAnalyzerDlg::OnBnClickedLoadButton)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_CTRL, &CDataAnalyzerDlg::OnTcnSelchangeTabCtrl)
END_MESSAGE_MAP()


// CDataAnalyzerDlg message handlers

BOOL CDataAnalyzerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here



	m_tab_ctrl.InsertItem(0, _T("Tab 1"));
	m_tab_ctrl.InsertItem(1, _T("Tab 2"));

	
	CRect rect;
	m_tab_ctrl.GetClientRect(&rect);

	//// Adjust rectangle to fit inside tab control’s display area
	//m_tab_ctrl.AdjustRect(FALSE, &rect);

	//// Convert tab client area to parent dialog coordinates
	//m_tab_ctrl.MapWindowPoints(this, &rect);

	// Create dialogs as children of the tab control
	m_tab_one.Create(IDD_DIALOG_TAB_ONE, &m_tab_ctrl);
	m_tab_two.Create(IDD_DIALOG_TAB_TWO, &m_tab_ctrl);

	// Position them correctly
	m_tab_one.SetWindowPos(NULL, rect.left + 1, rect.top + 25, rect.Width() - 2, rect.Height() - 26, SWP_SHOWWINDOW);
	m_tab_two.SetWindowPos(NULL, rect.left + 1, rect.top + 25, rect.Width() - 2, rect.Height() - 26, SWP_HIDEWINDOW);



	





	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDataAnalyzerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDataAnalyzerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDataAnalyzerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


bool CDataAnalyzerDlg::LoadTextFile(const CString& filePath)
{
	// Clear previous data
	headers.clear();
	rows.clear();

	std::ifstream file((CT2A)filePath); // Convert CString to ANSI string
	if (!file.is_open()) return false;

	std::string line;
	bool isHeader = true;

	while (std::getline(file, line))
	{
		if (line.empty()) continue; // skip empty lines

		std::vector<std::string> tokens;
		std::stringstream ss(line);
		std::string cell;

		// Determine separator: comma or space
		char separator = (line.find(',') != std::string::npos) ? ',' : ' ';

		while (std::getline(ss, cell, separator))
		{
			if (!cell.empty())
				tokens.push_back(cell);
		}

		if (tokens.empty()) continue; // skip empty rows

		if (isHeader)
		{
			for (const auto& h : tokens)
				headers.push_back(CString(h.c_str()));
			isHeader = false;
		}
		else
		{
			std::vector<double> row;
			try
			{
				for (const auto& t : tokens)
					row.push_back(std::stod(t));
			}
			catch (...)
			{
				// invalid number -> skip row or handle as needed
				continue;
			}
			rows.push_back(row);
		}
	}

	// Optional: print loaded sizes
	//CString msg;
	//msg.Format(_T("Loaded %d headers and %d rows"), headers.size(), rows.size());
	//AfxMessageBox(msg);

	return true;
}


int flag = 0;


void CDataAnalyzerDlg::InitTable(std::vector<CString> headers, std::vector<std::vector<double>> data)
{

	//CString msg;

	//// Add headers
	//for (size_t i = 0; i < headers.size(); ++i)
	//{
	//	msg += headers[i];
	//	if (i != headers.size() - 1)
	//		msg += _T("\t"); // tab between headers
	//}
	//msg += _T("\n");

	//// Add data rows
	//for (size_t i = 0; i < data.size(); ++i)
	//{
	//	for (size_t j = 0; j < data[i].size(); ++j)
	//	{
	//		msg.AppendFormat(_T("%.2f"), data[i][j]); // 2 decimal places
	//		if (j != data[i].size() - 1)
	//			msg += _T("\t");
	//	}
	//	msg += _T("\n");
	//}

	//// Show message
	//AfxMessageBox(msg);



	m_list_table.ModifyStyle(0, LVS_REPORT);

	m_list_table.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);


	int nColumnCount = 0;
	if (m_list_table.GetHeaderCtrl()->GetItemCount() != NULL)
		nColumnCount = m_list_table.GetHeaderCtrl()->GetItemCount();

	m_list_table.DeleteAllItems();

	// Loop nColumnCount times, always deleting the column at index 0.
	for (int i = 0; i < nColumnCount; i++)
		m_list_table.DeleteColumn(0);


	for (int i = 0; i < headers.size(); i++)
	{
		m_list_table.InsertColumn(i, headers[i], LVCFMT_LEFT, 100);
	}


	for (int i = 0; i < data.size(); i++)
	{
		int index = m_list_table.InsertItem(i, std::to_wstring(data[i][0]).c_str());
		for (int j = 1; j < data[i].size(); j++)
		{
			m_list_table.SetItemText(index, j, std::to_wstring(data[i][j]).c_str());
		}
	}



}




void  CDataAnalyzerDlg::render_tree()
{
	m_tree_ctrl.ModifyStyle(0, TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS);
	//tree control 
	m_tree_ctrl.DeleteAllItems();

	HTREEITEM hRoot = m_tree_ctrl.InsertItem(_T("Used Variables"), TVI_ROOT);
	for (int i = 0; i < headers.size(); i++)
	{
		//CString temp = headers[i];
		m_tree_ctrl.InsertItem((headers[i]), hRoot);
	}

	//HTREEITEM hChild2 = m_tree_control.InsertItem(_T("Child 2"), hRoot);
	//m_tree_control.InsertItem(_T("Subchild 1"), hChild1);

	m_tree_ctrl.Expand(hRoot, TVE_EXPAND);
}







void CDataAnalyzerDlg::OnBnClickedLoadButton()
{

	headers.clear();
	rows.clear();
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE, _T("txt"), NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
		_T("Text/CSV Files (*.txt;*.csv)|*.txt;*.csv|All Files (*.*)|*.*||"), this);
	if (dlg.DoModal() == IDOK)
	{
		CString filePath = dlg.GetPathName(); // Full file path selected by user
		//AfxMessageBox(filePath);              // Just to test

			// You can now read CSV and show in table
		LoadTextFile(filePath);

		//ShowDynamicTable(table);

		InitTable(headers, rows);
		render_tree();


		m_tab_one.InitChart(headers,rows);

		// Render chart in tab one
		
	}
}



void CDataAnalyzerDlg::OnTcnSelchangeTabCtrl(NMHDR* pNMHDR, LRESULT* pResult)
{
	int sel = m_tab_ctrl.GetCurSel();

	m_tab_one.ShowWindow((sel == 0 ? TRUE : FALSE));
	m_tab_two.ShowWindow((sel == 1 ? TRUE : FALSE));
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

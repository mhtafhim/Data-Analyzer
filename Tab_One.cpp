// Tab_One.cpp : implementation file
//

#include "stdafx.h"
#include "Data Analyzer.h"
#include "afxdialogex.h"
#include "Tab_One.h"
#include<iostream>

#include "ChartCtrl\ChartLineSerie.h"
#include "ChartCtrl\ChartPointsSerie.h"
#include "ChartCtrl\ChartSurfaceSerie.h"
#include "ChartCtrl\ChartGrid.h"
#include "ChartCtrl\ChartBarSerie.h"
#include "ChartCtrl\ChartLabel.h"

#include "ChartCtrl\ChartAxisLabel.h"
#include "ChartCtrl\ChartStandardAxis.h"
#include "ChartCtrl\ChartDateTimeAxis.h"

#include "ChartCtrl\ChartCrossHairCursor.h"
#include "ChartCtrl\ChartDragLineCursor.h"


// Tab_One dialog

IMPLEMENT_DYNAMIC(Tab_One, CDialogEx)

Tab_One::Tab_One(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TAB_ONE, pParent)
{

}

Tab_One::~Tab_One()
{
}

void Tab_One::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHARTCTRL, m_ChartCtrl);
	DDX_Control(pDX, IDC_COMBO1, m_combo_one);
	DDX_Control(pDX, IDC_COMBO2, m_combo_two);
}


BEGIN_MESSAGE_MAP(Tab_One, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &Tab_One::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &Tab_One::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_BUTTON1, &Tab_One::OnBnClickedButton1)
END_MESSAGE_MAP()


// Tab_One message handlers

// Fix for E0312: no suitable user-defined conversion from "CString" to "const TChartString"
// Convert CString to TChartString using GetString() or operator LPCTSTR


void Tab_One::InitChart(std::vector<CString> labels, std::vector<std::vector<double>> rows)
{

	headers.clear();
	data.clear();

	headers = labels;
	data = rows;
	//reset combobox values
	showComboBoxList(0, 1);

	headersSerial.clear();

	for(int i = 0; i < headers.size(); i++)
	{
		std::string tmp = CT2A(headers[i]);
		headersSerial[tmp] = i;
	}
}


void Tab_One::showComboBoxList(int first, int second)
{

	//reset combobox values
	m_combo_one.ResetContent();
	m_combo_two.ResetContent();

	int default_one;
	int default_two;
	for(int i = 0; i < headers.size(); i++)
	{
		if(i != second) m_combo_one.AddString(headers[i]);
		if(i!=first)m_combo_two.AddString(headers[i]);
	}

	CString xName = headers[first];
	CString yName = headers[second];


	m_combo_one.SetCurSel(m_combo_one.FindStringExact(-1, xName));
	m_combo_two.SetCurSel(m_combo_two.FindStringExact(-1, yName));

	double xMin = data[0][first], xMax = data[0][first], yMin = data[0][second], yMax = data[0][second];
	int n = data.size();
	//int m = data.size();

	double* XVal = new double[n];
	double* YVal = new double[n];

	for(int i = 0; i < n; i++)
	{
		XVal[i] = data[i][first];
		YVal[i] = data[i][second];
		xMin = min(xMin, XVal[i]);
		xMax = max(xMax, XVal[i]);
		yMin = min(yMin, YVal[i]);
		yMax = max(yMax, YVal[i]);

	}

	RenderChart(XVal, YVal, n, xName, yName, xMin, xMax, yMin, yMax);
}


void Tab_One::RenderChart(double* XVal, double* YVal, int sz, CString xName, CString yName, double xMinLimit, double xMaxLimit, double yMinLimit, double yMaxLimit )
{

	/*CString msg;

	for (int i = 0; i < sz; i++)
	{
		CString line;
		line.Format(_T("X[%d] = %.2f , Y[%d] = %.2f\n"), i, XVal[i], i, YVal[i]);
		msg += line;
	}

	AfxMessageBox(msg);*/


	CChartCtrl ref;
	ref.RemoveAllSeries();
	m_ChartCtrl.EnableRefresh(true);
	pBottomAxis = m_ChartCtrl.CreateStandardAxis(CChartCtrl::BottomAxis);
	pLeftAxis = m_ChartCtrl.CreateStandardAxis(CChartCtrl::LeftAxis);

	pBottomAxis->SetMinMax(xMinLimit, xMaxLimit);
	pBottomAxis->GetLabel()->SetText(TChartString(xName.GetString()));

	pLeftAxis->SetMinMax(yMinLimit, yMaxLimit);
	pLeftAxis->GetLabel()->SetText(TChartString(yName.GetString()));

	pBottomAxis->SetTickIncrement(false, 20.0);
	pBottomAxis->SetDiscrete(false);
	pBottomAxis->EnableScrollBar(true);

	pSeries = m_ChartCtrl.CreateLineSerie();
	pSeries->ClearSerie();
	pSeries->SetWidth(5); //line width
	pSeries->SetColor(RGB(255, 0, 0)); //color of line

	//double XVal[] = { 103.51 ,145.856 ,160.039 ,174.425 ,188.405 ,202.588 ,226.091 ,230.346 ,258.914 ,268.234 ,282.62 };
	//double YVal[] = { 0.812003 ,0.295188 ,0.131059 ,0.258975 ,0.299947 ,0.38009 ,1 ,0.977828 ,0.214769 ,0.283843 ,0.149118 };
	pSeries->SetPoints(XVal, YVal, sz);

	m_ChartCtrl.EnableRefresh(true);
}

void Tab_One::OnCbnSelchangeCombo1()
{
	CString selText_one;
	CString selText_two;
	m_combo_one.GetWindowTextW(selText_one);
	m_combo_two.GetWindowTextW(selText_two);

	std::string tmp = CT2A(selText_one);

	int sel1 = headersSerial[tmp];

	tmp = CT2A(selText_two);

	int sel2 = headersSerial[tmp];
	showComboBoxList(sel1, sel2);
	// TODO: Add your control notification handler code here
}

void Tab_One::OnCbnSelchangeCombo2()
{
	CString selText_one;
	CString selText_two;
	m_combo_one.GetWindowTextW(selText_one);
	m_combo_two.GetWindowTextW(selText_two);

	std::string tmp = CT2A(selText_one);

	int sel1 = headersSerial[tmp];

	tmp = CT2A(selText_two);

	int sel2 = headersSerial[tmp];
	showComboBoxList(sel1, sel2);
	// TODO: Add your control notification handler code here
}




void Tab_One::OnBnClickedButton1()
{
	CFileDialog dlg(FALSE, L"png", L"ChartOutput.png",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"PNG Files (*.png)|*.png|BMP Files (*.bmp)|*.bmp|JPEG Files (*.jpg)|*.jpg||");

	if (dlg.DoModal() != IDOK)
		return; // user cancelled

	CString filePath = dlg.GetPathName();
	m_ChartCtrl.SaveChartAsImage(filePath);
	AfxMessageBox(L"Chart exported successfully!");

	// TODO: Add your control notification handler code here
}

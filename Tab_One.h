#pragma once
#include "afxdialogex.h"
#include "ChartCtrl\ChartCtrl.h"
#include "ChartCtrl\ChartLineSerie.h"
#include "ChartCtrl\ChartLabel.h"
#include <string>
#include <unordered_map>

// Tab_One dialog

class Tab_One : public CDialogEx
{
	DECLARE_DYNAMIC(Tab_One)

public:
	Tab_One(CWnd* pParent = nullptr);   // standard constructor
	virtual ~Tab_One();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TAB_ONE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


	

	

	

	

	DECLARE_MESSAGE_MAP()

public:
	CChartCtrl m_ChartCtrl;
	CChartStandardAxis* pBottomAxis;
	CChartStandardAxis* pLeftAxis;
	CChartLineSerie* pSeries;

	//void showComboBoxList();

	//void showComboBoxList(std::vector<CString> headers);

	//void showComboBoxList(std::vector<CString> headers, int first, int second);
	//void showComboBoxList(std::vector<CString> headers, int first, int second);

	void InitChart(std::vector<CString> labels, std::vector<std::vector<double>> rows);

	void showComboBoxList(int first, int second);

	//void showComboBoxList(std::vector<CString> headers, std::vector<std::vector<double>> data, int first, int second);
	std::vector<CString> headers;
	std::vector<std::vector<double>> data;

	std::unordered_map<std::string, int> headersSerial;

	void RenderChart(double* XVal, double* YVal, int size, CString xName, CString yName, double xMinLimit, double xMaxLimit, double yMinLimit, double yMaxLimit);
	CComboBox m_combo_one;
	CComboBox m_combo_two;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();
	void SaveChartAsImage(const CString& filePath);
	afx_msg void OnBnClickedButton1();
};

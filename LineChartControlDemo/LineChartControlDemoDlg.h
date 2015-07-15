// LineChartControlDemoDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "Plot.h"
// ig added
#include "ig500.h"

using namespace RealtimeCurve;

// CLineChartControlDemoDlg dialog
class CLineChartControlDemoDlg : public CDialog
{
// Construction
public:
	CLineChartControlDemoDlg(CWnd* pParent = NULL);	// standard constructor

	// FIXME �������Type�ĺ���
	void setType(int type);
// Dialog Data
	enum { IDD = IDD_LINECHARTCONTROLDEMO_DIALOG };

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
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnTimerPro(UINT nIDEvent);
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedSetting();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnBnClickedDispLine1();
	afx_msg void OnBnClickedDispLine2();
	DECLARE_MESSAGE_MAP()
	CPlot m_plot;

	CRect m_rectBtnExit;
	CRect m_rectOldWindow;
	CRect m_rectOldPlotWindow;
private:
	float m_time;
	IG *ig;
	// dataType Ϊ��ʵ����������, 1ΪxAngel 2ΪyAngle 3ΪzAngle 4ΪxPosition 5ΪyPosition 6ΪzPosition
	int dataType = 1;

protected:
	CButton m_btnExit;
	int m_iBtnExitFromRight;
	int m_iBtnExitFromBottom;
	
};

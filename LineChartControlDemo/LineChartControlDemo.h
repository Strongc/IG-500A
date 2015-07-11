// LineChartControlDemo.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "LineChartControlDemoDlg.h"

// CLineChartControlDemoApp:
// See LineChartControlDemo.cpp for the implementation of this class
//

class CLineChartControlDemoApp : public CWinApp
{
public:
	CLineChartControlDemoApp();
	void DrawOther(CLineChartControlDemoDlg *pAnothers, int );  // 绘制另外5个曲线

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CLineChartControlDemoApp theApp;
// LineChartControlDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "LineChartControlDemo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CLineChartControlDemoApp

BEGIN_MESSAGE_MAP(CLineChartControlDemoApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CLineChartControlDemoApp construction

CLineChartControlDemoApp::CLineChartControlDemoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

void CLineChartControlDemoApp::DrawOther(CLineChartControlDemoDlg *pAnothers, int n){
	if (NULL == pAnothers){
		ASSERT(FALSE);
	}
	CLineChartControlDemoDlg *temp = NULL;
	for (int i = 0; i < n; i++){
		// 从2开始, 2~6
		temp = &pAnothers[i];
		temp->setType(i+2);
		BOOL ret = temp->Create(IDD_LINECHARTCONTROLDEMO_DIALOG);
		temp->ShowWindow(SW_SHOWNORMAL);
	}

	return;
}

// The one and only CLineChartControlDemoApp object

CLineChartControlDemoApp theApp;


// CLineChartControlDemoApp initialization

BOOL CLineChartControlDemoApp::InitInstance()
{
	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CLineChartControlDemoDlg dlg;
	m_pMainWnd = &dlg;
	//temp, 改变dlg数据
	dlg.setType(1);

	CLineChartControlDemoDlg *pAnothers = new CLineChartControlDemoDlg[5];

	//封装函数，绘制另外5个图形
	DrawOther(pAnothers, 5);

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	delete[] pAnothers;

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

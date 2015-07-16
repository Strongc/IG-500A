// LineChartControlDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LineChartControlDemo.h"
#include "LineChartControlDemoDlg.h"
#include <math.h>

using namespace RealtimeCurve;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{

}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// CLineChartControlDemoDlg dialog
CLineChartControlDemoDlg::CLineChartControlDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLineChartControlDemoDlg::IDD, pParent)
{
	ig = new IG();  // ��ʼ��ig��
	m_time	= 0.0f;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_iBtnExitFromRight = 10;
	m_iBtnExitFromBottom =10;
}

void CLineChartControlDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	// ����ͼ��
	DDX_Control(pDX, IDC_PLOT, m_plot);
	// ���ڽ����OK��ť
	//��ʼ��exit��ť
	DDX_Control(pDX, IDOK, m_btnExit);
}

BEGIN_MESSAGE_MAP(CLineChartControlDemoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	// this will be handled by OnTimer() in this Class
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_START, OnBnClickedStart)
	ON_BN_CLICKED(IDC_STOP, OnBnClickedStop)
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_BN_CLICKED(IDC_DISP_LINE1, OnBnClickedDispLine1)
	//ON_BN_CLICKED(IDC_DISP_LINE2, OnBnClickedDispLine2)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CLineChartControlDemoDlg message handlers
// �Ի������Ѿ����죬���ǶԻ���û����ʾ������ʱ��
BOOL CLineChartControlDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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

	((CButton*)GetDlgItem(IDC_DISP_LINE1))->SetCheck(TRUE);
	//((CButton*)GetDlgItem(IDC_DISP_LINE2))->SetCheck(TRUE);
	CString title;
	// TODO
	//field��������һ��ֵ���Ѿ�����,type����switch�л�����
	switch (dataType){
	case 1:
		title.Format("%s", "��̬��x����");
		break;
	case 2:
		title.Format("%s", "��̬��y����");
		break;
	case 3:
		title.Format("%s", "��̬��z����");
		break;
	case 4:
		title.Format("%s", "λ��Position(x����)");
		break;
	case 5:
		title.Format("%s", "λ��Position(y����)");
		break;
	case 6:
		title.Format("%s", "λ��Position(z����)");
		break;
	default:
		ASSERT(FALSE);
	}

	this->SetWindowText(title);

	//remember initial position
	GetWindowRect(&m_rectOldWindow);

	//�򵥵������˿�ȣ�ȴ������
	//CWnd::SetWindowPos(NULL, 0, 0, 600, 300, SWP_NOZORDER | SWP_NOMOVE);
	CRect rect;
	GetWindowRect(&rect);
	MoveWindow(0, 0, rect.Width(), rect.Height(), TRUE);

	m_btnExit.GetClientRect(&m_rectBtnExit);
	// plotָ��rect������ͼ��
	m_plot.GetWindowRect(&m_rectOldPlotWindow);
	TRACE("m_rectOldPlotWindow.left=%d,m_rectOldPlotWindow.width=%d\n",m_rectOldPlotWindow.left,m_rectOldPlotWindow.Width());
	//����Ļ�����λ��ת��Ϊ����Ŀͻ���������
	ScreenToClient(&m_rectOldPlotWindow);
	TRACE("m_rectOldPlotWindow.left=%d,m_rectOldPlotWindow.width=%d\n",m_rectOldPlotWindow.left,m_rectOldPlotWindow.Width());
	// ��ӵ������У���δ����
	m_plot.AddNewLine(_T("PV"),PS_SOLID,RGB(255,0,0));
	m_plot.AddNewLine(_T("SV"),PS_SOLID,RGB(0,255,0));

	m_plot.GetAxisX().AxisColor=RGB(0,255,0);
	m_plot.GetAxisY().AxisColor=RGB(0,255,0);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLineChartControlDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLineChartControlDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		// : ����ע����һ��,��������ʲôӰ��
		//SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLineChartControlDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/*
setType����
*/
void CLineChartControlDemoDlg::setType(int type){
	this->dataType = type;
	return;
}

/*
ontimer������6��ͼ��ֵͨ��timer����
*/
void CLineChartControlDemoDlg::OnTimer(UINT nIDEvent)
{

	//In fact, x values are not used when draw lines
	//If you want to use x values in any way, 
	//you may calculate point x in the way that point y is calculated.
	//see also: DrawLines(CDC* pDC);
	//float  y0 = 500*sin(m_time/5.0f);
	//float y1 = 500*cos(m_time/10.0f);
	
	/*��ȡy0, ����ig500a���ص�ֵ
	*/
	FinalData data;
	memset(&data, 0, sizeof(FinalData));
	ig->getIGData(&data);
	float y0 = 0;
	switch (dataType)
	{
	case 1:
		y0 = data.Angle[0];
		break;
	case 2:
		y0 = data.Angle[1];
		break;
	case 3:
		y0 = data.Angle[2];
		break;
	case 4:
		y0 = data.Position[0];
		break;
	case 5:
		y0 = data.Position[1];
		break;
	case 6:
		y0 = data.Position[2];
		break;
	default:
		ASSERT(FALSE);
	}

	m_plot.AddNewPoint(m_time,y0,0);
	//m_plot.AddNewPoint(m_time,y1,1);
	// time����ÿ0.1�����һ����
	m_time += 0.10f;
	//m_plot.GetAxisX().GetRangeLowerLimit() += 0.10f; 
	//CDialog::OnTimer(nIDEvent);
}

/*
���ǵ�timer, TODO,���ˣ�ֱ��������OnTimer������
*/
void CLineChartControlDemoDlg::OnTimerPro(UINT nIDEvent){
	//1.��IG���ȡ����, �����m_time���ӵ�ʱ��Ϊ0.2f�����ǿ϶���Ҫ���ĵģ���Ϊloop��˯��ʱ��
	FinalData finalData;
	memset(&finalData, 0, sizeof(finalData));
	ig->getIGData(&finalData);
	//���ӵ�, TODO
	m_plot.AddNewPoint(m_time, finalData.Angle[0], 0);
	m_plot.AddNewPoint(m_time, finalData.Angle[1], 1);
}

void CLineChartControlDemoDlg::OnBnClickedStart()
{
	SetTimer(1,10,NULL);
	m_plot.SetRate(10);//
	m_plot.Start();

	GetDlgItem(IDC_START)->EnableWindow(FALSE);
}

void CLineChartControlDemoDlg::OnBnClickedStop()
{
	KillTimer(1);
	m_plot.Stop();
	for(int i=0;i<m_plot.GetLineCount();i++)
	{
		m_plot.GetLineByIndex(i)->RemoveAllPoints();
	}
	GetDlgItem(IDC_START)->EnableWindow();
	m_plot.Invalidate();
}

/*
 Set new control postition as needed.
 */
void CLineChartControlDemoDlg::OnSize(UINT nType, int cx, int cy)
{	
	CDialog::OnSize(nType, cx, cy);
	CRect rect;
	GetClientRect(&rect);
	
	if(m_btnExit.GetSafeHwnd())
	{
		m_btnExit.MoveWindow(rect.right-m_iBtnExitFromRight-m_rectBtnExit.Width(),
							 rect.bottom-m_iBtnExitFromBottom-m_rectBtnExit.Height(),
							 m_rectBtnExit.Width(),m_rectBtnExit.Height() );
	}
	if(m_plot.GetSafeHwnd())
	{
		//TRACE("m_rectOldPlotWindow.left=%d,m_rectOldPlotWindow.width=%d\n",m_rectOldPlotWindow.left,m_rectOldPlotWindow.Width());

		m_plot.MoveWindow(m_rectOldPlotWindow.left,
			m_rectOldPlotWindow.top,
			rect.right-m_iBtnExitFromRight-5-m_rectOldPlotWindow.left,
			rect.bottom-m_iBtnExitFromBottom-m_rectBtnExit.Height()-7-m_rectOldPlotWindow.top);
	}
}

/*
 Check window size while resizeing, if small than origianl size, then restore to original size.
 */
void CLineChartControlDemoDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	/*if(pRect->right - pRect->left <=m_rectOldWindow.Width())
     	pRect->right = pRect->left + m_rectOldWindow.Width();
	
     if(pRect->bottom - pRect->top <=m_rectOldWindow.Height())
     	pRect->bottom = pRect->top + m_rectOldWindow.Height();*/

	CDialog::OnSizing(fwSide, pRect);
}

void CLineChartControlDemoDlg::OnBnClickedDispLine1()
{
	m_plot.GetLineByIndex(0)->IsShow = ((CButton*)GetDlgItem(IDC_DISP_LINE1))->GetCheck(); 
}

//void CLineChartControlDemoDlg::OnBnClickedDispLine2()
//{
//	m_plot.GetLineByIndex(1)->IsShow = ((CButton*)GetDlgItem(IDC_DISP_LINE2))->GetCheck(); 
//}
//

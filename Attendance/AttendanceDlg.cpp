
// AttendanceDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Attendance.h"
#include "AttendanceDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAttendanceDlg 对话框

CAttendanceDlg::CAttendanceDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAttendanceDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAttendanceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAttendanceDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CAttendanceDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CAttendanceDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CAttendanceDlg::OnBnClickedButtonSelectMember)
	ON_BN_CLICKED(IDC_BUTTON2, &CAttendanceDlg::OnBnClickedSelectTargetFile)
END_MESSAGE_MAP()


// CAttendanceDlg 消息处理程序

BOOL CAttendanceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAttendanceDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAttendanceDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAttendanceDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	// CDialogEx::OnOK();
	CString memberFilePath, targetFilePath;
	CWnd::GetDlgItemTextW(IDC_EDIT_MEMBER_FILE, memberFilePath);
	CWnd::GetDlgItemTextW(IDC_EDIT_TARGET_FILE, targetFilePath);
	if (memberFilePath.IsEmpty()){
		AfxMessageBox(L"请选择成员文件");
		return;
	}
	if (targetFilePath.IsEmpty()){
		AfxMessageBox(L"请定位目标文件夹位置");
		return;
	}

	CButton *pBtn = (CButton *)GetDlgItem(IDOK);
	pBtn->EnableWindow(FALSE); // True or False
	
	CFile memberfile;
	BOOL opened = memberfile.Open(memberFilePath, CFile::modeRead);
	if (!opened)
	{
		AfxMessageBox(L"文件不存在，请重新选择文件");
	}
	int fileLength = memberfile.GetLength();
	char *charBuf = new char[fileLength + 1];;
	memberfile.Read(charBuf, fileLength);
	CString member(charBuf);
	// CString member = CA2W(charBuf, CP_UTF8);
	memberfile.Close();
	delete charBuf;
	CWnd::SetDlgItemText(IDC_STATIC, member);

	//http://blog.csdn.net/fullsail/article/details/8449448

	pBtn->EnableWindow(TRUE);
}


void CAttendanceDlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

void CAttendanceDlg::OnBnClickedButtonSelectMember()
{
	CString defaultDir = L"F:\\";   //默认打开的文件路径  
	CString fileName = L"ccc.txt";         //默认打开的文件名
	CString filter = L"文件 (*.txt; *.csv; *.xls)|*.txt;*.csv;*.xls||";   //文件过虑的类型
	CFileDialog openFileDlg(TRUE, defaultDir, fileName, OFN_HIDEREADONLY | OFN_READONLY, filter, NULL);
	openFileDlg.GetOFN().lpstrInitialDir = L"F:\\ccc.txt";
	INT_PTR result = openFileDlg.DoModal();
	CString filePath = defaultDir + "\\ccc.txt";
	if (result == IDOK) {
		filePath = openFileDlg.GetPathName();
	}
	CWnd::SetDlgItemTextW(IDC_EDIT_MEMBER_FILE, filePath);
}


void CAttendanceDlg::OnBnClickedSelectTargetFile()
{
	static TCHAR filePath[MAX_PATH];

	CString openTitle = TEXT("选择一个源文件子文件夹");
	BROWSEINFO bi;
	bi.hwndOwner = ::GetFocus();
	bi.pidlRoot = NULL;
	bi.pszDisplayName = filePath;
	bi.lpszTitle = openTitle;
	bi.ulFlags = BIF_BROWSEFORCOMPUTER | BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS;
	bi.lpfn = NULL; //BrowseCallbackProc; 设置回调函数，实现记忆路径
	bi.lParam = 0;
	bi.iImage = 0;

	LPITEMIDLIST pItemIDList = ::SHBrowseForFolder(&bi);
	if (pItemIDList == NULL)
	{
		return;
	}

	::SHGetPathFromIDList(pItemIDList, filePath);

	CWnd::SetDlgItemTextW(IDC_EDIT_TARGET_FILE, filePath);
}

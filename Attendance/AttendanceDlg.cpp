
// AttendanceDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Attendance.h"
#include "AttendanceDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAttendanceDlg �Ի���

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
END_MESSAGE_MAP()


// CAttendanceDlg ��Ϣ��������

BOOL CAttendanceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ����Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի���������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CAttendanceDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CAttendanceDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAttendanceDlg::OnBnClickedOk()
{
	// TODO:  �ڴ����ӿؼ�֪ͨ�����������
	// CDialogEx::OnOK();
	CString filePath;
	CWnd::GetDlgItemTextW(IDC_EDIT_MEMBER_FILE, filePath);
	CFile memberfile;
	BOOL opened = memberfile.Open(filePath, CFile::modeRead);
	if (!opened)
	{
		AfxMessageBox(L"�ļ������ڣ�������ѡ���ļ�");
	}
	CString member;
	memberfile.Read(member.GetBuffer(memberfile.GetLength()), memberfile.GetLength());
	memberfile.Close();
	CWnd::SetDlgItemText(IDC_STATIC, member);
	
}


void CAttendanceDlg::OnBnClickedCancel()
{
	// TODO:  �ڴ����ӿؼ�֪ͨ�����������
	CDialogEx::OnCancel();
}

void CAttendanceDlg::OnBnClickedButtonSelectMember()
{
	CString defaultDir = L"F:\\";   //Ĭ�ϴ򿪵��ļ�·��  
	CString fileName = L"ccc.txt";         //Ĭ�ϴ򿪵��ļ���
	CString filter = L"�ļ� (*.txt; *.csv; *.xls)|*.txt;*.csv;*.xls||";   //�ļ����ǵ�����
	CFileDialog openFileDlg(TRUE, defaultDir, fileName, OFN_HIDEREADONLY | OFN_READONLY, filter, NULL);
	openFileDlg.GetOFN().lpstrInitialDir = L"F:\\ccc.txt";
	INT_PTR result = openFileDlg.DoModal();
	CString filePath = defaultDir + "\\ccc.txt";
	if (result == IDOK) {
		filePath = openFileDlg.GetPathName();
	}
	CWnd::SetDlgItemTextW(IDC_EDIT_MEMBER_FILE, filePath);
}
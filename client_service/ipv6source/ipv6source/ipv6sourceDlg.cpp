
// ipv6sourceDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ipv6source.h"
#include "ipv6sourceDlg.h"
#include "afxdialogex.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include "highgui.h"
#include "cv.h"
using namespace std;
// ���������
#pragma comment (lib,"Ws2_32.lib")
void showpic(void*);

HWND m_FatherHwnd;//�����ڵľ��
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cipv6sourceDlg �Ի���




Cipv6sourceDlg::Cipv6sourceDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cipv6sourceDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cipv6sourceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cipv6sourceDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_MESSAGE(WM_SHOW_IMAGE,&Cipv6sourceDlg::DrawPic)
END_MESSAGE_MAP()


// Cipv6sourceDlg ��Ϣ�������

BOOL Cipv6sourceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_FatherHwnd=this->m_hWnd;
	_beginthread(showpic,0,(void*)0);
	//SetTimer(1,1,NULL);
	//SetTimer(2,1,NULL);
		
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�
void showpic(void*)
{
	WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    SOCKET client_sock;  //�ͻ��˱����׽���
    struct addrinfo server_addr, *addrinfo=NULL; //�������˵�ַ 
    memset(&server_addr,0,sizeof(server_addr));//��getaddrinfo()֮ǰ������0
    server_addr.ai_family = AF_INET6;  //ָ����ipv6Э��
    server_addr.ai_socktype = SOCK_STREAM; //��ʽ
    server_addr.ai_protocol = IPPROTO_TCP;  //TCPЭ��,Ҳ������0����ϵͳ�Լ�ѡ
    int result = getaddrinfo("2001::1","2000",&server_addr,&addrinfo);  //��������ipv6��ַ, �����������Ķ˿�
	IplImage* img=cvCreateImage(cvSize(640,480),8,3);
	//IplImage* img;
	while(1)
    {
	   SOCKET service_sock = socket(addrinfo->ai_family,addrinfo->ai_socktype,addrinfo->ai_protocol);
	   int iframe=connect(service_sock,addrinfo->ai_addr,addrinfo->ai_addrlen);
	   if(iframe<0)continue;
	   char recvBuf[100];
	   memset(recvBuf,0,sizeof(recvBuf));
	   FILE* tof=fopen("output.jpg","wb+");
	   while (recv(service_sock,recvBuf,40,0)>0)
	   {
		   fwrite(recvBuf,sizeof(char),40,tof);
	   }
	   fclose(tof);
	   closesocket(service_sock);
	   //Sleep(100);
	   IplImage*  showimg=cvLoadImage("output.jpg");   
	   //cvZero(img);
	   //img=cvCopy(showimg);
	   cvCopy(showimg,img,NULL);
	   ::PostMessage(m_FatherHwnd,WM_SHOW_IMAGE,(WPARAM)img,NULL);
	   cvReleaseImage(&showimg);
	   
    }
	cvReleaseImage(&img);
}
void Cipv6sourceDlg::OnPaint()
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
HCURSOR Cipv6sourceDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void Cipv6sourceDlg::DrawPicToHDC(IplImage *img,unsigned int id)
{
	CDC* pDC = GetDlgItem(id)->GetDC();
	HDC hDC = pDC->GetSafeHdc();
	CRect rect;
	GetDlgItem(id)->GetClientRect(&rect);
	CvvImage cimg;
	cimg.CopyOf(img,img->nChannels); 
	cimg.DrawToHDC(hDC,&rect);
	ReleaseDC(pDC);
}
LRESULT Cipv6sourceDlg::DrawPic(WPARAM wParam,LPARAM lParam)
{
	IplImage *img = (IplImage*)wParam;
	DrawPicToHDC(img,IDC_VIDEOCOLOR);

	return 0;
}

void Cipv6sourceDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnTimer(nIDEvent);
}

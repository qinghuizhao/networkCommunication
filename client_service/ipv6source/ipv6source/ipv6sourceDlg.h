
// ipv6sourceDlg.h : ͷ�ļ�
//

#pragma once
#include "CvvImage.h"
#define WM_SHOW_IMAGE WM_USER+1
// Cipv6sourceDlg �Ի���
class Cipv6sourceDlg : public CDialogEx
{
// ����
public:
	Cipv6sourceDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_IPV6SOURCE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:
	void DrawPicToHDC(IplImage *img,unsigned int id);
	LRESULT DrawPic(WPARAM wParam,LPARAM lParam);
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

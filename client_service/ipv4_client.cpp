// myreserve.cpp : �������̨Ӧ�ó������ڵ㡣

#include "stdafx.h"
#include <WinSock2.h>
#include <stdio.h>
#include <string>
#pragma comment(lib,"Ws2_32")
#include<iostream>
#include "highgui.h"
#include "cv.h"
using namespace std;

int main()
{  
    //�����׽��ֿ�
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;
    wVersionRequested = MAKEWORD(1,1);
    err = WSAStartup(wVersionRequested,&wsaData);
    if (err!=0)
    {
        return 0;
    }
    if (LOBYTE(wsaData.wVersion)!=1||HIBYTE(wsaData.wVersion)!=1)
    {
        WSACleanup();
        return 0;
    }
    SOCKADDR_IN addrSrv;
    addrSrv.sin_addr.S_un.S_addr = inet_addr("192.168.118.56");
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(6000);
    int np=0;
    //��Ƶͷ
    IplImage* frame;
    CvCapture *capture ;
    capture=cvCreateCameraCapture(0);
    while(1)
    {
        frame=cvQueryFrame (capture);
        if(frame) break;
    }
    while(1)
    {
        //�����׽���
        SOCKET sockClient = socket(AF_INET,SOCK_STREAM,0);
        //�������������������
        connect(sockClient,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));
        //��������
        char recvBuf[100];
        memset(recvBuf,0,sizeof(recvBuf));
        FILE* tof=fopen("output.jpg","wb+");
        char sendBuf1[1000];
        memset(sendBuf1,0,sizeof(sendBuf1));
        frame=cvQueryFrame (capture);
        if(!frame) break;
        cvSaveImage("input.jpg",frame);
        FILE* fp1=fopen("input.jpg","rb+");
        while (recv(sockClient,recvBuf,100,0)>0)
        {
            fwrite(recvBuf,sizeof(char),100,tof);
            send(sockClient,sendBuf1,100,0);
        }
        fclose(tof);
        fclose(fp1);
        closesocket(sockClient);
        IplImage *showimage=cvLoadImage("output.jpg");
        cvNamedWindow("video");
        cvShowImage("video",showimage);
        cvWaitKey(10);
        cout<<"��"<<np<<"ͼƬ������ϣ�"<<endl;
        cvReleaseImage(&showimage);
    }
    WSACleanup();
    return 0;
}


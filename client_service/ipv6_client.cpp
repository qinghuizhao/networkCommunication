#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
using namespace std;
// ���������
#pragma comment (lib,"Ws2_32.lib")

int main()
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        cout<<"װ��socketʧ��!"<<endl;
        return -1 ;
    }
    SOCKET client_sock;  //�ͻ��˱����׽���
    struct addrinfo server_addr, *addrinfo=NULL; //�������˵�ַ
    memset(&server_addr,0,sizeof(server_addr));//��getaddrinfo()֮ǰ������0
    server_addr.ai_family = AF_INET6;  //ָ����ipv6Э��
    server_addr.ai_socktype = SOCK_STREAM; //��ʽ
    server_addr.ai_protocol = IPPROTO_TCP;  //TCPЭ��,Ҳ������0����ϵͳ�Լ�ѡ
    int result;
    result = getaddrinfo("::1","2000",&server_addr,&addrinfo);  //��������ipv6��ַ, �����������Ķ˿�
    if(result !=0)//��ַ������ȷʱ����0
    {
        cout<<"�ͻ��˽�����������ַʧ��!"<<endl;
        return -1;
    }
    client_sock = socket(addrinfo->ai_family,addrinfo->ai_socktype,addrinfo->ai_protocol); //�����ͻ����׽���
    if(client_sock == INVALID_SOCKET)
    {
        cout<<"�����ͻ���socketʧ��!"<<endl;
        return -1;
    }
    if( connect(client_sock,addrinfo->ai_addr,addrinfo->ai_addrlen) == SOCKET_ERROR)  //���ӷ�����
    {
        cout<<"���ӷ���������!"<<endl;
        return -1;
    }
    char buf[256];  //���ͺͽ��ջ�����
    int nRecv=0;

    while(1)
    {
        nRecv=recv(client_sock,buf,256,0);
        if(nRecv>0)
        {
            buf[nRecv]='/0';
            cout<<"�ͻ����յ�:"<<buf<<endl;
        }
        cout<<"�ͻ���������:";
        cin>>buf;
        send(client_sock,buf,256,0);
    }
    closesocket(client_sock); //�رտͻ����׽���
    return 1;
}

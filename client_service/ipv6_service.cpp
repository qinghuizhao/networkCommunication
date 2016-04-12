#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
using namespace std;
// ���������
#pragma comment (lib,"Ws2_32.lib")

int main(int argc, char *argv[])
{
    WSADATA wsaData;  //�汾Э��
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        cout<<"װ��socketʧ��!"<<endl;
        return -1;
    }

    SOCKET server_sock, client_sock;  //�������˺Ϳͻ����׽���
    //addrinfo�ṹ����Ϊ������IPv6Э����IPv4Э��֮��Ĳ��죬����ͳһ�ĳ����׷�ӵĽṹ������������IPv4��ַ��IPv6��ַ��������
    struct addrinfo server_addr , //�������˵�ַ��Ϣ
            *res=NULL; //���ж����ַ��res�ǵ�ַ��Ϣ����ָ��
    memset(&server_addr,0,sizeof(server_addr));//���û����仰�ͻ���ְ󶨴���,Ҳ�����ڵ���getaddrinfo()֮ǰ�ò���������0
    server_addr.ai_family = AF_INET6;  //��ַ��,����ָ����ipv6Э��,��ֵ������ AF_INET:ipv4, AF_INET6:ipv6
    server_addr.ai_socktype = SOCK_STREAM;  //�׽�������,��������ʽ,��ֵ������ SOCK_STREAM:��ʽ, SOCK_DGRAM:���ݱ�, SOCK_RAW:ԭʼ�׽���
    server_addr.ai_protocol = IPPROTO_TCP;  //�����Э��,������TCPЭ��,��ֵ������: IPPROTO_TCP:TCP, IPPROTO_UDP:UDP, ��Ϊ0ϵͳ�����׽��������Զ�ѡ��
    int result;
    result = getaddrinfo("::1", "2000", &server_addr, &res); //����������ַ, ��������ַ �����˿�
    if(result != 0)//��ַ������ȷʱ����0
    {
        cout<<"��������ַ��������!"<<endl;
        return -1 ;
    }

    server_sock = socket(res->ai_family,res->ai_socktype,res->ai_protocol); //������������socket
    if(server_sock == INVALID_SOCKET)
    {
        cout<<"����������socketʧ��!"<<endl;
        return -1;
    }

    if(bind(server_sock, res->ai_addr, res->ai_addrlen) == SOCKET_ERROR)  //��
    {
        cout<<"�������˰�ʧ��!"<<endl;
        return -1;
    }

    if( listen(server_sock ,2) == SOCKET_ERROR )  //����
    {
        cout<<"�������˼���ʧ��!"<<endl;
        return -1;
    }

    //  struct sockaddr_in6 client_addr; //�ͻ��˵�ַ
    struct sockaddr_storage client_addr; //�ṹ��sockaddr_storage���㹻��Ŀռ����洢�κ����͵�sockaddr
    int clientaddr_len = sizeof(client_addr);  //�ͻ��˵�ַ����
    while(1)
    {
        client_sock = accept(server_sock,(struct sockaddr*)&client_addr,&clientaddr_len);//���ܿͻ�������
        if(client_sock == INVALID_SOCKET)
        {
            cout<<"���ܿͻ�������ʧ��!"<<endl;
            continue;   //����
        }
        char buf[256];//���ͺͽ��ջ�����
        int nRecv=0;

        while(1)
        {
            cout<<"��������������:";
            cin>>buf;
            send(client_sock,buf,256,0);
            nRecv = recv(client_sock,buf,256,0);
            if(nRecv>0)
            {
                buf[nRecv]='/0';
                cout<<"�������յ�:"<<buf<<endl;
            }
        }
    }
    closesocket(server_sock);//�رշ��������׽���
    closesocket(client_sock);//�رտͻ����׽���
    
    return 1;
}

//�������������򣬵ȴ��ͻ������󣬷������ݿ��е����ݵ��ͻ��ˡ�
//���߳� ����־��mysql������IO��data�߳� RDB AOF
//�ṩ��¼�߼� Ȩ��
//epoll+thread+Reactor


//�ͻ�����QT ��¼ ���� ���� ��ȡ��Ӧ


//������� ��Ϣ��ʽ

//�ṩWeb�ˣ����Լ�����HTTP ��nginx��һ��
//cgi ��rpc��ftp

//������������ʱ���֡�ʱ��� ���źš���־
//���ܷ�����


#include"elemap.h"
#define BUFFER_SIZE 1024
//���̣߳��޸��ã�����IO echo
//�򵥰棺
//��������->����(����)->�˵���ִ�У�->��ȡ���->���루��װ�����->����

/*
int main(int argc,char* argv[])
{
	int sockfd;
	sockaddr_in address;
	if(argc<=2)
	{
		perror("Usage:serv ip port");
	}
	char* ip=argv[1];
	char* port=argv[2];
	char* buf=new char[BUFFER_SIZE];
	memset(&address,0,sizeof(address));
	address.sin_family=AF_INET;
	inet_pton(AF_INET,ip,address.sin_addr);
	address.port=htons(atoi(port));

	int ret=socket(sockfd,PF_INET,SOCK_STREAM,0);
	
	ret=bind(sockfd,(struct sockaddr*)&address,sizeof(address));

	listen(sockfd,5);
	sockaddr_in client_address;
	socklen_t len=sizeof(client_address);
	int ret=accept(sockfd,&client_address,&len);
	
	while(1)
	{
		int n=read(sockfd,buf,BUFFER_SIZE);
		decode(buf);
		n=write(sockfd,buf,BUFFER_SIZE);
	}
	close(sockfd);
	return 0;
}

*/


/*
template<typename T>//T��ʾ����
class mysqlpool {
	vector<mysqlc*> mysqlv;
	queue<T*> requeue;//���Ӷ���
	static const int MAX_CON = 5;
	int m_con;//������

	void initpool()
	{
		//��ʼ��5��mysql����
	}


};
*/


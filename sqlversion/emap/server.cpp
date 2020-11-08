//创建服务器程序，等待客户端请求，发送数据库中的数据到客户端。
//多线程 ，日志，mysql，连接IO，data线程 RDB AOF
//提供登录逻辑 权限
//epoll+thread+Reactor


//客户端用QT 登录 连接 请求 获取相应


//编解码器 消息格式

//提供Web端，用自己做的HTTP 和nginx各一个
//cgi 、rpc、ftp

//单例、并发、时间轮、时间堆 、信号、日志
//性能分析。


#include"elemap.h"
#define BUFFER_SIZE 1024
//单线程，无复用，阻塞IO echo
//简单版：
//读入数据->解码(命令)->菜单（执行）->获取结果->编码（分装结果）->发回

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
template<typename T>//T表示请求
class mysqlpool {
	vector<mysqlc*> mysqlv;
	queue<T*> requeue;//连接队列
	static const int MAX_CON = 5;
	int m_con;//连接数

	void initpool()
	{
		//初始化5个mysql连接
	}


};
*/


/*
#include"maptest.h"
//等待连接，接收请求，解析请求，执行命令，封装相应，发回相应。

class Server
{
public:
	Server() {};
	~Server() {};
	void ConnectionCallback();
	void MessageCallback();
private:
	int sockfd;
	sockaddr_in address;
	int epollfd;
};

class EventLoop
{
public:
	void poller();
private:
	Server* server;
};
class Channel 
{
public:
	void handleRead();
	void readcallback();
	void writecallback();
private:
	EventLoop* loop;
};

class Poller
{
public:
	Poller(){}
	~Poller(){}
	int poll(int epollfd,Server server);
private:
	int epollfd;
	Server* server;
};*/
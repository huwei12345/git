/*
#include"maptest.h"
//�ȴ����ӣ��������󣬽�������ִ�������װ��Ӧ��������Ӧ��

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
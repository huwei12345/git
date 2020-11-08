#ifndef MAPTEST_H
#define MAPTEST_H

#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#include<string>
#include<vector>
#include<fstream>
#include<iomanip>
#include<ctime>
#include"../mysqlapi/CMysql.h"
#include"../mysqlmgr/MysqlManager.h"


//#define DE
#define trans4(x) (x[0]<<24)&(0xff000000)|(x[1]<<16)&(0x00ff0000)|(x[2]<<8)&(0x0000ff00)|(x[3])&(0x000000ff)
#define trans2(x) (x[1])&(0x00ff)|(x[0]<<8)&(0xff00)
#define FNLIMIT 100  //����ѯforknumС��30����ʾ������������ļ�
#define CNLIMIT 100  //ͬ��
#define NAMELIMIT 100 //ͬ��

using namespace std;

//������¼�ڵ�
class node {
public:
	unsigned short record_size;//2�ֽ� Size
	unsigned int LinkID;//4�ֽ� LinkID
	unsigned short roadsize;//2�ֽ� ��·����Size
	//unsigned int flag;//ʼ��Node���鱨
	//31-8 Reserved
	bool hasflag;//7 ·����������Flag
	short forkroad;//6-4 ��·��
	short classnum;//3-0 ����Link�б�ʾClass����
	unsigned int information;
	char* name;//��������string �ѿռ䣬string��װchar*
	void show();//��ʾһ����¼
};

//�̳�vector����װ�Խڵ�vector��һЩ����
class Record:public vector<node*> //��¼,�̳�vector
{
public:
	//sort:
	void bubblesort();//ð��
	void selectsort();
	int partition(int l, int r);
	void quicksort(int l, int r);//quicksort,�ݹ���̫��
	void insertsort();
	void perdown(int i, int first, int last);//perdown,���½���ǰ�ڵ������ȷλ��
	void make_heap(int first, int last);//����
	void heapsort();
	void stlsort();
	void merge(int l, int r, int mid);
	void merge_sort(int l,int r);//�鲢����
	//search::
	int search(node** res, unsigned int Linknum);//����Linknum
	int searchcn(Record& res, unsigned short value);//����classnum
	int searchfn(Record& res, unsigned short value);//����forknum
	int search(Record& res, const char* name);//�������ƣ���ͨ����
	int binarysearch(node** res,int l, int r, unsigned int value);//�۰����LinkID
	//��д
	void readtext(const char* filename);
	void cupdate(vector<node*> &res,const char* filename);
	void bupdate(vector<node*> &res,const char* filename);
	void showall();//��ʾȫ����¼
};

//�������Mysql �Ľ�һ����װ���������mysql����������һЩ����
class MysqlManager
{
public:
	MysqlManager():m_mysql(new CMysql){
	}
	
	MysqlManager(CMysql* mysql)
		:m_mysql(mysql)
	{}

	~MysqlManager()
	{
		delete m_mysql;
	}

	CMysql* getCMysql() { return m_mysql; }

	void readtexttomysql(const char* filename);
	void mysqlsort();//����
	void mysqlsearch();//����
	void mysqlupdate(const char* filename);//����Ϊ�ַ��ļ�
	bool mysqlbupdate(const char* filename);//����Ϊ�ֽ��ļ�������
	
	void mysqlinsert();//����
	void mysqldelete();//ɾ��
	void mysqlmodify();//�޸�
	
	bool mysqlshowall();//��ʾȫ��
	bool mysqlread(const char* filename);//�ָ�
	void readRecord(Record& record);//����Record��

	bool writefile(QueryResult* pResult, const char* pathname);
	bool writefile(MYSQL_RES* result, const char* pathname, int k);

private:
	CMysql* m_mysql;//��Mysql���ӵķ�װ����װ��mysql�ײ�api����ѯ��ִ�С�����ṹ
};


class Window  //������
{
public:
	void normalwindow(Record& record);
	void sortwindow(Record& record);
	void searchwindow(Record& record);
	void startwindow(Record& record);
	void mysqlwindow(Record& record);
};
#endif
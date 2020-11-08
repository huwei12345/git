#ifndef MAPTEST
#define MAPTEST

#include<iostream>
#include<algorithm>
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
#define FNLIMIT 100  //当查询forknum小于30条显示，大于输出到文件
#define CNLIMIT 100  //同上
#define NAMELIMIT 100 //同上

using namespace std;

//单条记录节点
class node {
public:
	unsigned short record_size;//2字节 Size
	unsigned int LinkID;//4字节 LinkID
	unsigned short roadsize;//2字节 道路名称Size
	//unsigned int flag;//始点Node的情报
	//31-8 Reserved
	bool hasflag;//7 路线名称有无Flag
	short forkroad;//6-4 岔路数
	short classnum;//3-0 交叉Link列表示Class番号
	unsigned int information;
	char* name;//不建议用string 费空间，string封装char*
	void show();//显示一条记录
};

//继承vector，封装对节点vector的一些操作
class Record:public vector<node*> //记录,继承vector
{
public:
	//sort:
	void bubblesort();//冒泡
	void selectsort();
	int partition(int l, int r);
	void quicksort(int l, int r);//quicksort,递归层次太深
	void insertsort();
	void perdown(int i, int first, int last);//perdown,向下将当前节点放在正确位置
	void make_heap(int first, int last);//建堆
	void heapsort();
	void stlsort();
	void merge(int l, int r, int mid);
	void merge_sort(int l,int r);//归并排序
	//search::
	int search(node** res, unsigned int Linknum);//搜索Linknum
	int searchcn(Record& res, unsigned short value);//搜索classnum
	int searchfn(Record& res, unsigned short value);//搜索forknum
	int search(Record& res, const char* name);//搜索名称，普通搜索
	int binarysearch(node** res,int l, int r, unsigned int value);//折半查找LinkID
	//读写
	void readtext(const char* filename);
	void cupdate(vector<node*> &res,const char* filename);
	void bupdate(vector<node*> &res,const char* filename);
	void showall();//显示全部记录
};

//本程序对Mysql 的进一步封装，本程序对mysql连接所做的一些函数
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
	void mysqlsort();//排序
	void mysqlsearch();//查找
	void mysqlupdate(const char* filename);//更新为字符文件
	bool mysqlbupdate(const char* filename);//更新为字节文件，备份
	
	void mysqlinsert();//添加
	void mysqldelete();//删除
	void mysqlmodify();//修改
	
	bool mysqlshowall();//显示全部
	bool mysqlread(const char* filename);//恢复
	void readRecord(Record& record);//读到Record中

	bool writefile(QueryResult* pResult, const char* pathname);
	bool writefile(MYSQL_RES* result, const char* pathname, int k);

private:
	CMysql* m_mysql;//是Mysql连接的封装，封装了mysql底层api，查询、执行、结果结构
};


class Window  //窗口类
{
public:
	void normalwindow(Record& record);
	void sortwindow(Record& record);
	void searchwindow(Record& record);
	void startwindow(Record& record);
	void mysqlwindow(Record& record);
};
#endif
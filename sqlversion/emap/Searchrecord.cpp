#include"elemap.h"
extern int hassorted;
extern int hasread;
//4.采用顺序查找、折半查找、分块查找等多种查找方法进行性能比较。
//对于已检索到的信息分两部分处理，一部分可以作为界面显示，这部分内容一般数量较少，只有几条记录；
//另一部分数量比较大的可以写在一个文本文件中，这样有利于查阅和校对。
//除块查找外已完成

int Record::search(node** res,unsigned int Linknum)//搜索Linknum
{
	Record& record = (*this);
	int flag = 0;
	//只支持一种搜索LinkID
	size_t num=this->size();
	for (size_t i = 0; i <num ; i++)
		if (record[i]->LinkID == Linknum)
		{
			flag = 1;
			*res = record[i];
		}
	if (flag == 0)
	{
		*res = nullptr;
		return -1;
	}
	else
		return 0;
}
int Record::searchcn(Record &res,unsigned short value)//搜索classnum
{
	res.clear();
	Record& record = (*this);
	for (size_t i = 0; i < record.size(); i++)
		if (record[i]->classnum == value)
		{
			res.push_back(record[i]);
		}
	return 0;
}
int Record::searchfn(Record &res, unsigned short value)//搜索forknum
{
	res.clear();
	Record& record = (*this);
	for (size_t i = 0; i < record.size(); i++)
		if (record[i]->forkroad == value)
		{
			res.push_back(record[i]);
		}
	return 0;
}

int Record::search(Record& res, const char* name)//搜索名称，普通搜索
{
	res.clear();
	Record& record = (*this);
	//只支持一种搜索LinkID
	for (size_t i = 0; i < record.size(); i++)
		if (record[i]->name != nullptr)
		{
			if (!strcmp(record[i]->name, name))
			{
				res.push_back(record[i]);
			}
		}
	return 0;
}

int Record::binarysearch(node** res,int l, int r, unsigned int value)//折半查找LinkID
{
	Record& record = (*this);
	int re = -1;
	int mid = 0;
	while (l != r)
	{
		mid = (l + r) / 2;
		if (record[mid]->LinkID == value)
		{
			re = mid;
			break;
		}
		else if (record[mid]->LinkID > value)
			r = mid;
		else
			l = mid + 1;
	}
	if (re!=-1)
	{
		*res = record[re];
		return 0;
	}
	else
	{
		*res = nullptr;
		return -1;
	}
}
#include"elemap.h"
extern int hassorted;
extern int hasread;
//4.����˳����ҡ��۰���ҡ��ֿ���ҵȶ��ֲ��ҷ����������ܱȽϡ�
//�����Ѽ���������Ϣ�������ִ���һ���ֿ�����Ϊ������ʾ���ⲿ������һ���������٣�ֻ�м�����¼��
//��һ���������Ƚϴ�Ŀ���д��һ���ı��ļ��У����������ڲ��ĺ�У�ԡ�
//��������������

int Record::search(node** res,unsigned int Linknum)//����Linknum
{
	Record& record = (*this);
	int flag = 0;
	//ֻ֧��һ������LinkID
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
int Record::searchcn(Record &res,unsigned short value)//����classnum
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
int Record::searchfn(Record &res, unsigned short value)//����forknum
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

int Record::search(Record& res, const char* name)//�������ƣ���ͨ����
{
	res.clear();
	Record& record = (*this);
	//ֻ֧��һ������LinkID
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

int Record::binarysearch(node** res,int l, int r, unsigned int value)//�۰����LinkID
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
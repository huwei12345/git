#ifndef MYSQLPOOL_H
#define MYSQLPOOL_H
#include"elemap.h"
void mysql(Record& record)//���ڰ汾1����Recordд�뵽mysql��?
{
	string host("localhost");
	string user("root");
	string pwd("123456");
	string dbName("roadinfo");
	CMysqlManager mgr;//mgr�а���CMysql,CMysql���ɼ������������һ��ʼ��ʼ�����ݿ⣬��ʼ�����ر�����
	if (mgr.init(host.c_str(), user.c_str(), pwd.c_str(), dbName.c_str()) == false)//����
		return;
	char* str = new char[1024*1024];
	//��Ҫ��ѯ��Ҫ���½�������
	std::shared_ptr<CMysql> cmysql=static_cast<std::shared_ptr<CMysql>>(new CMysql());
	cmysql->init(host,user,pwd,dbName);
	cmysql->execute("delete from roadinfo;");

	sprintf(str,"insert into roadinfo(LinkID,classnum,forkroad,hasflag,information,name,record_size,roadsize) values");
	//(LinkID,classnum,forkroad,hasflag,information,name,record_size,roadsize)
	int size=record.size();
	clock_t start=clock();
	for (int i = 0; i < size; ++i)
	{
		node* p = record[i];
		//��ʽ��һ�����ݣ�������sql���
		//sprintf(str,"insert into roadinfo values( %d,%d,%d,%d,%d,%d,%d,%s);", record[i]->LinkID,record[i]->record_size
		//	,record[i]->roadsize,record[i]->hasflag,record[i]->forkroad,record[i]->classnum,record[i]->information,record[i]->name);
		
	// record_size Linkid    roadsize   hasflag  forkroad   classnum       roadname
		if ((i>0&&i % 1000 == 0)||i==size-1)
		{
			sprintf(str,"%s(%d,%d,%d,%d,%d,'%s',%d,%d);", str, p->LinkID, p->classnum
				, p->forkroad, p->hasflag, p->information, p->name, p->record_size, p->roadsize);
			if (cmysql->execute(str) == false)//��������,�Ѿ�����
			{
				cout << "insert error" << endl;
				break;
			}
			sprintf(str,"insert into roadinfo(LinkID,classnum,forkroad,hasflag,information,name,record_size,roadsize) values");
		}
		else
			sprintf(str,"%s(%d,%d,%d,%d,%d,%s,%d,%d),", str, p->LinkID, p->classnum
				, p->forkroad, p->hasflag, p->information, p->name, p->record_size, p->roadsize);

	}
	clock_t end = clock();
	cout << "cost " << ((double)end - (double)start) / CLOCKS_PER_SEC << " sec" << endl;
	cmysql.reset();
	delete[] str;
	//mysql.~CMysql();
}

#endif
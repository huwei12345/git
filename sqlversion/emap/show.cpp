#include"elemap.h"
#include<iomanip>
//void Show::show(node* p)//��ʾһ����¼
void node::show()//��ʾһ����¼
{
	node* p = this;
		cout << setw(10) << p->record_size << setw(10) << p->LinkID << setw(10) << p->roadsize << setw(10)\
		<< p->hasflag << setw(10) << p->forkroad << setw(10) << p->classnum;
	if (p->name != nullptr)
		cout <<setw(23)<< p->name << endl;
	else
		cout << setw(23) << "(null)"<<endl;
	//printf("%10hu %10u %10hu %10d %10hd %10hd %20s\n", p->record_size, p->LinkID, p->roadsize, \
	//	p->hasflag, p->forkroad, p->classnum, p->name);
}

//void Show::showall(vector<node*> record)//��ʾȫ����¼
void Record::showall()//��ʾȫ����¼
{
	Record& record = (*this);
	cout << "   record_size Linkid    roadsize   hasflag  forkroad   classnum       roadname" << endl;
	for (size_t i = 0; i < record.size(); ++i)
	{
		cout << setw(10) << record[i]->record_size << setw(10) << record[i]->LinkID << setw(10) << record[i]->roadsize << setw(10)\
			<< record[i]->hasflag << setw(10) << record[i]->forkroad << setw(10) << record[i]->classnum;
		if (record[i]->name != nullptr)
			cout << setw(20) << record[i]->name << endl;
		else
			cout << setw(20) << "(null)" << endl;
	}
	//	printf("%10hu %10u %10hu %10d %10hd %10hd %20s\n", record[i]->record_size, record[i]->LinkID, record[i]->roadsize, \
	//		record[i]->hasflag, record[i]->forkroad, record[i]->classnum, record[i]->name);
}
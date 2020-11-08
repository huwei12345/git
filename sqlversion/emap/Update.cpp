#include"elemap.h"
void Record::cupdate(vector<node*>& res, const char* pathname)
{
	Record& record = (*this);
	ofstream fp;
	fp.open(pathname,ios::out|ios::trunc);
	//FILE* fp;
	//errno_t err = fopen_s(&fp, pathname, "w+");
	fp<<"    record_size Linkid   roadsize    hasflag   forkroad   classnum         roadname"<<endl;
	for (size_t i = 0; i < record.size(); i++)
	{
		//fwrite("recordtext",fp);
		fp << setw(10) << record[i]->record_size << setw(10) << record[i]->LinkID << setw(10) << record[i]->roadsize\
			<< setw(10) << record[i]->hasflag << setw(10) << record[i]->forkroad << setw(10) << record[i]->classnum;
		if (record[i]->name != nullptr)
			fp<< setw(25) << record[i]->name << endl;
		else
			fp<< setw(25) << "(null)" << endl;
	}
	//fprintf(fp, "%10hu %10u %10hu %10d %10hd %10hd %20s\n", record[i]->record_size, record[i]->LinkID, record[i]->roadsize, \
		//	record[i]->hasflag, record[i]->forkroad, record[i]->classnum, record[i]->name);
	//		fprintf(fp, "%d %d %d %d %d %d %s", record[i]->record_size, record[i]->LinkID, record[i]->roadsize,\ 
	//		record[i]->hasflag,record[i]->forkroad, record[i]->classnum,record[i]->name);
	fp.close();
	cout<<pathname<<" file update success"<<endl;
}

void Record::bupdate(vector<node*>& res, const char* pathname)
{
	Record& record = (*this);
	ofstream fp;
	//errno_t err = fopen_s(&fp, pathname, "wb");
	fp.open(pathname, ios::binary|ios::trunc);
	int ret = 0;
	unsigned int trint = 0;
	unsigned short trshort = 0;
	char buf2[2];
	char buf3[4];
	unsigned short a = 0x00ff;
	unsigned int b = 0x000000ff;

	for (size_t i = 0; i < record.size(); i++)
	{
		trshort = record[i]->record_size;
		for (int i = 0; i < 2; i++)
		{
			buf2[i] = (trshort >> ((1 - i) * 8)) & a;
		}
		//±ØÐë·´Ðò int->buf
		
		//if (!(ret = fwrite(buf2, 2, 1, fp)))
		fp.write(buf2, 2);
		if(fp.fail())
			perror("get record_size error");

		trint = record[i]->LinkID;
		for (int i = 0; i < 4; i++)
		{
			buf3[i] = (trint >> ((3 - i) * 8)) & b;
		}
		//if (!(ret = fwrite(buf3, 4, 1, fp)))
		fp.write(buf3, 4);
		if (fp.fail())
			perror("get LinkID error");

		trshort = record[i]->roadsize;
		for (int i = 0; i < 2; i++)
		{
			buf2[i] = (trshort >> ((1 - i) * 8)) & a;
		}
		//if (!(ret = fwrite(buf2, 2, 1, fp)))
		fp.write(buf2, 2);
		if (fp.fail())
			perror("get roadsize error");

		trint = record[i]->information;
		for (int i = 0; i < 4; i++)
		{
			buf3[i] = (trint >> ((3 - i) * 8)) & b;
		}
		//if (!(ret = fwrite(buf3, 4, 1, fp)))
		fp.write(buf3, 4);
		if (fp.fail())
			perror("get information error");

		int m = record[i]->record_size - 12;
		if (m != 0)
		{
			fp.write(record[i]->name, m);
			if (fp.fail())
				perror("get name error");
			//fwrite(record[i]->name, m, 1, fp);
		}
	}
	fp.close();
}
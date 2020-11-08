#include"elemap.h"
//9.8:实现cout格式化、c++文件读取，并学习总结，nullptr无法用cout输出
void Record::readtext(const char* filename)
{
	Record &record = *this;
	record.clear();
	ifstream fp;
	//FILE* fp;
	//int err = fopen_s(&fp, filename, "rb");//打开文件
	fp.open(filename, ios::binary);
	if (!fp)
	{
		perror("open file error");
		return;
	}
	char buf1[2];//保存2字节信息
	char buf2[4];//保存4字节信息
	char buf3[100];//保存道路名字
	long long ret = 0;
	node* p=nullptr;
	//EOF是文本文件结束的标志。在文本文件中，数据是以字符的ASCⅡ代码值的形式存放，
	//ASCII代码值的范围是0～255，EOF的16进制代码为0xFF(十进制为-1)，因此可以用EOF作为文件结束标志。
	//但是如果文件格式为二进制文件，就不适合用EOF来判断文件到达结尾了，
	//因为有可能文件中也存在一个数据为0xFF，这样当读取到这个数据是，就无法判断是到达文件结尾
	//还是读取到的是文件的内容了。
	while (!fp.eof())
	{
		fp.read(buf1,2);
		ret = fp.gcount();
		//ret = fread(buf1, 2, 1, fp);//读“长度”
		unsigned short size = 0;
		//printf("%d\n", ret);
		if (ret == 2)
		{
			p = new node();//创建node
			p->name = nullptr;
			size = trans2(buf1);
			p->record_size = size;
			//size = (unsigned short)buf1;
			//size=25
			//cout << size << endl;
			size -= 2;
			fp.read(buf2, 4);
			//if (ret = fread(buf2, 4, 1, fp))//读道路编号
			if((ret=fp.gcount())==4)
			{
				if (ret != 4)//错误处理
				{
					delete(p);
					perror("get LinkId error");
					for (size_t j = 0; j < record.size(); j++)
						delete(record[j]);
					record.clear();
					exit(1);
				}
				size -= 4;
				unsigned int LinkId = trans4(buf2);
				//cout << "result:"<<LinkId<<endl;
				//unsigned int LinkId = (unsigned int)buf2[3] + (unsigned int)(buf2[2] << 8) + \
				//	(unsigned int)(buf2[1] << 16) + (unsigned int)(buf2[0] << 24);
				p->LinkID = LinkId;
				//cout << LinkId << endl;
			}
			//if (ret = fread(buf1, 2, 1, fp))//读道路名称长度
			fp.read(buf1, 2);
			if ((ret = fp.gcount()) == 2)
			{
				unsigned short namesize = 0;
				namesize = trans2(buf1);
				//namesize=(unsigned int)buf1[1] + (unsigned int)(buf1[0] << 8);
				p->roadsize = namesize;
				size -= 2;
			}
			else
			{
				delete(p);
				perror("get namesize error");
				for (size_t j = 0; j < record.size(); j++)
					delete(record[j]);
				record.clear();
				exit(1);
			}

			//if (ret = fread(buf2, 4, 1, fp))//读道路相关信息
			fp.read(buf2, 4);
			if ((ret = fp.gcount()) == 4)
			{
				unsigned int infor = trans4(buf2);
				p->information = infor;
				bool hasflag = buf2[3] & 0x80; 
				if (hasflag != 0) 
					p->hasflag = true;
				else 
					p->hasflag = false;
				
				short forknum = (buf2[3] & 0x70) >> 4; p->forkroad = forknum;
				short classnum = buf2[3] & 0x0f; p->classnum = classnum;
				size -= 4;
			}
			else
			{
				delete(p);
				perror("get road information error");
				for (size_t j = 0; j < record.size(); j++)
					delete(record[j]);
				record.clear();
				exit(1);
			}
			//if (ret = fread(buf3, size, 1, fp))//获取道路名称
			fp.read(buf3, size);
			if(size!=0)
			{
				if((ret = fp.gcount()) != size)
				{
					delete(p);
					cout << "rest size:" << size << endl;
					perror("get name error");
					//注意释放内存再退出
					for (size_t j = 0; j < record.size(); j++)
						delete(record[j]);
					record.clear();
					exit(1);
				}
				size = 0;
				size_t len = strlen(buf3);
				char* name = new char[len + 1];
				strcpy_s(name, strlen(buf3) + 1, buf3);
				//printf("len:%d\n", len);
				name[len] = '\0';
				p->name = name;
			}
#ifdef DE //调试
			show(p);
			//break;读一条
			delete p;
#else
			this->push_back(p);
#endif // DE
		}
		else
		{
			cout<<"The "<<this->size()+1;
			perror(" record get failed");
		}
	}
	cout << "get data success" << endl;
	fp.close();
}



//从文件读到mysql
void MysqlManager::readtexttomysql(const char* filename)
{
	char* str = new char[1024 * 1024];
	clock_t start = clock();
	sprintf_s(str, 150, "insert into roadinfo(LinkID,classnum,forkroad,hasflag,information,name,record_size,roadsize) values");
	ifstream fp;
	fp.open(filename, ios::binary);
	if (!fp)
	{
		perror("open file error");
		return;
	}
	char buf1[2];//保存2字节信息
	char buf2[4];//保存4字节信息
	char buf3[100];//保存道路名字

	node* p = new node();//创建node
	char* name = new char[100];
	p->name = name;
	long long ret = 0;
	//EOF是文本文件结束的标志。在文本文件中，数据是以字符的ASCⅡ代码值的形式存放，
	//ASCII代码值的范围是0～255，EOF的16进制代码为0xFF(十进制为-1)，因此可以用EOF作为文件结束标志。
	//但是如果文件格式为二进制文件，就不适合用EOF来判断文件到达结尾了，
	//因为有可能文件中也存在一个数据为0xFF，这样当读取到这个数据是，就无法判断是到达文件结尾
	//还是读取到的是文件的内容了。
	int i = 0;
	while (!fp.eof())
	{
		fp.read(buf1, 2);
		ret = fp.gcount();
		//ret = fread(buf1, 2, 1, fp);//读“长度”
		unsigned short size = 0;
		//printf("%d\n", ret);
		if (ret == 2)
		{
			size = trans2(buf1);
			p->record_size = size;
			//size = (unsigned short)buf1;
			//size=25
			//cout << size << endl;
			size -= 2;
			fp.read(buf2, 4);
			//if (ret = fread(buf2, 4, 1, fp))//读道路编号
			if ((ret = fp.gcount()) == 4)
			{
				if (ret != 4)//错误处理
				{
					delete(p);
					perror("get LinkId error");
					exit(1);
				}
				size -= 4;
				unsigned int LinkId = trans4(buf2);
				//cout << "result:"<<LinkId<<endl;
				//unsigned int LinkId = (unsigned int)buf2[3] + (unsigned int)(buf2[2] << 8) + \
				//	(unsigned int)(buf2[1] << 16) + (unsigned int)(buf2[0] << 24);
				p->LinkID = LinkId;
				//cout << LinkId << endl;
			}
			//if (ret = fread(buf1, 2, 1, fp))//读道路名称长度
			fp.read(buf1, 2);
			if ((ret = fp.gcount()) == 2)
			{
				unsigned short namesize = 0;
				namesize = trans2(buf1);
				//namesize=(unsigned int)buf1[1] + (unsigned int)(buf1[0] << 8);
				p->roadsize = namesize;
				size -= 2;
			}
			else
			{
				delete(p);
				perror("get namesize error");
				exit(1);
			}

			//if (ret = fread(buf2, 4, 1, fp))//读道路相关信息
			fp.read(buf2, 4);
			if ((ret = fp.gcount()) == 4)
			{
				unsigned int infor = trans4(buf2);
				p->information = infor;
				bool hasflag = buf2[3] & 0x80;
				if (hasflag != 0)
					p->hasflag = true;
				else
					p->hasflag = false;

				short forknum = (buf2[3] & 0x70) >> 4; p->forkroad = forknum;
				short classnum = buf2[3] & 0x0f; p->classnum = classnum;
				size -= 4;
			}
			else
			{
				delete(p);
				perror("get road information error");
				exit(1);
			}
			//if (ret = fread(buf3, size, 1, fp))//获取道路名称
			fp.read(buf3, size);
			if (size != 0)
			{
				if ((ret = fp.gcount()) != size)
				{
					delete(p);
					cout << "rest size:" << size << endl;
					perror("get name error");
					//注意释放内存再退出
					exit(1);
				}
				size = 0;
				size_t len = strlen(buf3);
				strcpy_s(name, strlen(buf3) + 1, buf3);
				//printf("len:%d\n", len);
				name[len] = '\0';
			}
			else
			{
				strcpy_s(name, 10, "null");
			}
			//格式化一条数据，并加入sql语句
			//sprintf_s(str, 200,"insert into roadinfo values( %d,%d,%d,%d,%d,%d,%d,%s);", record[i]->LinkID,record[i]->record_size
			//	,record[i]->roadsize,record[i]->hasflag,record[i]->forkroad,record[i]->classnum,record[i]->information,record[i]->name);

		// record_size Linkid    roadsize   hasflag  forkroad   classnum       roadname
			if (i > 0 && i % 1000 == 0)
			{
				sprintf_s(str, 1024 * 1024, "%s(%d,%d,%d,%d,%d,'%s',%d,%d);", str, p->LinkID, p->classnum
					, p->forkroad, p->hasflag, p->information,p->name, p->record_size, p->roadsize);
				if (m_mysql->execute(str) == false)//插入数据,已经有了
				{
					cout << "data already exists" << endl;
					return;
				}
				sprintf_s(str, 150, "insert into roadinfo(LinkID,classnum,forkroad,hasflag,information,name,record_size,roadsize) values");
			}
			else
				sprintf_s(str, 1024 * 1024, "%s(%d,%d,%d,%d,%d,'%s',%d,%d),", str, p->LinkID, p->classnum
					, p->forkroad, p->hasflag, p->information, p->name, p->record_size, p->roadsize);
			i++;
		}
		else
		{
			cout << "The " << i + 1;
			perror(" record get failed");
		}
	}
	if (strlen(str)>101)
	{
		int k=strlen(str);
		str[k-1] = ';';
		if (m_mysql->execute(str) == false)//插入数据,已经有了
		{
			cout << "insert error" << endl;
			return;
		}
	}
	cout << "get data success" << endl;
	
	clock_t end = clock();
	cout << "cost " << ((double)end - (double)start) / CLOCKS_PER_SEC << " sec" << endl;
	fp.close();
	delete[] name;
	delete p;
	delete[] str;
}
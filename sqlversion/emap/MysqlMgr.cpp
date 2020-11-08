#include"elemap.h"
//��Щ�������඼��Ҫ���棬���������ѡ��ѡ��
void MysqlManager::mysqlsort()
{
	clock_t start=0,end=0;
	double tm = 0;
	char c;
	int flag = 0;
	QueryResult* res=NULL;
	while (1)
	{
		cout << "				select sort by what?   " << endl;
		cout << "				1.LinkID              |" << endl;
		cout << "				2.LinkID(desc)        |" << endl;
		cout << "				3.forkroad            |" << endl;
		cout << "				4.classnum            |" << endl;
		cout << "				5.name                |" << endl;
		cout << "				0.quit" << endl;
		cin >> c;
		char b;
		while ((b = getchar()) != '\n' && b != EOF);//�����뻺����
		if (c >= '0' && c <= '9')
		{
			c -= '0';
			start = clock();
			switch (c)
			{
			case 1:
			{
				start = clock();
				res = m_mysql->query("select * from roadinfo order by LinkID;");
				break;
			}
			case 2:
			{
				start = clock();
				res = m_mysql->query("select * from roadinfo order by LinkID desc;");
				break;
			}
			case 3:
			{
				start = clock();
				res = m_mysql->query("select * from roadinfo order by forkroad;");
				break;
			}
			case 4:
			{
				start = clock();
				res = m_mysql->query("select * from roadinfo order by classnum;");
				break;
			}
			case 5:
			{
				start = clock();
				res = m_mysql->query("select * from roadinfo order by name;");
				break;
			}
			case 0:
			{
				flag = 1;
				break;
			}
			default:
			{
				flag = 1;
				break;
			}
			}
		}
		if (flag == 1)
			break;
		end = clock();
		writefile(res, "./sort_record");
		tm = 1000.0 * ((double)end - (double)start) / CLOCKS_PER_SEC;
		//showall(record);
		cout << "sort success" << endl;
		cout << "sort cost " << tm << " ms" << endl;
	}
}

void MysqlManager::mysqlsearch()
{
	//��sql����ѯ�����ֶβ�ѯ
	clock_t start=0, end=0;
	double tm;
	char b;
	char* value = new char[200];
	char* query = new char[250];
	QueryResult* res=NULL;
	MYSQL_RES* result = NULL;
	int flag = 0;
	while (1)
	{
		strcpy(query,"select * from roadinfo where ");
		char c;
		cout << "						search result in ./search_record" << endl;
		cout << "						1.search by LinkID" << endl;
		cout << "						2.search by classnum" << endl;
		cout << "						3.search by forknum" << endl;
		cout << "						4.search by roadname" << endl;
		cout << "						5.search by sql language" << endl;
		cout << "						6.search by roadname(less memory)" << endl;
		cout << "						0.quit" << endl;
		cin >> c;
		while ((b = getchar()) != '\n' && b != EOF);
		int fg = 0;
		if (c <= '9' && c >= '0')
		{
			c = c - '0';
			start = clock();
			switch (c)
			{
			case 1://˳������LinkID
			{
				cout << "please input you search LinkId" << endl;
				//scanf_s("%u", &value);
				cin >> value;
				fg = 0;
				while ((b = getchar()) != '\n' && b != EOF)//�����뻺����
				{
					if (b <= '0' || b >= '9')
						fg = 1;
				}
				if (fg == 1)
				{
					cin.clear();////�޸�������,cin.fail=0
					printf("please input correct num\n");
					break;
				}

				sprintf(query,"%s LinkId=%s;", query, value);
				res=m_mysql->query(query);//��ȡ���������ʾ�����
				break;
			}
			case 2:
			{
				cout << "please input you search classnum" << endl;
				//scanf_s("%u", &value);
				cin >> value;
				fg = 0;
				while ((b = getchar()) != '\n' && b != EOF)//�����뻺����
				{
					if (b <= '0' || b >= '9')
						fg = 1;
				}
				if (fg == 1)
				{
					cin.clear();////�޸�������,cin.fail=0
					printf("please input correct num\n");
					break;
				}
				sprintf(query,"%s classnum=%s;", query, value);
				res=m_mysql->query(query);//��ȡ���������ʾ�����
				break;
			}
			case 3:
			{
				cout << "please input you search forknum" << endl;
				//scanf_s("%u", &value);
				cin >> value;
				fg = 0;
				while ((b = getchar()) != '\n' && b != EOF)//�����뻺����
				{}//cin.clear();
				sprintf(query,"%s frokroad=%s;", query, value);
				res=m_mysql->query(query);//��ȡ���������ʾ�����
				break;
			}
			case 4:
			{
				cout << "please input you search roadname" << endl;
				//scanf_s("%u", &value);
				cin >> value;
				fg = 0;
				while ((b = getchar()) != '\n' && b != EOF){}//�����뻺����
				sprintf(query,"%s name='%s';", query, value);
				res=m_mysql->query(query);//��ȡ���������ʾ�����
				break;
			}
			case 5://�����ո��ֹͣ��ô����getline()
			{
				cout << "please input you search sql language" << endl;
				//scanf_s("%u", &value);
				cin.getline(value,200); //>> value;//getline()
				fg = 0;
				//while ((b = getchar()) != '\n' && b != EOF){}//�����뻺����
				res=m_mysql->query(value);//��ȡ���������ʾ�����
				break;
			}
			case 6:
			{
				cout << "please input you search roadname" << endl;
				//scanf_s("%u", &value);
				cin >> value;
				fg = 0;
				while ((b = getchar()) != '\n' && b != EOF) {}//�����뻺����
				sprintf(query,"%s name='%s';", query, value);
				result = m_mysql->query(query, 1);//��ȡ���������ʾ�����	
				break;
			}
			case 0:
				flag = 1;
				break;
			default:
				flag = 1;
				break;
			}
		if (flag == 1)
		{
			delete[] value;
			delete[] query;
			break;
		}
		if (c >= 1 && c <= 5)
		{
			end = clock();
			writefile(res, "./search_record");
			tm = 1000.0 * ((double)end - (double)start) / CLOCKS_PER_SEC;
			cout << "search cost " << tm << " ms" << endl;
		}
		else
		{
			end = clock();
			writefile(result, "./search_record",1);
			tm = 1000.0 * ((double)end - (double)start) / CLOCKS_PER_SEC;
			cout << "search cost " << tm << " ms" << endl;
		}
		}
	}
}

//����writefile
void MysqlManager::mysqlupdate(const char* filename)
{	
	//��mysql�ж�ȡ���ݲ������char�ļ�
		ofstream fp;
		fp.open(filename, ios::out | ios::trunc);
		//FILE* fp;
		//errno_t err = fopen_s(&fp, pathname, "w+");
		QueryResult *res = m_mysql->query("select * from roadinfo");
		writefile(res,"./new_record");
		fp.close();
		cout << filename << " file update success" << endl;
}

//mysql api��ȡ2�ַ�ʽ��һ��һ��ȫ����һ��һ��һ������Ӧһ��һ���������������

bool MysqlManager::mysqlbupdate(const char* filename)
{
	ofstream fp;
	//errno_t err = fopen_s(&fp, pathname, "wb");
	fp.open(filename, ios::binary | ios::trunc);
	int ret = 0;
	unsigned int trint = 0;
	unsigned short trshort = 0;
	char buf2[2];
	char buf3[4];
	unsigned short a = 0x00ff;
	unsigned int b = 0x000000ff;
	node p;
	QueryResult* pResult = m_mysql->query("select * from roadinfo");
	if (pResult == NULL)
		return false;
	//FILE* fp;
	//errno_t err = fopen_s(&fp, pathname, "w+");
	while (true)
	{
		Field* pRow = pResult->fetch();
		if (pRow == NULL)
			return false;
		p.LinkID = pRow[0].getInt32();
		p.classnum = pRow[1].getInt16();
		p.forkroad = pRow[2].getInt16();
		p.hasflag = pRow[3].getBool();
		p.information = pRow[4].getInt32();
		string temp = pRow[5].getString();
		p.record_size = pRow[6].getInt16();
		p.roadsize = pRow[7].getInt16();
		
		trshort = p.record_size;
		for (int i = 0; i < 2; i++)
		{
			buf2[i] = (trshort >> ((1 - i) * 8)) & a;
		}
		//���뷴�� int->buf

		//if (!(ret = fwrite(buf2, 2, 1, fp)))
		fp.write(buf2, 2);
		if (fp.fail())
			perror("get record_size error");

		trint = p.LinkID;
		for (int i = 0; i < 4; i++)
		{
			buf3[i] = (trint >> ((3 - i) * 8)) & b;
		}
		//if (!(ret = fwrite(buf3, 4, 1, fp)))
		fp.write(buf3, 4);
		if (fp.fail())
			perror("get LinkID error");

		trshort = p.roadsize;
		for (int i = 0; i < 2; i++)
		{
			buf2[i] = (trshort >> ((1 - i) * 8)) & a;
		}
		//if (!(ret = fwrite(buf2, 2, 1, fp)))
		fp.write(buf2, 2);
		if (fp.fail())
			perror("get roadsize error");

		trint = p.information;
		for (int i = 0; i < 4; i++)
		{
			buf3[i] = (trint >> ((3 - i) * 8)) & b;
		}
		//if (!(ret = fwrite(buf3, 4, 1, fp)))
		fp.write(buf3, 4);
		if (fp.fail())
			perror("get information error");

		int m = p.record_size - 12;
		if (m != 0)
		{
			fp.write(temp.c_str(), m);
			if (fp.fail())
				perror("get name error");
			//fwrite(record[i]->name, m, 1, fp);
		}
		if (!pResult->nextRow())
			break;
	}
	pResult->endQuery();
	delete pResult;

	fp.close();
	return true;
}

void MysqlManager::mysqlinsert()
{
	char* str = new char[200];
	char* value = new char[150];
	char* name = new char[40];
	int flag = 0;
	strcpy(str,"insert into roadinfo values(");
	clock_t start=0, end=0;
	double tm;
	char b;
	char c;
	while (1)
	{
		strcpy(str, "insert into roadinfo values(");
		cout << "						1.insert by information " << endl;
		cout << "						2.insert by sql language" << endl;
		cout << "						0.quit" << endl;
		cin >> c;
		while ((b = getchar()) != '\n' && b != EOF);
		int fg = 0;
		if (c <= '9' && c >= '0')
		{
			c = c - '0';
			start = clock();
			switch (c)
			{
			case 1:
			{
				cout << "please input your information:" << endl;
				cout << "LinkID classnum forkroad hasflag name" << endl;
				cout << "Usage: 0 0 0 0 hello" << endl;
				int LinkID=0, forkroad=0, hasflag=0,classnum=0;
				cin >> LinkID >>classnum>> forkroad >> hasflag >> name;
				hasflag = hasflag ? 1 : 0;
				//information record_size roadsize
				int roadsize = strlen(name);
				int record_size = 12 + roadsize+2;//2������� 00 00
				int information = ((hasflag & 0x01) << 7) + ((forkroad & 0x07) << 4) + (classnum & 0x0f);
				sprintf(str,"%s%d,%d,%d,%d,%d,'%s',%d,%d);",str,LinkID,classnum,forkroad,hasflag, information,name, record_size,roadsize);
				int i = 0;
				fg = 0;
				m_mysql->execute(str);//��ȡ���������ʾ�����
				break;
			}
			case 2:
			{
				cout << "please input your sql language" << endl;
				cin.getline(value, 200);
				fg = 0;
				//����sql���
				m_mysql->execute(value);//��ȡ���������ʾ�����
				break;
			}
			case 0:
			{
				flag = 1;
				break;
			}

			}
		}
		if (flag == 1)
			break;
		end = clock();
		tm = 1000.0 * ((double)end - (double)start) / CLOCKS_PER_SEC;
		cout << "insert cost " << tm << " ms" << endl;
	}
	delete[] str;
	delete[] value;
}
void MysqlManager::mysqldelete()
{
	char* str = new char[200];
	char* value = new char[150];
	int flag = 0;
	strcpy(str,"delete from roadinfo where LinkID=");
	clock_t start=0, end=0;
	double tm;
	char b;
	char c;
	while (1)
	{
		strcpy(str,"delete from roadinfo where LinkID=");
		cout << "						1.delete by LinkID " << endl;
		cout << "						2.delete by sql language" << endl;
		cout << "						0.quit" << endl;
		cin >> c;
		while ((b = getchar()) != '\n' && b != EOF);
		int fg = 0;
		if (c <= '9' && c >= '0')
		{
			c = c - '0';
			start = clock();
			switch (c)
			{
			case 1:
			{
				cout << "please input LinkID to delete:" << endl;
				cin.getline(value, 200);
				fg = 0;
				sprintf(str,"%s%s;", str, value);
				m_mysql->execute(str);//��ȡ���������ʾ�����
				break;
			}
			case 2:
			{
				cout << "please input your sql language" << endl;
				cin.getline(value, 200);
				fg = 0;
				m_mysql->execute(value);//��ȡ���������ʾ�����
				break;
			}
			case 0:
			{
				flag = 1;
				break;
			}
			default:
			{
				flag = 1;
				break;
			}
			}
		if (flag == 1)
			break;
		end = clock();
		tm = 1000.0 * ((double)end - (double)start) / CLOCKS_PER_SEC;
		cout << "delete cost " << tm << " ms" << endl;
		}	
	}
	delete[] str;
	delete[] value;
}

void MysqlManager::mysqlmodify()
{
	char* str = new char[200];
	char* value = new char[150];
	char* value2 = new char[150];
	int flag = 0;
	strcpy(str,"update roadinfo set ");
	clock_t start = 0, end = 0;
	double tm;
	char b;
	char c;
	while (1)
	{
		strcpy(str,"update roadinfo set ");
		cout << "						1.update by LinkID " << endl;
		cout << "						2.update by sql language" << endl;
		cout << "						0.quit" << endl;
		cin >> c;
		while ((b = getchar()) != '\n' && b != EOF);
		int fg = 0;
		if (c <= '9' && c >= '0')
		{
			c = c - '0';
			start = clock();
			switch (c)
			{
			case 1:
			{
				cout << "please input LinkID to update:" << endl;
				cin.getline(value, 200);
				cout << "please input set what to update" << endl;
				cout << "Usage: frokroad=3,name='hello'" << endl;
				cin.getline(value2, 200);
				fg = 0;
				sprintf(str,"%s %s where LinkID=%s;", str,value2, value);
				m_mysql->execute(str);//��ȡ���������ʾ�����
				break;
			}
			case 2:
			{
				cout << "please input your sql language" << endl;
				cin.getline(value, 200);
				fg = 0;
				m_mysql->execute(value);//��ȡ���������ʾ�����
				break;
			}
			case 0:
			{
				flag = 1;
				break;
			}
			default:
			{
				flag = 1;
				break;
			}
			}
			if (flag == 1)
				break;
			end = clock();
			tm = 1000.0 * ((double)end - (double)start) / CLOCKS_PER_SEC;
			cout << "modify cost " << tm << " ms" << endl;
		}
	}
	delete[] str;
	delete[] value;
	delete[] value2;
}

bool MysqlManager::mysqlshowall()
{
	node p;
	QueryResult *pResult = m_mysql->query("select * from roadinfo;");
	if (pResult == NULL)
		return false;
	//FILE* fp;
	//errno_t err = fopen_s(&fp, pathname, "w+");
	cout << "   Linkid   record_size  roadsize   hasflag  forkroad   classnum       roadname" << endl;
	while (true)
	{
		Field* pRow = pResult->fetch();
		if (pRow == NULL)
			return false;
		
		p.LinkID = pRow[0].getInt32();
		p.classnum = pRow[1].getInt16();
		p.forkroad = pRow[2].getInt16();
		p.hasflag = pRow[3].getBool();
		p.information = pRow[4].getInt32();
		string temp = pRow[5].getString();
		p.record_size = pRow[6].getInt16();
		p.roadsize = pRow[7].getInt16();
		cout << setw(10) << p.LinkID << setw(10) << p.record_size << setw(10) << p.roadsize << setw(10)\
			<< p.hasflag << setw(10) << p.forkroad << setw(10) << p.classnum<< setw(20) << temp << endl;
		if (!pResult->nextRow())
			break;
	}
	pResult->endQuery();
	delete pResult;
	return true;
}
bool MysqlManager::mysqlread(const char* filename)
{
	char* str = new char[1024 * 1024];
	//��Ҫ��ѯ��Ҫ���½�������
	if (!m_mysql->execute("delete from roadinfo;"))
		return false;
	sprintf(str,"insert into roadinfo(LinkID,classnum,forkroad,hasflag,information,name,record_size,roadsize) values");
	//(LinkID,classnum,forkroad,hasflag,information,name,record_size,roadsize)
	clock_t start = clock();
	ifstream fp;
	//FILE* fp;
	//int err = fopen_s(&fp, filename, "rb");//���ļ�
	fp.open(filename, ios::binary);
	if (!fp)
	{
		perror("open file error");
		return false;
	}
	char buf1[2];//����2�ֽ���Ϣ
	char buf2[4];//����4�ֽ���Ϣ
	char buf3[100];//�����·����

	node* p = new node();//����node
	char* name = new char[100];
	p->name = name;
	long long ret = 0;
	//EOF���ı��ļ������ı�־�����ı��ļ��У����������ַ���ASC�����ֵ����ʽ��ţ�
	//ASCII����ֵ�ķ�Χ��0��255��EOF��16���ƴ���Ϊ0xFF(ʮ����Ϊ-1)����˿�����EOF��Ϊ�ļ�������־��
	//��������ļ���ʽΪ�������ļ����Ͳ��ʺ���EOF���ж��ļ������β�ˣ�
	//��Ϊ�п����ļ���Ҳ����һ������Ϊ0xFF����������ȡ����������ǣ����޷��ж��ǵ����ļ���β
	//���Ƕ�ȡ�������ļ��������ˡ�
	int i = 0;
	while (!fp.eof())
	{
		fp.read(buf1, 2);
		ret = fp.gcount();
		//ret = fread(buf1, 2, 1, fp);//�������ȡ�
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
			//if (ret = fread(buf2, 4, 1, fp))//����·���
			if ((ret = fp.gcount()) == 4)
			{
				if (ret != 4)//������
				{
					delete(p);
					perror("get LinkId error");
					return false;
				}
				size -= 4;
				unsigned int LinkId = trans4(buf2);
				//cout << "result:"<<LinkId<<endl;
				//unsigned int LinkId = (unsigned int)buf2[3] + (unsigned int)(buf2[2] << 8) + \
				//	(unsigned int)(buf2[1] << 16) + (unsigned int)(buf2[0] << 24);
				p->LinkID = LinkId;
				//cout << LinkId << endl;
			}
			//if (ret = fread(buf1, 2, 1, fp))//����·���Ƴ���
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
				return false;
			}

			//if (ret = fread(buf2, 4, 1, fp))//����·�����Ϣ
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
				return false;
			}
			//if (ret = fread(buf3, size, 1, fp))//��ȡ��·����
			fp.read(buf3, size);
			if (size != 0)
			{
				if ((ret = fp.gcount()) != size)
				{
					delete(p);
					cout << "rest size:" << size << endl;
					perror("get name error");
					//ע���ͷ��ڴ����˳�
					return false;
				}
				size = 0;
				size_t len = strlen(buf3);
				strcpy(name,buf3);
				//printf("len:%d\n", len);
				name[len] = '\0';
			}
			else
			{
				strcpy(name,"null");
			}
			//��ʽ��һ�����ݣ�������sql���
			//sprintf(str,"insert into roadinfo values( %d,%d,%d,%d,%d,%d,%d,%s);", record[i]->LinkID,record[i]->record_size
			//	,record[i]->roadsize,record[i]->hasflag,record[i]->forkroad,record[i]->classnum,record[i]->information,record[i]->name);

		// record_size Linkid    roadsize   hasflag  forkroad   classnum       roadname
			if (i > 0 && i % 1000 == 0)
			{
				sprintf(str,"%s(%d,%d,%d,%d,%d,'%s',%d,%d);", str, p->LinkID, p->classnum
					, p->forkroad, p->hasflag, p->information, p->name, p->record_size, p->roadsize);
				if (m_mysql->execute(str) == false)//��������,�Ѿ�����
				{
					cout << "data already exists" << endl;
					return false;
				}
				sprintf(str,"insert into roadinfo(LinkID,classnum,forkroad,hasflag,information,name,record_size,roadsize) values");
			}
			else
				sprintf(str,"%s(%d,%d,%d,%d,%d,'%s',%d,%d),", str, p->LinkID, p->classnum
					, p->forkroad, p->hasflag, p->information, p->name, p->record_size, p->roadsize);
			i++;
		}
		else
		{
			cout << "The " << i + 1;
			perror(" record get failed");
		}
	}
	if (strlen(str) > 101)
	{
		int k = strlen(str);
		str[k - 1] = ';';
		if (m_mysql->execute(str) == false)//��������,�Ѿ�����
		{
			cout << "insert error" << endl;
			return false;
		}
	}
	cout << "get data success" << endl;

	clock_t end = clock();
	cout << "cost " << ((double)end - (double)start) / CLOCKS_PER_SEC << " sec" << endl;
	fp.close();
	delete[] name;
	delete p;
	//mysql.~CMysql();
	return true;
}


bool MysqlManager::writefile(QueryResult* pResult,const char* pathname)
{
	ofstream fp;
	fp.open(pathname, ios::out | ios::trunc);
	if (pResult == NULL)
		return false;
	//FILE* fp;
	//errno_t err = fopen_s(&fp, pathname, "w+");
	fp << "    Linkid  record_size  roadsize    hasflag   forkroad   classnum         roadname" << endl;
	while (true)
	{
		Field* pRow = pResult->fetch();
		if (pRow == NULL)
			return false;
		node p;
		p.LinkID = pRow[0].getInt32();
		p.classnum = pRow[1].getInt16();
		p.forkroad = pRow[2].getInt16();
		p.hasflag = pRow[3].getBool();
		p.information = pRow[4].getInt32();
		string temp=pRow[5].getString();
		p.record_size = pRow[6].getInt16();
		p.roadsize = pRow[7].getInt16();

		//��pд���ļ�
		fp << setw(10) << p.LinkID << setw(10) << p.record_size << setw(10) << p.roadsize\
			<< setw(10) << p.hasflag << setw(10) << p.forkroad << setw(10) << p.classnum
			<< setw(25) << temp << endl;
		if(!pResult->nextRow())
			break;
	}
	pResult->endQuery();
	delete pResult;
	fp.close();
	cout << pathname << " file update success" << endl;
	return true;
}

bool MysqlManager::writefile(MYSQL_RES* result, const char* pathname,int k)
{
	(void)k;
	ofstream fp;
	fp.open(pathname, ios::out | ios::trunc);
	if (result == NULL)
		return false;
	//FILE* fp;
	//errno_t err = fopen_s(&fp, pathname, "w+");
	fp << "    Linkid  record_size  roadsize    hasflag   forkroad   classnum         roadname" << endl;
	while (true)
	{
		MYSQL_ROW pRow = mysql_fetch_row(result);
		if (pRow == NULL)
			return false;
		node p;
		p.LinkID = atoi(pRow[0]);
		p.classnum = atoi(pRow[1]);
		p.forkroad = atoi(pRow[2]);
		p.hasflag = atoi(pRow[3]);
		p.information = atoi(pRow[4]);
		char* temp = pRow[5];
		p.record_size = atoi(pRow[6]);
		p.roadsize = atoi(pRow[7]);

		//��pд���ļ�
		fp << setw(10) << p.LinkID << setw(10) << p.record_size << setw(10) << p.roadsize\
			<< setw(10) << p.hasflag << setw(10) << p.forkroad << setw(10) << p.classnum
			<< setw(25) << temp << endl;
	}
	mysql_free_result(result);
	fp.close();
	cout << pathname << " file update success" << endl;
	return true;
}

void MysqlManager::readRecord(Record& record)
{
	record.clear();
	QueryResult* pResult = m_mysql->query("select * from roadinfo;");
	if (pResult == NULL)
		return;
	//FILE* fp;
	//errno_t err = fopen_s(&fp, pathname, "w+");
	int i = 0;
	while (true)
	{
		node* p = new node();
		Field* pRow = pResult->fetch();
		if (pRow == NULL)
			return;
		p->LinkID = pRow[0].getInt32();
		p->classnum = pRow[1].getInt16();
		p->forkroad = pRow[2].getInt16();
		p->hasflag = pRow[3].getBool();
		p->information = pRow[4].getInt32();

		//������˳�ʱ�����ڴ�ռ��
		size_t len = strlen(pRow[5].getString().c_str());
		char* name = new char[len + 1];
		strcpy(name,pRow[5].getString().c_str());
		//printf("len:%d\n", len);
		name[len] = '\0';

		p->name = name;
		p->record_size = pRow[6].getInt16();
		p->roadsize = pRow[7].getInt16();
		record.push_back(p);
		i++;
		if (!pResult->nextRow())
			break;
	}
	pResult->endQuery();
	delete pResult;
	cout << "Record update success" << endl;
}
#include"elemap.h"
//9.8:ʵ��cout��ʽ����c++�ļ���ȡ����ѧϰ�ܽᣬnullptr�޷���cout���
void Record::readtext(const char* filename)
{
	Record &record = *this;
	record.clear();
	ifstream fp;
	//FILE* fp;
	//int err = fopen_s(&fp, filename, "rb");//���ļ�
	fp.open(filename, ios::binary);
	if (!fp)
	{
		perror("open file error");
		return;
	}
	char buf1[2];//����2�ֽ���Ϣ
	char buf2[4];//����4�ֽ���Ϣ
	char buf3[100];//�����·����
	long long ret = 0;
	node* p=nullptr;
	//EOF���ı��ļ������ı�־�����ı��ļ��У����������ַ���ASC�����ֵ����ʽ��ţ�
	//ASCII����ֵ�ķ�Χ��0��255��EOF��16���ƴ���Ϊ0xFF(ʮ����Ϊ-1)����˿�����EOF��Ϊ�ļ�������־��
	//��������ļ���ʽΪ�������ļ����Ͳ��ʺ���EOF���ж��ļ������β�ˣ�
	//��Ϊ�п����ļ���Ҳ����һ������Ϊ0xFF����������ȡ����������ǣ����޷��ж��ǵ����ļ���β
	//���Ƕ�ȡ�������ļ��������ˡ�
	while (!fp.eof())
	{
		fp.read(buf1,2);
		ret = fp.gcount();
		//ret = fread(buf1, 2, 1, fp);//�������ȡ�
		unsigned short size = 0;
		//printf("%d\n", ret);
		if (ret == 2)
		{
			p = new node();//����node
			p->name = nullptr;
			size = trans2(buf1);
			p->record_size = size;
			//size = (unsigned short)buf1;
			//size=25
			//cout << size << endl;
			size -= 2;
			fp.read(buf2, 4);
			//if (ret = fread(buf2, 4, 1, fp))//����·���
			if((ret=fp.gcount())==4)
			{
				if (ret != 4)//������
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
				for (size_t j = 0; j < record.size(); j++)
					delete(record[j]);
				record.clear();
				exit(1);
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
				for (size_t j = 0; j < record.size(); j++)
					delete(record[j]);
				record.clear();
				exit(1);
			}
			//if (ret = fread(buf3, size, 1, fp))//��ȡ��·����
			fp.read(buf3, size);
			if(size!=0)
			{
				if((ret = fp.gcount()) != size)
				{
					delete(p);
					cout << "rest size:" << size << endl;
					perror("get name error");
					//ע���ͷ��ڴ����˳�
					for (size_t j = 0; j < record.size(); j++)
						delete(record[j]);
					record.clear();
					exit(1);
				}
				size = 0;
				size_t len = strlen(buf3);
				char* name = new char[len + 1];
				strcpy(name, buf3);
				//printf("len:%d\n", len);
				name[len] = '\0';
				p->name = name;
			}
#ifdef DE //����
			show(p);
			//break;��һ��
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



//���ļ�����mysql
void MysqlManager::readtexttomysql(const char* filename)
{
	char* str = new char[1024 * 1024];
	clock_t start = clock();
	sprintf(str,"insert into roadinfo(LinkID,classnum,forkroad,hasflag,information,name,record_size,roadsize) values");
	ifstream fp;
	fp.open(filename, ios::binary);
	if (!fp)
	{
		perror("open file error");
		return;
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
				exit(1);
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
				exit(1);
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
					exit(1);
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
					, p->forkroad, p->hasflag, p->information,p->name, p->record_size, p->roadsize);
				if (m_mysql->execute(str) == false)//��������,�Ѿ�����
				{
					cout << "data already exists" << endl;
					return;
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
	if (strlen(str)>101)
	{
		int k=strlen(str);
		str[k-1] = ';';
		if (m_mysql->execute(str) == false)//��������,�Ѿ�����
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
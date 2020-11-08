#include"elemap.h"
#include"Mysqlpool.h"
int hassorted=0;
//9.8 cin�建������ʹ��cin.clear(),cin.ignore(),��cin.ignore()���������û������������������ʹ��
//��cin.clear��getchar���,��Ϊ��֪���������е��ַ��Ƿ��ǲ��Ϸ��ġ�
void Window::startwindow(Record& record)//sort����
{
	while (1)
	{
		cout << "-------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "			|			���ӵ�ͼ����ϵͳ                         |" << endl;
		cout << "			|			��ͨ��   mysql��                         |" << endl;
		cout << "			|			   1       2                             |" << endl;
		cout << "			|			   ����0�˳�                             |" << endl;
		cout << "-------------------------------------------------------------------------------------------------------------------" << endl;
		char b, c;
		cin >> b;
		while ((c = getchar()) != '\n' && c != EOF);//������뻺����
		if (b - '1' == 0)
			normalwindow(record);
		else if (b - '2' == 0)
			mysqlwindow(record);
		else if (b - '0' == 0)
			break;
	}
	return;
}

void Window::normalwindow(Record &record)
{
	//�����ڲ˵�
	int hasread = 0;
	char choise = 0;
	int flag = 0;
	while (1)
	{
		choise = -1;
		char c;
		cout << endl;
		cout << "-------------------------------------------------------------------------------------------------------------------"<<endl;
		cout << "			|			���ӵ�ͼ����ϵͳ                         |" << endl;
		cout << "			|			1.����������ļ�(./GTBL.dat)             |" << endl;
		cout << "			|			2.����                                   |" << endl;
		cout << "			|			3.����                                   |" << endl;
		cout << "			|			4.����(./new record)                     |" << endl;
		cout << "			|			5.�������ļ�����(./brecord)              |" << endl;
		cout << "			|			6.�������ļ���ȡ(./brecord)              |" << endl;
		cout << "			|			7.��ʾȫ��                               |" << endl;
		cout << "			|			8.����mysql                              |" << endl;
		cout << "			|			0.�˳�                                   |" << endl;
		cout << "-------------------------------------------------------------------------------------------------------------------"<<endl;
		cout<<""<<endl;
		cin >> choise;
		//scanf_s("%c", &choise, 1);
		//fflush(stdin);
		while((c = getchar()) != '\n' && c != EOF);//������뻺����
		//change()
		if (choise >= '0' && choise <= '9')
		{
			choise = choise - '0';
			switch (choise)
			{
			case 1://��ȡ����
			{
				record.readtext("./GTBL.dat");
				hasread = 1;
				//showall(record);
				cout << "get " << (record).size() << " record " << endl;
				break;
			}
			case 2://����
			{
				if (hasread != 1)
				{
					cout<<"data has not been read"<<endl;
				}
				else
					sortwindow(record);
				break;
			}
			case 3://����
			{
				if (hasread != 1)
					cout<<"data has not been read"<<endl;
				else
					searchwindow(record);
				break;
			}
			case 4://����
			{
				if (hasread != 1)
					cout<<"data has not been read"<<endl;
				else
					record.cupdate(record,"new_record");
				break;
			}
			case 5://�����Ƹ���
				record.bupdate(record,"brecord");
				cout << "binary data update in ./brecord" << endl;
				break;
			case 6://���������¶�ȡ
				record.readtext("./brecord");
				break;
			case 7:
				if (hasread == 1)
					record.showall();
				else
					cout << "record has not been read" << endl;
				break;
			case 8:
				//����mysql;
				mysql(record);
				break;
			case 0:
				flag = 1;
				break;
			default:
				cout<<"please input 0-8 to choice"<<endl;
				break;
			}
			if (flag == 1)
				break;
		}
		else
		{
			cout<<"please input 0-8 to choice"<<endl;
		}
	}
}

void Window::sortwindow(Record& record)//sort����
{
	clock_t start, end;
	double tm = 0;
	char c;
	while (1)
	{
		cout<<"				sort only by LinkId"<<endl;
		cout<<"				1.bubblesort          |"<<endl;
		cout<<"				2.quicksort           |"<<endl;
		cout<<"				3.insertsort          |"<<endl;
		cout<<"				4.heapsort            |"<<endl;
		cout<<"				5.stlsort             |"<<endl;
		cout<<"				0.quit"<<endl;
		cin >> c;
		char b;
		while ((b = getchar()) != '\n' && b != EOF);//�����뻺����
		int flag = 0;
		if (c >= '0' && c <= '9')
		{
			c -= '0';
			switch (c)
			{
			case 1:
				start = clock();
				record.bubblesort();//ð��
				end = clock();
				tm = 1000.0 * ((double)end - (double)start) / CLOCKS_PER_SEC;
				hassorted = 1;
				//showall(record);
				cout<<"sort success"<<endl;
				cout<<"bubblesort cost "<<tm<<" ms"<<endl;
				break;
			case 2:
				start = clock();
				record.quicksort(0, record.size() - 1);//����
				end = clock();
				tm = 1000.0 * ((double)end - (double)start) / CLOCKS_PER_SEC;
				hassorted = 1;
				//showall(record);
				cout<<"sort success"<<endl;
				cout<<"quicksort cost " << tm << "  ms" << endl;
				break;
			case 3:
				start = clock();
				record.insertsort();//��������
				end = clock();
				tm = 1000.0 * ((double)end - (double)start) / CLOCKS_PER_SEC;
				//showall(record);
				cout<<"sort success"<<endl;
				cout<<"insertsort cost " << tm << " ms" << endl;
				hassorted = 1;
				break;
			case 4:
				start = clock();
				record.heapsort();
				end = clock();
				tm = 1000.0 * ((double)end - (double)start) / CLOCKS_PER_SEC;
				//showall(record);
				cout<<"sort success"<<endl;
				cout<<"heapsort cost " << tm << " ms" << endl;
				hassorted = 1;
				break;
			case 5:
				start = clock();
				record.stlsort();
				end = clock();
				tm = 1000.0 * ((double)end - (double)start) / CLOCKS_PER_SEC;
				//showall(record);
				cout<<"sort success"<<endl;
				cout<<"stlsort cost " << tm << " ms" << endl;
				hassorted = 1;
				break;
			case 6:
				start = clock();
				record.merge_sort(0, record.size() - 1);
				end = clock();
				tm = 1000.0 * ((double)end - (double)start) / CLOCKS_PER_SEC;
				//showall(record);
				cout << "sort success" << endl;
				cout << "mergesort cost " << tm << " ms" << endl;
				hassorted = 1;
				break;
			case 7:
				start = clock();
				record.selectsort();
				end = clock();
				tm = 1000.0 * ((double)end - (double)start) / CLOCKS_PER_SEC;
				//showall(record);
				cout << "sort success" << endl;
				cout << "selectsort cost " << tm << " ms" << endl;
				hassorted = 1;
				break;
			case 0:
				flag = 1;
				break;
			default:
				cout<<"please input 0-7"<<endl;
				break;
			}
		}
		else
		{
			cout<<"please input 0-5"<<endl;
		}
		if (flag == 1)
			break;
	}
}
void Window::searchwindow(Record& record)//search����
{
	clock_t start, end;
	double tm;
	char b;
	unsigned short val;
	Record res;
	node* resnode=nullptr;
	int num = 0;
	while (1)
	{
		char c;
		unsigned int value;
		cout<<"						1.search by LinkID"<<endl;
		cout<<"						2.search by Classnum"<<endl;
		cout<<"						3.search by forknum"<<endl;
		cout<<"						4.search by roadname"<<endl;
		cout<<"						5.search by LinkID using binary search"<<endl;
		cout<<"						0.quit"<<endl;
		cin >> c;
		while ((b = getchar()) != '\n' && b != EOF);
		int flag = 0;
		int fg = 0;
		if (c <= '9' && c >= '0')
		{
			c = c - '0';
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
				resnode = nullptr;
				start = clock();
				record.search(&resnode, value);
				end = clock();
				if (resnode != nullptr)
				{
					cout << "   record_size Linkid    roadsize   hasflag  forkroad   classnum         roadname" << endl;
					resnode->show();
				}
				else
					cout << "can't find or input error" << endl;
				tm = 1000.0 * ((double)end - (double)start) / CLOCKS_PER_SEC;
				cout << "normal search cost " << tm << " ms" << endl;
				break;
			}
			case 2://˳������classnum
				cout<<"please input you search Classnum"<<endl;
				cin >> val;
				fg = 0;
				while ((b = getchar()) != '\n' && b != EOF)//�����뻺����
				{
					if (c <= '0' || c >= '9')
						fg = 1;
				}
				if (fg == 1)
				{
					cin.clear();////�޸�������,cin.fail=0
					printf("please input correct num\n");
					break;
				}
				record.searchcn(res, val);
				if (res.size() < CNLIMIT)//30
				{
					if (res.size() == 0)
					{
						cout << "can't find or input error" << endl;
						break;
					}
					cout << "   record_size Linkid    roadsize   hasflag  forkroad   classnum         roadname" << endl;
					for (size_t j = 0; j < res.size(); j++)
						res[j]->show();
					cout << "the result num=" << res.size() << " (<" << CNLIMIT << ")" << endl;
				}
				else
				{
					record.cupdate(res, "classnum_record");
					cout << "the result num=" << res.size() << " (>=" << CNLIMIT << "%d),store in ./classnum_record" << endl;
				}
				break;
			case 3://˳������forknum
				cout<<"please input you search forknum"<<endl;
				//scanf_s("%hu", &val);
				cin >> val;
				fg = 0;
				while ((c = getchar()) != '\n' && c != EOF)//�����뻺����
				{
					if (c <= '0' || c >= '9')
						fg = 1;
				}
				if (fg == 1)
				{
					cin.clear();////�޸�������,cin.fail=0
					printf("please input correct num\n");
					break;
				}
				record.searchfn(res, val);
				if (res.size() < FNLIMIT)//30
				{
					if (res.size() == 0)
					{
						cout << "can't find or input error" << endl;
						break;
					}
					cout << "   record_size Linkid    roadsize   hasflag  forkroad   classnum           roadname" << endl;
					for (size_t j = 0; j < res.size(); j++)
						res[j]->show();
					cout << "the result num=" << res.size() << " (<" << FNLIMIT << ")" << endl;
				}
				else
				{
					res.cupdate(res, "./forknum_record");
					cout << "the result num=" << res.size() << " (>=" << FNLIMIT << "),store in ./forknum_record" << endl;
				}
				break;
			case 4://˳������roadname
			{
				char* name = new char[100];
				cout << "please input you search roadname" << endl;
				//scanf_s("%s", name, 51);
				cin >> name;
				while ((b = getchar()) != '\n' && b != EOF)//�����뻺����
					cout << "   record_size Linkid    roadsize   hasflag  forkroad   classnum         roadname" << endl;
				record.search(res, name);
				if (res.size() < NAMELIMIT)//30
				{
					if (res.size() == 0)
					{
						cout << "can't find or input error" << endl;
						break;
					}
					cout << "   record_size Linkid    roadsize   hasflag  forkroad   classnum           roadname" << endl;
					for (size_t j = 0; j < res.size(); j++)
						res[j]->show();
					cout << "the result num=" << res.size() << " (<" << NAMELIMIT << ")" << endl;
				}
				else
				{
					res.cupdate(res, "./roadname_record");
					cout << "the result num=" << res.size() << " (>=" << NAMELIMIT << "),store in ./roadname_record" << endl;
				}
				delete[]name;
				break;
			}
			case 5://��������Linknum
			{
				if (hassorted != 1)
				{
					cout << "the data hasn't been sorted,please sort the data" << endl;
					break;
				}
				cout << "please input you search LinkId" << endl;
				cin >> value;
				fg = 0;
				while ((b = getchar()) != '\n' && b != EOF)//�����뻺����
					if (b <= '0' || b >= '9')
						fg = 1;
				if (fg == 1)
				{
					cin.clear();////�޸�������,cin.fail=0
					printf("please input correct num\n");
					break;
				}
				resnode = nullptr;
				start = clock();
				record.binarysearch(&resnode, (unsigned int)0, record.size() - 1, value);
				end = clock();
				if (resnode == nullptr)
					cout << "can't find or input error" << endl;
				else
				{
					cout << "   record_size Linkid    roadsize   hasflag  forkroad   classnum         roadname" << endl;
					resnode->show();
				}
				tm = 1000.0 * ((double)end - (double)start) / CLOCKS_PER_SEC;
				cout << "binary search cost " << tm << " ms" << endl;
				break;
			}
			case 0://�˳�
				flag = 1;
				break;
			default:
				break;
			}
		}
		else
		{
			cout<<"please input 0-5"<<endl;
			//fflush(stdin);
		}
		if (flag == 1)
			break;
	}
}
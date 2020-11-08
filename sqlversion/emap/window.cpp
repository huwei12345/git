#include"elemap.h"
#include"Mysqlpool.h"
int hassorted=0;
//9.8 cin清缓存区，使用cin.clear(),cin.ignore(),但cin.ignore()如果缓存区没东西，会阻塞，所以使用
//了cin.clear和getchar组合,因为想知道缓冲区中的字符是否是不合法的。
void Window::startwindow(Record& record)//sort窗口
{
	while (1)
	{
		cout << "-------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "			|			电子地图管理系统                         |" << endl;
		cout << "			|			普通版   mysql版                         |" << endl;
		cout << "			|			   1       2                             |" << endl;
		cout << "			|			   输入0退出                             |" << endl;
		cout << "-------------------------------------------------------------------------------------------------------------------" << endl;
		char b, c;
		cin >> b;
		while ((c = getchar()) != '\n' && c != EOF);//清空输入缓冲区
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
	//主窗口菜单
	int hasread = 0;
	char choise = 0;
	int flag = 0;
	while (1)
	{
		choise = -1;
		char c;
		cout << endl;
		cout << "-------------------------------------------------------------------------------------------------------------------"<<endl;
		cout << "			|			电子地图管理系统                         |" << endl;
		cout << "			|			1.读入二进制文件(./GTBL.dat)             |" << endl;
		cout << "			|			2.排序                                   |" << endl;
		cout << "			|			3.检索                                   |" << endl;
		cout << "			|			4.更新(./new record)                     |" << endl;
		cout << "			|			5.二进制文件更新(./brecord)              |" << endl;
		cout << "			|			6.二进制文件读取(./brecord)              |" << endl;
		cout << "			|			7.显示全部                               |" << endl;
		cout << "			|			8.加入mysql                              |" << endl;
		cout << "			|			0.退出                                   |" << endl;
		cout << "-------------------------------------------------------------------------------------------------------------------"<<endl;
		cout<<""<<endl;
		cin >> choise;
		//scanf_s("%c", &choise, 1);
		//fflush(stdin);
		while((c = getchar()) != '\n' && c != EOF);//清空输入缓冲区
		//change()
		if (choise >= '0' && choise <= '9')
		{
			choise = choise - '0';
			switch (choise)
			{
			case 1://读取数据
			{
				record.readtext("./GTBL.dat");
				hasread = 1;
				//showall(record);
				cout << "get " << (record).size() << " record " << endl;
				break;
			}
			case 2://排序
			{
				if (hasread != 1)
				{
					cout<<"data has not been read"<<endl;
				}
				else
					sortwindow(record);
				break;
			}
			case 3://搜索
			{
				if (hasread != 1)
					cout<<"data has not been read"<<endl;
				else
					searchwindow(record);
				break;
			}
			case 4://更新
			{
				if (hasread != 1)
					cout<<"data has not been read"<<endl;
				else
					record.cupdate(record,"new_record");
				break;
			}
			case 5://二进制更新
				record.bupdate(record,"brecord");
				cout << "binary data update in ./brecord" << endl;
				break;
			case 6://二进制重新读取
				record.readtext("./brecord");
				break;
			case 7:
				if (hasread == 1)
					record.showall();
				else
					cout << "record has not been read" << endl;
				break;
			case 8:
				//加入mysql;
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

void Window::sortwindow(Record& record)//sort窗口
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
		while ((b = getchar()) != '\n' && b != EOF);//清输入缓冲区
		int flag = 0;
		if (c >= '0' && c <= '9')
		{
			c -= '0';
			switch (c)
			{
			case 1:
				start = clock();
				record.bubblesort();//冒泡
				end = clock();
				tm = 1000.0 * ((double)end - (double)start) / CLOCKS_PER_SEC;
				hassorted = 1;
				//showall(record);
				cout<<"sort success"<<endl;
				cout<<"bubblesort cost "<<tm<<" ms"<<endl;
				break;
			case 2:
				start = clock();
				record.quicksort(0, record.size() - 1);//快排
				end = clock();
				tm = 1000.0 * ((double)end - (double)start) / CLOCKS_PER_SEC;
				hassorted = 1;
				//showall(record);
				cout<<"sort success"<<endl;
				cout<<"quicksort cost " << tm << "  ms" << endl;
				break;
			case 3:
				start = clock();
				record.insertsort();//插入排序
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
void Window::searchwindow(Record& record)//search窗口
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
			case 1://顺序搜索LinkID
			{
				cout << "please input you search LinkId" << endl;
				//scanf_s("%u", &value);
				cin >> value;
				fg = 0;
				while ((b = getchar()) != '\n' && b != EOF)//清输入缓冲区
				{
					if (b <= '0' || b >= '9')
						fg = 1;
				}
				if (fg == 1)
				{
					cin.clear();////修复输入流,cin.fail=0
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
			case 2://顺序搜索classnum
				cout<<"please input you search Classnum"<<endl;
				cin >> val;
				fg = 0;
				while ((b = getchar()) != '\n' && b != EOF)//清输入缓冲区
				{
					if (c <= '0' || c >= '9')
						fg = 1;
				}
				if (fg == 1)
				{
					cin.clear();////修复输入流,cin.fail=0
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
			case 3://顺序搜索forknum
				cout<<"please input you search forknum"<<endl;
				//scanf_s("%hu", &val);
				cin >> val;
				fg = 0;
				while ((c = getchar()) != '\n' && c != EOF)//清输入缓冲区
				{
					if (c <= '0' || c >= '9')
						fg = 1;
				}
				if (fg == 1)
				{
					cin.clear();////修复输入流,cin.fail=0
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
			case 4://顺序搜索roadname
			{
				char* name = new char[100];
				cout << "please input you search roadname" << endl;
				//scanf_s("%s", name, 51);
				cin >> name;
				while ((b = getchar()) != '\n' && b != EOF)//清输入缓冲区
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
			case 5://二分搜索Linknum
			{
				if (hassorted != 1)
				{
					cout << "the data hasn't been sorted,please sort the data" << endl;
					break;
				}
				cout << "please input you search LinkId" << endl;
				cin >> value;
				fg = 0;
				while ((b = getchar()) != '\n' && b != EOF)//清输入缓冲区
					if (b <= '0' || b >= '9')
						fg = 1;
				if (fg == 1)
				{
					cin.clear();////修复输入流,cin.fail=0
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
			case 0://退出
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
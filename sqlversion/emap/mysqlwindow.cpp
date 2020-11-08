#include"elemap.h"
void Window::mysqlwindow(Record& record)//sort窗口
{
	string host("localhost");
	string user("root");
	string pwd("123456");
	string dbName("roadinfo");
	//库中的类，用于库表不存在，创建库表。
	CMysqlManager cmgr;//mgr中包含CMysql,CMysql不可见，此类仅用于一开始初始化数据库，初始化后会关闭连接
	if (cmgr.init(host.c_str(), user.c_str(), pwd.c_str(), dbName.c_str()) == false)//建表
		return;
	
	MysqlManager* mgr = new MysqlManager();
	mgr->getCMysql()->init(host, user, pwd, dbName);
	char choise = 0;
	int flag = 0;
	while (1)
	{
		choise = -1;
		char c;
		cout << endl;
		cout << "-------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "			|			电子地图管理系统(mysql版)                |" << endl;
		cout << "			|			1.读入二进制文件(./GTBL.dat)             |" << endl;
		cout << "			|			2.排序(./sort_record)                    |" << endl;
		cout << "			|			3.检索(./search_record)                  |" << endl;
		cout << "			|			4.更新字符文件(./new record)             |" << endl;
		cout << "			|			5.备份二进制文件(./brecord)              |" << endl;
		cout << "			|			6.插入数据                               |" << endl;
		cout << "			|			7.删除数据                               |" << endl;
		cout << "			|			8.显示全部                               |" << endl;
		cout << "			|			9.修改数据                               |" << endl;
		cout << "			|			m.从文件恢复(./brecord)                  |" << endl;
		cout << "			|			n.从数据库读到Record中                   |" << endl;
		cout << "			|			0.退出                                   |" << endl;
		cout << "-------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "" << endl;
		cin >> choise;
		//scanf_s("%c", &choise, 1);
		//fflush(stdin);
		while ((c = getchar()) != '\n' && c != EOF);//清空输入缓冲区
		//change()
		if (choise >= '0' && choise <= '9')
		{
			choise = choise - '0';
			switch (choise)
			{
			case 1://读取数据
			{
				mgr->readtexttomysql("./GTBL.dat");
				//showall(record);
				break;
			}
			case 2://排序
			{
				mgr->mysqlsort();//界面
				break;
			}
			case 3://搜索，多字段mysql查询，显示，多的写入文件
			{
				mgr->mysqlsearch();
				break;
			}
			case 4://更新，写入文件
			{
				mgr->mysqlupdate("new_record");
				break;
			}
			case 5://二进制更新，写入文件
				mgr->mysqlbupdate("brecord");
				cout << "binary data update in ./brecord" << endl;
				break;
			case 6://插入数据
				mgr->mysqlinsert();
				break;
			case 7://删除
				mgr->mysqldelete();
				break;
			case 8://cmd显示
				mgr->mysqlshowall();
				break;
			case 9:
				mgr->mysqlmodify();//恢复
				break;
			case 0:
				flag = 1;
				break;
			default:
				cout << "please input [0-9]/m/n to choice" << endl;
				break;
			}
			if (flag == 1)
				break;
		}
		else if (choise == 'm')
		{
			mgr->mysqlread("./brecord");//恢复
		}
		else if (choise == 'n')
		{
			mgr->readRecord(record);
		}
		else
		{
			cout << "please input 0-9/m/n to choice" << endl;
		}
	}
	delete mgr;
}

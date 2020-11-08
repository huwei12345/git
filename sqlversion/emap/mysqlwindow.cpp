#include"elemap.h"
void Window::mysqlwindow(Record& record)//sort����
{
	string host("localhost");
	string user("root");
	string pwd("123456");
	string dbName("roadinfo");
	//���е��࣬���ڿ�����ڣ��������
	CMysqlManager cmgr;//mgr�а���CMysql,CMysql���ɼ������������һ��ʼ��ʼ�����ݿ⣬��ʼ�����ر�����
	if (cmgr.init(host.c_str(), user.c_str(), pwd.c_str(), dbName.c_str()) == false)//����
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
		cout << "			|			���ӵ�ͼ����ϵͳ(mysql��)                |" << endl;
		cout << "			|			1.����������ļ�(./GTBL.dat)             |" << endl;
		cout << "			|			2.����(./sort_record)                    |" << endl;
		cout << "			|			3.����(./search_record)                  |" << endl;
		cout << "			|			4.�����ַ��ļ�(./new record)             |" << endl;
		cout << "			|			5.���ݶ������ļ�(./brecord)              |" << endl;
		cout << "			|			6.��������                               |" << endl;
		cout << "			|			7.ɾ������                               |" << endl;
		cout << "			|			8.��ʾȫ��                               |" << endl;
		cout << "			|			9.�޸�����                               |" << endl;
		cout << "			|			m.���ļ��ָ�(./brecord)                  |" << endl;
		cout << "			|			n.�����ݿ����Record��                   |" << endl;
		cout << "			|			0.�˳�                                   |" << endl;
		cout << "-------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "" << endl;
		cin >> choise;
		//scanf_s("%c", &choise, 1);
		//fflush(stdin);
		while ((c = getchar()) != '\n' && c != EOF);//������뻺����
		//change()
		if (choise >= '0' && choise <= '9')
		{
			choise = choise - '0';
			switch (choise)
			{
			case 1://��ȡ����
			{
				mgr->readtexttomysql("./GTBL.dat");
				//showall(record);
				break;
			}
			case 2://����
			{
				mgr->mysqlsort();//����
				break;
			}
			case 3://���������ֶ�mysql��ѯ����ʾ�����д���ļ�
			{
				mgr->mysqlsearch();
				break;
			}
			case 4://���£�д���ļ�
			{
				mgr->mysqlupdate("new_record");
				break;
			}
			case 5://�����Ƹ��£�д���ļ�
				mgr->mysqlbupdate("brecord");
				cout << "binary data update in ./brecord" << endl;
				break;
			case 6://��������
				mgr->mysqlinsert();
				break;
			case 7://ɾ��
				mgr->mysqldelete();
				break;
			case 8://cmd��ʾ
				mgr->mysqlshowall();
				break;
			case 9:
				mgr->mysqlmodify();//�ָ�
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
			mgr->mysqlread("./brecord");//�ָ�
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

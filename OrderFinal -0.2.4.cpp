#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <string>
#include <conio.h>
using namespace std;
#include "Person.h"
#include "User.h" 
#include "Page.h"
#include "Waiter.h"
#include "Customer.h" 
#include "Restaurant.h"
#include "Menus.h"    



#define SIZE 100//����û�����
int scount = 0;//�������浱ǰ��ע���û���
int admin = 0;//�жϹ���Ա��¼adminȫ�ֱ��� 





User user[SIZE];





int Customer::total=0;
int Menus::sums=0;


//��ҳ
int Page::homePage(int flag){
    if(!flag)    //system("mode con lines=13 cols=54");
    cout<<"*****************************************************\n";
    cout<<"*                       v0.2.4                      *\n";
    cout<<"*             ��ӭ�����Ƶ��˹���ϵͳ              *\n";
    cout<<"*                  ��ѡ��������                   *\n";
    cout<<"*                                                   *\n";
    cout<<"*                                                   *\n";
    cout<<"*  1.����Ա     2.�˿�     3.ϵͳ����Ա    4.�˳�   *\n";
    cout<<"*                                                   *\n";
    cout<<"*                                                   *\n";
    cout<<"*****************************************************\n";
    int ch;
    while(cin>>ch){
        switch (ch){
        case 1:
        	system("cls");
        	cout<<"����Ա��¼��\n";
            admin = 1; 
            return 0;
            break;
        case 2:
        	system("cls");
            cout<<"�˿͵�¼��\n";
            admin = 0;
            return 0;
            break;
        case 3:
            system("cls");
            cout<<"ϵͳ����Ա��¼��\n";
            admin = 2;
			this->login();
            return 1;
            break;
        case 4:
			exit(0); 
        default:
            cout<<"��ѡ����ȷ��ѡ��!\n";
            this->homePage(1);
        }
    }
}


//����Ա��¼
void Page::login(){
    string username,password;
    cout<<"�������û���:";
    cin>>username;
    cout<<"����������:";
    cin>>password;
    if(username==this->username && password==this->password){
        //system("mode con lines=30 cols=120");
        cout<<"��¼�ɹ���\n";
    }else{
        cout<<"�������!������ѡ����Ĳ���!\n";
        this->homePage(1);
    }
}

//����
void User::save()
{
	ofstream ofile;
	ofile.open("user.txt", ios::out);

	for (int i = 0; i < scount; i++)
	{
		ofile << user[i].phone << endl;
		ofile << user[i].password << endl;
	}
	ofile.close();
}

//��ȡ
void User::read()
{
	ifstream ifile;
	ifile.open("user.txt", ios::in);

	scount = 0;

	if (!ifile.is_open())
	{
		//cout << "�ļ���ʧ�ܣ�" << endl;
		return;
	}

	for (int i = 0; !ifile.eof(); i++)
	{
		ifile >> user[i].phone;
		ifile >> user[i].password;
		scount++;
	}
	scount--;
	ifile.close();
}

//ע��
void User::Registers()
{
	us.read();//��ȡ�Ѵ����û�����
	string ph;//�绰
	string pw1;//����1
	string pw2;//����2
	for (int i = scount; i < SIZE; i++)
	{
	here:
		cout << "\t\t��ϵͳ��ʾ���˿��������ֻ��ţ�Ա�������빤�ţ�";
		cin >> ph;
		//�ж���������û���Ϣ�Ƿ��Ѵ��ڣ�����Ѵ������������룩
		for (int i = 0; i < scount; i++)
		{
			if (ph == user[i].phone)
			{
				cout << "\t\t��ϵͳ��ʾ���û��Ѵ��ڣ�" << endl;
				goto here;
			}
		}
		user[i].phone = ph;

		int chose = -1;
		cout << endl;
		cout << "\t\t��������������������������������������������������������������������������������\n";
		cout << "\t\t��       1.��ʾ����     2.��������      ��\t\n";
		cout << "\t\t��������������������������������������������������������������������������������\n";
		cout << "\t\t��ϵͳ��ʾ�����������ѡ��";
		cin >> chose;
		if (chose > 2 || chose < -1)
		{
			cout << "\t\t��ϵͳ��ʾ�������ʽ�������������룺";
			cin >> chose;
		}

		string pword;
		char ch, passwords0[20];
		int x = 0;
		string pword1;
		char ch1, passwords1[20];
		int x1 = 0;
		switch (chose)
		{
		case 1:
			cout << "\t\t��ϵͳ��ʾ�����������룺";
			cin >> pword;
			user[i].password = pword;
			cout << "\t\t��ϵͳ��ʾ�����ٴ����룺";
			cin >> pword1;
			if (pword1 != user[i].password)
			{
				cout << "\t\t��ϵͳ��ʾ�����벻һ�£�" << endl;
				goto here;
			}
			else
			{
				scount++;//��ע���û���1
				cout << "\t\t��ϵͳ��ʾ��ע��ɹ���" << endl;
				us.save();//�����û�����
			}
			break;
		case 2:
			cout << "\t\t��ϵͳ��ʾ�����������룺";
			while ((ch = _getch()) != '\r' && x <= 20)
			{
				if (ch == '\b')
				{
					if (x > 0)
					{
						x--;
						cout << "\b \b";//����֧���˸��ʵ��
					}
					else
						putchar(7);
				}
				else
				{
					passwords0[x++] = ch;
					printf("*");
				}
			}
			passwords0[x] = '\0';
			cout << endl;
			user[i].password = passwords0;

			cout << "\t\t��ϵͳ��ʾ�����ٴ����룺";
			while ((ch1 = _getch()) != '\r' && x1 <= 20)
			{
				if (ch1 == '\b')
				{
					if (x1 > 0)
					{
						x1--;
						cout << "\b \b";//����֧���˸��ʵ��
					}
					else
						putchar(7);
				}
				else
				{
					passwords1[x1++] = ch1;
					printf("*");
				}
			}
			passwords1[x1] = '\0';
			cout << endl;
			//�Ƚ���������������Ƿ�ͳһ�������ͳһ���������룩
			if (passwords1 != user[i].password)
			{
				cout << "\t\t��ϵͳ��ʾ�����벻һ�£�" << endl;
				goto here;
			}
			else
			{
				scount++;//��ע���û���1
				cout << "\t\t��ϵͳ��ʾ��ע��ɹ���" << endl;
				us.save();//�����û�����
			}
			break;
		}
		char choice;
		cout << "\t\t��ϵͳ��ʾ���Ƿ����ע��(Y/N)�� :";
		while (1)
		{
			cin >> choice;
			if (choice == 'y' || choice == 'Y' || choice == 'n' || choice == 'N')
				break;
			else
				cout << "\t\t��ϵͳ��ʾ�������ʽ�������������룺 ";
		}
		if (choice == 'n' || choice == 'N')
		{
			break;
		}
	}
}

//��¼
void User::Login()
{
	us.read();//��ȡ�Ѵ����û�����
	string ph;//�绰
	string pw;//����
	int time = 0;//ͳ�ƱȽϴ���
here:
	cout << "\t\t��ϵͳ��ʾ���˿��������ֻ��ţ�Ա�������빤�ţ�";
	cin >> ph;
	int chose = -1;
	cout << endl;
	cout << "\t\t��������������������������������������������������������������������������������\n";
	cout << "\t\t��       1.��ʾ����     2.��������      ��\t\n";
	cout << "\t\t��������������������������������������������������������������������������������\n";
	cout << "\t\t��ϵͳ��ʾ�����������ѡ��";
	cin >> chose;
	if (chose > 2 || chose < -1)
	{
		cout << "\t\t��ϵͳ��ʾ�������ʽ�������������룺";
		cin >> chose;
	}

	string pword;
	char ch, passwords0[20];
	int x = 0;
	switch (chose)
	{
	case 1:
		cout << "\t\t��ϵͳ��ʾ�����������룺";
		cin >> pword;
		for (int i = 0; i < scount; i++)
		{
			if (ph == user[i].phone && pword == user[i].password)
			{
				time++;
				//cout << "\t\t\t��ϵͳ��ʾ����¼�ɹ���" << endl;
			}
		}
		if (time == 0)
		{
			cout << "\t\t��ϵͳ��ʾ���ֻ��š����Ż��������" << endl;
			goto here;
		}
		break;
	case 2:
		cout << "\t\t��ϵͳ��ʾ�����������룺";
		while ((ch = _getch()) != '\r' && x <= 20)
		{
			if (ch == '\b')
			{
				if (x > 0)
				{
					x--;
					cout << "\b \b";//����֧���˸��ʵ��
				}
				else
					putchar(7);
			}
			else
			{
				passwords0[x++] = ch;
				printf("*");
			}
		}
		passwords0[x] = '\0';
		cout << endl;
		//���αȽ��Ѵ�����Ϣ���Ƚ��Ƿ�ƥ�䣨�粻ƥ������ʾ����
		for (int i = 0; i < scount; i++)
		{
			if (ph == user[i].phone && passwords0 == user[i].password)
			{
				time++;
				cout << "\t\t��ϵͳ��ʾ����¼�ɹ���" << endl;
			}
		}
		if (time == 0)
		{
			cout << "\t\t��ϵͳ��ʾ���ֻ��š����Ż��������" << endl;
			goto here;
		}
		break;
	}
}

//****ȫ�ֺ���***//
void Menu()
{
    cout<<endl;cout<<endl;//cout<<endl;cout<<endl;cout<<endl;cout<<endl;
    cout<<setw(41)<<"�Ƶ��˹���ϵͳ"<<endl;
    cout<<endl;
    cout<<setw(50)<<"1**************��Ϣ��ѯ*************"<<endl;
        cout<<endl;
    cout<<setw(50)<<"2**************��Ϣ¼��*************"<<endl;
        cout<<endl;
    cout<<setw(50)<<"3**************�˿͵��*************"<<endl;
    cout<<endl;
    cout<<setw(50)<<"4**************�˿�����*************"<<endl;
    cout<<endl;
    cout<<setw(50)<<"5**************������ʷ*************"<<endl;
    cout<<endl;
    cout<<setw(50)<<"0**************�ǳ��˺�*************"<<endl;
    cout<<endl;
}

void Search()
{
   system("cls");
    cout<<endl;cout<<endl;cout<<endl;cout<<endl;cout<<endl;

   cout<<"         1   ��ѯ������Ϣ"<<endl;
       cout<<endl;

   cout<<"         2   ��ѯ����Ա��Ϣ"<<endl;
       cout<<endl;

   cout<<"         3   ��ѯ�˵�"<<endl;
       cout<<endl;
       cout<<"         4    �鿴����"<<endl;
       cout<<endl;

   cout<<"         5   ������һ���˵�"<<endl;
       cout<<endl;

   cout<<" "<<"��ѡ��"<<endl;
   int choice;
   Restaurant restaurant;
   Waiter waiter;
   Menus dish;
   cin>>choice;
   switch(choice)
   {
       case 1: restaurant.Search();break;
       case 2: waiter.Search();break;
       case 3: dish.Search();break;
       case 4: restaurant.evaluate();break;
       case 5: Menu();break;
   }
}
void Set()
{
    system("cls");
    cout<<endl<<endl<<endl<<endl;
    cout<<"              1 ��Ӳ�Ʒ"<<endl<<endl;
    cout<<"              2 ��ӷ���Ա"<<endl<<endl;
    cout<<"              3 ��Ӳ�����Ϣ"<<endl<<endl;
    cout<<"              4 ������һ���˵�"<<endl<<endl;
    cout<<"         ��ѡ��"<<endl;
    Menus dish;
    int choice;
    Waiter waiter;
    Restaurant restaurant;
    cin>>choice;
   switch(choice)
   {
       case 1:dish.Set();break;
       case 2:if(admin == 2)
	   			 waiter.Set();
			   else
			   	 cout << "Ȩ�޲��㣡"; 
			   break;
       case 3:if(admin == 2)
	   			 restaurant.Set();
			   else
			   	 cout << "Ȩ�޲��㣡"; 
			   break;
       case 4:Menu();break;
   }
}
void orderdish()
{
    Customer customer;
    customer.order();
    //system("cls");
    Menu();
}
void customer_evaluate()
{
    char evaluate[200];
    cin.clear();
    cin.get();
    cout<<"�����ۺ����֣�"<<endl;
    cin.getline(evaluate,50);
    
    ofstream out("evaluate.txt",ios::app);
    out<<evaluate<<endl;
    out.close();
    Menu();
}

class shiwu
{
public:
	string mingzi;
	int price;
	shiwu(){}
	shiwu(string n,int p):mingzi(n),price(p){}
};
shiwu zhucan[3]={shiwu("�󺺱�",13),shiwu("���ⷹ",13),shiwu("�����",11)};
shiwu fushi[3]={shiwu("��������",9),shiwu("�������׻�",9),shiwu("������",6)};
shiwu drink[3]={shiwu("�ɿڿ���",5),shiwu("��������",6),shiwu("��ţ��",6)};
class Taocan
{
public:
	string mingzi;
	shiwu tc[3];
	int price;
	Taocan(){}
	Taocan(string n,shiwu a,shiwu b,shiwu c)
	{
		mingzi=n;
		tc[0]=a;
		tc[1]=b;
		tc[2]=c;
		price=a.price+b.price+c.price-10;
	}
};
Taocan taocan[3]={Taocan("���ȼ����ײ�",zhucan[0],fushi[0],drink[0]),Taocan("���㼦�׻��ײ�",zhucan[1],fushi[1],drink[0]),Taocan("����������ײ�",zhucan[2],fushi[2],drink[0])};
shiwu myshiwu[13];
int mymoney;
int mynum=0;
void write()
{
	ofstream f("list.txt");
	int i;
	f << "�����嵥\n";
	for(i=0;i<mynum;i++)    
		f<<i+1<<"��"<<myshiwu[i].mingzi<<"	�۸�"<<myshiwu[i].price<<endl;
	f<<"�ܼ۸�"<<to_string(mymoney)<<endl;
	f<<endl<<endl;
    f.close();
	system("list.txt");
}

void history()//д��������ʷ������ 
{
	ofstream out("history.txt",ios::app);
	int i;
	out << "������ʷ\n";
	for(i=0;i<mynum;i++)
		out<<i+1<<"��"<<myshiwu[i].mingzi<<"	�۸�"<<myshiwu[i].price<<endl;
	out<<"�ܼ۸�"<<to_string(mymoney)<<endl;
	out<<endl<<endl;
    out.close();
	system("history.txt");
}

void xuanzhucan()
{
	void Menu1();
	void Diancan();
	system("cls");
	cout<<"1��"<<zhucan[0].mingzi<<"	�۸�"<<zhucan[0].price<<endl;
	cout<<"2��"<<zhucan[1].mingzi<<"	�۸�"<<zhucan[1].price<<endl;
	cout<<"3��"<<zhucan[2].mingzi<<"	�۸�"<<zhucan[2].price<<endl;
	cout<<"4������"<<endl;
	char c;
	c=getch();
	switch(c)
	{
		case '1':	myshiwu[mynum]=zhucan[0];mymoney+=zhucan[0].price;mynum++;		break;
		case '2':	myshiwu[mynum]=zhucan[1];mymoney+=zhucan[1].price;mynum++;		break;
		case '3':	myshiwu[mynum]=zhucan[2];mymoney+=zhucan[2].price;mynum++;		break;
		case '4':	Diancan();		break;
		default: 
			printf("\n���İ������󣬰����������ѡ��\n");
			getch();
			xuanzhucan();
	}	 
	printf("\n��ͳɹ����밴�����������ͻ��߷��أ�\n");
	getch();
	if(mynum>10)
	{
		cout<<"�����ε���Ѿ��ﵽ���ޣ������Ҫ�������������ͣ�"<<endl;
		printf("\n�����������˵���\n");
		getch();
		Menu1();
	}
	else
		xuanzhucan();
}
void xuanfushi()
{
	void Menu1();
	void Diancan();
	system("cls");
	cout<<"1��"<<fushi[0].mingzi<<"	�۸�"<<fushi[0].price<<endl;
	cout<<"2��"<<fushi[1].mingzi<<"	�۸�"<<fushi[1].price<<endl;
	cout<<"3��"<<fushi[2].mingzi<<"	�۸�"<<fushi[2].price<<endl;
	cout<<"4������"<<endl;
	char c;
	c=getch();
	switch(c)
	{
		case '1':	myshiwu[mynum]=fushi[0];mymoney+=fushi[0].price;mynum++;		break;
		case '2':	myshiwu[mynum]=fushi[1];mymoney+=fushi[1].price;mynum++;		break;
		case '3':	myshiwu[mynum]=fushi[2];mymoney+=fushi[2].price;mynum++;		break;
		case '4':	Diancan();		break;
		default: 
			printf("\n���İ������󣬰����������ѡ��\n");
			getch();
			xuanfushi();
	}	 
	printf("\n��ͳɹ����밴�����������ͻ��߷��أ�\n");
	getch();
	if(mynum>10)
	{
		cout<<"�����ε���Ѿ��ﵽ���ޣ������Ҫ�������������ͣ�"<<endl;
		printf("\n�����������˵���\n");
		getch();
		Menu1();
	}
	else xuanfushi();
}
void xuandrink()
{
	void Menu1();
	void Diancan();
	system("cls");
	cout<<"1��"<<drink[0].mingzi<<"	�۸�"<<drink[0].price<<endl;
	cout<<"2��"<<drink[1].mingzi<<"	�۸�"<<drink[1].price<<endl;
	cout<<"3��"<<drink[2].mingzi<<"	�۸�"<<drink[2].price<<endl;
	cout<<"4������"<<endl;
	char c;
	c=getch();
	switch(c)
	{
		case '1':	myshiwu[mynum]=drink[0];mymoney+=drink[0].price;mynum++;		break;
		case '2':	myshiwu[mynum]=drink[1];mymoney+=drink[1].price;mynum++;		break;
		case '3':	myshiwu[mynum]=drink[2];mymoney+=drink[2].price;mynum++;		break;
		case '4':	Diancan();		break;
		default: 
			printf("\n���İ������󣬰����������ѡ��\n");
			getch();
			xuandrink();
	}	 
	printf("\n��ͳɹ����밴�����������ͻ��߷��أ�\n");
	getch();
	if(mynum>10)
	{
		cout<<"�����ε���Ѿ��ﵽ���ޣ������Ҫ�������������ͣ�"<<endl;
		printf("\n�����������˵���\n");
		getch();
		Menu1();
	}
	else xuandrink();
}
void Taocan()
{
	void Menu1();
	void Diancan();
	system("cls");
	cout<<"1��"<<taocan[0].mingzi<<"	�۸�"<<taocan[0].price<<endl;
	cout<<"2��"<<taocan[1].mingzi<<"	�۸�"<<taocan[1].price<<endl;
	cout<<"3��"<<taocan[2].mingzi<<"	�۸�"<<taocan[2].price<<endl;
	cout<<"4������"<<endl;
	char c;
	c=getch();
	switch(c)
	{
		case '1':	mymoney+=taocan[0].price;myshiwu[mynum]=taocan[0].tc[0];mynum++;myshiwu[mynum]=taocan[0].tc[1];mynum++;myshiwu[mynum]=taocan[0].tc[2];mynum++;		break;
		case '2':	mymoney+=taocan[1].price;myshiwu[mynum]=taocan[1].tc[0];mynum++;myshiwu[mynum]=taocan[1].tc[1];mynum++;myshiwu[mynum]=taocan[1].tc[2];mynum++;		break;
		case '3':	mymoney+=taocan[2].price;myshiwu[mynum]=taocan[2].tc[0];mynum++;myshiwu[mynum]=taocan[2].tc[1];mynum++;myshiwu[mynum]=taocan[2].tc[2];mynum++;		break;
		case '4':	Diancan();		break;
		default: 
			printf("\n���İ������󣬰����������ѡ��\n");
			getch();
			Taocan();
	}	 
	printf("\n��ͳɹ����밴�����������ͻ��߷��أ�\n");
	getch();
	if(mynum>10)
	{
		cout<<"�����ε���Ѿ��ﵽ���ޣ������Ҫ�������������ͣ�"<<endl;
		printf("\n�����������˵���\n");
		getch();
		Menu1();
	}
	else Taocan();
}
void Diancan()
{
	void Menu1();
	system("cls");
	cout<<"1����ʳ"<<endl;
	cout<<"2��С��"<<endl;
	cout<<"3������"<<endl;
	cout<<"4���ײ�"<<endl;
	cout<<"5������"<<endl;
	char c;
	c=getch();
	switch(c)
	{
		case '1':	xuanzhucan();		break;
		case '2':	xuanfushi();		break;
		case '3':	xuandrink();		break;
		case '4':	Taocan();		break;
		case '5':	Menu1();		break;
		default: 
			printf("\n���İ������󣬰����������ѡ��\n");
			getch();
			Diancan();
	}	 
}
void Zhifu()
{
	void Menu1();
	system("cls");
	cout<<"����������"<<mymoney<<"Ԫ����֧���ֽ�"<<endl;
	int m,s;
	cin>>m;
	s=m-mymoney;
	while(s<0)
	{
		cout<<"�������ֽ��㣬����Ҫ"<<0-s<<"Ԫ�������֧���ֽ�"<<endl;
		cin>>m;
		s=m+s;
	}
	cout<<"֧���ɹ�������"<<s<<"Ԫ��ף��������죡"<<endl;
	write();
	history();//д��������ʷ 
	mynum=0;
	mymoney=0;
	printf("\n����������ز˵���\n");
	getch();
	Menu1();
}
void Youhuiquan()
{
	void Menu1();
	system("cls");
	printf("\n�����������Ż�ȯ��\n");
	string yhq;
	cin>>yhq;
	if(yhq=="156157158")
	{
		cout<<"���ѳɹ�ʹ��5Ԫ�Ż�ȯ��"<<endl;
		mymoney=mymoney-5;
	}
	else
	{
		cout<<"�Բ��������Ż�ȯ��Ч��"<<endl;
		getch();
		Menu1();
	}
	getch();
	Zhifu();
}

void Jiesuan()
{
	void Menu1();
	system("cls");
	cout<<"1��ʹ���Ż�ȯ"<<endl;
	cout<<"2��ֱ��֧��"<<endl;
	cout<<"4������"<<endl;
	char c;
	c=getch();
	switch(c)
	{
		case '1':	Youhuiquan();		break;
		case '2':	Zhifu();		break;
		case '4':	Menu1();		break;
		default: 
			printf("\n���İ������󣬰����������ѡ��\n");
			getch(); 
			Diancan();
	}	 
}
void Show()
{	
	void Menu1();
	system("cls");
	int i;
	for(i=0;i<mynum;i++)
		cout<<i+1<<"��"<<myshiwu[i].mingzi<<"	�۸�"<<myshiwu[i].price<<endl;
	cout<<"�ܼ۸�"<<mymoney<<endl;
	printf("\n����������ز˵���\n");
	getch();
	Menu1();
}

void ShowHistory()//��ȡ������ʷ 
{
    system("cls");
    system("history.txt");
    Menu();
}
void Clean()
{
	void Menu1();
	system("cls");
	mynum=0;
	mymoney=0;
	printf("\n��ճɹ���\n����������ز˵���\n");
	getch();
	Menu1();
}
void Menu1()
{
	system("cls");
	cout<<endl<<endl<<"��ӭ��ˣ�"<<endl<<endl;
	cout<<"��ѡ�����"<<endl;
	cout<<"1�����"<<endl;
	cout<<"2���鿴�ѵ�"<<endl;
	cout<<"3������ѵ�"<<endl;
	cout<<"4������"<<endl;
	cout<<"5���˳�"<<endl;
	char c;
	c=getch();
	switch(c)
	{
		case '1':	Diancan();		break;
		case '2':	Show();	break;
		case '3':	Clean();	break;
		case '4':	if(admin == 1)
		               Jiesuan();
					else
					   cout << "���Ʋ���������ǰ��ʾ�ѵ�˵�������ԱΪ����ˣ�лл��";
					break;
		case '5':	exit(0);	break;
		default: 
			printf("\n���İ������󣬰����������ѡ��\n");
			getch();
			Menu1();
	}	 
}

int main()
{
	User user;
	int chose;
	int rt;
	admin = 0;
	top:
	Page a;
    rt = a.homePage(0);		//1 
    if(rt == 1)
    	goto part2;
	chose = -1;
	cout << endl;
	cout << "\t\t��������������������������������������������������������������������������������\n";
	cout << "\t\t��       1.ע    ��     2.��    ¼      ��\t\n";
	cout << "\t\t��������������������������������������������������������������������������������\n";
	cout << "\t\t��ϵͳ��ʾ�����������ѡ��";
	cin >> chose;
	if (chose > 2 || chose < -1)
	{
		cout << "\t\t��ϵͳ��ʾ�������ʽ�������������룺";
		cin >> chose;
	}
	switch (chose)
	{
	case 1:user.Registers(); break;
	case 2:user.Login(); break;
	}		//2 
    part2:
	Menu();
    do
    {
        cout<<"���������ѡ��"<<endl;
        int choice;
        cin>>choice;
        switch(choice)
        {
           case 1:Search();break;
           case 2:if(admin == 0)
		   			cout << "Ȩ�޲��㣡\n" ;
				  else
				  	Set();break;
           case 3:Menu1();break;
           case 4:customer_evaluate();break;
           case 5:if(admin == 0)
		   			cout << "Ȩ�޲��㣡\n" ;
				  else
				  	ShowHistory();break;
           case 0:system("cls");admin = 0;goto top;break;
        }

    }while(1);
    return 0;
}
Customer::Customer()
{
    system("cls");
    total++;
    cout<<"            �㵱ǰ�ŶӺ���Ϊ��"<<total<<endl<<endl;
}

void Customer::order()
{
    int temp[50];
    int j=0;
    int sum =0;
    char flag ='y';
    int num =0;

    Menus menu[50];
    cout<<"         �˵�"<<endl<<endl;

    ifstream in ("Menus.txt");
    int i=0;
    while(in>>menu[i].number>>menu[i].dish_name>>menu[i].price)
    {
    cout<<"  "<<menu[i].number<<setw(10)<<menu[i].dish_name<<setw(10)<<menu[i].price<<endl;
    i++;
    }
    in.close();

        while(flag == 'y')
        {
            cout<<"����,ѡ����Ӧ��ţ�"<<endl;
           cin>>temp[num];
           num++;
           cout<<"�Ƿ����y or n"<<endl;
           cin>>flag;
        }
         for(j=0;j<num;j++)
        {
            for(i=0;i<10;i++)
            {
               if(temp[j]==menu[i].number)
               {
                  sum = sum + menu[i].price;
               }
            }
        }
    cout<<"�ܼ�Ǯ��"<<sum<<endl;

}


void Waiter::Set()
{
    system("cls");
    char flag ='y';
    do
    {
    cout<<"�������Ա�Ĺ��ţ��������Ա𣬵绰���룺"<<endl;
    cin>>job_number>>name>>sex>>phone_number;
    ofstream out("Waiter.txt",ios::app);
    out<<job_number<<" "<<name<<" "<<sex<<" "<<phone_number<<endl;
    out.close();
    cout<<"�Ƿ������(y)��(n)"<<endl;
    cin>>flag;
    }while(flag == 'y');
    Menu();
}
void Menus::Set()
{
    system("cls");
    char flag = 'y';
    do
    {
    sums++;
    cout<<"�����ţ��������۸�"<<endl;
    cin>>number>>dish_name>>price;
    ofstream out("Menus.txt",ios::app);
    out<<number<<"  "<<dish_name<<"  "<<price<<"  "<<endl;
    out.close();
    cout<<"�Ƿ������(y)��(n)"<<endl;
    cin>>flag;
    }while(flag == 'y');
    Menu();
}
void Restaurant::Set()
{
    cout<<"�������λ�ã��绰����"<<endl;
    cin>>location>>phone_number;
    ofstream out("Restaurant.txt");
    out<<location<<"  "<<phone_number<<endl;
    out.close();
    Menu();
}
void Restaurant::Search()
{
    system("cls");
    cout<<endl<<endl;
    ifstream in ("Restaurant.txt");
    cout<<"��ַ"<<"         "<<"��ϵ�绰"<<endl;
    while(in>>location>>phone_number)
    {
    cout<<location<<"  "<<phone_number<<endl;
    }
    in.close();
    Menu();
}
void Restaurant::evaluate()
{
	char a;
    system("cls");
    cout<<endl<<"       ��ʷ���ۣ�"<<endl<<endl;
    ifstream in("evaluate.txt");
    while(in.get(a))
        
		cout<<a; 
    in.close();
    Menu();
}

void Waiter::Search()
{
    system("cls");
    ifstream in("Waiter.txt");
    cout<<endl<<endl;
    cout<<"   ����"<<"  "<<"����"<<"    "<<"�Ա�"<<"  "<<"�绰����"<<endl;
    while(in>>job_number>>name>>sex>>phone_number)
    {
    cout<<"    "<<job_number<<"    "<<name<<"    "<<sex<<"    "<<phone_number<<endl;
    }
    in.close();
    Menu();
}
void Menus::Search()
{
    system("cls");
    ifstream in ("Menus.txt");
    cout<<endl<<endl;
    cout<<"  ���"<<setw(10)<<"����"<<setw(10)<<"�۸�"<<endl;
    while(in>>number>>dish_name>>price)
    {
    cout<<"  "<<number<<"   "<<setw(10)<<dish_name<<setw(10)<<price<<endl;
    }
    in.close();
    Menu();
}

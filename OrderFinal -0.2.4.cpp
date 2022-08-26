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



#define SIZE 100//最大用户容量
int scount = 0;//用作储存当前已注册用户数
int admin = 0;//判断管理员登录admin全局变量 





User user[SIZE];





int Customer::total=0;
int Menus::sums=0;


//主页
int Page::homePage(int flag){
    if(!flag)    //system("mode con lines=13 cols=54");
    cout<<"*****************************************************\n";
    cout<<"*                       v0.2.4                      *\n";
    cout<<"*             欢迎来到酒店点菜管理系统              *\n";
    cout<<"*                  请选择你的身份                   *\n";
    cout<<"*                                                   *\n";
    cout<<"*                                                   *\n";
    cout<<"*  1.管理员     2.顾客     3.系统管理员    4.退出   *\n";
    cout<<"*                                                   *\n";
    cout<<"*                                                   *\n";
    cout<<"*****************************************************\n";
    int ch;
    while(cin>>ch){
        switch (ch){
        case 1:
        	system("cls");
        	cout<<"管理员登录：\n";
            admin = 1; 
            return 0;
            break;
        case 2:
        	system("cls");
            cout<<"顾客登录：\n";
            admin = 0;
            return 0;
            break;
        case 3:
            system("cls");
            cout<<"系统管理员登录：\n";
            admin = 2;
			this->login();
            return 1;
            break;
        case 4:
			exit(0); 
        default:
            cout<<"请选择正确的选项!\n";
            this->homePage(1);
        }
    }
}


//管理员登录
void Page::login(){
    string username,password;
    cout<<"请输入用户名:";
    cin>>username;
    cout<<"请输入密码:";
    cin>>password;
    if(username==this->username && password==this->password){
        //system("mode con lines=30 cols=120");
        cout<<"登录成功！\n";
    }else{
        cout<<"密码错误!请重新选择你的操作!\n";
        this->homePage(1);
    }
}

//保存
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

//读取
void User::read()
{
	ifstream ifile;
	ifile.open("user.txt", ios::in);

	scount = 0;

	if (!ifile.is_open())
	{
		//cout << "文件打开失败！" << endl;
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

//注册
void User::Registers()
{
	us.read();//读取已储存用户数据
	string ph;//电话
	string pw1;//密码1
	string pw2;//密码2
	for (int i = scount; i < SIZE; i++)
	{
	here:
		cout << "\t\t【系统提示】顾客请输入手机号，员工请输入工号：";
		cin >> ph;
		//判断新输入的用户信息是否已存在（如果已存在则重新输入）
		for (int i = 0; i < scount; i++)
		{
			if (ph == user[i].phone)
			{
				cout << "\t\t【系统提示】用户已存在！" << endl;
				goto here;
			}
		}
		user[i].phone = ph;

		int chose = -1;
		cout << endl;
		cout << "\t\t┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
		cout << "\t\t┃       1.显示密码     2.隐藏密码      ┃\t\n";
		cout << "\t\t┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n";
		cout << "\t\t【系统提示】请输入你的选择：";
		cin >> chose;
		if (chose > 2 || chose < -1)
		{
			cout << "\t\t【系统提示】输入格式错误，请重新输入：";
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
			cout << "\t\t【系统提示】请输入密码：";
			cin >> pword;
			user[i].password = pword;
			cout << "\t\t【系统提示】请再次密码：";
			cin >> pword1;
			if (pword1 != user[i].password)
			{
				cout << "\t\t【系统提示】密码不一致！" << endl;
				goto here;
			}
			else
			{
				scount++;//已注册用户加1
				cout << "\t\t【系统提示】注册成功！" << endl;
				us.save();//保存用户数据
			}
			break;
		case 2:
			cout << "\t\t【系统提示】请输入密码：";
			while ((ch = _getch()) != '\r' && x <= 20)
			{
				if (ch == '\b')
				{
					if (x > 0)
					{
						x--;
						cout << "\b \b";//密码支持退格的实现
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

			cout << "\t\t【系统提示】请再次密码：";
			while ((ch1 = _getch()) != '\r' && x1 <= 20)
			{
				if (ch1 == '\b')
				{
					if (x1 > 0)
					{
						x1--;
						cout << "\b \b";//密码支持退格的实现
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
			//比较两次输入的密码是否统一（如果不统一则重新输入）
			if (passwords1 != user[i].password)
			{
				cout << "\t\t【系统提示】密码不一致！" << endl;
				goto here;
			}
			else
			{
				scount++;//已注册用户加1
				cout << "\t\t【系统提示】注册成功！" << endl;
				us.save();//保存用户数据
			}
			break;
		}
		char choice;
		cout << "\t\t【系统提示】是否继续注册(Y/N)？ :";
		while (1)
		{
			cin >> choice;
			if (choice == 'y' || choice == 'Y' || choice == 'n' || choice == 'N')
				break;
			else
				cout << "\t\t【系统提示】输入格式错误，请重新输入： ";
		}
		if (choice == 'n' || choice == 'N')
		{
			break;
		}
	}
}

//登录
void User::Login()
{
	us.read();//读取已储存用户数据
	string ph;//电话
	string pw;//密码
	int time = 0;//统计比较次数
here:
	cout << "\t\t【系统提示】顾客请输入手机号，员工请输入工号：";
	cin >> ph;
	int chose = -1;
	cout << endl;
	cout << "\t\t┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
	cout << "\t\t┃       1.显示密码     2.隐藏密码      ┃\t\n";
	cout << "\t\t┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n";
	cout << "\t\t【系统提示】请输入你的选择：";
	cin >> chose;
	if (chose > 2 || chose < -1)
	{
		cout << "\t\t【系统提示】输入格式错误，请重新输入：";
		cin >> chose;
	}

	string pword;
	char ch, passwords0[20];
	int x = 0;
	switch (chose)
	{
	case 1:
		cout << "\t\t【系统提示】请输入密码：";
		cin >> pword;
		for (int i = 0; i < scount; i++)
		{
			if (ph == user[i].phone && pword == user[i].password)
			{
				time++;
				//cout << "\t\t\t【系统提示】登录成功！" << endl;
			}
		}
		if (time == 0)
		{
			cout << "\t\t【系统提示】手机号、工号或密码错误！" << endl;
			goto here;
		}
		break;
	case 2:
		cout << "\t\t【系统提示】请输入密码：";
		while ((ch = _getch()) != '\r' && x <= 20)
		{
			if (ch == '\b')
			{
				if (x > 0)
				{
					x--;
					cout << "\b \b";//密码支持退格的实现
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
		//依次比较已储存信息，比较是否匹配（如不匹配则提示错误）
		for (int i = 0; i < scount; i++)
		{
			if (ph == user[i].phone && passwords0 == user[i].password)
			{
				time++;
				cout << "\t\t【系统提示】登录成功！" << endl;
			}
		}
		if (time == 0)
		{
			cout << "\t\t【系统提示】手机号、工号或密码错误！" << endl;
			goto here;
		}
		break;
	}
}

//****全局函数***//
void Menu()
{
    cout<<endl;cout<<endl;//cout<<endl;cout<<endl;cout<<endl;cout<<endl;
    cout<<setw(41)<<"酒店点菜管理系统"<<endl;
    cout<<endl;
    cout<<setw(50)<<"1**************信息查询*************"<<endl;
        cout<<endl;
    cout<<setw(50)<<"2**************信息录入*************"<<endl;
        cout<<endl;
    cout<<setw(50)<<"3**************顾客点菜*************"<<endl;
    cout<<endl;
    cout<<setw(50)<<"4**************顾客评价*************"<<endl;
    cout<<endl;
    cout<<setw(50)<<"5**************消费历史*************"<<endl;
    cout<<endl;
    cout<<setw(50)<<"0**************登出账号*************"<<endl;
    cout<<endl;
}

void Search()
{
   system("cls");
    cout<<endl;cout<<endl;cout<<endl;cout<<endl;cout<<endl;

   cout<<"         1   查询餐厅信息"<<endl;
       cout<<endl;

   cout<<"         2   查询服务员信息"<<endl;
       cout<<endl;

   cout<<"         3   查询菜单"<<endl;
       cout<<endl;
       cout<<"         4    查看评价"<<endl;
       cout<<endl;

   cout<<"         5   返回上一级菜单"<<endl;
       cout<<endl;

   cout<<" "<<"请选择："<<endl;
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
    cout<<"              1 添加菜品"<<endl<<endl;
    cout<<"              2 添加服务员"<<endl<<endl;
    cout<<"              3 添加餐厅信息"<<endl<<endl;
    cout<<"              4 返回上一级菜单"<<endl<<endl;
    cout<<"         请选择："<<endl;
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
			   	 cout << "权限不足！"; 
			   break;
       case 3:if(admin == 2)
	   			 restaurant.Set();
			   else
			   	 cout << "权限不足！"; 
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
    cout<<"请评价和评分："<<endl;
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
shiwu zhucan[3]={shiwu("大汉堡",13),shiwu("烤肉饭",13),shiwu("鸡肉卷",11)};
shiwu fushi[3]={shiwu("麻辣鸡钉",9),shiwu("劲爆鸡米花",9),shiwu("大薯条",6)};
shiwu drink[3]={shiwu("可口可乐",5),shiwu("拿铁咖啡",6),shiwu("热牛奶",6)};
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
Taocan taocan[3]={Taocan("鸡腿鸡翅套餐",zhucan[0],fushi[0],drink[0]),Taocan("鳕鱼鸡米花套餐",zhucan[1],fushi[1],drink[0]),Taocan("鸡肉卷薯条套餐",zhucan[2],fushi[2],drink[0])};
shiwu myshiwu[13];
int mymoney;
int mynum=0;
void write()
{
	ofstream f("list.txt");
	int i;
	f << "消费清单\n";
	for(i=0;i<mynum;i++)    
		f<<i+1<<"、"<<myshiwu[i].mingzi<<"	价格："<<myshiwu[i].price<<endl;
	f<<"总价格、"<<to_string(mymoney)<<endl;
	f<<endl<<endl;
    f.close();
	system("list.txt");
}

void history()//写入消费历史，订单 
{
	ofstream out("history.txt",ios::app);
	int i;
	out << "消费历史\n";
	for(i=0;i<mynum;i++)
		out<<i+1<<"、"<<myshiwu[i].mingzi<<"	价格："<<myshiwu[i].price<<endl;
	out<<"总价格、"<<to_string(mymoney)<<endl;
	out<<endl<<endl;
    out.close();
	system("history.txt");
}

void xuanzhucan()
{
	void Menu1();
	void Diancan();
	system("cls");
	cout<<"1、"<<zhucan[0].mingzi<<"	价格："<<zhucan[0].price<<endl;
	cout<<"2、"<<zhucan[1].mingzi<<"	价格："<<zhucan[1].price<<endl;
	cout<<"3、"<<zhucan[2].mingzi<<"	价格："<<zhucan[2].price<<endl;
	cout<<"4、返回"<<endl;
	char c;
	c=getch();
	switch(c)
	{
		case '1':	myshiwu[mynum]=zhucan[0];mymoney+=zhucan[0].price;mynum++;		break;
		case '2':	myshiwu[mynum]=zhucan[1];mymoney+=zhucan[1].price;mynum++;		break;
		case '3':	myshiwu[mynum]=zhucan[2];mymoney+=zhucan[2].price;mynum++;		break;
		case '4':	Diancan();		break;
		default: 
			printf("\n您的按键有误，按任意键重新选择！\n");
			getch();
			xuanzhucan();
	}	 
	printf("\n点餐成功！请按任意键继续点餐或者返回！\n");
	getch();
	if(mynum>10)
	{
		cout<<"您本次点餐已经达到上限！如果需要！请结算后继续点餐！"<<endl;
		printf("\n按任意键进入菜单！\n");
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
	cout<<"1、"<<fushi[0].mingzi<<"	价格："<<fushi[0].price<<endl;
	cout<<"2、"<<fushi[1].mingzi<<"	价格："<<fushi[1].price<<endl;
	cout<<"3、"<<fushi[2].mingzi<<"	价格："<<fushi[2].price<<endl;
	cout<<"4、返回"<<endl;
	char c;
	c=getch();
	switch(c)
	{
		case '1':	myshiwu[mynum]=fushi[0];mymoney+=fushi[0].price;mynum++;		break;
		case '2':	myshiwu[mynum]=fushi[1];mymoney+=fushi[1].price;mynum++;		break;
		case '3':	myshiwu[mynum]=fushi[2];mymoney+=fushi[2].price;mynum++;		break;
		case '4':	Diancan();		break;
		default: 
			printf("\n您的按键有误，按任意键重新选择！\n");
			getch();
			xuanfushi();
	}	 
	printf("\n点餐成功！请按任意键继续点餐或者返回！\n");
	getch();
	if(mynum>10)
	{
		cout<<"您本次点餐已经达到上限！如果需要！请结算后继续点餐！"<<endl;
		printf("\n按任意键进入菜单！\n");
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
	cout<<"1、"<<drink[0].mingzi<<"	价格："<<drink[0].price<<endl;
	cout<<"2、"<<drink[1].mingzi<<"	价格："<<drink[1].price<<endl;
	cout<<"3、"<<drink[2].mingzi<<"	价格："<<drink[2].price<<endl;
	cout<<"4、返回"<<endl;
	char c;
	c=getch();
	switch(c)
	{
		case '1':	myshiwu[mynum]=drink[0];mymoney+=drink[0].price;mynum++;		break;
		case '2':	myshiwu[mynum]=drink[1];mymoney+=drink[1].price;mynum++;		break;
		case '3':	myshiwu[mynum]=drink[2];mymoney+=drink[2].price;mynum++;		break;
		case '4':	Diancan();		break;
		default: 
			printf("\n您的按键有误，按任意键重新选择！\n");
			getch();
			xuandrink();
	}	 
	printf("\n点餐成功！请按任意键继续点餐或者返回！\n");
	getch();
	if(mynum>10)
	{
		cout<<"您本次点餐已经达到上限！如果需要！请结算后继续点餐！"<<endl;
		printf("\n按任意键进入菜单！\n");
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
	cout<<"1、"<<taocan[0].mingzi<<"	价格："<<taocan[0].price<<endl;
	cout<<"2、"<<taocan[1].mingzi<<"	价格："<<taocan[1].price<<endl;
	cout<<"3、"<<taocan[2].mingzi<<"	价格："<<taocan[2].price<<endl;
	cout<<"4、返回"<<endl;
	char c;
	c=getch();
	switch(c)
	{
		case '1':	mymoney+=taocan[0].price;myshiwu[mynum]=taocan[0].tc[0];mynum++;myshiwu[mynum]=taocan[0].tc[1];mynum++;myshiwu[mynum]=taocan[0].tc[2];mynum++;		break;
		case '2':	mymoney+=taocan[1].price;myshiwu[mynum]=taocan[1].tc[0];mynum++;myshiwu[mynum]=taocan[1].tc[1];mynum++;myshiwu[mynum]=taocan[1].tc[2];mynum++;		break;
		case '3':	mymoney+=taocan[2].price;myshiwu[mynum]=taocan[2].tc[0];mynum++;myshiwu[mynum]=taocan[2].tc[1];mynum++;myshiwu[mynum]=taocan[2].tc[2];mynum++;		break;
		case '4':	Diancan();		break;
		default: 
			printf("\n您的按键有误，按任意键重新选择！\n");
			getch();
			Taocan();
	}	 
	printf("\n点餐成功！请按任意键继续点餐或者返回！\n");
	getch();
	if(mynum>10)
	{
		cout<<"您本次点餐已经达到上限！如果需要！请结算后继续点餐！"<<endl;
		printf("\n按任意键进入菜单！\n");
		getch();
		Menu1();
	}
	else Taocan();
}
void Diancan()
{
	void Menu1();
	system("cls");
	cout<<"1、主食"<<endl;
	cout<<"2、小吃"<<endl;
	cout<<"3、饮料"<<endl;
	cout<<"4、套餐"<<endl;
	cout<<"5、返回"<<endl;
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
			printf("\n您的按键有误，按任意键重新选择！\n");
			getch();
			Diancan();
	}	 
}
void Zhifu()
{
	void Menu1();
	system("cls");
	cout<<"您本次消费"<<mymoney<<"元！请支付现金！"<<endl;
	int m,s;
	cin>>m;
	s=m-mymoney;
	while(s<0)
	{
		cout<<"您给的现金不足，还需要"<<0-s<<"元！请继续支付现金！"<<endl;
		cin>>m;
		s=m+s;
	}
	cout<<"支付成功！找零"<<s<<"元！祝您生活愉快！"<<endl;
	write();
	history();//写入消费历史 
	mynum=0;
	mymoney=0;
	printf("\n按任意键返回菜单！\n");
	getch();
	Menu1();
}
void Youhuiquan()
{
	void Menu1();
	system("cls");
	printf("\n请输入您的优惠券！\n");
	string yhq;
	cin>>yhq;
	if(yhq=="156157158")
	{
		cout<<"您已成功使用5元优惠券！"<<endl;
		mymoney=mymoney-5;
	}
	else
	{
		cout<<"对不起！您的优惠券无效！"<<endl;
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
	cout<<"1、使用优惠券"<<endl;
	cout<<"2、直接支付"<<endl;
	cout<<"4、返回"<<endl;
	char c;
	c=getch();
	switch(c)
	{
		case '1':	Youhuiquan();		break;
		case '2':	Zhifu();		break;
		case '4':	Menu1();		break;
		default: 
			printf("\n您的按键有误，按任意键重新选择！\n");
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
		cout<<i+1<<"、"<<myshiwu[i].mingzi<<"	价格："<<myshiwu[i].price<<endl;
	cout<<"总价格、"<<mymoney<<endl;
	printf("\n按任意键返回菜单！\n");
	getch();
	Menu1();
}

void ShowHistory()//读取消费历史 
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
	printf("\n清空成功！\n按任意键返回菜单！\n");
	getch();
	Menu1();
}
void Menu1()
{
	system("cls");
	cout<<endl<<endl<<"欢迎点菜！"<<endl<<endl;
	cout<<"请选择服务："<<endl;
	cout<<"1、点菜"<<endl;
	cout<<"2、查看已点"<<endl;
	cout<<"3、清空已点"<<endl;
	cout<<"4、结算"<<endl;
	cout<<"5、退出"<<endl;
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
					   cout << "请移步到收银柜前出示已点菜单，收银员为你结账，谢谢！";
					break;
		case '5':	exit(0);	break;
		default: 
			printf("\n您的按键有误，按任意键重新选择！\n");
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
	cout << "\t\t┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
	cout << "\t\t┃       1.注    册     2.登    录      ┃\t\n";
	cout << "\t\t┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n";
	cout << "\t\t【系统提示】请输入你的选择：";
	cin >> chose;
	if (chose > 2 || chose < -1)
	{
		cout << "\t\t【系统提示】输入格式错误，请重新输入：";
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
        cout<<"请输入你的选择："<<endl;
        int choice;
        cin>>choice;
        switch(choice)
        {
           case 1:Search();break;
           case 2:if(admin == 0)
		   			cout << "权限不足！\n" ;
				  else
				  	Set();break;
           case 3:Menu1();break;
           case 4:customer_evaluate();break;
           case 5:if(admin == 0)
		   			cout << "权限不足！\n" ;
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
    cout<<"            你当前排队号码为："<<total<<endl<<endl;
}

void Customer::order()
{
    int temp[50];
    int j=0;
    int sum =0;
    char flag ='y';
    int num =0;

    Menus menu[50];
    cout<<"         菜单"<<endl<<endl;

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
            cout<<"请点餐,选择相应编号："<<endl;
           cin>>temp[num];
           num++;
           cout<<"是否继续y or n"<<endl;
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
    cout<<"总价钱："<<sum<<endl;

}


void Waiter::Set()
{
    system("cls");
    char flag ='y';
    do
    {
    cout<<"输入服务员的工号，姓名，性别，电话号码："<<endl;
    cin>>job_number>>name>>sex>>phone_number;
    ofstream out("Waiter.txt",ios::app);
    out<<job_number<<" "<<name<<" "<<sex<<" "<<phone_number<<endl;
    out.close();
    cout<<"是否继续是(y)否(n)"<<endl;
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
    cout<<"输入编号，菜名，价格"<<endl;
    cin>>number>>dish_name>>price;
    ofstream out("Menus.txt",ios::app);
    out<<number<<"  "<<dish_name<<"  "<<price<<"  "<<endl;
    out.close();
    cout<<"是否继续是(y)否(n)"<<endl;
    cin>>flag;
    }while(flag == 'y');
    Menu();
}
void Restaurant::Set()
{
    cout<<"输入餐厅位置，电话号码"<<endl;
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
    cout<<"地址"<<"         "<<"联系电话"<<endl;
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
    cout<<endl<<"       历史评价："<<endl<<endl;
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
    cout<<"   工号"<<"  "<<"姓名"<<"    "<<"性别"<<"  "<<"电话号码"<<endl;
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
    cout<<"  编号"<<setw(10)<<"菜名"<<setw(10)<<"价格"<<endl;
    while(in>>number>>dish_name>>price)
    {
    cout<<"  "<<number<<"   "<<setw(10)<<dish_name<<setw(10)<<price<<endl;
    }
    in.close();
    Menu();
}

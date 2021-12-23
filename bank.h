/********************************头文件调用*********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <conio.h>
#include <curses.h>
#include <time.h>
//#include <windows.h>

/***************************银行客户信息结构体管理员***********************************/
struct Client;                        //银行客户信息结构体声明
typedef struct Client Client, *Ptrone; //结构体指针定义
typedef Ptrone List;                  //链表头指针定义
typedef Ptrone Position;              //链表结点指针定义

/********************************存取款记录结构体**************************************/
struct Records;                         //职称结构体声明
typedef struct Records Records, *PtrRe; //结构体指针定义
typedef PtrRe List1;                    //链表头指针定义
typedef PtrRe Position1;                //链表结点指针定义

/********************************链表函数声明******************************************/
void DeleteList(List L);            //链表删除函数(客户信息
List MakeEmpty(List L);             //空链表创建函数(客户信息
void TravelList(List L);            //遍历客户信息链表函数
List SortMoney(List L);             //链表冒泡排序函数(余额
List SortNum(List L);               //链表冒泡排序函数(账号

void DeleteList1(List1 L);                  //链表删除函数(收支记录
List1 MakeEmpty1(List1 L);                  //空链表创建函数(收支记录
void TravelList1(List1 L);                  //遍历收支记录链表函数
List1 SortNum1(List1 L);                    //操作记录(账号
List1 SortTime1(List1 L);                   //操作记录(时间

/********************************文件函数声明******************************************/
List Load(List L);         //将客户信息加载到内存函数
void Save(List L);         //将客户信息保存到磁盘函数
void MakeFileEmpty();      //清空文件函数

List1 Load1(List1 L);               //将收支记录信息加载到内存函数
void Save1(List1 L);                //将收支记录信息保存到磁盘函数
void MakeFileEmpty1();              //清空文件函数

/********************************菜单函数声明******************************************/
void Choose();                              //访客选择身份
void MainMeun1(List L, List1 L1);            //管理员主菜单
void MainMeun2(char[], List L, List1 L1);     //客户主菜单
void ViewMeun(List L, List1 L1);                      //查询客户信息菜单
void RecordMeun(List1 L);                   //查询客户存取款记录菜单
void OrderMeun(List L, List1 L1);            //客户信息排序菜单
void ModMeun(List L, List1 L1);              //修改菜单
void ModMeun1(Position p, List L, List1 L1);  //修改的部分菜单

/********************************客户信息管理函数声明**********************************/

void Add(List L);                                          //信息录入函数
void ViewNum(char num[], List L);                           //账号显示函数
void ViewName(char name[], List L);                         //姓名信息显示函数
void ViewTel(char tel[], List L);                           //电话信息显示函数
void ViewID(char ID[], List L);                             //身份证显示函数
void ViewCom(List L);                                      //综合查询
void CircleTel(char tel[], Position p, List L, List1 L1);     //电话
void CircleName(char name[], Position p, List L, List1 L1);   //姓名
void CircleID(char ID[], Position p, List L, List1 L1);       //身份证查询
void ModName(Position p, List L, List1 L1);                  //客户姓名修改函数
void ModTel(Position p, List L);                            //客户电话修改函数
void ModPassword(Position p, List L);                       //客户密码修改函数
void ModMoney(Position p, List L, double n);                 //客户余额修改函数
void Delete(List L, List1 L1);                              //删除函数，客户信息

/********************************收支记录管理函数声明**********************************/
void Add1(char sj[], Position p, List L, List1 L1);   //收支记录录入函数
void ViewNum1(char num[], List1 L);       //收支记录查询函数(按账号
void ViewName1(char name[], List1 L);     //收支记录查询函数(按姓名
void ViewCom1(List1 L);                  //综合查询

/********************************功能函数声明******************************************/
Position Logon(List L);
int Mimayincan(char a[]);         //密码隐藏函数
void PrintRecords(Position1 p);    //收支记录打印函数
void PrintClient(Position P);      //客户信息打印函数
int Testl(int a, int b, int c);      //菜单输入检测函数
void jiesuo(List L, List1 L1);

/*********************************结构体定义*******************************************/
struct Client//客户信息结构体客户
{
	char num[30];               //账号
	char ID[19];           //身份证号
	char name[10];         //姓名
	char tel[12];          //电话
	char password[20];     //密码
	char loc[10];          //办卡地址
	double money;          //余额
	char sd[10];            //锁定
	char time[20];         //还款日期
	int type;              //卡类型1.储蓄卡，2.信用卡
	int point;             //信用积分
	Position next;         //next指针 (指向下一结构体)
};
struct Records//操作记录结构体
{
	char num[30];      
	char name[20];         //姓名
	char ID[20];
	char time[20];         //操作时间 年/月/日,时:分 2019/2/6-17.40
	double rmb;            //存取款
	char sd[10];                 //锁定
	struct Records *next;  //next指针
};

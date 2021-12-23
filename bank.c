/********************************客户管理函数声明********************************************/
//信息录入函数与删除
void Add(List L)//客户信息
{
	getchar();
	Position p,q = L->next;
	char num[20], a[10] = "Normal", b[20] = "00";
	int t;
	printf("\n请输入所要创建的账号:  ");                         //提示输入账号
	gets(num);
	while (q != NULL && strcmp(num, q->num) != 0)
		q = q->next;
	if (q)
	{
		printf("\n该账号已创建\n");
		char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
		return;
		
	}
	p = (Position)malloc(sizeof(struct Client));                   //创建新结点
	if (p == NULL)
	{
		printf("\n添加失败,内存不足!!!\n\n");                    //添加失败，提示内存不足
		char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");                                         //暂停屏幕显示
		return;                                                  //返回上一级菜单
	}
	strcpy(p->num, num);                                                  //保存账号
	printf("\n请输入您需要办理的卡类型(1.储蓄卡2.信用卡)： ");
	
	scanf("%d", &t);
	t = Testl(t, 1, 2);
	p->type = t;
	printf("\n请输入客户身份证号:  ");                               //保存身份证号
	scanf("%s", p->ID);
	printf("\n请输入客户电话:  ");                                         //保存电话
	scanf("%s", p->tel);
	printf("\n请输入客户的姓名： ");                             //保存姓名
	scanf("%s", p->name);
	printf("\n请输入客户密码： ");                               //保存密码
	scanf("%s", p->password);
	printf("\n请输入客户办卡地址:  ");                           //保存办卡地址
	scanf("%s", p->loc);
	p->money = 0.00;                                             //余额
	p->point = 0;                                                //信用积分
	strcpy(p->time, b);                                           //还款日期
	strcpy(p->sd, a);                                             //状态
	p->next = L->next;                                             //将结点p用头插法插入到链表中
	L->next = p;
	Save(L); 
	getchar();                                                    //调用 信息保存函数
	char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
	return;
}
void Add1(char sj[], Position p, List L, List1 L1)//收支记录
{
	char a[10] = "Normal", b[20] = "00";
	Position1 p1;
	p1 = (Position1)malloc(sizeof(struct Records));                   //创建新结点
	if (p == NULL)
	{
		printf("\n添加失败,内存不足!!!\n\n");                    //添加失败，提示内存不足
		char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");                                         //暂停屏幕显示
	}
	strcpy(p1->num, p->num);
	strcpy(p1->name, p->name);
	strcpy(p1->ID, p->ID);
	strcpy(p1->time, sj);
	if (p->type == 1)//储蓄卡
	{
		printf("\n您的当前余额为:%lf\n",p->money); 
		printf("\n请输入存取款金额(带符号)： ");                       //保存存取款
		scanf("%lf", &p1->rmb);
		getchar();
		if (p->money + p1->rmb < 0)
		{
			printf("\n余额不足！");
			char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear"); return;
		}
		p->money = p->money + p1->rmb;
	}
	else if (p->type == 2)//信用卡
	{
		printf("\n您的当前余额为:%lf\n",p->money); 
		printf("\n请输入消费或还款金额(带符号)");
		scanf("%lf", &p1->rmb);
		//getchar();
		if (p1->rmb<0)//消费金额超过透支额度
		{
			if (p1->rmb+p->money >	-5000 && p->point == 0)//透支额度不够时
			{
				printf("\n您本月还可以消费%.2lf元", 5000 + p->money+p1->rmb);
				char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear"); //return;
			}
			else if (p->point==-1)
			{
				printf("\n您的信用分不够，请先还款哦！您需要还款%.2lf元。", p->money);
				char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear"); return;
			}
			
			else if(p->money==-5000){
				getchar();
				printf("\n您的消费达到本月的最大消费额度，本月已无法再消费，若需要再次消费，请及时还款\n"); 
				char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear"); return; 
			}
			else if(p->money+p1->rmb<-5000){
				getchar();
				printf("您本月最多还可以消费%.2lf元",5000+p->money);
				char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear"); return;
			}
			if (p->money+p1->rmb<0 && p->point == 0)
			{
				time_t rawtime;
				struct tm * timeinfo;
				time(&rawtime);
				timeinfo = localtime(&rawtime);//获取系统时间
				int year=timeinfo->tm_year+1900;
				int mon =timeinfo->tm_mon+1;
				if(mon==12)
				{
					printf("\n\t\t%4d/%02d/%02d-%02d.%02d.%02d\n", year+1, mon-11,
						timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
				}                                                                      //还款日期，加一个月 
				else{
					printf("\n\t\t%4d/%02d/%02d-%02d.%02d.%02d\n", 1900 + timeinfo->tm_year, 1 + timeinfo->tm_mon + 1,
			    		timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
				}                                                                     //还款日期，加一个月
				printf("\n请输入以上时间(年/月/日-时.分.秒):  ");                               //保存操作日期
				scanf("%s", p->time);
				getchar();
				printf("\n请在%s之前还款", p->time);//提醒还款
			}
			
		}
		else if(p1->rmb>0 && p1->rmb+p->money<=0)
		{
			getchar();
			printf("您还需还款%lf元\n",-p->money-p1->rmb);
			char buf[1024]={0};
			fgets(buf,1024,stdin);
			system("clear");
		}
		else if(p1->rmb>0 && p1->rmb+p->money>0)
		{
			getchar();
			printf("您的当前余额为：%lf元\n",p->money+p1->rmb);
			char buf[1024]={0};
			fgets(buf,1024,stdin);
			system("clear");
		}
		if (p1->rmb+p->money >= 0)//违约后还款信用分恢复
		{
			p->point = 0;
			strcpy(p->time, b);
		}
		p->money = p->money + p1->rmb;
	}
	p1->next = L1->next;                                             //将结点p用头插法插入到链表中
	L1->next = p1;
	strcpy(p1->sd, a);
	Save1(L1);                                                     //调用 信息保存函数
	Save(L);
	char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
	return;
}
void Delete(List L, List1 L1)//客户信息
{
	getchar();
	Position  p = L->next,   m=L ,a;
	Position1  n=L1,b=NULL,p1=L1,n1=L1,n2=L1,n3=L1;
	char num[20];
	//char num2[10];
	printf("\n请输入想注销的账号: ");
	gets(num); //按账号删除
	//strcpy(num2,num);
	while (p != NULL&&strcmp(p->num, num) != 0){
		p = p->next;
	}
	if (!p)
	{
		printf("\n不存在该账户哦~\n");
		char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear"); return;
	}
	PrintClient(p);      //调用职工信息打印函数
	fflush(stdin);                   //清除键盘缓冲区
	if (p->money > 0)
	{
		printf("\n请先取出账户余额！");
		char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
		return;
	}
	if(p->money<0)
	{
		printf("\n请先还款！");
		char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
		return;
	}
	printf("\n是否确认要删除？回复'Y'/'N'\n");
	while(p )
	{
		if(m->next==p)	
		break;
		m=m->next;
	}
	if (getchar() == 'Y')
	{
		fflush(stdin);
		Mimayincan(p->password);
		a = p;
		m->next = a->next;
		free(a);
		while (n2 )  //判断P的Next指针是否为空，且P的下一个结点的客户姓名是否为查找账号
		{
			while(n!=NULL && strcmp(num,n->num) !=0 ) //判断n是否为查找账号 
			n=n->next;
			if(n==NULL)
				break;
			while(n1)                                //查找n的前一位地址 
			{		
				if(n1->next==n)
				break;
				n1=n1->next;				
			}	
				b = n;                              //释放查找的账号 
				n1->next = b->next;
				free(b);
			n=L1;
			n2=n2->next;
		
		}
		printf("\n删除成功!!!\n\n");
		Save(L);                     //调用信息保存函数
		Save1(L1);
	}
	getchar();
	char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
}
//查询函数
void ViewNum(char num[], List L)//账号
{
	Position p = L->next;
	int f = 0;
	while (p)
	{
		if (strcmp(p->num, num)==0)
		{
			PrintClient(p);
			f = 1;
		}
		p = p->next;
	}
	if (f == 0)             //判断是否存在该客户
		printf("\n没有匹配的信息");
	char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
}
void ViewName(char name[], List L)//姓名
{
	int f = 0;
	Position p = L->next;
	while (p)
	{
		if (strcmp(p->name, name)==0)
		{
			PrintClient(p);
			f = 1;
		}
		p = p->next;
	}
	if (f == 0)             //判断是否存在该客户
		printf("\n没有匹配的信息");
	char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
}
void ViewTel(char tel[], List L)//电话
{
	Position p = L->next;
	int f = 0;
	while (p)
	{
		if (strcmp(p->tel, tel)==0)
		{
			PrintClient(p);
			f = 1;
		}
		p = p->next;
	}
	if (f == 0)             //判断是否存在该客户
		printf("\n没有匹配的信息");
	char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
}
void ViewID(char ID[], List L)//身份证号
{ 
	Position p = L->next;
	int f = 0;
	while (p)
	{
		if (strcmp(p->ID, ID)==0)
		{
			PrintClient(p);
			f = 1;
		}
		p = p->next;
	}
	if (f == 0)             //判断是否存在该客户
		printf("\n没有匹配的信息");
	
char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
}
void ViewCom(List L)//综合查询
{
	Position p = L->next;
	char name[10], tel[12];
	printf("输入姓名: \n");
	gets(name);
	printf("请输入电话: \n");
	gets(tel);
	int f = 0;
	while (p)
	{
		if (strcmp(p->name, name) == 0 && strcmp(p->tel, tel) == 0)
		{
			PrintClient(p);
			f = 1;
		}
		p = p->next;
	}
	if (f == 0)             //判断是否存在该客户
		printf("\n没有匹配的信息");
	char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
}
//收支记录查询
void ViewName1(char name[], List1 L)//按姓名查询
{
	int f = 0;
	Position1 p = L->next;
	while (p)  //判断P的Next指针是否为空，且P的下一个结点的客户账号是否为查找账号
	{
		if (strcmp(p->name, name)==0 )
		{
			PrintRecords(p);
			f = 1;
		}
		p = p->next;
	}
	if (f == 0)              //判断是否存在该客户
		printf("\n没有匹配的信息");
	char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
}
void ViewNum1(char num[], List1 L)//按账号查询
{
	int f = 0;
	Position1 p = L->next;
	while (p)  //判断P的Next指针是否为空，且P的下一个结点的客户账号是否为查找账号
	{
		if (strcmp(p->num, num)==0)
		{
			PrintRecords(p);
			f = 1;
		}
		p = p->next;
	}
	if (f == 0)
		printf("\n没有匹配的信息");
	char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
}
void ViewCom1(List1 L)//综合查询
{
	Position1 p = L->next;
	char num[30], time[18];
	printf("输入账号: \n");
	gets(num);
	printf("请输入操作时间: \n");
	gets(time);
	int f = 0;
	while (p)
	{
		if (strcmp(p->num, num) == 0 && strcmp(p->time, time) == 0)
		{
			PrintRecords(p);
			f = 1;
		}
		p = p->next;
	}
	if (f == 0)             //判断是否存在该客户
		printf("\n没有匹配的信息");
	char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
}
//排序函数(升序
List SortMoney(List L)//余额(客户信息
{
	getchar();
	Position a, b, p = L->next;
	int i, j, num = 0;
	while (p)
	{
		num++;
		p = p->next;
	}
	for (j = 0; j < num - 1; j++)
	{
		a = L->next;
		b = a->next;
		p = L;
		for (i = 0; i < num - 1 - j; i++)
		{ 
			if(a->money>b->money)	
            {
				a->next = b->next;
				p->next = b;
				b->next = a;
			}
			p = p->next;
			a = p->next;
			b = a->next;
		}
	}
	Save(L);
	TravelList(L);
	return L;
}
List SortNum(List L)//账号(客户信息
{
	getchar();
	Position a, b, p = L->next;
	int i, j, num = 0;
	while (p)
	{
		num++;
		p = p->next;
	}
	for (j = 0; j < num - 1; j++)
	{
		p = L;
		a = L->next;
		b = a->next;
		for (i = 0; i < num - 1 - j; i++)
		{
			if (strcmp(a->num, b->num)>0)
			{
				a->next = b->next;
				p->next = b;
				b->next = a;
			}
			p = p->next;
			a = p->next;
			b = a->next;
		}
	}
	Save(L);
	TravelList(L);
	return L;
}
List1 SortNum1(List1 L)//按账号排序显示收支记录
{
	getchar();
	Position1 a, b, p = L->next;
	int i, j, num = 0;
	while (p)
	{
		num++;
		p = p->next;
	}
	for (j = 0; j < num - 1; j++)
	{
		p = L;
		a = L->next;
		b = a->next;
		for (i = 0; i < num - 1 - j; i++)
		{
			if (strcmp(a->num, b->num)>0)
			{
				a->next = b->next;
				p->next = b;
				b->next = a;
			}
			p = p->next;
			a = p->next;
			b = a->next;
		}
	}
	Save1(L);
	TravelList1(L);
	return L;
}
List1 SortTime1(List1 L)//按收支记录时间排序 
{
	getchar();
	Position1 a, b, p = L->next;
	int i, j, num = 0;
	while (p)
	{
		num++;
		p = p->next;
	}
	for (j = 0; j < num - 1; j++)
	{
		a = L->next;
		b = a->next;
		p = L;
		for (i = 0; i < num - 1 - j; i++)
		{
			if (strcmp(a->time, b->time)>0)
			{
				a->next = b->next;
				p->next = b;
				b->next = a;
			}
			p = p->next;
			a = p->next;
			b = a->next;
		}
	}
	Save1(L);
	TravelList1(L);
	return L;
}
//查询修改
void CircleName(char name[], Position p, List L, List1 L1)//姓名
{
	printf("\033c");
	while (p)  //判断P的Next指针是否为空，且P的下一个结点的客户电话是否为查找账号
	{
		if (strcmp(name, p->name) == 0)
		{
			PrintClient(p);
			printf("\n是否是您想修改的账户：回复'Y'/'N'\n");
			if (getchar() == 'Y')
			{
				char a[20];
				strcpy(a, p->password);
				Mimayincan(a);
				ModMeun1(p, L, L1);
			}
			else if (getchar() == 'N')
				CircleName(name, p->next, L, L1);
		}
		p = p->next;
		if (!p)
		{
			printf("\n该账号不存在： ");
			char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
		}
	}
}
void CircleID(char ID[], Position p, List L, List1 L1)//身份证
{
	printf("\033c");
	while (p)  //判断P的Next指针是否为空，且P的下一个结点的客户电话是否为查找账号
	{
		if (strcmp(ID, p->ID) == 0)
		{
			PrintClient(p);
			printf("\n是否是您想修改的账户：回复'Y'/'N'\n");
			if (getchar() == 'Y')
			{
				char a[20];
				strcpy(a, p->password);
				Mimayincan(a);
				ModMeun1(p, L, L1);
			}
			else if (getchar() == 'N')
				CircleID(ID, p->next, L, L1);
		}
		p = p->next;
		if (!p)
		{
			printf("\n该账号不存在： ");
			char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
		}
	}
}
void CircleTel(char tel[], Position p, List L, List1 L1)//电话
{
	printf("\033c");
	while (p)  //判断P的Next指针是否为空，且P的下一个结点的客户电话是否为查找账号
	{
		if (strcmp(tel, p->tel) == 0)
		{
			PrintClient(p);
			printf("\n是否是您想修改的账户：回复'Y'/'N'\n");
			if (getchar() == 'Y')
			{
				char a[20];
				strcpy(a, p->password);
				Mimayincan(a);
				ModMeun1(p, L, L1);
			}
			else if (getchar() == 'N')
				CircleTel(tel, p->next, L, L1);
		}
		p = p->next;
		if (!p)
		{
			printf("\n该账号不存在： ");
			char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
		}
	}
}
//修改函数
void ModName(Position p, List L, List1 L1)//姓名
{
	getchar(); 
	char name[10];
	Position1 p1 = L1->next;
	Position p2 = L->next;
	printf("\n请输入新的姓名: ");
	gets(name);
	while (p2)
	{
		if (strcmp(p->ID, p2->ID) == 0)
		
{
			strcpy(p2->name, name);
			Save(L);
		}
		p2 = p2->next;
	}
	while (p1)
	{
		if (strcmp(p->ID, p1->ID) == 0)
		{
			strcpy(p1->name, name);
			Save1(L1);
		}
		p1 = p1->next;
	}
	char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
}
void ModTel(Position p, List L)//电话
{
	getchar();
	char tel[20];
	printf("\n请输入新的电话号:  ");
	gets(tel);
	strcpy(p->tel, tel);
	Save(L);         //调用信息保存函数
	char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
}
void ModPassword(Position p, List L)//密码
{
	getchar();
	char a[20];
	printf("\n请输入新的密码: ");
	gets(a);
	strcpy(p->password, a);
	Save(L);
	char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
}

/********************************功能函数定义******************************************/
Position Logon(List L)//登录函数
{
	getchar();
	char password[20], num[30], a[10] = "Normal", b[10] = "Lock", c[10] = "Loss";//密码，账号
	int f;
	printf("\n\t\t请输入您的账号: ");
	gets(num);
	Position p = L->next;
	while (p != NULL && strcmp(num, p->num) != 0)
		p = p->next;
	if (!p)
	{
		printf("\n\t\t该账号不存在！");
		char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
		return NULL;
	}
	if (strcmp(p->sd, b) == 0)
	{
		printf("\n\t\t该账号已被锁定，请到柜台解锁！");
		char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
		return NULL;
	}
	if (strcmp(p->sd, c) == 0)
	{
		printf("\n\t\t该账号以被挂失，请到柜台取消挂失！");
		char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
		return NULL;
	}
	strcpy(password, p->password);
	if (strcmp(p->sd, a) == 0)
	f = Mimayincan(password);
	if (f == 1)
		return p;
	else
	{
		printf("\n\t\t该账号已被锁定，请到柜台解锁！\n");
		strcpy(p->sd, b); Save(L);
		char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
		return NULL;
	}
}
int Mimayincan(char a[])//密码隐藏函数//退格不删*
{
	getchar();
	int i, j = 0, flag = 0;
	char b[20];
	int n = strlen(a);
	while (j < 3)
	{
		printf("\n\t\t请输入您的密码(少于20位)：");
		for (i = 0; i < n; i++)
		{
			system("stty -echo");
			b[i] = getchar();
			system("stty echo");
			if (i>0 && b[i] == '\b')
			{
				i = i - 2;
				printf("\b");
			}
			/*else
				printf("*");*/
		}
		b[i] = '\0';
		j++;
		if (strncmp(a, b, n) == 0)
			return 1;
else if (j < 3)
			printf("\n\t\t密码错误，请重新输入\n\a");
		else if (flag == 0)
		{
			printf("\n\t\t抱歉，该账号暂时已被锁定\n");
			return 0;
		}
	}
	return 1;
}
void PrintClient(Position p)//客户信息打印函数
{
	printf("\n客户信息如下:\n");
	printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
	printf("账号\t\t\t姓名\t\t电话\t\t办卡地址\t\t余额\t\t\t状态\n");
	printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
	printf("%-20s\t%-10s\t%-11s\t%-20s\t%-20.2lf    %-5s\n", p->num, p->name, p->tel, p->loc, p->money, p->sd);
	printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
}
void PrintRecords(Position1 p)//收支记录打印函数
{
	printf("\n\t\t\t\t收支记录如下:\n");
	printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - - - - - -\n");
	printf("账号\t\t\t姓名\t\t操作日期\t\t存取款                  \n");
	printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - - - - - -\n");
	printf("%-20s\t%-10s\t%-18s\t%-.2lf          \n", p->num, p->name, p->time, p->rmb);
	printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - - - - - -\n");
}
int Testl(int a, int b, int c)//菜单输入检测函数
{
	while (a<b || a>c)
	{
		fflush(stdin);                           //清除键盘缓冲区
		printf("\n\t\t\t输入错误，请重新输入: ");
		scanf("%d", &a);
	}
	return a;
}
void jiesuo(List L, List1 L1)
{
	getchar();
	char buf[1024]={0};
	char ID[20], num[30], a[10] = "Normal", c[10] = "Loss";
	int x;
	Position p = L->next;
	Position1 p1 = L1->next;
	printf("\n\t\t请输入您要选择的操作：1.解锁账号 2.账号挂失 3.取消挂失 0.返回上一层");
	printf("\n\n\t\t请输入您的选择:\n");
	while (1)
	{
		scanf("%d", &x);
		x = Testl(x, 0, 3);
		fflush(stdin); 
		getchar();                     //清除键盘缓冲区
		switch (x)
		{
		case 1:  printf("\n\t\t请输入您需要解锁的账号：");
			gets(num);
			while (p != NULL && strcmp(num, p->num) != 0)
				p = p->next;
			if (!p)
			{
				printf("\n\t\t该账号不存在");
				//char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear"); return;
			}
			else if (strcmp(p->sd, a) == 0)
			{
				printf("\n\t\t该账号未被锁定");
				//char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear"); return;
			}
			printf("\n\t\t请输入您的身份证号： ");//确认身份信息
			gets(ID);
			if (strcmp(ID, p->ID) == 0)
			{
				strcpy(p->sd, a); Save(L);
				ModPassword(p, L);
			}
			while (p1)//修改收支记录信息
			{
				if (strcmp(p->num, p1->num) == 0)
				{
					strcpy(p1->sd, a);
					Save1(L1);
				}
				p1 = p1->next;
			}
			MainMeun1(L, L1); break;
		case 2:  printf("\n\t\t请输入您需要挂失的账号：");
			gets(num);
			while (p != NULL && strcmp(num, p->num) != 0)
				p = p->next;
			if (!p)
			{
				printf("\n\t\t该账号不存在");
			//	char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear"); return;
			}
			else if (strcmp(p->sd, c) == 0)
			{
				printf("\n\t\t该账号已挂失");
			//	char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear"); return;
			}
			printf("\n\t\t请输入您的身份证号： ");//确认身份信息
			gets(ID);
			if (strcmp(ID, p->ID) != 0)
			{
				printf("\n\t\t身份证输入有误！");
			//	char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear"); return;
			}
			Mimayincan(p->password);
			strcpy(p->sd, c); Save(L);
			while (p1)//修改收支记录的信息
			{
				if (strcmp(p->num, p1->num) == 0)
				{
					strcpy(p1->sd, c);
					Save1(L1);
				}
				p1 = p1->next;
			}
			printf("\t\t该账号完成挂失\n");
		//	char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");MainMeun1(L, L1); break;
		case 3:  printf("\n\t\t请输入您需要取消挂失的账号：");
			gets(num);
			while (p != NULL && strcmp(num, p->num) != 0)
				p = p->next;
			if (!p)
			{
				printf("\n\t\t该账号不存在");
		//		char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear"); return;
			}
			else if (strcmp(p->sd, a) == 0)
			{
				printf("\n\t\t该账号未挂失");
		//		char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear"); return;
			}
			printf("\n\t\t请输入您的身份证号： ");//确认身份信息
			gets(ID);
			if (strcmp(ID, p->ID) != 0)
			{
				printf("\n\t\t身份证输入有误！");
		//		char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear"); return;
			}
			Mimayincan(p->password);
			strcpy(p->sd, a); Save(L);
			while (p1)//修改收支记录的信息
			{
				if (strcmp(p->num, p1->num) == 0)
				{
					strcpy(p1->sd, a);
					Save1(L1);
				}
				p1 = p1->next;
			}
			printf("\t\t该账号完成取消挂失\n");
		//	char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
			MainMeun1(L, L1); break;
		case 0: MainMeun1(L, L1); break;//返回上一层
		}
	}
}

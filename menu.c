/********************************菜单函数定义******************************************/
void Choose()//访客选择身份 @
{
	printf("\n\t\t**         选择您的身份          **");
	printf("\n\t\t**                               **");
	printf("\n\t\t**          1.管理员             **");
	printf("\n\t\t**          2.客户               **");
	printf("\n\t\t**          0.退出系统           **");
	printf("\n\t\t**                               **");
	printf("\n\n\t\t\t请输入您的选择:");
}
void MainMeun1(List L, List1 L1)//管理员主菜单
{
	printf("\033c");
	printf("\n\t\t**            主菜单                  **");//
	printf("\n\t\t**                                    **");//
	printf("\n\t\t**         1.注册账户                 **");//
	printf("\n\t\t**         2.注销账户                 **");//
	printf("\n\t\t**         3.查询客户信息             **");//
	printf("\n\t\t**         4.查询客户操作记录         **");//
	printf("\n\t\t**         5.修改客户信息             **");//
	printf("\n\t\t**         6.信息查看                 **");//
	printf("\n\t\t**         7.客户后台操作             **");//
	printf("\n\t\t**         8.重置系统                 **");//
	printf("\n\t\t**         9.账户解锁，挂失，取消挂失 **");//
	printf("\n\t\t**         0.返回上一层               **");//
	printf("\n\t\t**                                    **");
	printf("\n\n\t\t\t请输入您的选择:");
	int x;
	scanf("%d", &x);
while (1)
	{
		printf("\033c");                      //实现清屏
		x = Testl(x, 0, 9);
		fflush(stdin);                      //清除键盘缓冲区
		switch (x)
		{
		case 1:  printf("\033c");  Add(L);    printf("\033c");  MainMeun1(L, L1);          //注册账户
		case 2:  printf("\033c");  Delete(L, L1);    printf("\033c");  MainMeun1(L, L1);    //注销账户
		case 3:  printf("\033c");  ViewMeun(L, L1);      printf("\033c");  MainMeun1(L, L1);                          //查询客户信息
		case 4:  printf("\033c");  RecordMeun(L1);      return;                         //查询客户存取款信息
		case 5:  printf("\033c");  ModMeun(L, L1);         return;                       //修改客户信息
		case 6:  printf("\033c");  OrderMeun(L, L1);     return;                         //信息查看
		case 7:  {printf("\033c"); 
			Position p = Logon(L); MainMeun2(p->num, L, L1); MainMeun1(L, L1);} break;     //客户存取款,修改密码等操作
		case 8:  printf("\033c");  getchar();printf("是否需要重置系统，回复'Y'/'N'\n");
			if (getchar() == 'Y')
			{
				MakeFileEmpty(), MakeFileEmpty1(); printf("\033c"); return;
			}//重置系统
			MainMeun1(L, L1);
		case 9:  printf("\033c");  jiesuo(L, L1); MainMeun1(L, L1); break;                     //返回上一层
		case 0:  printf("\033c");  main();   break;                     //返回上一层
		}
		return;
	}
}
void MainMeun2(char num[], List L, List1 L1)//客户主菜单
{
	//char a[20]; 
	Position p = L->next;
	Position1 p1 = L1->next;
	char sj[20]="00", b[20] = "00";
	while (p1 != NULL && strcmp(num, p1->num) != 0)
		p1 = p1->next;
	while (p != NULL && strcmp(num, p->num) != 0)
		p = p->next;
	printf("\n\t\t**           主菜单              **");
	printf("\n\t\t**                               **");
	if (p->type == 1)
		printf("\n\t\t**         1.存取款              **");//
	else
		printf("\n\t\t**         1.消费与还款          **");//
	printf("\n\t\t**         2.操作记录查询        **");//
	printf("\n\t\t**         3.个人信息查询        **");//
	printf("\n\t\t**         4.修改密码            **");//
	printf("\n\t\t**         5.退出客户系统        **");//
	printf("\n\t\t**                               **");
	if(p->type==2){
		printf("\n\t\t最迟还款日期:%s",p->time);
		printf("\n\t\t信用分:%d",p->point);
	}
	printf("\n\n\t\t当前操作时间为:\n");	
	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);//获取系统时间
	printf("\t\t%4d/%02d/%02d-%02d.%02d.%02d\n", 1900 + timeinfo->tm_year, 1 + timeinfo->tm_mon,
		timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
	printf("\n\t\t请输入以上时间(年/月/日-时.分.秒):  ");
	scanf("%s", sj);
	if (p->money<0 && strcmp(p->time,sj)<=0)//超时未还款信用分为负 
	{
		p->point = -1;
		//p->money = 1.1*p->money;
	}
	if (p->money>0)
	{
		strcpy(p->time, b);
		p->point=0; 
		Save(L);
	}
	printf("\n\n\t\t\t请输入您的选择:");
	int x;
	scanf("%d", &x);
	getchar();
	while (1)
	{
		printf("\033c");                      //实现清屏
		x = Testl(x, 1, 5);
		fflush(stdin);                 //清除键盘缓冲区
		switch (x)
		{
		case 1:  printf("\033c");  Add1(sj, p, L, L1);   printf("\033c"); MainMeun2(p->num, L, L1);                //存款
		case 2:  printf("\033c");  if (p1 == NULL)
		{
			printf("\n无操作记录： ");
			char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
			return;
		}
				 ViewNum1(num, L1);  printf("\033c"); MainMeun2(p->num, L, L1);                //操作记录查询
		case 3:  printf("\033c");  ViewNum(num, L);    printf("\033c"); MainMeun2(p->num, L, L1);               //个人信息查询
		case 4:  printf("\033c");  ModPassword(p, L);  printf("\033c"); MainMeun2(p->num, L, L1);              //修改密码
		case 5:  printf("\033c");  main();  break;                          //返回上一层
		}
		return;
	}
}
void OrderMeun(List L, List1 L1)//信息查看菜单
{
	printf("\n\t\t**           信息查看             **");
	printf("\n\t\t**                                **");
	printf("\n\t\t**    1.按账号排序(客户信息)      **");//@
	
    printf("\n\t\t**    2.按余额排序(客户信息)      **");//@
	printf("\n\t\t**    3.按账号排序(操作记录)      **");//@
	printf("\n\t\t**    4.按时间排序(操作记录)      **");//@
	printf("\n\t\t**    5.返回上一级菜单            **");//
	printf("\n\t\t**                                **");
	printf("\n\n\t\t\t请输入您的选择:");
	int x;
	scanf("%d", &x);
	while (1)
	{
		printf("\033c");                      //实现清屏
		x = Testl(x, 1, 5);
		fflush(stdin);                      //清除键盘缓冲区
		switch (x)
		{
		case 1:  printf("\033c");  L = SortNum(L);      printf("\033c");  OrderMeun(L, L1);              //按账号排序
		case 2:  printf("\033c");  L = SortMoney(L);    printf("\033c");  OrderMeun(L, L1);           //按余额排序
		case 3:  printf("\033c");  L1 = SortNum1(L1);   printf("\033c");  OrderMeun(L, L1);                 //按账号排序
		case 4:  printf("\033c");  L1 = SortTime1(L1);  printf("\033c");  OrderMeun(L, L1);                //按时间排序
		case 5:  printf("\033c");  MainMeun1(L, L1);                                    //返回上一层
		}
	}
}
void ViewMeun(List L, List1 L1)//查询客户信息菜单
{
	printf("\n\t\t**        查询客户信息            **");
	printf("\n\t\t**                                **");
	printf("\n\t\t**        1.按账号查询            **");//@
	printf("\n\t\t**        2.按身份证查询          **");//@
	printf("\n\t\t**        3.按姓名查询            **");//@
	printf("\n\t\t**        4.按电话查询            **");//@
	printf("\n\t\t**        5.按电话和姓名查询      **");//@
	printf("\n\t\t**        6.返回上一层            **");//@
	printf("\n\t\t**                                **");
	printf("\n\n\t\t\t请输入您的选择:");
	int x;
	scanf("%d", &x);
	getchar();
	while (1)
	{
		printf("\033c");                      //实现清屏
		x = Testl(x, 1, 6);
		fflush(stdin);                      //清除键盘缓冲区
		switch (x)
		{
		case 1:  printf("\033c");  char num[30]; printf("\n请输入所要查询的账号:  ");
			gets(num); ViewNum(num, L);      printf("\033c");  ViewMeun(L, L1);   break;   //按账号查询
		case 2:  printf("\033c");  char ID[20]; printf("\n请输入需要查询的身份证： ");
			gets(ID); ViewID(ID, L);         printf("\033c");  ViewMeun(L, L1);   break;   //按身份证号查询
		case 3:  printf("\033c");  char name[10]; printf("\n请输入需要查询的姓名： ");
			gets(name); ViewName(name, L);  printf("\033c");  ViewMeun(L, L1);    break;  //按姓名查询
		case 4:  printf("\033c");  char tel[20]; printf("\n请输入需要查询的电话： ");
			gets(tel); ViewTel(tel, L);      printf("\033c");  ViewMeun(L, L1);   break;   //按电话查询
		case 5:  printf("\033c"); ViewCom(L);  MainMeun1(L, L1);    break;                   //按电话和姓名查询
		case 6:  printf("\033c");  MainMeun1(L, L1); break;                   //返回上一层
		}
	}
}
void RecordMeun(List1 L1)//查询客户存取款记录菜单
{
	printf("\n\t\t**       查询客户操作记录         **");
	printf("\n\t\t**                                **");
	printf("\n\t\t**        1.按账号查询            **");//@
	printf("\n\t\t**        2.按姓名查询            **");//@
	printf("\n\t\t**        3.按账号和操作时间查询  **");//@
	printf("\n\t\t**        4.返回上一层            **");//@
	printf("\n\t\t**                                **");
	printf("\n\n\t\t\t请输入您的选择:");
	int x;
	List L = NULL;
	L = Load(L);
	char num[30], name[10];
	scanf("%d", &x);
	while (1)
	{
		printf("\033c");                      //实现清屏
		x = Testl(x, 1, 4);
		fflush(stdin);                      //清除键盘缓冲区
		switch (x)
		{
		case 1:  printf("\033c");getchar();  printf("\n请输入所要查询的账号:  "); gets(num); ViewNum1(num, L1);
			printf("\033c");  RecordMeun(L1);
		case 2:  printf("\033c");getchar();  printf("\n请输入所要查询的姓名:  "); gets(name); ViewName1(name, L1);
			printf("\033c");  RecordMeun(L1);
		case 3:  printf("\033c");getchar();  ViewCom1(L1);  MainMeun1(L, L1);    break;                   //按账号和操作时间查询
		case 4:  printf("\033c");  MainMeun1(L, L1);                                    //返回上一层
		}
	}
}
void ModMeun(List L, List1 L1)//修改菜单
{
	printf("\n\t\t**        修改客户信息            **");
	printf("\n\t\t**                                **");
	printf("\n\t\t**        1.按账号查询修改        **");//
	printf("\n\t\t**        2.按姓名查询修改        **");//
	printf("\n\t\t**        3.按电话查询修改        **");//
	printf("\n\t\t**        4.按身份证号查询修改    **");//
	printf("\n\t\t**        5.返回上一层            **");//
	printf("\n\t\t**                                **");
	printf("\n\n\t\t\t请输入您的选择:");
	int x;

	char name[10], tel[20], ID[20], num[30], a[20];
	Position p = L->next;
	scanf("%d", &x);
	getchar();
	while (1)
	{
		printf("\033c");                      //实现清屏
		x = Testl(x, 1, 5);
		fflush(stdin);                      //清除键盘缓冲区
		switch (x)
		{
		case 1:  printf("\033c");  printf("\n请输入查询修改的账号: ");     gets(num);      //按账号查询
			while (p)  //判断P的Next指针是否为空，且P的下一个结点的客户电话是否为查找账号
			{
				if (strcmp(num, p->num) == 0)
				{
					PrintClient(p);
					printf("\n是否是您想修改的账户：回复'Y'/'N'\n");
					if (getchar() == 'Y')
					{
						strcpy(a, p->password);
						Mimayincan(a);
						ModMeun1(p, L, L1);
					}
					else
					{
						printf("未找到您想要修改的账号~\n");
						char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear"); printf("\033c");  ModMeun(L, L1);
					}
				}
				p = p->next;
				if (!p)
				{
					printf("\n该账号不存在： ");
					char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear"); printf("\033c");  ModMeun(L, L1);
				}
			}
			printf("\033c");  ModMeun(L, L1);
		case 2:  printf("\033c");  printf("\n请输入查询修改的姓名: ");     gets(name);      //按姓名查询
			CircleName(name, p, L, L1);                printf("\033c");  ModMeun(L, L1);
		case 3:  printf("\033c");  printf("\n请输入查询修改的电话: ");     gets(tel);       //按电话查询
			CircleTel(tel, p, L, L1);                  printf("\033c");  ModMeun(L, L1);
		case 4:  printf("\033c"); printf("\n请输入查询修改的身份证号: "); gets(ID);        //按身份证查询
			CircleID(ID, p, L, L1);                   printf("\033c");  ModMeun(L, L1);
		case 5:  printf("\033c");  MainMeun1(L, L1);                             //返回上一层
		}
	}
}
void ModMeun1(Position p, List L, List1 L1)//修改客户信息菜单
{
	printf("\n\t\t**        修改客户信息            **");
	printf("\n\t\t**                                **");
	printf("\n\t\t**        1.修改姓名              **");//
	printf("\n\t\t**        2.修改密码              **");//
	printf("\n\t\t**        3.修改电话              **");//
	printf("\n\t\t**        4.返回上一层            **");//
	printf("\n\t\t**                                **");
	printf("\n\n\t\t\t请输入您的选择:");
	int x;
	scanf("%d", &x);
	while (1)
	{
		printf("\033c");                      //实现清屏
		x = Testl(x, 1, 4);
		fflush(stdin);                      //清除键盘缓冲区
		switch (x)
		{
		case 1:  printf("\033c");  ModName(p, L, L1);   printf("\033c");  ModMeun1(p, L, L1);                //修改姓名
		case 2:  printf("\033c");  ModPassword(p, L);  printf("\033c");  ModMeun1(p, L, L1);                //修改密码
		case 3:  printf("\033c");  ModTel(p, L);       printf("\033c");  ModMeun1(p, L, L1);                //修改电话
		case 4:  printf("\033c");  ModMeun(L, L1);                            //返回上一层
		}
	}
}

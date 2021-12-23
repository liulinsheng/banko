int main()//主函数
{
	system("color B0");
	List L = NULL;
	List1 L1 = NULL;
	int x;
	printf("\033c");
	printf("\n\n\n\n\t\t\t欢迎进入九院银行~~~~~\n\n");
	L = Load(L);
	L1 = Load1(L1);
	printf("\n\t\t输入回车键继续");
	getchar();
	printf("\033c");                      //实现清屏
	Choose();                           //调用访客选择身份函数
	scanf("%d", &x);
	x = Testl(x, 0, 2);
	while (1)
	{
		fflush(stdin);                      //清除键盘缓冲区
		switch (x)
		{
		case 1:  {printf("\033c");  	char a[] = "123123";
			if (Mimayincan(a) == 1)
				MainMeun1(L, L1);
			exit(0); }                   //调用管理员主菜单函数
		case 2:  {printf("\033c");  	Position p = Logon(L);
			if (p)
				MainMeun2(p->num, L, L1);                      //调用客户主菜单函数
			else
				main();}
		case 0:  exit(0);                                               //退出系统
		}
	}
	return 0;
}

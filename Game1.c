#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
struct player{
	char val;
	char position;
}p[4];
char board[10][10];
void show(struct player,struct player,struct player,struct player);
int num=1,n;
int main()
{
	p[0].position=1;
	p[0].val=3;
	p[1].position=1;
	p[1].val=4;
	p[2].position=1;
	p[2].val=5;
	p[3].position=1;
	p[3].val=6;
    srand(time(0));
	char *q;
	q=(&board[0][0])-1;
	int i,j;
	for(i=0;i<100;i++)
	{
		q++;
		*q=i+1;
	}
	show(p[0],p[1],p[2],p[3]);
	printf("Enter the number of player want to play the game\t");
	scanf("%d",&n);
	system("cls");
	int di,num=1,choice=1;
	while((p[0].position<100)&&(p[1].position<100)&&(p[2].position<100)&&(p[3].position<100))
	{
		if(choice==0)
		break;	
		while(num==1&&choice==1)
		{
			di=rand();
			di=di%6+1;
			p[0].position+=di;
			printf("You(Player 1) have got a %d\n",di);
			if(p[0].position>=100)
			break;
			if(di==6)
			{
				continue;	
			}
			else
			{
				show(p[0],p[1],p[2],p[3]);
				printf("Do you want to roll again(1 for yes)\n");
				scanf("%d",&choice);
				system("cls");
			}
			if(num==n)
			num--;
			num++;
		}
		while(num==2&&choice==1)
		{
			di=rand();
			di=di%6+1;
			p[1].position+=di;
			printf("You(Player 2) have got a %d\n",di);
			if(p[1].position>=100)
			break;
			if(di==6)
			{
				continue;	
			}
			else
			{
				show(p[0],p[1],p[2],p[3]);
				printf("Do you want to roll again(1 for yes)\n");
				scanf("%d",&choice);
				system("cls");
			}			
			if(n==num)
			num=1;
			else
			num++;
		}
		while(num==3&&choice==1)
		{
			di=rand();
			di=di%6+1;
			p[2].position+=di;
			printf("You(Player 3) have got a %d\n",di);
			if(p[2].position>=100)
			break;
			if(di==6)
			{
				continue;	
			}
			else
			{
				show(p[0],p[1],p[2],p[3]);
				printf("Do you want to roll again(1 for yes)\n");
				scanf("%d",&choice);
				system("cls");
			}
			if(n==num)
			num=1;
			else
			num++;
		}
		while(num==4&&choice==1)
		{
			di=rand();
			di=di%6+1;
			p[3].position+=di;
			printf("You(Player 4) have got a %d\n",di);
			if(p[3].position>=100)
			break;
			if(di==6)
			{
				continue;	
			}
			else
			{
				show(p[0],p[1],p[2],p[3]);
				printf("Do you want to roll again(1 for yes)\n");
				scanf("%d",&choice);
				system("cls");
			}
			if(n==num)
			num=1;
			else
			num++;
		}
	}
	system("cls");
	if(choice==1)
	{
		printf("Player %d has won the game\n",num);
	}
	else
	{
		num=0;
		for(i=0;i<4;i++)
		{
			
			if(i==0)
			j=p[0].position;
			else
			{
				if(p[i].position>j)
				{	
					j=p[i].position;
					num=i;
				}
			}
		}
		printf("Player %d has won the game\n",num+1);
	}
	show(p[0],p[1],p[2],p[3]);
	return 0;
}
void show(struct player a,struct player b,struct player c,struct player d)
{
	char ch1,ch2,ch3,ch4;
	char *p,*q,*r,*s;
	int num=n;
	ch1=a.position;
	ch2=b.position;
	ch3=c.position;
	ch4=d.position;
	int i,j,k=0;
	p=&board[0][0];
	q=&board[0][0];
	r=&board[0][0];
	s=&board[0][0];
	while(1)
	{
		if(*p==ch1)
		break;
		p++;
	}
	while(1)
	{
		if(*q==ch2)
		break;
		q++;
	}
	while(1)
	{
		if(*r==ch3)
		break;
		r++;
	}
	while(1)
	{
		if(*s==ch4)
		break;
		s++;
	}
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			k=0;
			if((*p==board[i][j])&&(num>=1))
			{
				printf("%c\t",a.val);
				k++;
			}
			if((*q==board[i][j])&&(num>=2)&&(p!=q))
			{
				printf("%c\t",b.val);
				k++;
			}
			if((*r==board[i][j])&&(num>=3)&&(r!=q)&&(r!=p))
			{
				printf("%c\t",c.val);
				k++;
			}
			if((*s==board[i][j])&&(num==4)&&(s!=q)&&(s!=p)&&(s!=r))
			{
				printf("%c\t",d.val);
				k++;
			}
			if(k==0)
			printf("%d\t",board[i][j]);
		}
		printf("\n");
	}
	if(num>=1)
	printf("Position of first player is %d\n",a.position);
	if(num>=2)
	printf("Position of second player is %d\n",b.position);
	if(num>=3)
	printf("Position of third player is %d\n",c.position);
	if(num>=4)
	printf("Position of fourth player is %d\n",d.position);
}

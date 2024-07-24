#include<iostream>
#include<conio.h>
#include<vector>
#include<iomanip>
#include<windows.h>
using namespace std;
pair<int,int> player;
vector<vector<int>> head;
const int height=80,width=15;
int N=80;
bool gameover=false;
bool direction[height];
void startingwindow();
void generatematrix(int);
void playwindow();
void showmatrix();
void logic();
void setup();
void moveplayer();
void movedanger();
void providedirection();
void instructionwindow();
void forwardmotion(vector<int>&);
void backwardmotion(vector<int>&);
void endingwindow();
bool winner=false;
int main()
{
	startingwindow();
	instructionwindow();
	
	setup();
	while(!gameover)
	playwindow();
	endingwindow();
}
void startingwindow()
{
	cout<<"Enter the number of the rows you want to play(more the number of rows, harder it will be)(The max capacity is 40 and minimum capacity is 3)\n";
	cin>>N;
	system("cls");
}
void instructionwindow()
{
	srand(time(0));
	generatematrix(N);
	system("cls");
	cout<<setw(3)<<"1) "<<"You will be represented by Y.\n";
	cout<<setw(3)<<"2) "<<"Your task is to reach to the other end of the matrix without striking to the obstacle(*).\n";
	cout<<setw(3)<<"3) "<<"Four sides motions are available.\n";
	cout<<setw(3)<<"4) "<<"Please continue by pressing return key.\n";
	while(1)
	{
		if(kbhit())
		{
			if(getch()==13)
			break;
		}
	}
	system("cls");
}
void setup()
{
	player.first=0;
	player.second=width/2;
	providedirection();
}
void playwindow()
{
	system("cls");
	movedanger();
	for(auto i=0;i<3;i++)
	moveplayer();
	showmatrix();
	logic();
	Sleep(300);
}
void showmatrix()
{
	for(auto j=0;j<width;j++)
	{
		if(player.first==0 and player.second==j)
		cout<<"Y";
		else
		cout<<' ';
	}
	cout<<endl;
	for(auto i=1;i<N-1;i++)
	{
		for(auto j=0;j<width;j++)
		{
			if(i==player.first and j==player.second)
			{
				cout<<"Y";
				continue;
			}
			if(head[i][j])
			{
				cout<<"*";
				continue;
			}
			cout<<' ';
		}
		cout<<i<<endl;
	}
	for(auto j=0;j<width;j++)
	{
		if(player.first==N-1 and player.second==j)
		cout<<"Y";
		else
		cout<<' ';
	}
}
void logic()
{
	if(player.first==N-1)
	{
		winner=true;
		gameover=true;
	}
	if(head[player.first][player.second] and player.first and player.first!=N-1)
	{
		gameover=true;
	}
}
void moveplayer()
{
	if(kbhit())
	{
		char A=getch();
		switch(A)
		{
			case 'W':
			case 'w':
			case 72:
			if(player.first!=0)
			player.first--;
			break;
			case 'A':
			case 'a':
			case 75:
			if(player.second!=0)
			player.second--;
			break;
			case 'D':
			case 'd':
			case 77:
			if(player.second!=width-1)
			player.second++;
			break;
			case 'S':
			case 's':
			case 80:
			if(player.first!=N-1)
			player.first++;
		}
	}
}
void movedanger()
{
	for(auto i=1;i<N-1;i++)
	{
		if(direction[i])
		forwardmotion(head[i]);
		else
		backwardmotion(head[i]);
	}
}
void providedirection()
{
	for(auto i=0;i<80;i++)
	{
		direction[i]=rand()%2;
	}
}
void generatematrix(int N)
{
	for(auto i=0;i<N;i++)
	{
		vector<int> vt;
		float count=0;
		for(auto j=0;j<width;j++)
		{
			int A=rand()%2;
			if(A)
			count++;
			if(count>=0.3*width)
			A=0;
			vt.emplace_back(A);
		}
		head.emplace_back(vt);
	}
}
void forwardmotion(vector<int> &vt)
{
	int i=vt.at(vt.size()-1);
	vector<int> vt2;
	vt2.emplace_back(i);
	for(auto it:vt)
	vt2.emplace_back(it);
	vt2.pop_back();
	vt=vt2;
}
void backwardmotion(vector<int> &vt)
{
	int i=vt[0];
	vector<int> vt2;
	for(auto it=1;it<vt.size();it++)
	{
		vt2.emplace_back(vt[it]);
	}
	vt2.emplace_back(i);
	vt=vt2;
}
void endingwindow()
{
	system("cls");
	if(winner)
	{
		cout<<"Congratulation, you had successfully completed the matrix\n";
	}
	else
	{
		cout<<"Well played!! Better luck next time\n";
	}
	while(1)
	{
		if(kbhit())
		{
			if(getch()==13)
			break;
		}
	}
}

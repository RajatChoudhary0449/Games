#include<iostream>
#include<ctime>
#include<windows.h>
#include<conio.h>
#include<vector>
#include<iomanip>
using namespace std;
bool gameover=false;
bool level[11];
const int height=40,width=100;
int speed=50,lifes=3;
bool brick[height][width]={};
enum direction{
	stop=0,topleft,topright,bottomleft,bottomright
} dir=stop;
void startingwindow();
void setup(int);
void playwindow();
void placebrick(int);
pair<int,int> ball;
int board,sizeofboard=20;
void placeball();
void level1();
void ballmotion();
void boardmotion();
void endingwindow();
int main()
{
	startingwindow();
	setup(1);
	while(!gameover)
	{
		playwindow();
	}
	
	endingwindow();
}
void startingwindow()
{
	cout<<"Before starting, You can read the instructions:\n";
	cout<<left<<setw(3)<<"1)"<<setw(20)<<"You will be given a movable board.\n";
	cout<<setw(3)<<"2)"<<setw(20)<<"You will be given 3 lifes to play.\n";
	cout<<left<<setw(3)<<"3)"<<setw(20)<<"There will be random powerups drop for you. Powerups are:\n";
	cout<<"\tI->This will increase the size of the board.\n";
	cout<<"\tD->This will decrease the size of the board.\n";
	cout<<"\tF->This will increase the speed of the ball.\n";
	cout<<"\tS->This will decrease the speed of the ball.\n";
	cout<<"Thats all start the game by pressing return key\n";
	while(1)
	{
		if(kbhit())
		{
			if(getch()==13)
			break;
		}
	}
}
void ballmotion()
{
	//Brick Handling
	if(brick[ball.first][ball.second])
	{
		if(dir==1)
		{
			dir=bottomleft;
		}
		if(dir==topright)
		{
			dir=bottomright;
		}
		brick[ball.first][ball.second]=0;
	}
	//Walls
	if(ball.first==6)
	{
		if(dir==topleft)
		dir=bottomleft;
		else if(dir==topright)
		dir=bottomright;
	}
	if(ball.second==1)
	{
		if(dir==topleft)
		dir=topright;
		if(dir==bottomleft)
		dir=bottomright;
	}
	if(ball.second==width-1)
	{
		if(dir==topright)
		{
			dir=topleft;
		}
		if(dir==bottomright)
		{
			dir=bottomleft;
		}
	}
	if(ball.first==height-4 and ball.second>=board and ball.second<=(board+sizeofboard-1))
	{
		if(dir==bottomleft)	
		dir=topleft;
		else if(dir==bottomright)
		dir=topright;
	}
	//Normal space motion
	if(dir==1)
	{
		ball.first--;
		ball.second--;
	}
	if(dir==2)
	{
		ball.first--;
		ball.second++;
	}
	if(dir==3)
	{
		ball.first++;
		ball.second--;
	}
	if(dir==4)
	{
		ball.first++;
		ball.second++;
	}
}
void boardmotion()
{
	if(kbhit())
	{
		char A=getch();
		switch(A)
		{
			case 'A':
			case 'a':
			if(board!=1)
			board--;
			break;
			case 'D':
			case 'd':
			if(board+sizeofboard-1!=width-1)
			board++;
		}
	}
}
void setup(int A)
{
	board=(width-sizeofboard)/2;//Board will be at height-3;
	placeball();
	int random=rand()%2;
	random++;
	if(random==1)
	{
		dir=topleft;
	}
	if(random==2)
	{
		dir=topright;
	}
	placebrick(A);
}
void placeball()
{
	ball.first=height-4;
	ball.second=width/2;
}
void placebrick(int A)
{
	if(A==1)
	{
		for(auto i=6;i<10;i++)
		{
			for(auto j=5;j<20;j++)
			{
				brick[i][j]=1;
			}
			for(auto j=70;j<90;j++)
			{
				brick[i][j]=1;
			}
		}
	}
}
void showbox()
{
	for(auto i=0;i<height;i++)
	{
		
		for(auto j=0;j<width;j++)
		{
			if(i==0 or j==0 or i==height-1 or j==width-1)
			{
				cout<<'#';
				continue;
			}
			
			if(ball.first==i and ball.second==j)
			{
				cout<<"O";
				continue;
			}
			if(brick[i][j])
			{
				cout<<'-';
				continue;
			}
			if(i==height-3 and (j>=board and j<=board+sizeofboard))
			{
				cout<<"=";
				continue;
			}
			cout<<' ';
		}
		if(i!=height-1)
		cout<<endl;
	}
}
void logic()
{
	if(ball.first>=height-2)
	gameover=true;
}
void playwindow()
{
	if(!level[1])
	{
		level1();
	}
	
}
void level1()
{
	ballmotion();
	showbox();
	logic();
	ballmotion();
	for(auto it=5;it>0;it--)
	boardmotion();
	Sleep(speed);
	system("cls");
}
void endingwindow()
{
	system("cls");
	cout<<"Well played!! You completed 0 levels";
	while(1)
	{
		if(kbhit())
		{
			if(getch()==13)
			break;
		}
	}
}

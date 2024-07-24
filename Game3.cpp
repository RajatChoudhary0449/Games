#include<iostream>
#include<ctime>
#include<conio.h>
#include<windows.h>
#include<iomanip>
using namespace std;
const int height=20,width=70,sizeofboard=6;
bool gameover=false;
void instructionwindow();
void playwindow();
void endingwindow();
void logic();
void showmatrix();
void intermediatesetup();
void moveboard();
void moveup(int&);
void movedown(int&);
bool getposition();
void placeball();
bool winner{false};
pair<int,int> ball;
int board1=1,board2=1;
enum direction{
	stop=0,topleft,topright,bottomleft,bottomright
}dir=direction::stop;
int main()
{
	srand(time(0));
	instructionwindow();
	while(!gameover)
	{
		playwindow();
	}
	endingwindow();
}
void instructionwindow()
{
	cout<<"Welcome to the game, Please read the instructions before proceeding to the game\n";
	cout<<setw(3)<<"1)"<<"The two player will have a fix sized board which is restricted to ";
	cout<<"two motions\n";
	cout<<setw(3)<<"2)"<<"The runner will be decided by the position of the ball if the ball is"
	<<"in the left half only the left board can move \n"<<setw(3)<<"3)"<<" if the ball is in the right half only the"
	<<" right board will move\n";
	cout<<"W/w for up movement\nS/s for down movement\n";
	cout<<"That's all start the game by pressing return key\n";
	while(1)
	{
		if(kbhit())
		{
			if(getch()==13)
			break;
		}
	}
	placeball();
	intermediatesetup();
}
void intermediatesetup()
{
	int i=rand()%4;
	i+=1;
	if(i==1)
	{
		dir=direction::topleft;
	}
	else if(i==2)
	{
		dir=direction::topright;
	}
	else if(i==3)
	{
		dir=direction::bottomleft;
	}
	else
	dir=direction::bottomright;
}
void playwindow()
{
	system("cls");
	showmatrix();
	logic();
	moveboard();
	Sleep(50);
}
void placeball()
{
//	auto h=rand()%(height-1);
//	h++;
//	auto w=rand()%(width-3);
//	w+=2;
//	ball.first=h;
//	ball.second=w;
	ball.first=height/2;
	ball.second=width/2;
}
void logic()
{
	//Wall collisions
	if(dir==topleft and ball.first==1)
	{
		dir=bottomleft;
	}
	if(dir==topright and ball.first==1)
	{
		dir=bottomright;
	}
	if(dir==bottomleft and ball.first==height-2)
	{
		dir=topleft;
	}
	if(dir==bottomright and ball.first==height-2)
	{
		dir=topright;
	}
	//Board collision
	if(getposition())
	{
		if(ball.second==2 and (ball.first>=board1 and ball.first<=board1+sizeofboard-1))
		{
			if(dir==topleft)
			dir=topright;
			if(dir==bottomleft)
			dir=bottomright;
		}
	}
	else
	{
		if(ball.second==width-3 and (ball.first>=board2 and ball.first<=board2+sizeofboard-1))
		{
			if(dir==topright)
			dir=topleft;
			if(dir==bottomright)
			dir=bottomleft;
		}
	}
	//Terminating condition
	if(ball.second<=1 or ball.second>=width-2)
	{
		gameover=true;
		if(ball.second<=2)
		{
			winner=true;
		}
	}
}
void moveboard()
{
	if(dir==0)
	return;
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
	if(getposition())
	{
		if(kbhit())
		{
			switch(getch())
			{
				case 'W':
				case 'w':
				case 72:
				moveup(board1);
				break;
				case 'S':
				case 's':
				case 80:
				movedown(board1);
			}
		}
	}
	else
	{
		if(kbhit())
		{
			switch(getch())
			{
				case 'W':
				case 'w':
				case 72:
				moveup(board2);
				break;
				case 'S':
				case 's':
				case 80:
				movedown(board2);
			}
		}
	}
}
void moveup(int& A)
{
	if(A==1)
	return;
	A--;
}
void movedown(int& A)
{
	if(A+sizeofboard-1==height-2)
	return;
	A++;
}
void showmatrix()
{
	for(auto i=0;i<height;i++)
	{
		for(auto j=0;j<width;j++)
		{
			if(i==0 or i==height-1 )
			{
				cout<<"#";
				continue;
			}
			if(i==ball.first and j==ball.second)
			{
				cout<<"O";
				continue;
			}
			if(j==1 or j==width-2)
			{
				if(j==1)
				{
					if(i<=board1+sizeofboard-1 and i>=board1)
					{
						cout<<"|";
						continue;
					}
				}
				else
				{
					if(i<=board2+sizeofboard-1 and i>=board2)
					{
						cout<<"|";
						continue;
					}
				}
			}
			cout<<' ';
		}
		cout<<endl;
	}
}
void endingwindow()
{
	system("cls");
	if(winner)
	cout<<"The right side(player2) won the game\n";
	else
	cout<<"The left side(player1) won the game\n";
	cout<<"Press enter to exit";
	while(1)
	{
		if(kbhit())
		{
			if(getch()==13)
			break;
		}
	}
}
bool getposition()
{
	if(ball.second<=width/2)
	return 1;
	return 0;
}

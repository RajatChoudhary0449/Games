#include<iostream>
#include<conio.h>//kbhit and getch
#include<iomanip>
//#include<ctime>
#include<windows.h>// Sleep(millisec)
#include<vector>
#include<fstream>
using namespace std;
enum direction{
	stop=0,left,right,up,down
} dir=direction::stop;
bool started;
const int height=20,width=20;
bool gameover=false;
int highestscore{};
vector<int>snakex,snakey;
int sizeofsnake{};
pair<int,int> player,food;
void startwindow();
void playwindow();
void movesnake();
void endingscreen();
void placeplayer();
void mazedisplay();
void placefood();
bool checkfile();
void logic();
void updatefile(int);
int fetchfile();
void changedirection();
int score=0;
int main()
{
	srand(time(0));
	startwindow();
	while(!gameover)
	playwindow();
	checkfile();
	endingscreen();
}
void placeplayer()
{
	player.first=height/2;
	player.second=width/2;
}
bool checkfile()
{
	if(fetchfile()>score)
	{
		return 0;
	}
	else
	{
		highestscore=fetchfile();
		updatefile(score);
		return 1;
	}
}
void updatefile(int A)
{
	ofstream of;
	of.open("Game2");
	of<<A;
	of.close();
}
int fetchfile()
{
	int A;
	ifstream in;
	in.open("Game2");
	if(!in)
	{
		updatefile(0);
	}
	in>>A;
	return A;
}
void mazedisplay()
{
	bool snakeshown[sizeofsnake]{false};
	bool printed=false;
	for(auto i=0;i<height;i++)
	{
		for(auto j=0;j<width;j++)
		{
			printed=false;
			if(i==0 or j==0 or i==height-1 or j==height-1)
			{
				cout<<"#";
				continue;
			}
			if(player.first==i and player.second==j)
			{
				cout<<"O";
				continue;
			}
			if(food.first==i and food.second==j)
			{
				cout<<"F";
				continue;
			}
			for(auto k=sizeofsnake-1;k>=0;k--)
			{
				if(snakex[snakex.size()-1-k]==i and snakey[snakey.size()-1-k]==j and snakeshown[k]==0)
				{
					cout<<"o";
					snakeshown[k]=1;
					printed=true;
					continue;
				}
			}
			if(!printed)
			cout<<" ";
		}
		
		cout<<endl;
	}
}
void placefood()
{
	int h=(rand()%(height-3))+1;
	int w=(rand()%(width-3))+1;
	bool check=false;
	while(1)
	{
		check=false;
		for(auto i=0;i<sizeofsnake;i++)
		{
			if(h==snakex[snakex.size()-1+i] and w==snakey[snakey.size()-1+i])
			{
				h=(rand()%(height-3))+1;
				w=(rand()%(width-3))+1;
				check=true;
			}
			if(check)
			break;
		}
		if(!check)
		{
			break;
		}
	}
	food.first=h;
	food.second=w;
}
void playwindow()
{
	system("cls");
	if(kbhit())
	changedirection();
	system("cls");
	movesnake();
	logic();
	if(!started)
	{
		cout<<"Choose the direction you want to go first:\n";
		cout<<"W for Up\nA for Left\t D for right \nS for down\n";
	}
	cout<<"The score is "<<score<<endl;
	cout<<"The highest score is "<<fetchfile()<<endl;
	mazedisplay();
	
	Sleep(100);
}
void startwindow()
{
	placeplayer();
	placefood();
	cout<<"Important points to note down are:\n";
	cout<<setw(5)<<"1) "<<"The snake will keep on increasing its size until unless it will hit with itself.\n";
	cout<<setw(5)<<"2) "<<"When the snake will interact with the food F it will increase its size.\n";
	cout<<setw(5)<<"3) "<<"You can pause anytime using the p key or escape key or space bar.\n";
	cout<<setw(5)<<"4) "<<"The controllers are :"<<endl;
	cout<<setw(6)<<setfill(' ')<<setw(3)<<"\t"<<"W/w for up"<<endl;
	cout<<setw(3)<<setfill(' ')<<setw(3)<<"A/a for left"<<"\t"<<"D/d for right\n";
	cout<<setw(6)<<setfill(' ')<<"\t"<<"S/s for down"<<endl;
	cout<<"That's all you can start the game by pressing return key";
	while(1)
	{
		if(kbhit())
		{
			if(getch()==13)
			break;
		}
	}
}
void endingscreen()
{
	system("cls");
	if(checkfile())
	{
		cout<<"Congrats you have achieved the highest score this time\n";
		cout<<"Your Score: "<<score<<endl;
	}
	else
	{
		cout<<"Your Score: "<<score<<endl;
		cout<<"Highest Score: "<<fetchfile()<<endl;
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
void changedirection()
{
	direction dt;
	if(kbhit())
	{
		char A=getch();
		switch(A)
		{
			case 'W':
			case 'w':
			case 72:
			case '8':
			if(dir!=direction::down)
			dir=direction::up;
			break;
			case 'A':
			case 'a':
			case 75:
			case '4':
			if(dir!=direction::right)
			dir=direction::left;
			break;
			case 'D':
			case 'd':
			case 77:
			case '6':
			if(dir!=direction::left)
			dir=direction::right;
			break;
			case 'S':
			case 's':
			case 80:
			case '2':
			if(dir!=direction::up)
			dir=direction::down;
			break;
			case 27:
			case 'p':
			case 32:
			dt=dir;
			dir=direction::stop;
			while(1)
			{
				system("cls");
				mazedisplay();
				
				if(kbhit())
				{
					char A=getch();
					if(A==27 or A=='p' or A==32)
					{
						dir=dt;
						break;
					}
				}
				Sleep(1000);
			}
		}
	}
}
void movesnake()
{
	if(dir)
	{
		snakex.emplace_back(player.first);
		snakey.emplace_back(player.second);
	}
	if(dir==0)
	{
		return;
	}
	if(dir==1)
	{
		if(player.second==1)
		player.second=width-2;
		else
		player.second--;
	}
	else if(dir==2)
	{
		if(player.second==width-2)
		player.second=1;
		else
		player.second++;
	}
	else if(dir==3)
	{
		if(player.first==1)
		player.first=height-2;
		else
		player.first--;
	}
	else
	{
		if(player.first==height-2)
		player.first=1;
		else
		player.first++;
	}
	
}
void logic()
{
	if(dir!=0)
	started=true;
	if(player.first==0 or player.second==0 or player.first==height-1 or player.second==width-1)
	{
		gameover=true;
		return;
	}
	if(player==food)
	{
		sizeofsnake++;
		placefood();
		score+=10;
	}
	for(auto i=sizeofsnake-1;i>=0;i--)
	{
		if(snakex[snakex.size()-1-i]==player.first and snakey[snakey.size()-1-i]==player.second)
		{
			gameover=true;
		}
	}
}

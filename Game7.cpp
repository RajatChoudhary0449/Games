#include<iostream>
#include<iomanip>
#include<vector>
#include<queue>
#include<set>
#include<windows.h>
#include<conio.h>
#include<ctime>
using namespace std;
int row=8,col=8;
bool checkway();
bool gameover=false;
bool possibilityofmove(pair<int,int>,int);
void playwindow();
void instructionwindow();
void show();
void setup();
void logic();
void randomize();
void randomizingloop();
vector<vector<bool>> r;
vector<vector<bool>> c;
pair<int,int> player(0,0);
int main()
{
	setup();
	instructionwindow();
	while(!gameover)
	playwindow();
	cout<<"Congratulation you had completed the game";
}
void instructionwindow()
{
	cout<<"Welcome, In this game:\n";
	cout<<"P represents You\nD represents Destination\n";
	cout<<"$ represents Boundary\n| represents vertical walls\n_ represents horizontal walls\n";
	cout<<"Instructions set:\n";
	cout<<setw(4)<<"1)"<<"You cannot cross the walls and boundary.\n";
	cout<<setw(4)<<"2)"<<"You can restart the maze if you wish by pressing r or R. But note that you must be on the starting square for this purpose\n";
	cout<<setw(4)<<"3)"<<"You can move by wasd or 8426 or arrows key.\n";
	cout<<"You are ready to go press return to continue";
	while(1)
	{
		if(kbhit())
		{
			if(getch()==13)
			break;
		}
	}
}
void setup()
{
	srand(time(0));
	player.first=player.second=0;
	r.resize(col-1,vector<bool>(row,1));
	c.resize(row,vector<bool>(col-1));
	randomizingloop();
}
void playwindow()
{
	Sleep(300);
	system("cls");
	logic();
	show();
}
void logic()
{
	if(kbhit())
	{
		char p=getch();
		switch(p)
		{
			case 'w':
			case 'W':
			case 72:
			case 8:
				if(player.first and !r[player.first-1][player.second])
				player.first--;
				break;
			case 'A':
			case 'a':
			case 75:
			case '4':
				if(player.second and !c[player.first][player.second-1])
				player.second--;
				break;
			case 'D':
			case 'd':
			case 77:
			case '6':
				if(player.second!=col-1 and !c[player.first][player.second])
				player.second++;
				break;
			case 'S':
			case 's':
			case 80:
			case '2':
				if(player.first!=row-1 and !r[player.first][player.second])
				player.first++;
				break;
			case 'R':
			case 'r':
				if(player.first==0 and player.second==0)
				randomizingloop();
				break;
		}
	}
	if(player.first==row-1 and player.second==col-1)
	gameover=true;
}
bool possibilityofmove(pair<int,int> pr,int move)
{
	if(move==8)
	{
		return (pr.first and !r[pr.first-1][pr.second]);
	}
	else if(move==4)
	{
		return (pr.second and !c[pr.first][pr.second-1]);
	}
	else if(move==6)
	{
		return (pr.second!=col-1 and !c[pr.first][pr.second]);
	}
	else return (pr.first!=row-1 and !r[pr.first][pr.second]);
}
void show()
{
	for(auto j=0;j<2*col+1;j++)
	cout<<"$";
	cout<<endl;
	for(auto i=0;i<row;i++)
	{
		cout<<"$";
		for(auto j=0;j<col;j++)
		{
			if(player.first==i and player.second==j)
			cout<<"P";
			else if(i==row-1 and j==col-1)
			cout<<"D";
			else
			cout<<" ";
			if(j!=col-1 and c[i][j])
			cout<<"|";
			else if(j!=col-1)
			cout<<" ";
		}
		cout<<"$\n";
		if(i==row-1)
		{
			continue;
		}
		cout<<"$";
		for(auto j=0;j<col;j++)
		{
			if(r[i][j])
			{
				cout<<"-";
			}
			else
			{
				cout<<" ";
			}
			if(j!=col-1)
			cout<<"+";
		}
		cout<<"$\n";
	}
	for(auto j=0;j<2*col+1;j++)
	cout<<"$";
	cout<<endl;
}
bool checkway()
{
	queue<pair<int,int>> qu,qu2;
	qu.push({0,0});
	for(auto i=0;i<row*col;i++)
	{
		while(!qu.empty())
		{
			pair<int,int> pt=qu.front();
			qu.pop();
			if(possibilityofmove(pt,8))
			{
				qu2.push(pair<int,int>(pt.first-1,pt.second));
			}	
			if(possibilityofmove(pt,4))
			{
				qu2.push(pair<int,int>(pt.first,pt.second-1));
			}
			if(possibilityofmove(pt,6))
			{
				qu2.push(pair<int,int>(pt.first,pt.second+1));
			}
			if(possibilityofmove(pt,2))
			{
				qu2.push(pair<int,int>(pt.first+1,pt.second));
			}
		}
		set<pair<int,int>> st;
		while(!qu2.empty())
		{
			st.insert(qu2.front());
			qu2.pop();
		}
		for(auto it:st)
		{
			qu2.push(it);
		}
		while(!qu2.empty())
		{
			pair<int,int> pt=qu2.front();
			qu2.pop();
			if(pt.first==row-1 and pt.second==col-1)
			return true;
			qu.push(pt);
		}
	}
	return false;
}
void randomizingloop()
{
	while(1)
	{
		randomize();
		if(checkway())
		break;
	}
}
void randomize()
{
	for(auto i=0;i<r.size();i++)
	{
		for(auto j=0;j<r[i].size();j++)
		{
			r[i][j]=rand()%2;
		}
	}
	for(auto i=0;i<c.size();i++)
	{
		for(auto j=0;j<c[i].size();j++)
		{
			c[i][j]=rand()%2;
		}
	}
}

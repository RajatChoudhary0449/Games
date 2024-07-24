#include<iostream>
#include<vector>
#include<iomanip>
#include<algorithm>
#include<conio.h>//kbhit and getch()(Keyboard interaction)
#include<windows.h>//Sleep
using namespace std;
void show();
void setup();
char charteller(int,int);
int check(pair<int,int>);
int present(pair<int,int>);
bool validpos(int);
bool stringchecker(string);
pair<int,int> decode(string);
vector<pair<int,int>> combine(vector<pair<int,int>>,vector<pair<int,int>>);
string encode(pair<int,int>);
static int i=0;
bool gameover=false;
struct king{
	vector<pair<int,int>> k;
	vector<pair<int,int>> K;
	vector<pair<int,int>> move(pair<int,int>);
	vector<pair<int,int>> attack(pair<int,int>);
	void playmove(pair<int,int>,pair<int,int>);
	void capture(pair<int,int>,pair<int,int>);
}k;
struct queen{
	vector<pair<int,int>> q;
	vector<pair<int,int>> Q;
	vector<pair<int,int>> move(pair<int,int>);
	vector<pair<int,int>> attack(pair<int,int>);
	void playmove(pair<int,int>,pair<int,int>);
	void capture(pair<int,int>,pair<int,int>);
}q;
struct bishop{
	vector<pair<int,int>> b;
	vector<pair<int,int>> B;
	vector<pair<int,int>> move(pair<int,int>);
	vector<pair<int,int>> attack(pair<int,int>);
	void playmove(pair<int,int>,pair<int,int>);
	void capture(pair<int,int>,pair<int,int>);
}b;
struct knight{
	vector<pair<int,int>> n;
	vector<pair<int,int>> N;
	vector<pair<int,int>> move(pair<int,int>);
	vector<pair<int,int>> attack(pair<int,int>);
	void playmove(pair<int,int>,pair<int,int>);
	void capture(pair<int,int>,pair<int,int>);
}n;
struct rook{
	vector<pair<int,int>> r;
	vector<pair<int,int>> R;
	vector<pair<int,int>> move(pair<int,int>);
	vector<pair<int,int>> attack(pair<int,int>);
	void playmove(pair<int,int>,pair<int,int>);
	void capture(pair<int,int>,pair<int,int>);
}r;
struct pawn{
	vector<pair<int,int>> p;
	vector<pair<int,int>> P;
	vector<pair<int,int>> move(pair<int,int>);
	vector<pair<int,int>> attack(pair<int,int>);
	void playmove(pair<int,int>,pair<int,int>);
	void capture(pair<int,int>,pair<int,int>);
	void promotion(pair<int,int>,pair<int,int>);
}p;
void start();
void playwindow();
void end();
int main()
{
	setup();
	while(1)
	{
		system("cls");
		start();
		if(kbhit())
		{
			if(getch()==13)
			break;
		}
		Sleep(1000);
	}
	while(!gameover)
	playwindow();
	end();
}
void setup()
{
	for(auto i=0;i<8;i++)
	{
		p.p.emplace_back(1,i);
		p.P.emplace_back(6,i);
	}
	r.r.emplace_back(0,0);
	r.r.emplace_back(0,7);
	r.R.emplace_back(7,0);
	r.R.emplace_back(7,7);
	n.n.emplace_back(0,1);
	n.n.emplace_back(0,6);
	n.N.emplace_back(7,1);
	n.N.emplace_back(7,6);
	b.b.emplace_back(0,2);
	b.b.emplace_back(0,5);
	b.B.emplace_back(7,2);
	b.B.emplace_back(7,5);
	k.k.emplace_back(0,4);
	q.q.emplace_back(0,3);
	k.K.emplace_back(7,4);
	q.Q.emplace_back(7,3);	
}
void start()
{
	cout<<"Welcome:\n";
	cout<<"Capitals are White, and smalls are black\n";
	cout<<"K->King, Q->Queen, B->Bishop, N->Knight, R->Rook, P->Pawn\nPress return to continue:\n";
}
bool stringchecker(string st)
{
	if(st.size()>2 or !isalpha(st[0]) or !isdigit(st[1]))
	return false;
	st[0]=tolower(st[0]);
	if(st[0]>'h' or st[1]=='9' or st[1]=='0')
	return false;
	return true;
}
void playwindow()
{
	system("cls");
	show();
	static int i=0;
	string st,end;
	while(i%2==0)
	{
		cout<<"It's white to move.\n";
		cout<<"Tell the starting square: ";
		cin>>st;
		pair<int,int> pr=decode(st);
		if(!stringchecker(st))
		{
			system("cls");
			cout<<"Invalid Move, Try again:\n";
			show();
			continue;
		}
		if(!present(pr) or present(pr)>8)
		{
			system("cls");
			cout<<"Please choose your piece for the move\n";
			show();
			continue;
		}
		vector<pair<int,int>> vt,vt2;
		switch(present(pr))
		{
			case 1: vt=k.move(pr);
					vt2=k.attack(pr);
			break;
			case 2: vt=q.move(pr);
					vt2=q.attack(pr);
			break;
			case 3: vt=b.move(pr);
					vt2=b.attack(pr);
			break;
			case 4: vt=n.move(pr);
					vt2=n.attack(pr);
			break;
			case 5: vt=r.move(pr);
					vt2=r.attack(pr);
			break;
			case 6: vt=p.move(pr);
					vt2=p.attack(pr);
		}
		vector<pair<int,int>> vt3=combine(vt,vt2);
		sort(vt3.begin(),vt3.end());
		if(vt3.size()==0)
		{
			system("cls");
			cout<<"There were no available moves for your selected piece, Try again with different piece\n";
			show();
			continue;
		}
		cout<<"The possible moves are: ";
		for(auto it:vt3)
		{
			cout<<encode(it);
			if(it!=vt3.back())cout<<", ";
		}
		cout<<endl;
		cout<<"Tell the ending square: ";
		cin>>end;
		bool first=find(vt.begin(),vt.end(),decode(end))!=vt.end();
		bool second=find(vt2.begin(),vt2.end(),decode(end))!=vt2.end();
		if(!first and !second)
		{
			system("cls");
			cout<<"Invalid ending square, Try again\n";
			show();
			continue;
		}
		if(first)
		{
			switch(present(decode(st)))	
			{
				case 1: k.playmove(decode(st),decode(end));
				break;
				case 2: q.playmove(decode(st),decode(end));
				break;
				case 3: b.playmove(decode(st),decode(end));
				break;
				case 4: n.playmove(decode(st),decode(end));
				break;
				case 5: r.playmove(decode(st),decode(end));
				break;
				case 6: 
				if(decode(st).first==1 and decode(end).first==0)
				p.promotion(decode(st),decode(end));
				else
				p.playmove(decode(st),decode(end));
				break;
			}
		}
		else if(second)
		{
			switch(present(decode(st)))	
			{
				case 1: k.capture(decode(st),decode(end));
				break;
				case 2: q.capture(decode(st),decode(end));
				break;
				case 3: b.capture(decode(st),decode(end));
				break;
				case 4: n.capture(decode(st),decode(end));
				break;
				case 5: r.capture(decode(st),decode(end));
				break;
				case 6: 
				if(decode(st).first==1 and decode(end).first==0)
				p.promotion(decode(st),decode(end));
				else
				p.capture(decode(st),decode(end));
				break;
			}
		}
		i++;
		break;
	}
	system("cls");
	show();
	while(i%2)
	{
		cout<<"It's black to move.\n";
		cout<<"Tell the starting square: ";
		cin>>st;
		pair<int,int> pr=decode(st);
		if(!stringchecker(st))
		{
			system("cls");
			cout<<"Invalid Move, Try again:\n";
			show();
			continue;
		}
		if(!present(pr) or present(pr)<8)
		{
			system("cls");
			cout<<"Please choose your piece for the move\n";
			show();
			continue;
		}
		vector<pair<int,int>> vt,vt2;
		switch(present(pr))
		{
			case 9: vt=k.move(pr);
					vt2=k.attack(pr);
			break;
			case 10: vt=q.move(pr);
					vt2=q.attack(pr);
			break;
			case 11: vt=b.move(pr);
					vt2=b.attack(pr);
			break;
			case 12: vt=n.move(pr);
					vt2=n.attack(pr);
			break;
			case 13: vt=r.move(pr);
					vt2=r.attack(pr);
			break;
			case 14: vt=p.move(pr);
					vt2=p.attack(pr);
		}
		vector<pair<int,int>> vt3=combine(vt,vt2);
		if(vt3.size()==0)
		{
			system("cls");
			cout<<"There were no available moves for your selected piece, Try again with different piece\n";
			show();
			continue;
		}
		cout<<"The possible moves are: ";
		for(auto it:vt3)
		{
			cout<<encode(it);
			if(it!=vt3.back())cout<<", ";
		}
		cout<<endl;
		cout<<"Tell the ending square: ";
		cin>>end;
		bool first=find(vt.begin(),vt.end(),decode(end))!=vt.end();
		bool second=find(vt2.begin(),vt2.end(),decode(end))!=vt2.end();
		if(!first and !second)
		{
			system("cls");
			cout<<"Invalid ending square, Try again\n";
			show();
			continue;
		}
		if(first)
		{
			switch(present(decode(st)))	
			{
				case 9: k.playmove(decode(st),decode(end));
				break;
				case 10: q.playmove(decode(st),decode(end));
				break;
				case 11: b.playmove(decode(st),decode(end));
				break;
				case 12: n.playmove(decode(st),decode(end));
				break;
				case 13: r.playmove(decode(st),decode(end));
				break;
				case 14:
				if(decode(st).first==6 and decode(end).first==7)
				p.promotion(decode(st),decode(end));
				else
				p.playmove(decode(st),decode(end));
				break;
			}
		}
		else if(second)
		{
			switch(present(decode(st)))	
			{
				case 9: k.capture(decode(st),decode(end));
				break;
				case 10: q.capture(decode(st),decode(end));
				break;
				case 11: b.capture(decode(st),decode(end));
				break;
				case 12: n.capture(decode(st),decode(end));
				break;
				case 13: r.capture(decode(st),decode(end));
				break;
				case 14: 
				if(decode(st).first==6 and decode(end).first==7)
				p.promotion(decode(st),decode(end));
				else
				p.capture(decode(st),decode(end));
				break;
			}
		}
		i++;
		break;
	}
}
void show()
{
	cout<<left;
	for(auto i=0;i<9;i++)
	{
		if(i)
		{
			cout<<setw(2)<<' ';
			for(auto j=0;j<8;j++)
			{
				cout<<"--";
			}
			cout<<"-";
			cout<<endl;
		}
		for(auto j=0;j<9;j++)
		{
			if(i==0 and j==0)
			{
				cout<<setw(2)<<' ';
				continue;
			}
			if(i==0)
			{
				cout<<setw(2)<<" "+string(1,(char)('a'+j-1));
				continue;
			}
			if(j==0)
			{
				cout<<left<<setw(2)<<9-i;
				continue;
			}
			cout<<'|';
			cout<<charteller(i,j);
			if(j==8)
			cout<<'|';
		}
		cout<<endl;
		if(i==8)
		{
			cout<<setw(2)<<' ';
			for(auto j=0;j<8;j++)
			{
				cout<<"--";
			}
			cout<<"-";
			cout<<endl;
		}	
	}
}
void end()
{
	cout<<"Game Over";
}
char charteller(int i,int j)
{
	i--;
	j--;
	switch(present(pair<int,int>(i,j)))
	{
		case 1: return 'K';
		case 2: return 'Q';
		case 3: return 'B';
		case 4: return 'N';
		case 5: return 'R';
		case 6: return 'P';
		case 9: return 'k';
		case 10: return 'q';
		case 11: return 'b';
		case 12: return 'n';
		case 13: return 'r';
		case 14: return 'p';
		default: return '*';
	}
}
//1 for white king, 2 for white queen, 3 for white bishop, 4 for white knight, 5 for white rook
//6 for white pawn
//9 for black king, 10 for black queen, 11 for black bishop, 12 for black knight, 13 for black rook
//14 for black pawn
int present(pair<int,int> pr)
{
	for(auto i=0;i<k.K.size();i++)
	{
		if(k.K[i]==pr)
		return 1;
	}
	for(auto i=0;i<q.Q.size();i++)
	{
		if(q.Q[i]==pr)
		return 2;
	}
	for(auto i=0;i<b.B.size();i++)
	{
		if(b.B[i]==pr)
		return 3;
	}
	for(auto i=0;i<n.N.size();i++)
	{
		if(n.N[i]==pr)
		return 4;
	}
	for(auto i=0;i<r.R.size();i++)
	{
		if(r.R[i]==pr)
		return 5;
	}
	for(auto i=0;i<p.P.size();i++)
	{
		if(p.P[i]==pr)
		return 6;
	}
	for(auto i=0;i<k.k.size();i++)
	{
		if(k.k[i]==pr)
		return 9;
	}
	for(auto i=0;i<q.q.size();i++)
	{
		if(q.q[i]==pr)
		return 10;
	}
	for(auto i=0;i<b.b.size();i++)
	{
		if(b.b[i]==pr)
		return 11;
	}
	for(auto i=0;i<n.n.size();i++)
	{
		if(n.n[i]==pr)
		return 12;
	}
	for(auto i=0;i<r.r.size();i++)
	{
		if(r.r[i]==pr)
		return 13;
	}
	for(auto i=0;i<p.p.size();i++)
	{
		if(p.p[i]==pr)
		return 14;
	}
	return 0;
}
pair<int,int> decode(string st)
{
	pair<int,int> pr;
	pr.second=st[0]-'a';
	pr.first=8-(st[1]-48);
	return pr;
}
string encode(pair<int,int> pr)
{
	string st;
	st.push_back(pr.second+'a');
	st.push_back(8-pr.first+48);
	return st;
}
vector<pair<int,int>> king::move(pair<int,int> pr)
{
	vector<pair<int,int>> vt;
	int row=pr.first;
	int col=pr.second;
	for(auto i=-1;i<2;i++)
	{
		for(auto j=-1;j<2;j++)
		{
			if(i==0 and j==0)
			continue;
			pr.first=row+i;
			pr.second=col+j;
			if(validpos(row+i) and validpos(col+j) and !present(pair<int,int>(row+i,col+j)))
			{
				vt.emplace_back(pr);
			}
		}
	}
	if(present(pr)==1)
	{
		//castling
	}
	else
	{
		
	}
	sort(vt.begin(),vt.end());
	return vt;
}
vector<pair<int,int>> queen::move(pair<int,int> pr)
{
	vector<pair<int,int>> vt;
	int row=pr.first;
	int col=pr.second;
	//up
	for(auto i=1;i<8;i++)
	{
		if(validpos(row-i) and !present(pair<int,int>(row-i,col)))
		vt.emplace_back(row-i,col);
		else break;
	}
	//down
	for(auto i=1;i<8;i++)
	{
		if(validpos(row+i) and !present(pair<int,int>(row+i,col)))
		vt.emplace_back(row+i,col);
		else break;
	}
	//left
	for(auto i=1;i<8;i++)
	{
		if(validpos(col-i) and !present(pair<int,int>(row,col-i)))
		vt.emplace_back(row,col-i);
		else break;
	}
	//right
	for(auto i=1;i<8;i++)
	{
		if(validpos(col+i) and !present(pair<int,int>(row,col+i)))
		vt.emplace_back(row,col+i);
		else break;
	}
	//topleft
	for(auto i=1;i<8;i++)
	{
		if(validpos(row-i) and validpos(col-i) and !present(pair<int,int>(row-i,col-i)))
		vt.emplace_back(row-i,col-i);
		else break;
	}
	//topright
	for(auto i=1;i<8;i++)
	{
		if(validpos(row-i) and validpos(col+i) and !present(pair<int,int>(row-i,col+i)))
		vt.emplace_back(row-i,col+i);
		else break;
	}
	//bottomleft
	for(auto i=1;i<8;i++)
	{
		if(validpos(row+i) and validpos(col-i) and !present(pair<int,int>(row+i,col-i)))
		vt.emplace_back(row+i,col-i);
		else break;
	}
	//bottomright
	for(auto i=1;i<8;i++)
	{
		if(validpos(row+i) and validpos(col+i) and !present(pair<int,int>(row+i,col+i)))
		vt.emplace_back(row+i,col+i);
		else break;
	}
	sort(vt.begin(),vt.end());
	return vt;
}
vector<pair<int,int>> bishop::move(pair<int,int> pr)
{
	vector<pair<int,int>> vt;
	int row=pr.first;
	int col=pr.second;
	for(auto i=1;i<8;i++)
	{
		if(validpos(row-i) and validpos(col-i) and !present(pair<int,int>(row-i,col-i)))
		vt.emplace_back(row-i,col-i);
		else break;
	}
	//topright
	for(auto i=1;i<8;i++)
	{
		if(validpos(row-i) and validpos(col+i) and !present(pair<int,int>(row-i,col+i)))
		vt.emplace_back(row-i,col+i);
		else break;
	}
	//bottomleft
	for(auto i=1;i<8;i++)
	{
		if(validpos(row+i) and validpos(col-i) and !present(pair<int,int>(row+i,col-i)))
		vt.emplace_back(row+i,col-i);
		else break;
	}
	//bottomright
	for(auto i=1;i<8;i++)
	{
		if(validpos(row+i) and validpos(col+i) and !present(pair<int,int>(row+i,col+i)))
		vt.emplace_back(row+i,col+i);
		else break;
	}
	sort(vt.begin(),vt.end());
	return vt;
}
vector<pair<int,int>> knight::move(pair<int,int> pr)
{
	vector<pair<int,int>> vt;
	int row=pr.first;
	int col=pr.second;
	for(auto i=-2;i<3;i+=4)
	{
		for(auto j=-1;j<2;j+=2)
		{
			if(validpos(row+i) and validpos(col+j) and !present(pair<int,int>(row+i,col+j)))
			vt.emplace_back(row+i,col+j);
			if(validpos(row+j) and validpos(col+i) and !present(pair<int,int>(row+j,col+i)))
			vt.emplace_back(row+j,col+i);
		}
	}
	sort(vt.begin(),vt.end());
	return vt;
}
vector<pair<int,int>> rook::move(pair<int,int> pr)
{
	vector<pair<int,int>> vt;
	int row=pr.first;
	int col=pr.second;
	//up
	for(auto i=1;i<8;i++)
	{
		if(validpos(row-i) and !present(pair<int,int>(row-i,col)))
		vt.emplace_back(row-i,col);
		else break;
	}
	//down
	for(auto i=1;i<8;i++)
	{
		if(validpos(row+i) and !present(pair<int,int>(row+i,col)))
		vt.emplace_back(row+i,col);
		else break;
	}
	//left
	for(auto i=1;i<8;i++)
	{
		if(validpos(col-i) and !present(pair<int,int>(row,col-i)))
		vt.emplace_back(row,col-i);
		else break;
	}
	//right
	for(auto i=1;i<8;i++)
	{
		if(validpos(col+i) and !present(pair<int,int>(row,col+i)))
		vt.emplace_back(row,col+i);
		else break;
	}
	sort(vt.begin(),vt.end());
	return vt;
}
vector<pair<int,int>> pawn::move(pair<int,int> pr)
{
	int row=pr.first;
	int col=pr.second;
	vector<pair<int,int>> vt;
	if(present(pair<int,int>(row,col))<9)
	{
		if(validpos(row-1) and !present(pair<int,int>(row-1,col)))
		vt.emplace_back(row-1,col);
		if(row==6)
		{
			if(!present(pair<int,int>(row-2,col)) and !present(pair<int,int>(row-1,col)))
			vt.emplace_back(row-2,col);
		}
	}
	else
	{
		if(validpos(row+1) and !present(pair<int,int>(row+1,col)))
		vt.emplace_back(row+1,col);
		if(row==1)
		{
			if(!present(pair<int,int>(row+1,col)) and !present(pair<int,int>(row+2,col)))
			vt.emplace_back(row+2,col);
		}
	}
	sort(vt.begin(),vt.end());
	return vt;
}
bool validpos(int i)
{
	if(i<8 and i>=0)
	return true;
	return false;
}
vector<pair<int,int>> king::attack(pair<int,int> pr)
{
	vector<pair<int,int>> vt;
	int row=pr.first;
	int col=pr.second;
	if(present(pr)==1)
	{
		for(auto i=-1;i<2;i++)
		{
			for(auto j=-1;j<2;j++)
			{
				if(i==0 and j==0)
				continue;
				if(validpos(row+i) and validpos(col+i) and present(pair<int,int>(row+i,col+j))>8)
				vt.emplace_back(pair<int,int>(row+i,col+j));
			}
		}
	}
	else
	{
		for(auto i=-1;i<2;i++)
		{
			for(auto j=-1;j<2;j++)
			{
				if(i==0 and j==0)
				continue;
				if(validpos(row+i) and validpos(col+j) and present(pair<int,int>(pr.first+i,pr.second+j))<8 and present(pair<int,int>(pr.first+i,pr.second+j)))
				vt.emplace_back(pair<int,int>(row+i,col+j));
			}
		}
	}
	sort(vt.begin(),vt.end());
	return vt;
}
vector<pair<int,int>> queen::attack(pair<int,int> pr)
{
	vector<pair<int,int>> vt;
	int row=pr.first;
	int col=pr.second;
	bool white=(present(pr)==2);
	if(white)
	{
		//up
		for(auto i=1;i<8;i++)
		{
			if(validpos(row-i) and !present(pair<int,int>(row-i,col)))
			continue;
			if(!validpos(row-i))
			break;
			if(validpos(row-i) and present(pair<int,int>(row-i,col))>8)
			vt.emplace_back(row-i,col);
			break;
		}
		//down
		for(auto i=1;i<8;i++)
		{
			if(validpos(row+i) and !present(pair<int,int>(row+i,col)))
			continue;
			if(!validpos(row+i))
			break;
			if(validpos(row+i) and present(pair<int,int>(row+i,col))>8)
			vt.emplace_back(row+i,col);
			break;
		}
		//left
		for(auto i=1;i<8;i++)
		{
			if(validpos(col-i) and present(pair<int,int>(row,col-i))==0)
			continue;
			if(!validpos(col-i))
			break;
			if(validpos(col-i) and present(pair<int,int>(row,col-i))>8)
			vt.emplace_back(row,col-i);	
			break;
		}
		//right
		for(auto i=1;i<8;i++)
		{
			if(validpos(col+i) and present(pair<int,int>(row,col+i))==0)
			continue;
			if(!validpos(col+i))
			break;
			if(validpos(col+i) and present(pair<int,int>(row,col+i))>8)
			vt.emplace_back(row,col+i);
			break;
		}
		//topleft
		for(auto i=1;i<8;i++)
		{
			if(validpos(col-i) and validpos(row-i) and !present(pair<int,int>(row-i,col-i)))
			continue;
			if(!validpos(col-i) or !validpos(row-i))
			break;
			if(validpos(col-i) and validpos(row-i) and present(pair<int,int>(row-i,col-i))>8)
			vt.emplace_back(row-i,col-i);
			break;
		}
		//topright
		for(auto i=1;i<8;i++)
		{
			if(validpos(col+i) and validpos(row-i) and !present(pair<int,int>(row-i,col+i)))
			continue;
			if(!validpos(col+i) or !validpos(row-i))
			break;
			if(validpos(col+i) and validpos(row-i) and present(pair<int,int>(row-i,col+i))>8)
			vt.emplace_back(row-i,col+i);
			break;
		}
		//bottomleft
		for(auto i=1;i<8;i++)
		{
			if(validpos(col-i) and validpos(row+i) and !present(pair<int,int>(row+i,col-i)))
			continue;
			if(!validpos(col-i) or !validpos(row+i))
			break;
			if(validpos(col-i) and validpos(row+i) and present(pair<int,int>(row+i,col-i))>8)
			vt.emplace_back(row+i,col-i);
			break;
		}
		//bottomright
		for(auto i=1;i<8;i++)
		{
			if(validpos(col+i) and validpos(row+i) and !present(pair<int,int>(row+i,col+i)))
			continue;
			if(!validpos(col+i) or !validpos(row+i))
			break;
			if(validpos(col+i) and validpos(row+i) and present(pair<int,int>(row+i,col+i))>8)
			vt.emplace_back(row+i,col+i);
			break;
		}
	}
	else
	{
		//up
		for(auto i=1;i<8;i++)
		{
			if(validpos(row-i) and !present(pair<int,int>(row-i,col)))
			continue;
			if(!validpos(row-i))
			break;
			if(validpos(row-i) and present(pair<int,int>(row-i,col))<8 and !present(pair<int,int>(row-i,col)))
			vt.emplace_back(row-i,col);
			break;
		}
		//down
		for(auto i=1;i<8;i++)
		{
			if(validpos(row+i) and !present(pair<int,int>(row+i,col)))
			continue;
			if(!validpos(row+i))
			break;
			if(validpos(row+i) and present(pair<int,int>(row+i,col))<8 and present(pair<int,int>(row+i,col)))
			vt.emplace_back(row+i,col);
			break;
		}
		//left
		for(auto i=1;i<8;i++)
		{
			if(validpos(col-i) and present(pair<int,int>(row,col-i))==0)
			continue;
			if(!validpos(col-i))
			break;
			if(validpos(col-i) and present(pair<int,int>(row,col-i))<8 and present(pair<int,int>(row,col-i)))
			vt.emplace_back(row,col-i);
			break;
		}
		//right
		for(auto i=1;i<8;i++)
		{
			if(validpos(col+i) and present(pair<int,int>(row,col+i))==0)
			continue;
			if(!validpos(col+i))
			break;
			if(validpos(col+i) and present(pair<int,int>(row,col+i))<8 and present(pair<int,int>(row,col+i)))
			vt.emplace_back(row,col+i);
			break;
		}
		//topleft
		for(auto i=1;i<8;i++)
		{
			if(validpos(col-i) and validpos(row-i) and !present(pair<int,int>(row-i,col-i)))
			continue;
			if(!validpos(col-i) or !validpos(row-i))
			break;
			if(validpos(col-i) and validpos(row-i) and present(pair<int,int>(row-i,col-i))<8 and present(pair<int,int>(row-i,col-i)))
			vt.emplace_back(row-i,col-i);
			break;
		}
		//topright
		for(auto i=1;i<8;i++)
		{
			if(validpos(col+i) and validpos(row-i) and !present(pair<int,int>(row-i,col+i)))
			continue;
			if(!validpos(col+i) or !validpos(row-i))
			break;
			if(validpos(col+i) and validpos(row-i) and present(pair<int,int>(row-i,col+i))<8 and present(pair<int,int>(row-i,col+i)))
			vt.emplace_back(row-i,col+i);
			break;
		}
		//bottomleft
		for(auto i=1;i<8;i++)
		{
			if(validpos(col-i) and validpos(row+i) and !present(pair<int,int>(row+i,col-i)))
			continue;
			if(!validpos(col-i) or !validpos(row+i))
			break;
			if(validpos(col-i) and validpos(row+i) and present(pair<int,int>(row+i,col-i))<8 and present(pair<int,int>(row+i,col-i)))
			vt.emplace_back(row+i,col-i);
			break;
		}
		//bottomright
		for(auto i=1;i<8;i++)
		{
			if(validpos(col+i) and validpos(row+i) and !present(pair<int,int>(row+i,col+i)))
			continue;
			if(!validpos(col+i) or !validpos(row+i))
			break;
			if(validpos(col+i) and validpos(row+i) and present(pair<int,int>(row+i,col+i))<8 and present(pair<int,int>(row+i,col+i)))
			vt.emplace_back(row+i,col+i);
			break;
		}
	}
	sort(vt.begin(),vt.end());
	return vt;
}
vector<pair<int,int>> bishop::attack(pair<int,int> pr)
{
	vector<pair<int,int>> vt;
	int row=pr.first;
	int col=pr.second;
	if(present(pr)<8)
	{
		//topleft
		for(auto i=1;i<8;i++)
		{
			if(validpos(col-i) and validpos(row-i) and !present(pair<int,int>(row-i,col-i)))
			continue;
			if(!validpos(col-i) or !validpos(row-i))
			break;
			if(validpos(col-i) and validpos(row-i) and present(pair<int,int>(row-i,col-i))>8)
			vt.emplace_back(row-i,col-i);
			break;
		}
		//topright
		for(auto i=1;i<8;i++)
		{
			if(validpos(col+i) and validpos(row-i) and !present(pair<int,int>(row-i,col+i)))
			continue;
			if(!validpos(col+i) or !validpos(row-i))
			break;
			if(validpos(col+i) and validpos(row-i) and present(pair<int,int>(row-i,col+i))>8)
			vt.emplace_back(row-i,col+i);
			break;
		}
		//bottomleft
		for(auto i=1;i<8;i++)
		{
			if(validpos(col-i) and validpos(row+i) and !present(pair<int,int>(row+i,col-i)))
			continue;
			if(!validpos(col-i) or !validpos(row+i))
			break;
			if(validpos(col-i) and validpos(row+i) and present(pair<int,int>(row+i,col-i))>8)
			vt.emplace_back(row+i,col-i);
			break;
		}
		//bottomright
		for(auto i=1;i<8;i++)
		{
			if(validpos(col+i) and validpos(row+i) and !present(pair<int,int>(row+i,col+i)))
			continue;
			if(!validpos(col+i) or !validpos(row+i))
			break;
			if(validpos(col+i) and validpos(row+i) and present(pair<int,int>(row+i,col+i))>8)
			vt.emplace_back(row+i,col+i);
			break;
		}	
	}
	else
	{
		//topleft
		for(auto i=1;i<8;i++)
		{
			if(validpos(col-i) and validpos(row-i) and !present(pair<int,int>(row-i,col-i)))
			continue;
			if(!validpos(col-i) or !validpos(row-i))
			break;
			if(validpos(col-i) and validpos(row-i) and present(pair<int,int>(row-i,col-i))<8 and present(pair<int,int>(row-i,col-i)))
			vt.emplace_back(row-i,col-i);
			break;
		}
		//topright
		for(auto i=1;i<8;i++)
		{
			if(validpos(col+i) and validpos(row-i) and !present(pair<int,int>(row-i,col+i)))
			continue;
			if(!validpos(col+i) or !validpos(row-i))
			break;
			if(validpos(col+i) and validpos(row-i) and present(pair<int,int>(row-i,col+i))<8 and present(pair<int,int>(row-i,col-i)))
			vt.emplace_back(row-i,col+i);
			break;
		}
		//bottomleft
		for(auto i=1;i<8;i++)
		{
			if(validpos(col-i) and validpos(row+i) and !present(pair<int,int>(row+i,col-i)))
			continue;
			if(!validpos(col-i) or !validpos(row+i))
			break;
			if(validpos(col-i) and validpos(row+i) and present(pair<int,int>(row+i,col-i))<8 and present(pair<int,int>(row+i,col-i)))
			vt.emplace_back(row+i,col-i);
			break;
		}
		//bottomright
		for(auto i=1;i<8;i++)
		{
			if(validpos(col+i) and validpos(row+i) and !present(pair<int,int>(row+i,col+i)))
			continue;
			if(!validpos(col+i) or !validpos(row+i))
			break;
			if(validpos(col+i) and validpos(row+i) and present(pair<int,int>(row+i,col+i))<8 and present(pair<int,int>(row+i,col+i)))
			vt.emplace_back(row+i,col+i);
			break;
		}
	}
	sort(vt.begin(),vt.end());
	return vt;
}
vector<pair<int,int>> knight::attack(pair<int,int> pr)
{
	vector<pair<int,int>> vt;
	int row=pr.first;
	int col=pr.second;
	if(present(pr)<8)
	{
		for(auto i=-2;i<3;i+=4)
		{
			for(auto j=-1;j<2;j+=2)
			{
				if(validpos(row+i) and validpos(col+j) and present(pair<int,int>(row+i,col+j))>8)
				vt.emplace_back(row+i,col+j);
				if(validpos(row+j) and validpos(col+i) and present(pair<int,int>(row+i,col+j))>8)
				vt.emplace_back(row+j,col+i);
			}
		}
	}
	else
	{
		for(auto i=-2;i<3;i+=4)
		{
			for(auto j=-1;j<2;j+=2)
			{
				if(validpos(row+i) and validpos(col+j) and present(pair<int,int>(row+i,col+j))<8 and present(pair<int,int>(row+i,col+j)))
				vt.emplace_back(row+i,col+j);
				if(validpos(row+j) and validpos(col+i) and present(pair<int,int>(row+j,col+i))<8 and present(pair<int,int>(row+j,col+i)))
				vt.emplace_back(row+j,col+i);
			}
		}
	}
	sort(vt.begin(),vt.end());
	return vt;
}
vector<pair<int,int>> rook::attack(pair<int,int> pr)
{
	vector<pair<int,int>> vt;
	int row=pr.first;
	int col=pr.second;
	if(present(pr)<8)		
	{
		//up
		for(auto i=1;i<8;i++)
		{
			if(validpos(row-i) and !present(pair<int,int>(row-i,col)))
			continue;
			if(!validpos(row-i))
			break;
			if(validpos(row-i) and present(pair<int,int>(row-i,col))>8)
			vt.emplace_back(row-i,col);
			break;
		}
		//down
		for(auto i=1;i<8;i++)
		{
			if(validpos(row+i) and !present(pair<int,int>(row+i,col)))
			continue;
			if(!validpos(row+i))
			break;
			if(validpos(row+i) and present(pair<int,int>(row+i,col))>8)
			vt.emplace_back(row+i,col);
			break;
		}
		//left
		for(auto i=1;i<8;i++)
		{
			if(validpos(col-i) and present(pair<int,int>(row,col-i))==0)
			continue;
			if(!validpos(col-i))
			break;
			if(validpos(col-i) and present(pair<int,int>(row,col-i))>8)
			vt.emplace_back(row,col-i);
			break;
		}
		//right
		for(auto i=1;i<8;i++)
		{
			if(validpos(col+i) and present(pair<int,int>(row,col+i))==0)
			continue;
			if(!validpos(col+i))
			break;
			if(validpos(col+i) and present(pair<int,int>(row,col+i))>8)
			vt.emplace_back(row,col+i);
			break;
		}
	}
	else
	{
		//up
		for(auto i=1;i<8;i++)
		{
			if(validpos(row-i) and !present(pair<int,int>(row-i,col)))
			continue;
			if(!validpos(row-i))
			break;
			if(validpos(row-i) and present(pair<int,int>(row-i,col))<8 and present(pair<int,int>(row-i,col)))
			vt.emplace_back(row-i,col);
			break;
		}
		//down
		for(auto i=1;i<8;i++)
		{
			if(validpos(row+i) and !present(pair<int,int>(row+i,col)))
			continue;
			if(!validpos(row+i))
			break;
			if(validpos(row+i) and present(pair<int,int>(row+i,col))<8 and present(pair<int,int>(row+i,col)))
			vt.emplace_back(row+i,col);
			break;
		}
		//left
		for(auto i=1;i<8;i++)
		{
			if(validpos(col-i) and present(pair<int,int>(row,col-i))==0)
			continue;
			if(!validpos(col-i))
			break;
			if(validpos(col-i) and present(pair<int,int>(row,col-i))<8 and present(pair<int,int>(row,col-i)))
			vt.emplace_back(row,col-i);
			break;
		}
		//right
		for(auto i=1;i<8;i++)
		{
			if(validpos(col+i) and present(pair<int,int>(row,col+i))==0)
			continue;
			if(!validpos(col+i))
			break;
			if(validpos(col+i) and present(pair<int,int>(row,col+i))<8 and present(pair<int,int>(row,col+i)))
			vt.emplace_back(row,col+i);
			break;
		}	
	}
	sort(vt.begin(),vt.end());
	return vt;
}
vector<pair<int,int>> pawn::attack(pair<int,int> pr)
{
	vector<pair<int,int>> vt;
	int row=pr.first;
	int col=pr.second;
	if(present(pr)<8)
	{
		if(validpos(row-1) and validpos(col-1) and present(pair<int,int>(row-1,col-1))>8)
		vt.emplace_back(row-1,col-1);
		if(validpos(row-1) and validpos(col+1) and present(pair<int,int>(row-1,col+1))>8)
		vt.emplace_back(row-1,col+1);
	}
	else
	{
		if(validpos(row+1) and validpos(col-1) and present(pair<int,int>(row+1,col-1))<8 and present(pair<int,int>(row+1,col-1)))
		vt.emplace_back(row+1,col-1);
		if(validpos(row+1) and validpos(col+1) and present(pair<int,int>(row+1,col+1))<8 and present(pair<int,int>(row+1,col+1)))
		vt.emplace_back(row+1,col+1);
	}
	sort(vt.begin(),vt.end());
	return vt;
}
void king::playmove(pair<int,int> pr, pair<int,int> pr2)
{
	if(present(pr)<8)
	{
		for(auto i=0;i<K.size();i++)
		{
			if(K[i]==pr)
			{
				K[i]=pr2;
				break;
			}
		}
	}
	else
	{
		for(auto i=0;i<k.size();i++)
		{
			if(k[i]==pr)
			{
				k[i]=pr2;
				break;
			}
		}
	}
}
void queen::playmove(pair<int,int> pr, pair<int,int> pr2)
{
	if(present(pr)<8)
	{
		for(auto i=0;i<Q.size();i++)
		{
			if(Q[i]==pr)
			{
				Q[i]=pr2;
				break;
			}
		}
	}
	else
	{
		for(auto i=0;i<q.size();i++)
		{
			if(q[i]==pr)
			{
				q[i]=pr2;
				break;
			}
		}
	}
}
void bishop::playmove(pair<int,int> pr,pair<int,int> pr2)
{
	if(present(pr)<8)
	{
		for(auto i=0;i<B.size();i++)
		{
			if(B[i]==pr)
			{
				B[i]=pr2;
				break;
			}
		}
	}
	else
	{
		for(auto i=0;i<b.size();i++)
		{
			if(b[i]==pr)
			{
				b[i]=pr2;
				break;
			}
		}
	}
}
void knight::playmove(pair<int,int> pr,pair<int,int> pr2)
{
	if(present(pr)<8)
	{
		for(auto i=0;i<N.size();i++)
		{
			if(N[i]==pr)
			{
				N[i]=pr2;
				break;
			}
		}
	}
	else
	{
		for(auto i=0;i<n.size();i++)
		{
			if(n[i]==pr)
			{
				n[i]=pr2;
				break;
			}
		}
	}
}
void rook::playmove(pair<int,int> pr,pair<int,int> pr2)
{
	if(present(pr)<8)
	{
		for(auto i=0;i<R.size();i++)
		{
			if(R[i]==pr)
			{
				R[i]=pr2;
				break;
			}
		}
	}
	else
	{
		for(auto i=0;i<r.size();i++)
		{
			if(r[i]==pr)
			{
				r[i]=pr2;
				break;
			}
		}
	}
}
void pawn::playmove(pair<int,int> pr,pair<int,int> pr2)
{
	if(present(pr)<8)
	{
		for(auto i=0;i<P.size();i++)
		{
			if(P[i]==pr)
			{
				P[i]=pr2;
				break;
			}
		}
	}
	else
	{
		for(auto i=0;i<p.size();i++)
		{
			if(p[i]==pr)
			{
				cout<<"The pawn was earlier to "<<pr.first<<' '<<pr.second<<endl;
				cout<<"And now the pawn is on "<<pr2.first<<' '<<pr2.second<<endl;
				p[i]=pr2;
				break;
			}
		}
	}
}
vector<pair<int,int>> combine(vector<pair<int,int>> vt,vector<pair<int,int>> vt2)
{
	vector<pair<int,int>> vt3;
	for(auto it:vt)
	vt3.emplace_back(it);
	for(auto it:vt2)
	vt3.emplace_back(it);
	return vt3;
}
void king::capture(pair<int,int> pr,pair<int,int>pr2)
{
	if(present(pr2)<8)
	{
		for(auto i=0;i<q.Q.size();i++)
		{
			if(q.Q[i]==pr2)
			{
				q.Q.erase(q.Q.begin()+i);
			}
		}
		for(auto i=0;i<b.B.size();i++)
		{
			if(b.B[i]==pr2)
			{
				b.B.erase(b.B.begin()+i);
			}
		}
		for(auto i=0;i<n.N.size();i++)
		{
			if(n.N[i]==pr2)
			{
				n.N.erase(n.N.begin()+i);
			}
		}
		for(auto i=0;i<r.R.size();i++)
		{
			if(r.R[i]==pr2)
			{
				r.R.erase(r.R.begin()+i);
			}
		}
		for(auto i=0;i<p.P.size();i++)
		{
			if(p.P[i]==pr2)
			{
				p.P.erase(p.P.begin()+i);
			}
		}
	}
	else
	{
		for(auto i=0;i<q.q.size();i++)
		{
			if(q.q[i]==pr2)
			{
				q.q.erase(q.q.begin()+i);
			}
		}
		for(auto i=0;i<b.b.size();i++)
		{
			if(b.b[i]==pr2)
			{
				b.b.erase(b.b.begin()+i);
			}
		}
		for(auto i=0;i<n.n.size();i++)
		{
			if(n.n[i]==pr2)
			{
				n.n.erase(n.n.begin()+i);
			}
		}
		for(auto i=0;i<r.r.size();i++)
		{
			if(r.r[i]==pr2)
			{
				r.r.erase(r.r.begin()+i);
			}
		}
		for(auto i=0;i<p.p.size();i++)
		{
			if(p.p[i]==pr2)
			{
				p.p.erase(p.p.begin()+i);
			}
		}
	}
	playmove(pr,pr2);
}
void queen::capture(pair<int,int> pr,pair<int,int>pr2)
{
	if(present(pr2)<8)
	{
		for(auto i=0;i<q.size();i++)
		{
			if(q[i]==pr2)
			{
				q.erase(q.begin()+i);
			}
		}
		for(auto i=0;i<b.B.size();i++)
		{
			if(b.B[i]==pr2)
			{
				b.B.erase(b.B.begin()+i);
			}
		}
		for(auto i=0;i<n.N.size();i++)
		{
			if(n.N[i]==pr2)
			{
				n.N.erase(n.N.begin()+i);
			}
		}
		for(auto i=0;i<r.R.size();i++)
		{
			if(r.R[i]==pr2)
			{
				r.R.erase(r.R.begin()+i);
			}
		}
		for(auto i=0;i<p.P.size();i++)
		{
			if(p.P[i]==pr2)
			{
				p.P.erase(p.P.begin()+i);
			}
		}
	}
	else
	{
		for(auto i=0;i<Q.size();i++)
		{
			if(Q[i]==pr2)
			{
				Q.erase(Q.begin()+i);
			}
		}
		for(auto i=0;i<b.b.size();i++)
		{
			if(b.b[i]==pr2)
			{
				b.b.erase(b.b.begin()+i);
			}
		}
		for(auto i=0;i<n.n.size();i++)
		{
			if(n.n[i]==pr2)
			{
				n.n.erase(n.n.begin()+i);
			}
		}
		for(auto i=0;i<r.r.size();i++)
		{
			if(r.r[i]==pr2)
			{
				r.r.erase(r.r.begin()+i);
			}
		}
		for(auto i=0;i<p.p.size();i++)
		{
			if(p.p[i]==pr2)
			{
				p.p.erase(p.p.begin()+i);
			}
		}
	}
	playmove(pr,pr2);
}
void bishop::capture(pair<int,int> pr,pair<int,int>pr2)
{
	if(present(pr2)<8)
	{
		for(auto i=0;i<q.Q.size();i++)
		{
			if(q.Q[i]==pr2)
			{
				q.Q.erase(q.Q.begin()+i);
			}
		}
		for(auto i=0;i<b.size();i++)
		{
			if(b[i]==pr2)
			{
				b.erase(b.begin()+i);
			}
		}
		for(auto i=0;i<n.N.size();i++)
		{
			if(n.N[i]==pr2)
			{
				n.N.erase(n.N.begin()+i);
			}
		}
		for(auto i=0;i<r.R.size();i++)
		{
			if(r.R[i]==pr2)
			{
				r.R.erase(r.R.begin()+i);
			}
		}
		for(auto i=0;i<p.P.size();i++)
		{
			if(p.P[i]==pr2)
			{
				p.P.erase(p.P.begin()+i);
			}
		}
	}
	else
	{
		for(auto i=0;i<q.q.size();i++)
		{
			if(q.q[i]==pr2)
			{
				q.q.erase(q.q.begin()+i);
			}
		}
		for(auto i=0;i<B.size();i++)
		{
			if(B[i]==pr2)
			{
				B.erase(B.begin()+i);
			}
		}
		for(auto i=0;i<n.n.size();i++)
		{
			if(n.n[i]==pr2)
			{
				n.n.erase(n.n.begin()+i);
			}
		}
		for(auto i=0;i<r.r.size();i++)
		{
			if(r.r[i]==pr2)
			{
				r.r.erase(r.r.begin()+i);
			}
		}
		for(auto i=0;i<p.p.size();i++)
		{
			if(p.p[i]==pr2)
			{
				p.p.erase(p.p.begin()+i);
			}
		}
	}
	playmove(pr,pr2);
}
void knight::capture(pair<int,int> pr,pair<int,int>pr2)
{
	if(present(pr2)<8)
	{
		for(auto i=0;i<q.Q.size();i++)
		{
			if(q.Q[i]==pr2)
			{
				q.Q.erase(q.Q.begin()+i);
			}
		}
		for(auto i=0;i<b.B.size();i++)
		{
			if(b.B[i]==pr2)
			{
				b.B.erase(b.B.begin()+i);
			}
		}
		for(auto i=0;i<n.size();i++)
		{
			if(n[i]==pr2)
			{
				n.erase(n.begin()+i);
			}
		}
		for(auto i=0;i<r.R.size();i++)
		{
			if(r.R[i]==pr2)
			{
				r.R.erase(r.R.begin()+i);
			}
		}
		for(auto i=0;i<p.P.size();i++)
		{
			if(p.P[i]==pr2)
			{
				p.P.erase(p.P.begin()+i);
			}
		}
	}
	else
	{
		for(auto i=0;i<q.q.size();i++)
		{
			if(q.q[i]==pr2)
			{
				q.q.erase(q.q.begin()+i);
			}
		}
		for(auto i=0;i<b.b.size();i++)
		{
			if(b.b[i]==pr2)
			{
				b.b.erase(b.b.begin()+i);
			}
		}
		for(auto i=0;i<N.size();i++)
		{
			if(N[i]==pr2)
			{
				N.erase(N.begin()+i);
			}
		}
		for(auto i=0;i<r.r.size();i++)
		{
			if(r.r[i]==pr2)
			{
				r.r.erase(r.r.begin()+i);
			}
		}
		for(auto i=0;i<p.p.size();i++)
		{
			if(p.p[i]==pr2)
			{
				p.p.erase(p.p.begin()+i);
			}
		}
	}
	playmove(pr,pr2);
}
void rook::capture(pair<int,int> pr,pair<int,int>pr2)
{
	if(present(pr2)<8)
	{
		for(auto i=0;i<q.Q.size();i++)
		{
			if(q.Q[i]==pr2)
			{
				q.Q.erase(q.Q.begin()+i);
			}
		}
		for(auto i=0;i<b.B.size();i++)
		{
			if(b.B[i]==pr2)
			{
				b.B.erase(b.B.begin()+i);
			}
		}
		for(auto i=0;i<n.N.size();i++)
		{
			if(n.N[i]==pr2)
			{
				n.N.erase(n.N.begin()+i);
			}
		}
		for(auto i=0;i<r.size();i++)
		{
			if(r[i]==pr2)
			{
				r.erase(r.begin()+i);
			}
		}
		for(auto i=0;i<p.P.size();i++)
		{
			if(p.P[i]==pr2)
			{
				p.P.erase(p.P.begin()+i);
			}
		}
	}
	else
	{
		for(auto i=0;i<q.q.size();i++)
		{
			if(q.q[i]==pr2)
			{
				q.q.erase(q.q.begin()+i);
			}
		}
		for(auto i=0;i<b.b.size();i++)
		{
			if(b.b[i]==pr2)
			{
				b.b.erase(b.b.begin()+i);
			}
		}
		for(auto i=0;i<n.n.size();i++)
		{
			if(n.n[i]==pr2)
			{
				n.n.erase(n.n.begin()+i);
			}
		}
		for(auto i=0;i<R.size();i++)
		{
			if(R[i]==pr2)
			{
				R.erase(R.begin()+i);
			}
		}
		for(auto i=0;i<p.p.size();i++)
		{
			if(p.p[i]==pr2)
			{
				p.p.erase(p.p.begin()+i);
			}
		}
	}
	playmove(pr,pr2);
}
void pawn::capture(pair<int,int> pr,pair<int,int>pr2)
{
	if(present(pr2)<8)
	{
		for(auto i=0;i<q.Q.size();i++)
		{
			if(q.Q[i]==pr2)
			{
				q.Q.erase(q.Q.begin()+i);
			}
		}
		for(auto i=0;i<b.B.size();i++)
		{
			if(b.B[i]==pr2)
			{
				b.B.erase(b.B.begin()+i);
			}
		}
		for(auto i=0;i<n.N.size();i++)
		{
			if(n.N[i]==pr2)
			{
				n.N.erase(n.N.begin()+i);
			}
		}
		for(auto i=0;i<r.R.size();i++)
		{
			if(r.R[i]==pr2)
			{
				r.R.erase(r.R.begin()+i);
			}
		}
		for(auto i=0;i<P.size();i++)
		{
			if(P[i]==pr2)
			{
				P.erase(P.begin()+i);
			}
		}
	}
	else
	{
		for(auto i=0;i<q.q.size();i++)
		{
			if(q.q[i]==pr2)
			{
				q.q.erase(q.q.begin()+i);
			}
		}
		for(auto i=0;i<b.b.size();i++)
		{
			if(b.b[i]==pr2)
			{
				b.b.erase(b.b.begin()+i);
			}
		}
		for(auto i=0;i<n.n.size();i++)
		{
			if(n.n[i]==pr2)
			{
				n.n.erase(n.n.begin()+i);
			}
		}
		for(auto i=0;i<r.r.size();i++)
		{
			if(r.r[i]==pr2)
			{
				r.r.erase(r.r.begin()+i);
			}
		}
		for(auto i=0;i<p.size();i++)
		{
			if(p[i]==pr2)
			{
				p.erase(p.begin()+i);
			}
		}
	}
	playmove(pr,pr2);
}
void pawn::promotion(pair<int,int> pr,pair<int,int> pr2)
{
	
	int row1=pr.first;
	int col1=pr.second;
	int row2=pr2.first;
	int col2=pr2.second;
	if((pr.first==1 and pr2.first==0) or (pr.first==6 and pr2.first==7))
	{
		cout<<"Congratulation, your pawn has reached the last square. \n";
		cout<<"You can choose to make it either of the following: \n";
		char opt;
		cout<<"1) Queen\n";
		cout<<"2) Bishop\n";
		cout<<"3) Knight\n";
		cout<<"4) Rook\n";
		cin>>opt;
		if(opt>'4' or opt<'1')
		return;
		capture(pr,pr2);
		for(auto i=0;i<P.size();i++)
		{
			if(P[i]==pr2)
			P.erase(P.begin()+i);
		}
		for(auto i=0;i<p.size();i++)
		{
			if(p[i]==pr2)
			p.erase(p.begin()+i);
		}
		if(pr.first==1)
		{
			switch(opt)
			{
				case '1': q.Q.emplace_back(pr2);
				case '2': b.B.emplace_back(pr2);
				case '3': n.N.emplace_back(pr2);
				case '4': r.R.emplace_back(pr2);
			}	
		}
		else
		{
			switch(opt)
			{
				case '1': q.q.emplace_back(pr2);
				case '2': b.b.emplace_back(pr2);
				case '3': n.N.emplace_back(pr2);
				case '4': r.r.emplace_back(pr2);
			}
		}
	}
}

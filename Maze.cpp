#include<iostream>
using namespace std;
#include<stdio.h>

struct seat
{
public:
	seat(int x,int y)
		:_x(x)
		,_y(y)
	{}
	int _x;
	int _y;
};
class Maze
{
public:
	Maze(int Row,int Col,FILE*p)
		:_Row(Row)
		,_Col(Col)
	{
		_map=new char*[_Row];//动态开辟一个二级指针
		for(int i=0; i<_Row; i++)
			_map[i]=new char[_Col];
		

		for(int i=0;i<_Row; i++)
		for(int j=0; j<_Col; j++)
		{
			_map[i][j]=fgetc(p);
			if(_map[i][j]==' '||_map[i][j]=='\n')//跳过文件中的换行符和空格
				--j;
		}
	
	}
	bool IsPass(const seat &s)const
	{
		if('1'==(_map[s._x][s._y]))
			return true;
		return false;
	}
	bool PassMaze(seat&s)
	{
		if((s._x<0||s._x>=_Row)||(s._y<0||s._y>=_Col))
		{
			return true;
		}
		if(IsPass(s))
		{
			_map[s._x][s._y]= '2';
			seat left(s._x,s._y-1);//向左走
			if(PassMaze(left))
				return true;

			seat right(s._x,s._y+1);//向右走
			if(PassMaze(right))
				return true;
			
			seat up(s._x-1,s._y);//向前走
			if(PassMaze(up))
				return true;
			
			seat down(s._x+1,s._y);//向后走
			if(PassMaze(down))
				return true;
			

			_map[s._x][s._y]='3';
		}
		return false;
	}
	void Print()
	{
		for(int i=0; i<_Row;i++)
		{
			for(int j=0; j<_Col; j++)
			{
				cout<<_map[i][j];
			}
			cout<<endl;
		}
	}
	~Maze()
	{
		if(_map!=NULL)
			for(int i=0; i<_Row; i++)
			{
				delete[] _map[i];
			}
			delete [] _map; 
	}
private:
	char **_map;
	int _Row;
	int _Col;
};
void Funtest()
{
	FILE * p=fopen("2.txt","r");
	if(NULL==p)
	{
		perror("fopen");
		exit(EXIT_FAILURE);  
	}
	char Row[4];
	char Col[4];
	int _Row;
	int _Col;
	fgets(Row,4,p);//得到行数
	_Row=atoi(Row);
	fgets(Col,4,p);//得到列数
	_Col=atoi(Col);
	
	Maze m(_Row,_Col,p);
	seat s(9,6);
	if(m.PassMaze(s))
	{
		cout<<"恭喜找到迷宫有出口"<<endl;
		m.Print();
	}
	else
	{
		cout<<"失败了"<<endl;
		m.Print();
	}

	fclose(p);
}
int main()
{
	Funtest();
	system("pause");
	return 0;
}
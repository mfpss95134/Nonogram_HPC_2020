#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
using namespace std;

char line[26]={'x','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u','u'};
int md_row[26][26]=	{
					{0, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					{0, 20, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
					};
int md_col[26][26];
string rowcol;	int index=1;


bool Fix(int i, int j);
bool Fix0(int i, int j);
bool Fix1(int i, int j);
bool match(int i, int dj);


int main(int argc, char** argv) 
{
	for(int i=0;i<26;i++)
		cout << line[i] << " ";
	cout << endl;
	
	rowcol="row";
	//md_row[1][26]={0, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	cout << Fix(25, 2);
	
	return 0;
}

bool Fix(int i, int j)
{
	if(i==0 && j==0)
		return true;
		
	if(i==0 && j>=1)
		return false;
		
	return (Fix0(i,j) || Fix1(i,j));
}

bool Fix0(int i, int j)
{
	if(line[i]=='0' || line[i]=='u')
		return Fix(i-1, j);
	else
		return false;
}

bool Fix1(int i, int j)
{
	if(rowcol=="col")
	{
		int dj=md_col[index][j];
		if(j>=1 && i>=dj+1 && match(i, dj))
		{
			return Fix(i-dj-1, j-1);
		}
		else
		{
			return false;
		}
	}
	else
	{
		int dj=md_row[index][j];
		if(j>=1 && i>=dj+1 && match(i, dj))
		{
			return Fix(i-dj-1, j-1);
		}
		else
		{
			return false;
		}
	}
}

bool match(int i, int dj)
{
	for(int ii=i;ii>=i-dj;ii--)
	{
		if(line[ii]=='u')
			continue;
		else
			return false;
	}
	
	return true;
}

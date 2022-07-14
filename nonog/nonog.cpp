#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <cstring>
using namespace std;


fstream in_file("in2.txt", ios::in);
string in_line;
int tmp_num=0;
char table[26][26]={'u'}, line[26];
//stack<int> d_row[25];
//stack<int> d_col[25];
int md_row[26][26];
int md_col[26][26];
//stack<int> tmpstk, tmpstk1, tmpstk2;
stringstream ss;
string rowcol, curline;	int index=0;


bool Fix(int i, int j);
bool Fix0(int i, int j);
bool Fix1(int i, int j);
bool match(int i, int dj);

void Paint(int i, int j);
void Paintp(int i, int j);
void Paint0(int i, int j);
void Paint1(int i, int j);
void Merge(int i, int j, int dj);

int getj(int i);
void fetchline(char* ln, char* tb);


int main(int argc, char** argv) 
{
	for(int i=0;i<26;i++)
	{
		for(int j=0;j<26;j++)
		{
			if(i==0 || j==0)
				table[i][j]=' ';
			else
				table[i][j]='u';
			cout << table[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	
	
	
	getline(in_file, in_line);	// READ DOLLAR SIGN
	for(int i=1;i<=25;i++)	// READ EACH COLUMN
	{
		getline(in_file, in_line);
		cout << in_line << endl;
		
		ss.str("");
		ss.clear();
		ss << in_line;
		
		for(int j=1;ss >> tmp_num;j++)
		{
			md_col[i][j]=tmp_num;
		}
	}
	
	for(int i=1;i<=25;i++)	// READ EACH ROW
	{
		getline(in_file, in_line);
		cout << in_line << endl;
		
		ss.str("");
		ss.clear();
		ss << in_line;
		
		for(int j=1;ss >> tmp_num;j++)
		{
			md_row[i][j]=tmp_num;
		}
	}
	
	
	/////////////////////////////
	cout << endl << endl << endl;
	/////////////////////////////
	
	rowcol="row";
	for(int i=1;i<=25;i++)
	{
		index=i;
		strcpy(line, table[i]);
		Paint(24, 3);
	}
	
	
	for(int i=1;i<=25;i++)
	{
		for(int j=1;j<=25;j++)
		{
			if(md_col[i][j]!=0)
				cout << md_col[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	
	for(int i=1;i<=25;i++)
	{
		for(int j=1;j<=25;j++)
		{
			if(md_row[i][j]!=0)
				cout << md_row[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	
	
	return 0;
}



bool Fix(int i, int j)
{
	if(i==0 && j==0)
		return true;
		
	if(i==0 && j>=1)
		return false;
		
	return (Fix0(i, j) || Fix1(i, j));
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



void Paint(int i, int j)
{
	if(i==0)
	{
		return;
	} 
	else
	{
		return Paintp(i, j);
	}
	
	//return;
}

void Paintp(int i, int j)
{
	if(Fix0(i, j) && !Fix(i, j))
	{
		return Paint0(i, j);
	}
	else if(!Fix0(i, j) && Fix1(i, j))
	{
		return Paint1(i, j); 
	}
	else
	{
		if(rowcol=="col")
		{
			int dj=md_col[index][j];
			return Merge(i, j, dj);	//Merge(Paint0(i, j), Paint1(i, j))
		}
		else
		{
			int dj=md_row[index][j];
			return Merge(i, j, dj);	//Merge(Paint0(i, j), Paint1(i, j))
		}	
	}
	
	//return;
}

void Paint0(int i, int j)
{
	line[i]='0';
	return Paint(i-1, j); //0
	
	//return;
}

void Paint1(int i, int j)
{
	if(rowcol=="col")
	{
		int dj=md_col[index][j];
		for(int ii=i;ii>=i-dj;ii--)
		{
			if(ii==i-dj)
			{
				line[ii]='0';
			}
			else
			{
				line[ii]='1';
			}
		}
		return Paint(i-dj-1, j-1); //1
	}
	else
	{
		int dj=md_row[index][j];
		for(int ii=i;ii>=i-dj;ii--)
		{
			if(ii==i-dj)
			{
				line[ii]='0';
			}
			else
			{
				line[ii]='1';
			}
		}
		return Paint(i-dj-1, j-1); //1
	}
	
	//return;
}

void Merge(int i, int j, int dj)
{
	char SK[26];	strcpy(SK, line);	//Paint0
	char TK[26];	strcpy(TK, line);	//Paint1
	char MK[26];	strcpy(MK, line);
	
	SK[i]='0';
	for(int ii=i;i>=i-dj;ii--)
	{
		if(ii==i-dj)
		{
			line[ii]='0';
		}
		else
		{
			line[ii]='1';
		}
	}
	
	for(int ii=1;ii<=i;ii++)
	{
		if(SK[ii]=='0' && TK[ii]=='0')
		{
			MK[ii]='0';
		}
		else if(SK[ii]=='1' && TK[ii]=='1')
		{
			MK[ii]='1';
		}	
		else
		{
			MK[ii]='u';
		}
	}
	
	strcpy(line, MK);
	
	return;
}



int getj(int i)
{
	if(rowcol=="col")
	{
		for(int ii=1;ii<=25;ii++)
		{
			if(md_col[i][ii]==0)
				return ii-1;
		}
	}
	else
	{
		for(int ii=1;ii<=25;ii++)
		{
			if(md_row[i][ii]==0)
				return ii-1;
		}
	}
}

 






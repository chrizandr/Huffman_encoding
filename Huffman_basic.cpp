#include <iostream>
#include <queue>
#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <fstream>
#include <stdio.h>
using namespace std;
struct symb
{
	string a;
	int n;
	symb* l;
	symb* r;
};
struct comp
{
	bool operator()(symb * a, symb * b) const
	{
		int x=a->n;
		int y=b->n;
		return x > y;
	}
};

class Huffman
{
private:
	map<char,int> chctrs;//frequency of all characters in infile
	map<char,string> bin;//binary string for representing each character
	string infile;//name of input file
	string outfile;//name of output file
	int k[1000000];//k has contents of total file
	int num;
	symb *root;//root node of Huffman tree
public:
	
	Huffman(string a, string b)
	{
		infile=a;
		outfile=b;
	}

	void filein()//reads contents of input file and calculates frequency of each character (into "chctrs")
	{
		char temp[100000];
		int x;
		for(x=0;x<infile.size();x++)
			temp[x]=infile[x];
		temp[x]='\0';
		num=0;
		ifstream f;
		f.open(temp);
		int m;
		while(f>>m)
		{
			k[num]=m;
			num++;
		}
		for(int i=0;i<num;i++)
		{
			char c=i;
			chctrs[c]=k[i];
		}
		f.close();
		return;
	}
	void constructtree()//constructs Huffman tree(into "root") and finds binary string of each character(into "bin")
	{
		priority_queue<symb*,vector<symb*>,comp> q;
		symb *t1,*t2,*t3;
		map<char,int>::iterator it;
		for(it=chctrs.begin(); it!=chctrs.end(); ++it)
		{
			t1=new symb();
			string s;
			s.push_back(it->first);
			t1->a=s;
			t1->n=it->second;
			t1->l=NULL;
			t1->r=NULL;
			q.push(t1);
		}
		while(q.size()>1)
		{
			
			t1=(q.top());
			q.pop();
			t2=(q.top());
			q.pop();
			t3=new symb();
			t3->n=t1->n+t2->n;
			t3->a=t1->a+t2->a;
			t3->l=t1;
			t3->r=t2;
			q.push(t3);
			
		}
		char temp[100000];
		int x;
		for(x=0;x<outfile.size();x++)
			temp[x]=outfile[x];
		temp[x]='\0';
		ofstream f;
		f.open(temp);
		for(it=chctrs.begin(); it!=chctrs.end(); ++it)//Constructing map "bin" and storing it in "decode.txt"
		{
			t1=q.top();
			bin[it->first]="";
			
			while(t1->l!=NULL&&t1->r!=NULL)
			{
				if((t1->l)->a.find(it->first)<(t1->l)->a.size())
				{
					bin[it->first]=bin[it->first]+"0";
					t1=t1->l;
				}
				else
				{
					bin[it->first]=bin[it->first]+"1";
					t1=t1->r;
				}
				
			}
			f<<bin[it->first]<<" ";
			
		}
		
		return;
	}
	
};
int main(int argc,char *argv[])
{
	string a(argv[1]);
	string b(argv[2]);
	Huffman h(a,b);
	h.filein();
	h.constructtree();
	
	return 0;
}
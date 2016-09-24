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
	char k[1000000];//k has contents of total file
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
		FILE* f;
		f=fopen(temp,"r");
		fscanf(f,"%[^EOF]s",k);
		int n=strlen(k);
		for(int i=0;i<n;i++)
		{
			chctrs[k[i]]=0;
		}
		for(int i=0;i<n;i++)
		{
			chctrs[k[i]]=chctrs[k[i]]+1;
		}
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
		FILE *f=fopen("decode.txt","w");
		for(it=chctrs.begin(); it!=chctrs.end(); ++it)//Constructing map "bin" and storing it in "decode.txt"
		{
			t1=q.top();
			bin[it->first]="1";
			
			while(t1->l!=NULL&&t1->r!=NULL)
			{
				if((t1->l)->a.find(it->first)<(t1->l)->a.size())
				{
					bin[it->first]=bin[it->first]+"1";
					t1=t1->l;
				}
				else
				{
					bin[it->first]=bin[it->first]+"0";
					t1=t1->r;
				}
				
			}
			fprintf(f,"%s:%c",bin[it->first].c_str(),it->first);

			
		}
		fclose(f);
		return;
	}
	int b2c(string s)
	{
		int x=1;
		int val=0;
		for(int i=0;i<8;i++)
		{
			if(s[i]=='1')
			{
				val=val+x;
			}
			x=x*2;
		}
		return val;
	}
	void intofile()//Takes the binary string, encodes it and prints it (into "outfile"), "bin" is also printed into a file("dec.txt")
	{
		FILE* f;
		char temp[100000];
		char content[1000000];
		int x;
		for(x=0;x<outfile.size();x++)
			temp[x]=outfile[x];
		temp[x]='\0';
		f=fopen(temp,"w");
		int n=strlen(k);
		for(int i=0;i<n;i++)
		{
			string s=bin[k[i]];
			fprintf(f,"%s",s.c_str());
		}
		fclose(f);

		f=fopen(temp,"r");
		fscanf(f,"%[^EOF]s",content);
		fclose(f);
		f=fopen(temp,"w");
		n=strlen(content);
		for(int i=0;i<n;i=i+8)
		{
			string t;
			for(int j=i;j<i+8&&j<n;j++)
			{

				t.push_back(content[j]);
				
			}
			if(t.size()<8)
			{
				FILE* u=fopen("decode.txt","a");
				int z=t.size();
				fprintf(u,"%d",z);
				fclose(u);
				for(int m=0;m<8-t.size();m++)
				{
					t.push_back('0');
				}
			}
			//cout<<t<<" : "<<t.size()<<endl;
			unsigned char c=b2c(t);
			int y=c;
			fprintf(f,"%c",c);
		}
		fclose(f);
	}
};
int main(int argc,char *argv[])
{
	if( argc == 3)
	{
		string a(argv[1]);
		string b(argv[2]);
		Huffman h(a,b);
		h.filein();
		h.constructtree();
		h.intofile();
	}
	else
		cout<<"Format ./a.out <inputfile> <outputfile>"<<endl;
	return 0;
}
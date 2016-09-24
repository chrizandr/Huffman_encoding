/*
Author : Chris Andrew
Email : chris.g14@iiits.in
This code was written for educational purposes and is free to use and modify by anyone.

Usage:
The compiled file must be called on the command line using ./<compiled_file> <input_file> <output_file>
Reads the text from <input_file> and writes the Huffman tree to <output_file>
*/

#include <iostream>
#include <queue>
#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <fstream>
#include <stdio.h>
using namespace std;

//An object that represents a charcter or a symbol in the <input_file>
struct symb
{
	string a;
	int n;
	symb* l;
	symb* r;
};

//Structure to compare the values of two 'symb' objects; Will be given to sorting function for sorting.
struct comp
{
	bool operator()(symb * a, symb * b) const
	{
		int x=a->n;
		int y=b->n;
		return x > y;
	}
};

//Huffman class constructs the Huffman tree, stores it in a dictionary and prints it to an output file
class Huffman
{
private:
	map<char,int> chctrs;			//frequency of all characters in infile
	map<char,string> bin;			//binary string for representing each character
	string infile;			//name of input file
	string outfile;			//name of output file
	int k[1000000];			//k has contents of total file, limit set to 1000000 characters
	int num;			//stores the number of characters
	symb *root;			//root node of Huffman tree
public:

	//Class constructor
	Huffman(string a, string b)
	{
		infile=a;
		outfile=b;
	}

	//Reads contents of input file and calculates frequency of each character
	void filein()
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

	//Constructs Huffman tree and finds binary string of each character
	void constructtree()
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
		{
			temp[x]=outfile[x];
		}
		temp[x]='\0';
		ofstream f;
		f.open(temp);
		for(it=chctrs.begin(); it!=chctrs.end(); ++it)
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
			cout<<bin[it->first]<<endl;
		}
		f.close();
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

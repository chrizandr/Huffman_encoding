#include <iostream>
#include <queue>
#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <fstream>
#include <stdio.h>
#include <algorithm>
using namespace std;
string c2b(int n)
{
	string s;
	int x=2;
	while(n!=0)
	{
		if(n%x==1)
		{
			s.push_back('1');
		}
		else
			s.push_back('0');
		n=n/x;
	}
	if(s.size()!=8)
	{
		int k=s.size();
		for(int i=0;i<8-k;i++)
			s.push_back('0');
	}
	//reverse(s.begin(), s.end());
	return s;
}
int main(int argc, char *argv[])
{
	if(argc==3)
	{	char *infile=argv[1];
		char *outfile=argv[2];
		char content[1000000];
		FILE *f;
		f=fopen("decode.txt","r");
		fscanf(f,"%[^EOF]s",content);
		int n=strlen(content);
		int temp=content[n]-'0';
		n--;
		map<string,char> p;
		for(int i=0;i<n;i++)
		{
			string s;
			while(content[i]!=':')
			{
				s.push_back(content[i]);
				i++;
			}
			i++;
			char c=content[i];
			p[s]=c;
		}
		fclose(f);
		f=fopen(infile,"r");
		unsigned char ucontent[1000000];
		fscanf(f,"%[^EOF]s",content);
		n=strlen(content);
		fclose(f);
		f=fopen(infile,"r");
		fscanf(f,"%[^EOF]s",ucontent);
		FILE *u=fopen(outfile,"w");
		for(int i=0;i<n;i++)
		{
			int m=ucontent[i];
			if(i==n-1)
			{
				for(int j=0;j<temp;j++)
				{
					m=m/2;
				}
			}
			string s=c2b(m);
			fprintf(u,"%s",s.c_str());
		}
		fclose(f);
		fclose(u);
		u=fopen(outfile,"r");
		fscanf(f,"%[^EOF]s",content);
		fclose(u);

		 u=fopen(outfile,"w");
		n=strlen(content);
		string s="";
		for(int i=0;i<n;i++)
		{
			s.push_back(content[i]);
			map<string,char>::iterator it;
			for(it=p.begin(); it!=p.end(); ++it)
			{
				if(it->first==s)
				{
					fprintf(u,"%c",it->second);
					s="";
				}
			}
		}
		fclose(u);

	}
	else 
		cout<<"Format ./a.out <compressed file> <output file>";
	return 0;
}
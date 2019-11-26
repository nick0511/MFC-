#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include<vector>
#include <algorithm>
using namespace std;
#define SIZE 2

typedef struct Memory
{
	int block_number;//分区号
	char job_name;//作业名
	int start_address;//起始地址
	int block_size;//分区大小
	int state;//状态 （0 1）   1：已分配 2：未分配
} memory;

vector<memory> me;

bool cmp(memory a,memory b)
{
	return a.start_address<b.start_address;
}

void FF()   //首次适应算法
{
	int flag=0;//分配成功 1  失败 0
	memory node;//申请新节点
	//input
	cout<<"作业名(一个字符):";
	char name;
	cin>>name;
	node.job_name=name;
	cout<<"作业占内存大小：";
	int u;
	cin>>u;
	node.block_size=u;
	//ff算法
	sort(me.begin(),me.end(),cmp);//地址递增排序
	vector<memory>::iterator it;
	for(it=me.begin(); it!=me.end(); it++)
	{
		if((*it).state==0)   //空闲分区链
		{
			if((*it).block_size>u)
			{
				if((*it).block_size-u<=2)
				{
					(*it).state=1;//将该分区从空闲链中移除
					(*it).job_name=name;
					flag=1;
					break;
				}
				else     //有空闲块能满足需求且有剩余
				{
					node.block_number=(*it).block_number;
					node.start_address=(*it).start_address;
					(*it).block_number+=1;
					(*it).start_address+=u;
					(*it).block_size-=u;
					node.state=1;
					me.insert(it--,node);
					flag=1;
					break;
				}
			}
		}
	}
	if(flag==1)
	{
		cout<<"分配成功！！！"<<endl;
	}
	else
		cout<<"分配失败！！！"<<endl;
}

void recovery()   //回收内存
{
	cout<<"输入要回收分区的作业名(一个字符):";
	char name;
	cin>>name;
	if(me.size()==1)
	{
		me[0].job_name=' ';
		me[0].state=0;
		cout<<"回收成功！！！"<<endl;
		return;
	}
	for(int i=0; i<me.size(); i++)
	{
		if(i==0&&me[i].job_name==name)
		{
			if(me[i+1].state==0)
			{
				me[i].block_size+=me[i+1].block_size;//合并 回收区与f2
				me[i].state=0;
				me[i].job_name=' ';
				for(int j=i+1; j<me.size()-1; j++)
				{
					me[j].job_name=me[j+1].job_name;
					me[j].start_address=me[j+1].start_address;
					me[j].block_size=me[j+1].block_size;
					me[j].state=me[j+1].state;
				}
				me.pop_back();
				cout<<"回收成功！！！"<<endl;
				break;
			}
			else
			{
				me[i].job_name=' ';
				me[i].state=0;
				cout<<"回收成功！！！"<<endl;
				break;
			}
		}
		if((i==(me.size()-1))&&me[i].job_name==name)
		{
			if(me[i-1].state==0)
			{
				me[i-1].block_size+=me[i].block_size;
				me[i-1].job_name=' ';
				me.pop_back();
				cout<<"回收成功！！！"<<endl;
				break;
			}
			else
			{
				me[i].job_name=' ';
				me[i].state=0;
				cout<<"回收成功！！！"<<endl;
				break;
			}
		}
		if(me[i].job_name==name)
		{
			if(me[i-1].state==0&&me[i+1].state==0)
			{
				me[i-1].block_size=me[i-1].block_size+me[i].block_size+me[i+1].block_size;
				me[i-1].job_name=' ';
				for(int j=i; j<me.size()-1; j++) //i+1->i i+2->i
				{
					me[j].job_name=me[j+1].job_name;
					me[j].start_address=me[j+1].start_address;
					me[j].block_size=me[j+1].block_size;
					me[j].state=me[j+1].state;
				}
				me.pop_back();
				for( j=i; j<me.size()-1; j++) // i+2->i
				{
					me[j].job_name=me[j+1].job_name;
					me[j].start_address=me[j+1].start_address;
					me[j].block_size=me[j+1].block_size;
					me[j].state=me[j+1].state;
				}
				me.pop_back();
				cout<<"回收成功！！！"<<endl;
				break;
			}
			else if(me[i-1].state==0)
			{
				me[i-1].block_size+=me[i].block_size;
				me[i-1].job_name=' ';
				for(int j=i; j<me.size()-1; j++)
				{
					me[j].job_name=me[j+1].job_name;
					me[j].start_address=me[j+1].start_address;
					me[j].block_size=me[j+1].block_size;
					me[j].state=me[j+1].state;
				}
				me.pop_back();
			}
			else if(me[i+1].state==0)
			{
				me[i].block_size+=me[i+1].block_size;
				me[i].job_name=' ';
				me[i].state=0;
				for(int j=i+1; j<me.size()-1; j++)
				{
					me[j].job_name=me[j+1].job_name;
					me[j].start_address=me[j+1].start_address;
					me[j].block_size=me[j+1].block_size;
					me[j].state=me[j+1].state;
				}
				me.pop_back();
			}
			else
			{
				me[i].job_name=' ';
				me[i].state=0;
				cout<<"回收成功！！！"<<endl;
				break;
			}
		}
	}
}

void menu()
{
	cout<<"\n\n";
	cout<<"1. 分配内存"<<endl;
	cout<<"2. 回收内存"<<endl;
	cout<<"3. 显示内存使用情况"<<endl;
	cout<<"4. 退出"<<endl;
	cout<<"\n\n";
	cout<<"请输入选择:";
}

void print()   //显示内存使用情况
{

	cout<<"分区号\t作业名\t起始地址\t分区大小\t状态"<<endl;
	vector<memory>::iterator it;
	for(it=me.begin(); it!=me.end(); it++)
	{
		cout<<(*it).block_number<<"\t"<<(*it).job_name<<"\t"<<(*it).start_address<<"\t\t"<<(*it).block_size<<"\t\t"<<(*it).state<<endl;
	}
}

int main()
{
	//初始化头结点
	memory head;
	head.block_number=0;
	head.start_address=0;
	head.block_size=1024;
	head.state=0;

	me.push_back(head);

	int sel;
	int flag=1;
	while(1)
	{
		menu();
		cin>>sel;
		switch(sel)
		{
			case 1:
				FF();
				break;
			case 2:
				recovery();
				break;
			case 3:
				print();
				break;
			case 4:
				flag=0;
				break;
		}
		if(flag==0)
			break;
	}
}

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
	int block_number;//������
	char job_name;//��ҵ��
	int start_address;//��ʼ��ַ
	int block_size;//������С
	int state;//״̬ ��0 1��   1���ѷ��� 2��δ����
} memory;

vector<memory> me;

bool cmp(memory a,memory b)
{
	return a.start_address<b.start_address;
}

void FF()   //�״���Ӧ�㷨
{
	int flag=0;//����ɹ� 1  ʧ�� 0
	memory node;//�����½ڵ�
	//input
	cout<<"��ҵ��(һ���ַ�):";
	char name;
	cin>>name;
	node.job_name=name;
	cout<<"��ҵռ�ڴ��С��";
	int u;
	cin>>u;
	node.block_size=u;
	//ff�㷨
	sort(me.begin(),me.end(),cmp);//��ַ��������
	vector<memory>::iterator it;
	for(it=me.begin(); it!=me.end(); it++)
	{
		if((*it).state==0)   //���з�����
		{
			if((*it).block_size>u)
			{
				if((*it).block_size-u<=2)
				{
					(*it).state=1;//���÷����ӿ��������Ƴ�
					(*it).job_name=name;
					flag=1;
					break;
				}
				else     //�п��п���������������ʣ��
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
		cout<<"����ɹ�������"<<endl;
	}
	else
		cout<<"����ʧ�ܣ�����"<<endl;
}

void recovery()   //�����ڴ�
{
	cout<<"����Ҫ���շ�������ҵ��(һ���ַ�):";
	char name;
	cin>>name;
	if(me.size()==1)
	{
		me[0].job_name=' ';
		me[0].state=0;
		cout<<"���ճɹ�������"<<endl;
		return;
	}
	for(int i=0; i<me.size(); i++)
	{
		if(i==0&&me[i].job_name==name)
		{
			if(me[i+1].state==0)
			{
				me[i].block_size+=me[i+1].block_size;//�ϲ� ��������f2
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
				cout<<"���ճɹ�������"<<endl;
				break;
			}
			else
			{
				me[i].job_name=' ';
				me[i].state=0;
				cout<<"���ճɹ�������"<<endl;
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
				cout<<"���ճɹ�������"<<endl;
				break;
			}
			else
			{
				me[i].job_name=' ';
				me[i].state=0;
				cout<<"���ճɹ�������"<<endl;
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
				cout<<"���ճɹ�������"<<endl;
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
				cout<<"���ճɹ�������"<<endl;
				break;
			}
		}
	}
}

void menu()
{
	cout<<"\n\n";
	cout<<"1. �����ڴ�"<<endl;
	cout<<"2. �����ڴ�"<<endl;
	cout<<"3. ��ʾ�ڴ�ʹ�����"<<endl;
	cout<<"4. �˳�"<<endl;
	cout<<"\n\n";
	cout<<"������ѡ��:";
}

void print()   //��ʾ�ڴ�ʹ�����
{

	cout<<"������\t��ҵ��\t��ʼ��ַ\t������С\t״̬"<<endl;
	vector<memory>::iterator it;
	for(it=me.begin(); it!=me.end(); it++)
	{
		cout<<(*it).block_number<<"\t"<<(*it).job_name<<"\t"<<(*it).start_address<<"\t\t"<<(*it).block_size<<"\t\t"<<(*it).state<<endl;
	}
}

int main()
{
	//��ʼ��ͷ���
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

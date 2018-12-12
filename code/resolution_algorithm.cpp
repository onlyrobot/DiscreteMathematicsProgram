/********************************************************************************
*File name:ResolutionAlgorithm.cpp                                              *
*Author:彭瑶                                                                    *
*Version:1.0                                                                    *
*Date:2018.05.10                                                                *
*Debug Environment:Visual Studio 2017                                           *
*Description:利用消解算法来判断某个合式公式是否可满足，当为可满足时输出YES，不可*
*满足时输出NO                                                                   *
*********************************************************************************/

#include<iostream>
#include<set>
using namespace std;

struct dnf //简单析取范式，包含所有逻辑变量（用链表来储存）
{
	int flag = 0; //标识逻辑变量是否含有非（!)
	char var = '\0';
	dnf *next = NULL; //下一个逻辑变量
	bool operator < (const dnf right) const
	{
		const dnf *dnf1, *dnf2;
		dnf1 = this;
		dnf2 = &right;
		while (dnf1 != NULL || dnf2 != NULL)
		{
			if (dnf1 == NULL)
			{
				return true;
			}
			else if (dnf2 == NULL)
			{
				return false;
			}
			if (dnf1->var != dnf2->var)
			{
				return dnf1->var < dnf2->var;
			}
			else if (dnf1->flag != dnf2->flag)
			{
				return dnf1->flag < dnf2->flag;
			}
			dnf1 = dnf1->next, dnf2 = dnf2->next;
		}
		return false;
	}
}; //简单析取范式

void init(set<dnf> &);
dnf *resolution(const dnf *dnf1, const dnf *dnf2);

int main()
{
	set<dnf> s1, s2, s3; //三个集合备用
	int flag;
	dnf *temp; //临时变量
	init(s1); //初始化
	//下面开始消解
	set<dnf>::iterator it1, it2, it3;
	while (true)
	{
		for (it1 = s1.begin(); it1 != s1.end(); it1++)
		{
			/*先是集合s1自消（即s1中的元素相互之间进行消解），如果消解得到的简单析取式为
			空，则结束循环，并将flag变量赋为0，否则如果集合s2和s3中不含消解得到的简单析
			取式，则添加到集合s3中*/
			for (it2 = it1, it2++; it2 != s1.end(); it2++)
			{
				//开始消解，resolution返回值为NULL或某个简单析取式
				temp = resolution(&*it1, &*it2);
				if (temp == NULL) //如果不能消解
				{
					continue;
				}
				if (temp->var == '\0') //如果消解得到的简单析取式为空，则将flag赋为0
				{
					flag = 0;
					goto end;
				}
				//否则如果集合s2和s3中不含消解得到的简单析取式，则添加到集合s3中
				else if (s1.find(*temp) == s1.end() && s2.find(*temp) == s2.end())
				{
					s3.insert(*temp);
				}
			}

			/*再让集合s1和集合s2相互消（即s1中的元素与s2中的元素之间进行消解），如果消解得到的简
			单析取式为空，则结束循环，并将flag变量赋为0，否则如果集合s2和s3中不含消解得到的简单
			析取式，则添加到集合s3中*/
			for (it3 = s2.begin(); it3 != s2.end(); it3++)
			{
				temp = resolution(&*it1, &*it3);
				if (temp == NULL) //如果不能消解
				{
					continue;
				}
				if (temp->var == '\0') //如果消解得到的简单析取式为空
				{
					flag = 0;
					goto end;
				}
				//否则如果集合s2和s3中不含消解得到的简单析取式，则添加到集合s3中
				else if (s1.find(*temp) == s1.end() && s2.find(*temp) == s2.end())
				{
					s3.insert(*temp);
				}
			}
		}
		
		//如果集合s3中没有任何元素（即无法再进行消解，则将flag赋为1）
		if (s3.size() == 0)
		{
			flag = 1; 
			goto end;
		}
		else //否则交换集合中的元素，准备下一次循环
		{
			for (it1 = s1.begin(); it1 != s1.end(); it1++)
			{
				s2.insert(*it1);
			}
			s1.clear();
			for (it1 = s3.begin(); it1 != s3.end(); it1++)
			{
				s1.insert(*it1);
			}
			s3.clear();
		}
	}
end:;
	//判断输出是否是可满足式
	if (flag == 0)
	{
		cout << "NO" << endl;
	}
	else
	{
		cout << "YES" << endl;
	}
	system("pause");
}
void init(set<dnf> &s1) //初始化
{
	char c;
	dnf *dnf_ = new dnf;
	dnf *dnf_first = dnf_;
	//不断读取解析出简单析取范式，并放入到集合s1中
	while ((c = getchar()) != '\n')
	{
		switch (c)
		{
		case '(': case ')': break;
		case '!': dnf_->flag = 1; break;
		case '|': dnf_->next = new dnf; dnf_ = dnf_->next; break;
		case '&': s1.insert(*dnf_first);
			dnf_first = dnf_ = new dnf; break;
		default: dnf_->var = c; break;
		}
	}
	s1.insert(*dnf_first); //把最后一个简单析取式添加进入集合
	
	/*
	//输出集合中的元素（用于测试）
	set<dnf>::iterator it;
	const dnf *dnf__;
	for (it = s1.begin(); it != s1.end(); it++)
	{
		dnf__ = &*it;
		while (dnf__ != NULL)
		{
			cout << dnf__->flag << dnf__->var << endl;
			dnf__ = dnf__->next;
		}
		printf("\n");
	}*/
	
}
dnf *resolution(const dnf *dnf1, const dnf *dnf2) //消解dnf1和dnf2
{
	dnf *dnf_head = new dnf;
	dnf *temp = dnf_head; //临时变量
	int flag = 0; //表示能否消解
	while (dnf1 != NULL || dnf2 != NULL)
	{
		if (dnf1 == NULL || dnf2 == NULL)
		{
			if (flag == 0) //如果之前还未消解，那么不可能消解了，直接结束循环
			{
				break;
			}
			else //将非NULL的dnf赋给消解得到的简单析取式
			{
				if (dnf1 == NULL)
				{
					*temp = *dnf2;
					dnf2 = dnf2->next;
				}
				else
				{
					*temp = *dnf1;
					dnf1 = dnf1->next;
				}
				temp->next = new dnf, temp = temp->next;
				continue;
			}
		}

		if (dnf1->var == dnf2->var && flag == 0) //如果逻辑变量相同，而且之前未消去过
		{
			if (dnf1->flag != dnf2->flag) //而且二者有不同的非（!）取值，那么消去
			{
				flag = 1;
			}
			else
			{
				temp->var = dnf1->var, temp->flag = dnf1->flag;
				temp->next = new dnf, temp = temp->next;
			}
			//判断下一个
			dnf1 = dnf1->next, dnf2 = dnf2->next;
		}
		else //如果逻辑变量不同
		{
			//先将较小的放到消解得到的简单析取式（dnf_）中，并将小的dnf指向下一个
			if (dnf1->var < dnf2->var || dnf1->var == dnf2->var && dnf1->flag < dnf2->flag)
			{
				*temp = *dnf1;
				dnf1 = dnf1->next;
			}
			else
			{
				*temp = *dnf2;
				dnf2 = dnf2->next;
			}
			temp->next = new dnf, temp = temp->next;
		}
	}
	if (flag == 0) //如果不能消解 
	{
		//释放空间
		while (dnf_head != NULL)
		{
			temp = dnf_head;
			dnf_head = dnf_head->next;
			delete temp;
		}
		return NULL;
	}
	if (temp->var == '\0')
	{
		temp = dnf_head;
		//删除没有用到的temp变量
		if (dnf_head->next != NULL)
		{
			while (temp->next->next != NULL)
			{
				temp = temp->next;
			}
			delete temp->next, temp->next = NULL;
		}
	}
	return dnf_head;
}

#include "DFS.h"




CBfsDfs::CBfsDfs(int *point,int *goal)
{
	numStep = 0;
	beg = new map;
	for (int n=0;n<N;n++)
	{
		beg->dig[n] = *(point+n);
		end.dig[n] = *(goal+n);
	}
	beg->last = NULL;
	beg->lockDir = None;

	beg->layer = 0;
}
bool CBfsDfs::Judge()
{
	int a1=numDes(&end);
	int a2=numDes(beg);
	if(a1!=a2) return 0;
	if (CheckRepeat(beg)) return 0;
	if (CheckRepeat(&end)) return 0;
	return 1;
}



map * CBfsDfs::Move(map *Map, dir Direct, bool CreateNewMap)
{
	map * NewMap; 
	//获取空闲格位置
	int i;
	for(i=0;i<N;i++)
		if(Map->dig[i]==0)
			break;
	//移动数字
	int j=i;				//j记录了0的原始位置，i记录了0换后的位置
	bool AbleMove = true;
	switch(Direct)
	{    
	case Up:  
		if(i<3)
			AbleMove=false;
		i=i+add[0];
		break;
	case Down:  
		if(i>5)
			AbleMove=false;
		i=i+add[1];
		break;
	case Left:  
		if(i%3==0)
			AbleMove=false;
		i=i+add[2];
		break;
	case Right:  
		if(i%3==2)
			AbleMove=false;
		i=i+add[3];
		break;
	};
	if(!AbleMove)//不可以移动则返回原节点
		return Map;
	if(CreateNewMap)			//创建一个新的节点
	{
		NewMap= new map();

		m_Queue.push(NewMap);

		for(int x=0;x<N;x++)
		{
			NewMap->dig[x]=Map->dig[x];
		}
	}
	else
		NewMap = Map;
	NewMap->dig[j] = NewMap->dig[i];
	NewMap->dig[i]=0;
	return NewMap;
}

bool CBfsDfs::ifSuccess(map *Map, map *end)
{
	bool suc = true;
	for(int i=0;i<N;i++)
	{
		if(Map->dig[i]!=end->dig[i])
		{
			suc = false;
			break;
		}
	}
	return suc;
}

map * CBfsDfs::BNFS(map * beg,map * end)
{
	map * p1, *p2, *p=NULL;
	bool IsSucc = false;
	queue<map *> Queue;					//创建一个队列，并指定放入队列的类型
	if(ifSuccess(beg,end))
		return beg;
	Queue.push(beg);					//放入队列中
	do
	{
		p1 = Queue.front();
		Queue.pop();
		for (int i = 0; i < 4; i++)
		{
			dir Direct=(dir)i;
			if(Direct==p1->lockDir)		//自己原来错了，这里没能理解continue的用法，continue表示：不进行这次循环，而直接进行下一次的循环
				continue;
			p2 = Move(p1,Direct,true);
			if(p2 != p1)//数码是否可以移动
			{ 
				p2->last = p1;
				switch(Direct)//设置屏蔽方向
				{
				case Up:
					p2->lockDir = Down;			//记录父节点的操作，防止又回到原状态，又走回去
					break;
				case Down:
					p2->lockDir = Up;
					break;
				case Left:
					p2->lockDir = Right;
					break;
				case Right:
					p2->lockDir = Left;
					break;
				}

				p2->layer = p1->layer+1;

				if (ifSuccess(p2,end))
				{
					p = p2;
					return p;
				}
				Queue.push(p2);
			}
		}
	}
	while(!Queue.empty() || p==NULL);
	return p;
}

map * CBfsDfs::DNFS(map *beg, map *end)
{
	int node;
	map * p1, *p2, *p=NULL;
	bool IsSucc = false;
	stack<map *> Stack_;
	if(ifSuccess(beg,end))
		return beg;
	Stack_.push(beg);
	do
	{


		p1 = Stack_.top();
		Stack_.pop();		

		node=0;

		for (int i = 0; i < 4; i++)
		{
			dir Direct=(dir)i;
			if(Direct==p1->lockDir)
				continue;
			p2 = Move(p1,Direct,true);
			if(p2 != p1)//数码是否可以移动
			{ 
				p2->last = p1;						 //记录父节点的位置
				switch(Direct)//设置屏蔽方向
				{
				case Up:
					p2->lockDir = Down;node++;
					break;
				case Down:
					p2->lockDir = Up;node++;
					break;
				case Left:
					p2->lockDir = Right;node++;
					break;
				case Right:
					p2->lockDir = Left;node++;
					break;
				}

				p2->layer = p1->layer+1;

				if (ifSuccess(p2,end))
				{
					p = p2;
					return p;
				}
				Stack_.push(p2);
			}
		}

		p2 = Stack_.top();

		if (maxlayer == p2->layer)
		{
			//node = p2->last->SonNum;
			for (;node>0;node--)	
			{
				Stack_.pop();
			}

		}
		if (Stack_.empty())
		{
			break;
		}
	}while(!Stack_.empty() || p==NULL);
	return p;
}


int CBfsDfs::numDes(map *Map)
{
	int a=0;
	for(int i=0;i<N;i++)
	{
		if(Map->dig[i]==0) continue;
		for(int j=i+1;j<N;j++)
		{
			if(Map->dig[j]==0) continue;
			if(Map->dig[j] <Map->dig[i])
				a++;
		}
	}
	return a%2;
}

void CBfsDfs::InitMaxlayer(int layer)
{
	maxlayer = layer;
}

int CBfsDfs::GetStep()
{
	return numStep;
}

double CBfsDfs::GetTime()
{
	return caltime;
}

bool CBfsDfs::CheckRepeat(map *point)
{
	for (int i=0;i<9;i++)
	{
		for (int j=i+1;j<9;j++)
		{
			if (point->dig[i] == point->dig[j])
			{
				return 1;
			}
		}

	}
	return 0;
}
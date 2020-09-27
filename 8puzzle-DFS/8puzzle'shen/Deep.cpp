#include"Deep.h"

Puzzle Puzzle::up()
{
    string::size_type loc = code.find('0');//0��λ��,��0��ʼ����
    Puzzle son;
    son.code = code;
    son.deep = deep + 1;
    if (loc>=3)
	{
        char temp = son.code[loc];  //0
        son.code[loc] = son.code[loc - 3];
        son.code[loc-3] = temp;
    }
    else{
        son.code = "";
    }
    return son;
}

Puzzle Puzzle::down()
{
    string::size_type loc = code.find('0');//0��λ��,��0��ʼ����
    Puzzle son;
    son.code = code;
    son.deep = deep + 1;
    if (loc<=5)
	{
        char temp = son.code[loc];  //0
        son.code[loc] = son.code[loc + 3];
        son.code[loc + 3] = temp;
    }
    else{
        son.code = "";
    }
    return son;
}

Puzzle Puzzle::left()
{
    string::size_type loc = code.find('0');//0��λ��,��0��ʼ����
    Puzzle son;
    son.code = code;
    son.deep = deep + 1;
    if (loc!=0&&loc!=3&&loc!=6)
	{
        char temp = son.code[loc];//��0
        son.code[loc] = son.code[loc - 1];
        son.code[loc - 1] = temp;
    }
    else{
        son.code = "";
    }
    return son;
}

Puzzle Puzzle::right()
{
    string::size_type loc = code.find('0');//0��λ��,��0��ʼ����
    Puzzle son;
    son.code = code;
    son.deep = deep + 1;
    if (loc!=2&&loc!=5&&loc!=8)
	{
        char temp = son.code[loc];  //0
        son.code[loc] = son.code[loc + 1];
        son.code[loc + 1] = temp;
    }
    else{
        son.code = "";
    }
    return son;
}

bool Puzzle::isGoal()
{
    return code == GOAL;
}

bool Puzzle::isInOpen(deque<Puzzle> &open)
{
   deque<Puzzle>::iterator it = open.begin();
    while (it != open.end())
	{
        if (code == (*it).code)
		{
            return true;
        }
        it++;
    }
    return false;
}

bool Puzzle::isInClosed(deque<Puzzle> &closed)
{
    deque<Puzzle>::iterator it = closed.begin();
    while (it!=closed.end())
	{
        if (code == (*it).code)
		{
            return true;
        }
        it++;
    }
    return false;
}

void Puzzle::show() const
{
    if (!code.empty())
	{
        cout << code[0] << code[1] << code[2] << endl
            << code[3] << code[4] << code[5] << endl
            << code[6] << code[7] << code[8] << endl << endl;
    }
    else
	{
        cout << "�յ�" << endl;
    }
}

void Puzzle::show(string code) const
{
    if (!code.empty())
	{
        cout << code[0] << code[1] << code[2] << endl
            << code[3] << code[4] << code[5] << endl
            << code[6] << code[7] << code[8] << endl << endl;
    }
    else
	{
        cout << "�յ�" << endl;
    }
}

void Puzzle::show_deque(deque<Puzzle> &m_deque) const
{
    deque<Puzzle>::iterator it = m_deque.begin();
    while (it!=m_deque.end())
    {
        (*it).show();
        it++;
    }

}

//·��
deque<Puzzle> Puzzle::showWay(deque<Puzzle> &closed)
{
    deque<Puzzle> dequeList;
    Puzzle temp = closed.back();
    dequeList.push_back(temp);
    for (int i = closed.size()-1; i >= 0;i--)
	{
        if (temp.father==closed.at(i).code)
		{
            dequeList.push_back(closed.at(i));
            temp = closed.at(i);
        }
    }
    return dequeList;
}

void Puzzle::showAnswer(deque<Puzzle> &closed)
{
    deque<Puzzle> way(showWay(closed));
    cout << "����Ҫ" << way.size() << "��" << endl;
    for (int i = way.size() - 1; i >= 0; i--)
    {
        way.at(i).show();
    }
    //���
    show(GOAL);
}
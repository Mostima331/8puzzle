
#include<iostream>
#include"queue"
#include"string"
#include<list>

using namespace std;

const string GOAL = "803214765";

class Puzzle{
private:
    
public:
    string father;
    string code;//当前状态
    int deep;
    Puzzle up();
    Puzzle down();
    Puzzle left();
    Puzzle right();
    bool isGoal();
    bool isInOpen(deque<Puzzle> &open);
    bool isInClosed(deque<Puzzle> &closed);
    void show() const;
    void show(string) const;
    void show_deque(deque<Puzzle> &) const;
    deque<Puzzle> showWay(deque<Puzzle> &closed);
    void showAnswer(deque<Puzzle> &closed);//显示解答
    Puzzle() :father(""), code(""), deep(-1){};
};
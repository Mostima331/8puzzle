#include<stdio.h>
//广度优先
struct puzzle
{
    int xy[3][3];
    int dir;
};
struct puzzle pu[10002];   //上限10000次
int count = 1;
 
void init()
{
	int i,j;
    printf("输入起始位置:\n");  
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            scanf("%d", &pu[0].xy[i][j]);
    pu[0].dir = -1;
    printf("输入目标位置:\n");
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            scanf("%d", &pu[10001].xy[i][j]);
    pu[10001].dir = -1;
	printf("过程：\n");
}

 
//0的位置
int loction(int num)
{
    int i;
    for (i = 0; i < 9; i++)
        if (pu[num].xy[i / 3][i % 3] == 0) 
			return i;
}

 
 
//(把九宫格看成一个数)
long long sign(int num)
{
    long long  sum;
    sum = pu[num].xy[0][0]*100000000 + pu[num].xy[0][1]*10000000 + 
 		  pu[num].xy[0][2]*1000000 + pu[num].xy[1][0]*100000 + 
	   	  pu[num].xy[1][1]*10000 + pu[num].xy[1][2]*1000 + 
   		  pu[num].xy[2][0]*100 + pu[num].xy[2][1]*10 + 
		  pu[num].xy[2][2];
    return sum;
}
 
void move(int num)
{
 
    int temp; //中介
    int loc;
	int last = pu[num].dir;
    loc = loction(num);
    //dir的8 2 4 6分别代表上 下 左 右
    if (loc / 3 != 0 && last != 8)  //不是第一行上一次不是上
    {
        pu[count] = pu[num];
        temp = pu[count].xy[loc / 3][loc % 3];
        pu[count].xy[loc / 3][loc % 3] = pu[count].xy[loc / 3 - 1][loc % 3];
        pu[count].xy[loc / 3 - 1][loc % 3] = temp;
        pu[count].dir = 2;
        count++;
    };
    if (loc / 3 != 2 && last != 2) //不是第三行上一次不是下
    {
        pu[count] = pu[num];
        temp = pu[count].xy[loc / 3][loc % 3];
        pu[count].xy[loc / 3][loc % 3] = pu[count].xy[loc / 3 + 1][loc % 3];
        pu[count].xy[loc / 3 + 1][loc % 3] = temp;
        pu[count].dir = 8;
        count++;
    }
    if (loc % 3 != 0 && last != 4) //不是第一列上一次不是左
    {
        pu[count] = pu[num];
        temp = pu[count].xy[loc / 3][loc % 3];
        pu[count].xy[loc / 3][loc % 3] = pu[count].xy[loc / 3][loc % 3 - 1];
        pu[count].xy[loc / 3][loc % 3 - 1] = temp;
        pu[count].dir = 6;
        count++;
    }
    if (loc % 3 != 2 && last != 6) //不是第三列上一次不是右
    {
        pu[count] = pu[num];
        temp = pu[count].xy[loc / 3][loc % 3];
        pu[count].xy[loc / 3][loc % 3] = pu[count].xy[loc / 3][loc % 3 + 1];
        pu[count].xy[loc / 3][loc % 3 + 1] = temp;
        pu[count].dir = 4;
        count++;
    }
 
}
void display(int num)
{
    int i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
            printf("%d ", pu[num].xy[i][j]);
        printf("\n");
    }
}
 
int search()
{
    int i = 0;
    while (1)
    {
        printf("\n");
        display(i);
        printf("\n");
        if (i == 10000)
        {
            printf("超出了上限次数\n");
            return 0;
        }
        if (sign(i) == sign(10001))
        {
            printf("在第%d次找到了\n", i);
            display(i);
            return i;
        }
        move(i);
        i++;
    }
}
 
int main()
{
    init();
    search();
    return 0;
}

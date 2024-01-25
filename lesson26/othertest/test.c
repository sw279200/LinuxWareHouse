#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define UP    1
#define DOWN  -1
#define LEFT  2
#define RIGHT -2

struct snake
{
        int hang;
        int lie;
        struct snake *pnext;
};
//struct snake node1 = {2,2,NULL};//创建贪吃蛇节点
//struct snake node2 = {2,3,NULL};//创建贪吃蛇节点
//struct snake node3 = {2,4,NULL};//创建贪吃蛇节点
struct snake *head = NULL;
struct snake *tail = NULL;
int key;
int dir;

struct snake food;

void initFood()
{
        int x = rand()%20;
        int y = rand()%20;
        food.hang = x;
        food.lie = y;
}

//ncurse初始化函数
void initNcurse()
{
        initscr();
        keypad(stdscr,1);
        noecho();//不要打印无关信息
}

//判断是否为贪吃蛇身子
int isSnakeNode(int i,int j)
{
        struct snake *p;
        p = head;

        while(NULL != p)
        {
                if(p->hang == i && p->lie == j)
                {
                        return 1;
                }

                p = p->pnext;
        }
        return 0;
}

//判断是否为失误
int isFood(int i,int j)
{
                if(food.hang == i && food.lie == j)
                {
                        return 1;
                }
        return 0;

}

//显示外围框架函数
void gamePic()
{
        int hang;
        int lie;

        move(0,0);//移动ncurse的光标
        for(hang=0;hang<20;hang++)
        {
                if(hang == 0)
                {
                        for(lie=0;lie<20;lie++)
                        {
                                printw("--");
                        }
                        printw("\n");
                }
                if(hang >= 0 || hang <= 19)
                {
                        for(lie=0;lie<=20;lie++)
                        {
                                if(lie == 0 || lie == 20)
                                {
										printw("|");
                                }
                                else if(isSnakeNode(hang,lie))
                                {
                                        printw("[]");
                                }
                                else if(isFood(hang,lie))
                                {
                                        printw("##");
                                }
                                else
                                {
                                        printw("  ");
                                }
                        }
                        printw("\n");
                }
                if(hang == 19)
                {
                        for(lie=0;lie<20;lie++)
                        {
                                printw("--");
                        }
                        printw("\n");
                        printw("by zzh,key = %d,food.hang = %d,food.lie = %d\n",key,food.hang,food.lie);
                }
        }
}

void addNode()
{
        struct snake *new = (struct snake *)malloc(sizeof(struct snake));
        new->pnext = NULL;

        switch(dir)
        {
                case UP:
                        new->hang = tail->hang-1;
                        new->lie = tail->lie;
                        break;
                case DOWN:
                        new->hang = tail->hang+1;
                        new->lie = tail->lie;
                        break;
                case LEFT:
                        new->hang = tail->hang;
                        new->lie = tail->lie-1;
                        break;
                case RIGHT:
                        new->hang = tail->hang;
                        new->lie = tail->lie+1;
                        break;
        }
        tail->pnext = new;
        tail = new;
}

void deleteNode()
{
        struct snake *p;
        p = head;
        head = head->pnext;
        free(p);

}

void initSnake()
{
        struct snake *p;

        dir = RIGHT;


        while(head != NULL)
        {
                p = head;
                head = head->pnext;
                free(p);
        }
        initFood();
        head = (struct snake *)malloc(sizeof(struct snake));
        head->hang = 1;
        head->lie = 1;
        head->pnext = NULL;
        tail = head;
        addNode();
        addNode();
        addNode();
        addNode();
}

//头撞到尾巴死掉函数
int ifSnakeDie()
{
        struct snake *p;
        p = head;

        if(tail->hang < 0 || tail->lie == 0 || tail->hang == 20 || tail->lie == 20)
        {
                return 1;
        }
        while(NULL != p->pnext)
        {
                if(p->hang == tail->hang && p->lie == tail->lie)
                {
                        return 1;
                }
                p = p->pnext;
        }
        return 0;
}

void moveSnake()
{
        //struct snake *p;

        //p = head;
        addNode();
        if(isFood(tail->hang,tail->lie))
        {
                initFood();
        }
        else
        {
                deleteNode();
        }

        if(ifSnakeDie())
        {
                initSnake();
        }

}

//刷新界面函数
void *refreshJieMian()
{
        while(1)
        {
                        moveSnake();
                        gamePic();//刷新地图

                        refresh();//每隔100000微秒刷新界面
                        usleep(100000);
        }
}

//转弯函数
void turn(int direction)
{
        if(abs(dir) != abs(direction))//abs求绝对值
        {
                dir = direction;
        }
}

//改变方向函数
void *changeDir()
{
        sleep(1);//让另一个线程先执行，否则出现地图乱码
        while(1)
        {
                key = getch();//等待用户输入
                switch(key)
                {
                        case KEY_DOWN:
                                printw("DOWN\n");
                                turn(DOWN);
                                break;
                        case KEY_UP:
                                printw("UP\n");
                                turn(UP);
                                break;
                        case KEY_LEFT:
                                printw("LEFT\n");
                                turn(LEFT);
                                break;
                        case KEY_RIGHT:
                                printw("RIGHT\n");
                                turn(RIGHT);
                                break;
                }
        }
}

int main()
{
        pthread_t t1;
        pthread_t t2;

        initNcurse();
        initSnake();
        gamePic();

        pthread_create(&t1,NULL,refreshJieMian,NULL);
        pthread_create(&t2,NULL,changeDir,NULL);

        while(1);
        getch();
        endwin();
        return 0;
}


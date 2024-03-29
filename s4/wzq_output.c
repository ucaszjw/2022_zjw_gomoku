#include "gomoku.h"

void black();
void white();
int full(int array[SIZE][SIZE]);

extern char arrayForDisplayBoard[SIZE][SIZE*CHARSIZE+1];
extern int arrayForInnerBoardLayout[SIZE][SIZE];
extern int arrayforRegret[SIZE][SIZE];
extern char play1CurrentPic[];
extern char play2CurrentPic[];

static int color=1; //指明当前棋子颜色

//输出函数，用于输出棋盘
void output(){
    extern int color;
    extern struct point point;

    while (full(arrayForInnerBoardLayout) == 0){
        switch (color){
        case 1:
            printf("现在是黑方行棋，请输入黑棋落子位置：");
            black();
            if (forbid(point.x, point.y, (-color+3)/2, 0) == 1)
            {
                printf("黑棋触犯禁手，白方胜利！");
                return;
            }
            if (judgeWin(point.x, point.y, (-color+3)/2) == 1)
            {
                printf("黑方胜利！\n");
                return;
            }
            color=-1;
            break;
        case -1:
            printf("现在是白方行棋，请输入白棋落子位置：");
            white();
            if (judgeWin(point.x, point.y, (-color+3)/2) == 1)
            {
                printf("白方胜利！\n");
                return;
            }
            color=1;
            break;
        default:
            break;
        }
    }
    printf("平局！\n");
    return;
}

//黑方落子
void black(){
    point=Input();
    
    innerLayoutToDisplayArray();
    arrayForDisplayBoard[point.x][point.y*2] = play1CurrentPic[0];
    arrayForDisplayBoard[point.x][point.y*2+1] = play1CurrentPic[1]; //这里的point.y*2+1是因为中文字符占两个字节
    displayBoard();
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            arrayforRegret[i][j] = arrayForInnerBoardLayout[i][j];  //记录悔棋前的棋盘格局
        }            
    }        
    arrayForInnerBoardLayout[point.x][point.y] = 1;
    getchar();  
}
//白方落子
void white(){
    point=Input();

    innerLayoutToDisplayArray();
    arrayForDisplayBoard[point.x][point.y*2] = play2CurrentPic[0];
    arrayForDisplayBoard[point.x][point.y*2+1] = play2CurrentPic[1];
    displayBoard();
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            arrayforRegret[i][j] = arrayForInnerBoardLayout[i][j];
        }            
    }
    arrayForInnerBoardLayout[point.x][point.y] = 2;
    getchar();
}


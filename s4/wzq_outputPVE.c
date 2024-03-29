#include "gomoku.h"

void black_p();
void white_e();
void black_e();
void white_p();
int full(int array[SIZE][SIZE]);
struct point randomgomoku();

extern char arrayForDisplayBoard[SIZE][SIZE*CHARSIZE+1];
extern int arrayForInnerBoardLayout[SIZE][SIZE];
extern int arrayforRegret1[SIZE][SIZE];
extern int arrayforRegret2[SIZE][SIZE];
extern char play1CurrentPic[];
extern char play2CurrentPic[];
extern int begin;

static int color=1;
int win=0;

void outputPVE(int begin){
    extern int color;
    extern struct point point;
    while (full(arrayForInnerBoardLayout) == 0){
        switch (begin) //begin=1时，玩家先手，begin=2时，电脑先手
        {
        case 1:
            switch (color){
                case 1:
                    printf("现在是黑方行棋，请输入黑棋落子位置：");
                    black_p();
                    if (forbid(point.x, point.y, (-color+3)/2, 0) == 1) //判断是否触犯禁手
                    {
                        printf("黑棋触犯禁手，白方胜利！\n");
                        return;
                    }
                    arrayForInnerBoardLayout[point.x][point.y] = 1;
                    if (judgeWin(point.x, point.y, (-color+3)/2) == 1)  //判断是否胜利
                    {
                        printf("黑方胜利！\n");
                        return;
                    }
                    color=-1;
                    break;
                case -1:
                    white_e();
                    printf("白棋落子位置为：%c%d\n",point.y+'A',point.x+1);
                    if (judgeWin(point.x, point.y, (-color+3)/2) == 1)  //判断是否胜利
                    {
                        printf("白方胜利！\n");
                        return;
                    }
                    arrayForInnerBoardLayout[point.x][point.y] = 2;
                    color=1;
                    break;
                default:
                    break;
            }
            break;
        case 2:
            switch (color){
                case 1:
                    black_e();
                    printf("黑棋落子位置为：%c%d\n",point.y+'A',point.x+1);
                    if (forbid(point.x, point.y, (-color+3)/2, 0) == 1) //判断是否触犯禁手
                    {
                        printf("白方胜利！\n");
                        return;
                    }
                    arrayForInnerBoardLayout[point.x][point.y] = 1;
                    if (judgeWin(point.x, point.y, (-color+3)/2))   //判断是否胜利
                    {
                        printf("黑方胜利！\n");
                        return;
                    }
                    color=-1;
                    break;
                case -1:
                    white_p();
                    if (judgeWin(point.x, point.y, (-color+3)/2) == 1)
                    {
                        printf("白方胜利！\n");
                        return;
                    }
                    arrayForInnerBoardLayout[point.x][point.y] = 2;
                    color=1;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
        }       
    }
    printf("平局！\n");
    return;
}

void outputEVE(){
    extern int color;
    extern struct point point;
    while (full(arrayForInnerBoardLayout) == 0){    //棋盘未满时循环
        switch (color)
        {
        case 1:
            black_e();
            printf("落子位置为：%c%d\n",point.y+'A',point.x+1);
            if (forbid(point.x, point.y, (-color+3)/2, 0) == 1)
            {
                printf("黑棋触犯禁手，白方胜利！\n");
                return;
            }
            if (judgeWin(point.x, point.y, (-color+3)/2) == 1)
            {
                printf("黑方胜利！\n");
                return;
            }
            arrayForInnerBoardLayout[point.x][point.y] = 1;
            color=-1;
            break;
        case -1:
            white_e();
            printf("落子位置为：%c%d\n",point.y+'A',point.x+1);
            if (judgeWin(point.x, point.y, (-color+3)/2) == 1)
            {
                printf("白方胜利！\n");
                return;
            }
            arrayForInnerBoardLayout[point.x][point.y] = 2;
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
void black_p(){
    point=InputPVE(begin);
    
    innerLayoutToDisplayArray();
    arrayForDisplayBoard[point.x][point.y*2] = play1CurrentPic[0];
    arrayForDisplayBoard[point.x][point.y*2+1] = play1CurrentPic[1];
    displayBoard();
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            arrayforRegret2[i][j] = arrayforRegret1[i][j];  //记录悔棋前两步的棋盘格局
        }
        
    }
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            arrayforRegret1[i][j] = arrayForInnerBoardLayout[i][j]; //记录悔棋前一步的棋盘格局
        }            
    }    
}

//白方落子
void white_e(){
    point=position(point.x, point.y, (-color+3)/2);

    innerLayoutToDisplayArray();
    arrayForDisplayBoard[point.x][point.y*2] = play2CurrentPic[0];
    arrayForDisplayBoard[point.x][point.y*2+1] = play2CurrentPic[1];
    displayBoard();
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            arrayforRegret2[i][j] = arrayforRegret1[i][j];  //记录悔棋前两步的棋盘格局
        }
        
    }
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            arrayforRegret1[i][j] = arrayForInnerBoardLayout[i][j]; //记录悔棋前一步的棋盘格局
        }            
    }
}

//黑方落子
void black_e(){
    point=position(point.x, point.y, (-color+3)/2);
    
    innerLayoutToDisplayArray();
    arrayForDisplayBoard[point.x][point.y*2] = play1CurrentPic[0];
    arrayForDisplayBoard[point.x][point.y*2+1] = play1CurrentPic[1];
    displayBoard();
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            arrayforRegret2[i][j] = arrayforRegret1[i][j];  //记录悔棋前两步的棋盘格局
        }
    }
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            arrayforRegret1[i][j] = arrayForInnerBoardLayout[i][j]; //记录悔棋前一步的棋盘格局
        }            
    }
}

//白方落子
void white_p(){
    point=InputPVE(begin);

    innerLayoutToDisplayArray();
    arrayForDisplayBoard[point.x][point.y*2] = play2CurrentPic[0];
    arrayForDisplayBoard[point.x][point.y*2+1] = play2CurrentPic[1];
    displayBoard();
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            arrayforRegret2[i][j] = arrayforRegret1[i][j];  //记录悔棋前两步的棋盘格局
        }
        
    }
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            arrayforRegret1[i][j] = arrayForInnerBoardLayout[i][j]; //记录悔棋前一步的棋盘格局
        }            
    }
}
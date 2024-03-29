#include "gomoku.h"

void initRecordBorard(void);
void innerLayoutToDisplayArray(void);
void displayBoard(void);

int mode;
int color;
int begin;

int main(){
    printf("请选择游戏模式：\n 1. 人人对战\n 2. 人机对战\n 3. 机机对战\n");
    scanf("%d",&mode);

    if (mode==1)
    {
        getchar();
        printf("坐标输入形式如：A1,9g,12h,e4\n 输入r悔棋（每回合最多可悔棋一次）\n 输入q退出游戏\n 现在开始游戏吧！\n");
        getchar();
        initRecordBorard();    //初始化一个空棋盘
        innerLayoutToDisplayArray();
        displayBoard();
        getchar();
        
        output();
    }else if (mode==2){
        getchar();
        printf("坐标输入形式如：A1,9g,12h,e4\n 输入r悔棋（每回合最多可悔棋一次）\n 输入q退出游戏\n 现在开始游戏吧！\n");
        getchar();
        initRecordBorard();    //初始化一个空棋盘
        innerLayoutToDisplayArray();
        displayBoard();

        printf("请选择执黑棋或白棋：\n 1. 执黑棋\n 2. 执白棋\n");
        scanf("%d",&begin);
        if (begin==1 || begin==2)
        {
            outputPVE(begin);
        }else{
            printf("输入错误！");
        }
    }else if (mode==3)
    {
        initRecordBorard();    //初始化一个空棋盘
        innerLayoutToDisplayArray();
        displayBoard();
        getchar();

        outputEVE();
    }
    
    else{
        printf("输入错误！");
    }    
    return 0;
}
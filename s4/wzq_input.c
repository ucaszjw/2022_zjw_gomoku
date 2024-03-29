#include "gomoku.h"
int mygetline(char *line);
struct point xyToBoard(char *line);

//Input函数，用于输入棋子坐标并判断是否合法
struct point Input(){
    char line[6];
    extern struct point point;
    
    extern int color;
    extern int arrayForInnerBoardLayout[SIZE][SIZE];
    extern int arrayforRegret[SIZE][SIZE];

    mygetline(line);
    if (line[0] == 'q' && line [1] == '\n') //输入q时退出程序
        exit(0);
    else if (line[0] == 'r' && line[1] == '\n'){    //输入r时悔棋
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                arrayForInnerBoardLayout[i][j] = arrayforRegret[i][j];  //悔棋时，将当前棋盘的格局恢复到悔棋前的状态
            }            
        }
        color = -color;
        output();
    }else{
        point=xyToBoard(line);
        if (point.x >= SIZE || point.y >= SIZE || point.x < 0 || point.y < 0)
        {
            printf("不在棋盘有效范围内，请重新输入：");
            return Input();    //输入错误时递归调用，直到输入正确
        }else if (arrayForInnerBoardLayout[point.x][point.y] != 0)
        {
            printf("该处已有棋子，请重新输入：");
            return Input();   //输入错误时递归调用，直到输入正确
        }else{
            return point;
        }
    }
}
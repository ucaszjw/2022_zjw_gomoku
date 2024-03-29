#include "gomoku.h"
extern int arrayForInnerBoardLayout[SIZE][SIZE];

int judgeWin(int x, int y, int color){  //判断是否胜利
    int connect_0(int x, int y, int color);
    int connect_1(int x, int y, int color);
    int connect_2(int x, int y, int color);
    int connect_3(int x, int y, int color);
    int connect_4(int x, int y, int color);
    int connect_5(int x, int y, int color);
    int connect_6(int x, int y, int color);
    int connect_7(int x, int y, int color);
    int count_0,count_1,count_2,count_3,
        count_4,count_5,count_6,count_7;

    count_0=connect_0(x,y,color);
    count_1=connect_1(x,y,color);
    count_2=connect_2(x,y,color);
    count_3=connect_3(x,y,color);
    count_4=connect_4(x,y,color);
    count_5=connect_5(x,y,color);
    count_6=connect_6(x,y,color);
    count_7=connect_7(x,y,color);

    if (count_0 + count_4 + 1 >= 5 || count_1 + count_5 + 1 >= 5 || count_2 + count_6 + 1 >= 5 || count_3 + count_7 + 1>= 5) {
        return 1;  // win
    } else {
        return 0;  // not win
    }
}

int connect_0(int x, int y, int color){
    int count = 0;
    for (int i = 1; i < 5; i++){
        if (x + i >= 15 || arrayForInnerBoardLayout[x+i][y] != color){
            break;
        } else {
            count++;
        }
    }
    return count;   //返回连子数
}

int connect_1(int x, int y, int color){
    int count = 0;
    for (int i = 1; i < 5; i++){
        if (x + i >= 15 || y + i >= 15 || arrayForInnerBoardLayout[x+i][y+i] != color){
            break;
        } else {
            count++;
        }
    }
    return count;   //返回连子数
}

int connect_2(int x, int y, int color){
    int count = 0;
    for (int i = 1; i < 5; i++){
        if (y + i >= 15 || arrayForInnerBoardLayout[x][y+i] != color){
            break;
        } else {
            count++;
        }
    }
    return count;   //返回连子数
}

int connect_3(int x, int y, int color){
    int count = 0;
    for (int i = 1; i < 5; i++){
        if (x - i < 0 || y + i >= 15 || arrayForInnerBoardLayout[x-i][y+i] != color){
            break;
        } else {
            count++;
        }
    }
    return count;   //返回连子数
}

int connect_4(int x, int y, int color){
    int count = 0;
    for (int i = 1; i < 5; i++){
        if (x - i < 0 || arrayForInnerBoardLayout[x-i][y] != color){
            break;
        } else {
            count++;
        }
    }
    return count;   //返回连子数
}

int connect_5(int x, int y, int color){
    int count = 0;
    for (int i = 1; i < 5; i++){
        if (x - i < 0 || y - i < 0 || arrayForInnerBoardLayout[x-i][y-i] != color){
            break;
        } else {
            count++;
        }
    }
    return count;   //返回连子数
}

int connect_6(int x, int y, int color){
    int count = 0;
    for (int i = 1; i < 5; i++){
        if (y - i < 0 || arrayForInnerBoardLayout[x][y-i] != color){
            break;
        } else {
            count++;
        }
    }
    return count;   //返回连子数
}

int connect_7(int x, int y, int color){
    int count = 0;
    for (int i = 1; i < 5; i++){
        if (x + i >= 15 || y - i < 0 || arrayForInnerBoardLayout[x+i][y-i] != color){
            break;
        } else {
            count++;
        }
    }
    return count;   //返回连子数
}
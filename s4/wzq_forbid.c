#include "gomoku.h"
extern int arrayForInnerBoardLayout[SIZE][SIZE];


int lineLength(int x,int y,int dx, int dy, int color){  //计算某一方向上的连子长度
    int num1 = 0, num2 = 0;
    for (int i = 1; inRange(x+i*dx, y+i*dy); i++){
        if (arrayForInnerBoardLayout[x+i*dx][y+i*dy] == color){
            num1++;
        }else{
            break;
        }
    }
    for (int i=1; inRange(x-i*dx, y-i*dy); i++){
        if (arrayForInnerBoardLayout[x-i*dx][y-i*dy] == color){
            num2++;
        }else{
            break;
        }
    }
    return num1+num2;
}

int forbid(int x, int y, int color, int isRecursive) {  //判断是否触犯禁手
    int num_four = 0;
    int num_three = 0;
    int max_length = 1;
    int isHuoFour(int x,int y,int dx,int dy,int color);
    int isChongFour1(int x,int y,int dx,int dy,int color);
    int isChongFour2(int x, int y, int dx, int dy, int color);
    int isHuoThree(int x, int y, int dx, int dy, int color);
    
    if (color==2)
    {
        return 0;  //白棋不会禁手
    }

    int line1 = lineLength(x, y, 1, 0, color);
    int line2 = lineLength(x, y, 0, 1, color);
    int line3 = lineLength(x, y, 1, 1, color);
    int line4 = lineLength(x, y, 1, -1, color);

    if (max_length < line1)
        max_length = line1;
    if (max_length < line2)
        max_length = line2;
    if (max_length < line3)
        max_length = line3;
    if (max_length < line4)
        max_length = line4;

    int originalValue = arrayForInnerBoardLayout[x][y]; //保存原来的值
    arrayForInnerBoardLayout[x][y] = 1;

    /*判断长连禁手*/
    if (max_length > 4) {
        if (line1 == 4 || line2 == 4 || line3 == 4 || line4 == 4) {
            arrayForInnerBoardLayout[x][y] = originalValue;
            return 0;   //成五时无视禁手
        } else {
            printf("长连禁手！\n");
            arrayForInnerBoardLayout[x][y] = originalValue;
            return 1; 
        }
    }

    /*判断双四禁手*/
    if (isHuoFour(x, y, 1, 0, color)) num_four++;
    if (isHuoFour(x, y, 0, 1, color)) num_four++;
    if (isHuoFour(x, y, 1, 1, color)) num_four++;
    if (isHuoFour(x, y, 1, -1, color)) num_four++;

    num_four += isChongFour2(x, y, 1, 0, color) + isChongFour2(x, y, 0, 1, color) + isChongFour2(x, y, 1, 1, color) + isChongFour2(x, y, 1, -1, color)
            +  isChongFour1(x, y ,1 ,0 ,color) + isChongFour1(x, y, 0, 1, color) + isChongFour1(x, y, 1, 1, color) + isChongFour1(x, y, 1, -1, color);

    /*判断三三禁手*/
    if (!isRecursive) {
        num_three += isHuoThree(x, y, 1, 0, color) + isHuoThree(x, y, 0, 1, color) + isHuoThree(x, y, 1, 1, color) + isHuoThree(x, y, 1, -1, color);
    }

    if (num_four >= 2) {
        printf("双四禁手！\n");
        arrayForInnerBoardLayout[x][y] = originalValue;
        return 1;
    } else if (num_three >= 3) {
        printf("三三禁手！\n");
        arrayForInnerBoardLayout[x][y] = originalValue;
        return 1;
    } else {
        arrayForInnerBoardLayout[x][y] = originalValue;
        return 0;
    }
}
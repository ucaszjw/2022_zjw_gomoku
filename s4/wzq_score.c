#include "gomoku.h"

extern int arrayForInnerBoardLayout[SIZE][SIZE];
int base[]={1,3,9,27,81,243,729,2187,6561,19683,59049,177147};  //base数组，用三进制数表示棋盘格局
int scoretab[15][15]={
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,1,2,2,2,2,2,2,2,2,2,2,2,1,0},
    {0,1,2,3,3,3,3,3,3,3,3,3,2,1,0},
    {0,1,2,3,4,4,4,4,4,4,4,3,2,1,0},
    {0,1,2,3,4,5,5,5,5,5,4,3,2,1,0},
    {0,1,2,3,4,5,6,6,6,5,4,3,2,1,0},
    {0,1,2,3,4,5,6,7,6,5,4,3,2,1,0},
    {0,1,2,3,4,5,6,6,6,5,4,3,2,1,0},
    {0,1,2,3,4,5,5,5,5,5,4,3,2,1,0},
    {0,1,2,3,4,4,4,4,4,4,4,3,2,1,0},
    {0,1,2,3,3,3,3,3,3,3,3,3,2,1,0},
    {0,1,2,2,2,2,2,2,2,2,2,2,2,1,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};  //棋盘上每个位置的分数

int inRange(int x, int y) { //判断是否在棋盘范围内
    if (x >= 0 && x < SIZE && y >= 0 && y < SIZE) 
        return 1;
    else 
        return 0;
}

int isHuoTwo(int x, int y, int dx, int dy, int color){  //判断是否为活二
    int value, key_x1, key_y1, key_x2, key_y2, now_x, now_y, end_x, end_y, search_x, search_y;
    int index1; 
    int index2 = 0; //

    for (now_x = x - dx, now_y = y - dy; index2 < 4 && inRange(now_x, now_y);now_x -= dx, now_y -= dy, index2++) {
        value = 0;
        search_x = now_x - dx;
        search_y = now_y - dy;
        if (inRange(search_x, search_y) && arrayForInnerBoardLayout[search_x][search_y] == color) 
            continue;

        search_x = now_x;
        search_y = now_y;
        for (index1 = 0; index1 < 6 && inRange(search_x, search_y);index1++, search_x += dx, search_y += dy) {
            if (arrayForInnerBoardLayout[search_x][search_y] == 3-color) 
                break;
            else 
                value += arrayForInnerBoardLayout[search_x][search_y] * base[index1];
        } 

        end_x = now_x + index1*dx;
        end_y = now_y + index1*dy;

        if(index1 < 6) continue;

        if (value == huotwo_1b) {
            key_x1 = now_x + 3*dx;
            key_y1 = now_y + 3*dy;
            key_x2 = now_x + 2*dx;
            key_y2 = now_y + 2*dy;
            if (!(forbid(key_x1, key_y1, color,1)) || !(forbid(key_x2, key_y2, color,1))) {
                return 2;
            }
        } else if (value == huotwo_2b) {
            key_x1 = now_x + 3*dx;
            key_y1 = now_y + 3*dy;
            key_x2 = now_x + 4*dx;
            key_y2 = now_y + 4*dy;
            if (!(forbid(key_x1, key_y2, color,1)) || !(forbid(key_x2, key_y2, color,1))) {
                return 2;
            }
        } else if (value == huotwo_3b) {
            key_x1 = now_x + 4*dx;
            key_y1 = now_y + 4*dy;
            if (!(forbid(key_x1, key_y1, color,1))) {
                return 1;
            }
        } else if (value == huotwo_4b) {
            key_x1 = now_x + 1*dx;
            key_y1 = now_y + 1*dy;
            if (!(forbid(key_x1, key_y1, color,1))) {
                return 1;
            }
        } else if (value == huotwo_5b) {
            key_x1 = now_x + 2*dx;
            key_y1 = now_y + 2*dy;
            key_x2 = now_x + 3*dx;
            key_y2 = now_y + 3*dy;
            if (!(forbid(key_x1, key_y1, color,1)) || !(forbid(key_x2, key_y2, color,1))) { 
                return 1;
            }
        } else if (value == huotwo_1w)
            return 2;
          else if (value == huotwo_2w)
            return 2;
          else if (value == huotwo_3w) 
            return 1;
          else if (value == huotwo_4w) 
            return 1;
          else if (value == huotwo_5w) 
            return 1;
    }
    return 0;
}

//判断是否为活四
int isHuoFour(int x,int y,int dx,int dy,int color){
    int num1 = 0, num2 = 0;
    for (int i = 1; i < 5 && inRange(x+i*dx, y+i*dy); i++){
        if (arrayForInnerBoardLayout[x+i*dx][y+i*dy] == color){
            num1++;
        }else{
            break;
        }
    }
    for (int i=1; i<5 && inRange(x-i*dx, y-i*dy); i++){
        if (arrayForInnerBoardLayout[x-i*dx][y-i*dy] == color){
            num2++;
        }else{
            break;
        }
    }
    if (num1+num2 == 3 && 
        (inRange(x+dx*(num1+1), y+dy*(num1+1)) && arrayForInnerBoardLayout[x+dx*(num1+1)][y+dy*(num1+1)] == 0) &&
        (inRange(x-dx*(num2+1), y-dy*(num2+1)) && arrayForInnerBoardLayout[x-dx*(num2+1)][y-dy*(num2+1)] == 0)){
    
        return 1;
    }else{
        return 0;
    }
}

//判断是否为半活四（连冲四）
int isChongFour1(int x,int y,int dx,int dy,int color){
    int num1 = 0, num2 = 0;
    for (int i = 1; i < 5 && inRange(x+i*dx, y+i*dy); i++){
        if (arrayForInnerBoardLayout[x+i*dx][y+i*dy] == color){
            num1++;
        }else{
            break;
        }
    }
    for (int i=1; i<5 && inRange(x-i*dx, y-i*dy); i++){
        if (arrayForInnerBoardLayout[x-i*dx][y-i*dy] == color){
            num2++;
        }else{
            break;
        }
    }
    if (num1+num2 == 3 && 
        ((inRange(x+dx*(num1+1), y+dy*(num1+1)) && inRange(x-dx*(num2+1), y-dy*(num2+1)) && arrayForInnerBoardLayout[x+dx*(num1+1)][y+dy*(num1+1)]==0 && arrayForInnerBoardLayout[x-dx*(num2+1)][y-dy*(num2+1)]==3-color) ||
        (inRange(x+dx*(num1+1), y+dy*(num1+1)) && inRange(x-dx*(num2+1), y-dy*(num2+1)) && arrayForInnerBoardLayout[x+dx*(num1+1)][y+dy*(num1+1)]==3-color && arrayForInnerBoardLayout[x-dx*(num2+1)][y-dy*(num2+1)]==0) ||
        (!(inRange(x+dx*(num1+1), y+dy*(num1+1))) && inRange(x-dx*(num2+1), y-dy*(num2+1)) && arrayForInnerBoardLayout[x-dx*(num2+1)][y-dy*(num2+1)]==0 ||
        (!(inRange(x-dx*(num2+1), y-dy*(num2+1))) && inRange(x+dx*(num1+1), y+dy*(num1+1)) && arrayForInnerBoardLayout[x+dx*(num1+1)][y+dy*(num1+1)]==0)))){
        return 1;
    }else{
        return 0;
    }
}

//判断是否为跳冲四
int isChongFour2(int x, int y, int dx, int dy, int color) {
    int value, key_x, key_y, now_x, now_y, search_x, search_y;
    int num = 0;
    int index1, index2;
    index2 = 0;

    for (now_x = x, now_y = y; index2 < 5 && inRange(now_x, now_y);now_x -= dx, now_y -= dy, index2++) { 
        value = 0;
        search_x = now_x;
        search_y = now_y;
        for (index1 = 0; index1 < 5 && inRange(search_x, search_y);index1++, search_x += dx, search_y += dy) {
            if (arrayForInnerBoardLayout[search_x][search_y] == 3-color) 
                break;
            else 
                value += arrayForInnerBoardLayout[search_x][search_y] * base[index1];
        } 
        if (index1 == 5) {
            if (value == chongfour_1b) {
                key_x = now_x + 2*dx;
                key_y = now_y + 2*dy;
                num++;
            } else if (value == chongfour_2b) {
                key_x = now_x + 3*dx;
                key_y = now_y + 3*dy;
                num++;
            } else if (value == chongfour_3b) {
                key_x = now_x + 1*dx;
                key_y = now_y + 1*dy;
                num++;
            } else if (value == chongfour_1w)
            {
                num++;
            } else if (value == chongfour_2w)
            {
                num++;
            } else if (value == chongfour_3w)
            {
                num++;
            }
        }
    }
    return num;
}

//判断是否为活三
int isHuoThree(int x, int y, int dx, int dy, int color) {
    int value, key_x, key_y, now_x, now_y, end_x, end_y, search_x, search_y;
    int index1;
    int index2 = 0;

    for (now_x = x - dx, now_y = y - dy; index2 < 4 && inRange(now_x, now_y);now_x -= dx, now_y -= dy, index2++) {
        value = 0;
        search_x = now_x - dx;
        search_y = now_y - dy;
        if (inRange(search_x, search_y) && arrayForInnerBoardLayout[search_x][search_y] == color) 
            continue;

        search_x = now_x;
        search_y = now_y;
        for (index1 = 0; index1 < 6 && inRange(search_x, search_y);index1++, search_x += dx, search_y += dy) {
            if (arrayForInnerBoardLayout[search_x][search_y] == 3-color) 
                break;
            else 
                value += arrayForInnerBoardLayout[search_x][search_y] * base[index1];
        } 

        end_x = now_x + index1*dx;
        end_y = now_y + index1*dy;

        if(index1 < 6) continue;
        else if(!inRange(end_x, end_y) || arrayForInnerBoardLayout[end_x][end_y] != color) {
            switch (value) {
                case huothree_1b:
                    key_x = now_x + dx*1;  
                    key_y = now_y + dy*1;
                    if (!(forbid(key_x, key_y,color,1))) 
                        return 2;
                    break;
                case huothree_2b:
                    key_x = now_x + dx*4;  
                    key_y = now_y + dy*4;
                    if (!(forbid(key_x, key_y,color,1))) 
                        return 2;
                    break;
                case huothree_3b:
                    key_x = now_x + dx*2;  
                    key_y = now_y + dy*2;
                    if ((!forbid(key_x, key_y,color,1)))
                        return 1;
                    break;
                case huothree_4b:
                    key_x = now_x + dx*3;  
                    key_y = now_y + dy*3;  
                    if ((!forbid(key_x, key_y,color,1)))
                        return 1; 
                    break;
                case huothree_1w:
                    return 2;
                    break;
                case huothree_2w:
                    return 2;
                    break;
                case huothree_3w:
                    return 1;
                    break;
                case huothree_4w:
                    return 1; 
                    break;
            }
        } 
    }
    return 0;
}

//判断是否为冲三
int isChongThree(int x, int y, int dx, int dy, int color) {
    int value, key_x1, key_y1, key_x2, key_y2, now_x, now_y , end_x, end_y, search_x, search_y;
    int index1;
    int index2 = 0;

    for (now_x = x - dx, now_y = y - dy; index2 < 4 && inRange(now_x, now_y);now_x -= dx, now_y -= dy, index2++) {
        value = 0;
        search_x = now_x - dx;
        search_y = now_y - dy;
        if (inRange(search_x, search_y) && arrayForInnerBoardLayout[search_x][search_y] == color) 
            continue;

        search_x = now_x;
        search_y = now_y;
        for (index1 = 0; index1 < 5 && inRange(search_x, search_y);index1++, search_x += dx, search_y += dy) {
            if (arrayForInnerBoardLayout[search_x][search_y] == 3-color) 
                break;
            else 
                value += arrayForInnerBoardLayout[search_x][search_y] * base[index1];
        } 

        end_x = now_x + index1*dx;
        end_y = now_y + index1*dy;

        if(index1 < 5) continue;
        else if(!inRange(end_x, end_y) || arrayForInnerBoardLayout[end_x][end_y] != color) {
            switch (value) {
                case chongthree_1b:
                    return 1;
                    break;
                case chongthree_2b:
                    return 1;
                    break;
                case chongthree_3b:
                    return 1;
                    break;
                case chongthree_4b:
                    return 1; 
                    break;
                case chongthree_5b:
                    return 1;
                    break;
                case chongthree_6b:
                    return 1;
                    break;
                case chongthree_7b:
                    return 1;
                    break;
                case chongthree_1w:
                    return 1;
                    break;
                case chongthree_2w:
                    return 1;
                    break;
                case chongthree_3w:
                    return 1;
                    break;
                case chongthree_4w:
                    return 1; 
                    break;
                case chongthree_5w:
                    return 1;
                    break;
                case chongthree_6w:
                    return 1;
                    break;
                case chongthree_7w:
                    return 1;
                    break;
            }
        }
    }
    return 0;
}

//为自己的棋子打分
int scoreSelf(int x, int y, int color){
    int huo4 = 0, chong4_1 = 0, chong4_2 = 0, huo3, chong3 = 0, huo2 = 0;

    if (forbid(x, y, color, 0) == 1){
        return 0;   //触犯禁手时返回0分
    } else if (judgeWin(x, y, color) == 1){
        return 99999999;    //己方胜利时返回最大分
    }
    huo4 = isHuoFour(x, y, 1, 0, color) + isHuoFour(x, y, 0, 1, color) + isHuoFour(x, y, 1, 1, color) + isHuoFour(x, y, 1, -1, color);
    chong4_1 = isChongFour1(x, y ,1 ,0 ,color) + isChongFour1(x, y, 0, 1, color) + isChongFour1(x, y, 1, 1, color) + isChongFour1(x, y, 1, -1, color);
    chong4_2 = isChongFour2(x, y, 1, 0, color) + isChongFour2(x, y, 0, 1, color) + isChongFour2(x, y, 1, 1, color) + isChongFour2(x, y, 1, -1, color);
    huo3 = isHuoThree(x, y, 1, 0, color) + isHuoThree(x, y, 0, 1, color) + isHuoThree(x, y, 1, 1, color) + isHuoThree(x, y, 1, -1, color);
    chong3 = isChongThree(x, y, 1, 0, color) + isChongThree(x, y, 0, 1, color) + isChongThree(x, y, 1, 1, color) + isChongThree(x, y, 1, -1, color);
    huo2 = isHuoTwo(x, y, 1, 0, color) + isHuoTwo(x, y, 0, 1, color) + isHuoTwo(x, y, 1, 1, color) + isHuoTwo(x, y, 1, -1, color);
    return huo4*12000+chong4_1*3999+chong4_2*3990+huo3*2100+chong3*400+huo2*110+scoretab[x][y]; //为每个位置打分
}

//为对方的棋子打分
int scoreOpponent(int x, int y, int color){
    int huo4 = 0, chong4_1 = 0, chong4_2 = 0, huo3, chong3 = 0, huo2 = 0;

    if (forbid(x, y, color, 0) == 1){   
        return 0;   //触犯禁手时返回0分
    } else if (judgeWin(x, y, color) == 1){
        return 80000000;    //对方胜利时返回次大分
    }
    huo4 = isHuoFour(x, y, 1, 0, color) + isHuoFour(x, y, 0, 1, color) + isHuoFour(x, y, 1, 1, color) + isHuoFour(x, y, 1, -1, color);
    chong4_1 = isChongFour1(x, y ,1 ,0 ,color) + isChongFour1(x, y, 0, 1, color) + isChongFour1(x, y, 1, 1, color) + isChongFour1(x, y, 1, -1, color);
    chong4_2 = isChongFour2(x, y, 1, 0, color) + isChongFour2(x, y, 0, 1, color) + isChongFour2(x, y, 1, 1, color) + isChongFour2(x, y, 1, -1, color);
    huo3 = isHuoThree(x, y, 1, 0, color) + isHuoThree(x, y, 0, 1, color) + isHuoThree(x, y, 1, 1, color) + isHuoThree(x, y, 1, -1, color);
    chong3 = isChongThree(x, y, 1, 0, color) + isChongThree(x, y, 0, 1, color) + isChongThree(x, y, 1, 1, color) + isChongThree(x, y, 1, -1, color);
    huo2 = isHuoTwo(x, y, 1, 0, color) + isHuoTwo(x, y, 0, 1, color) + isHuoTwo(x, y, 1, 1, color) + isHuoTwo(x, y, 1, -1, color);
    return huo4*10000+chong4_1*4999+chong4_2*4990+huo3*3000+chong3*70+huo2*40+scoretab[x][y];   //为每个位置打分
}

int score(int x, int y, int color){
    int self = scoreSelf(x, y, color);
    int opponent = scoreOpponent(x, y, 3-color);
    return self + opponent; //返回总分
}

struct point position(int x, int y, int color){
    PositionScore positionScore;
    PositionScore scores[SIZE * SIZE]; 
    int compare(const void *a, const void *b);
    int count = 0;

    for (int x = 0; x < SIZE; x++) {
        for (int y = 0; y < SIZE; y++) {
            if (arrayForInnerBoardLayout[x][y] == 0) {
                scores[count].i = x;
                scores[count].j = y;
                scores[count].score = score(x, y, color);
                count++;    //记录每个位置的分数
            }
        }
    }
    qsort(scores, count, sizeof(PositionScore), compare);   //按分数从大到小排序
    point.x = scores[0].i;
    point.y = scores[0].j;
    return point;   //返回最高分的位置
}  

int compare(const void *a, const void *b) {
    PositionScore *c = (PositionScore *)a;
    PositionScore *d = (PositionScore *)b;
    return d->score - c->score; //按分数从大到小排序
}
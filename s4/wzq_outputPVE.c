#include "gomoku.h"

void black_p();
void white_e();
void black_e();
void white_p();
int full(int array[SIZE][SIZE]);

extern char arrayForDisplayBoard[SIZE][SIZE*CHARSIZE+1];
extern int arrayForInnerBoardLayout[SIZE][SIZE];
extern int arrayforRegret1[SIZE][SIZE];
extern int arrayforRegret2[SIZE][SIZE];
extern char play1CurrentPic[];
extern char play2CurrentPic[];
extern int begin;
extern struct Point point;

static int color=1;
int win=0;

void outputPVE(int begin){
    extern int color;
    while (full(arrayForInnerBoardLayout) == 0){
        switch (begin) //begin=1Ê±ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ö£ï¿½begin=2Ê±ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
        {
        case 1:
            switch (color){
                case 1:
                    printf("ÏÖÔÚÊÇºÚ·½ÐÐÆå£¬ÇëÊäÈëºÚÆåÂä×ÓÎ»ÖÃ£º");
                    black_p();
                    if (forbid(point.x, point.y, (-color+3)/2, 0) == 1) //ï¿½Ð¶ï¿½ï¿½Ç·ñ´¥·ï¿½ï¿½ï¿½ï¿½ï¿½
                    {
                        printf("ºÚ·½´¥·¸½ûÊÖ£¬°×·½Ê¤Àû£¡\n");
                        return;
                    }
                    arrayForInnerBoardLayout[point.x][point.y] = 1;
                    if (judgeWin(point.x, point.y, (-color+3)/2) == 1)  //ï¿½Ð¶ï¿½ï¿½Ç·ï¿½Ê¤ï¿½ï¿½
                    {
                        printf("ºÚ·½Ê¤Àû£¡\n");
                        return;
                    }
                    color=-1;
                    break;
                case -1:
                    white_e();
                    printf("°×·½Âä×ÓÎ»ÖÃÎª£º%c%d\n",point.y+'A',point.x+1);
                    if (judgeWin(point.x, point.y, (-color+3)/2) == 1)  //ï¿½Ð¶ï¿½ï¿½Ç·ï¿½Ê¤ï¿½ï¿½
                    {
                        printf("°×·½Ê¤Àû£¡\n");
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
                    printf("ºÚ·½Âä×ÓÎ»ÖÃÎª£º%c%d\n",point.y+'A',point.x+1);
                    if (forbid(point.x, point.y, (-color+3)/2, 0) == 1) //ï¿½Ð¶ï¿½ï¿½Ç·ñ´¥·ï¿½ï¿½ï¿½ï¿½ï¿½
                    {
                        printf("ºÚ·½´¥·¸½ûÊÖ£¬°×·½Ê¤Àû£¡\n");
                        return;
                    }
                    arrayForInnerBoardLayout[point.x][point.y] = 1;
                    if (judgeWin(point.x, point.y, (-color+3)/2))   //ï¿½Ð¶ï¿½ï¿½Ç·ï¿½Ê¤ï¿½ï¿½
                    {
                        printf("ºÚ·½Ê¤Àû£¡\n");
                        return;
                    }
                    color=-1;
                    break;
                case -1:
                    printf("ÏÖÔÚÊÇ°×·½ÐÐÆå£¬ÇëÊäÈë°×ÆåÂä×ÓÎ»ÖÃ£º");
                    white_p();
                    if (judgeWin(point.x, point.y, (-color+3)/2) == 1)
                    {
                        printf("°×·½Ê¤Àû£¡\n");
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
    printf("Æ½¾Ö£¡\n");
    return;
}

void outputEVE(){
    extern int color;
    while (full(arrayForInnerBoardLayout) == 0){    //ï¿½ï¿½ï¿½ï¿½Î´ï¿½ï¿½Ê±Ñ­ï¿½ï¿½
        switch (color)
        {
        case 1:
            black_e();
            printf("ºÚ·½Âä×ÓÎ»ÖÃÎª£º%c%d\n",point.y+'A',point.x+1);
            if (forbid(point.x, point.y, (-color+3)/2, 0) == 1)
            {
                printf("ºÚ·½´¥·¸½ûÊÖ£¬°×·½Ê¤Àû£¡\n");
                return;
            }
            if (judgeWin(point.x, point.y, (-color+3)/2) == 1)
            {
                printf("ºÚ·½Ê¤Àû£¡\n");
                return;
            }
            arrayForInnerBoardLayout[point.x][point.y] = 1;
            color=-1;
            break;
        case -1:
            white_e();
            printf("°×·½Âä×ÓÎ»ÖÃÎª£º%c%d\n",point.y+'A',point.x+1);
            if (judgeWin(point.x, point.y, (-color+3)/2) == 1)
            {
                printf("°×·½Ê¤Àû£¡\n");
                return;
            }
            arrayForInnerBoardLayout[point.x][point.y] = 2;
            color=1;
            break;
        default:
            break;
        }       
    }
    printf("Æ½¾Ö£¡\n");
    return;
}

//ï¿½Ú·ï¿½ï¿½ï¿½ï¿½ï¿½
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
            arrayforRegret2[i][j] = arrayforRegret1[i][j];  //ï¿½ï¿½Â¼ï¿½ï¿½ï¿½ï¿½Ç°ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ì¸ï¿½ï¿?
        }
        
    }
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            arrayforRegret1[i][j] = arrayForInnerBoardLayout[i][j]; //ï¿½ï¿½Â¼ï¿½ï¿½ï¿½ï¿½Ç°Ò»ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ì¸ï¿½ï¿?
        }            
    }    
}

//ï¿½×·ï¿½ï¿½ï¿½ï¿½ï¿½
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
            arrayforRegret2[i][j] = arrayforRegret1[i][j];  //ï¿½ï¿½Â¼ï¿½ï¿½ï¿½ï¿½Ç°ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ì¸ï¿½ï¿?
        }
        
    }
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            arrayforRegret1[i][j] = arrayForInnerBoardLayout[i][j]; //ï¿½ï¿½Â¼ï¿½ï¿½ï¿½ï¿½Ç°Ò»ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ì¸ï¿½ï¿?
        }            
    }
}

//ï¿½Ú·ï¿½ï¿½ï¿½ï¿½ï¿½
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
            arrayforRegret2[i][j] = arrayforRegret1[i][j];  //ï¿½ï¿½Â¼ï¿½ï¿½ï¿½ï¿½Ç°ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ì¸ï¿½ï¿?
        }
    }
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            arrayforRegret1[i][j] = arrayForInnerBoardLayout[i][j]; //ï¿½ï¿½Â¼ï¿½ï¿½ï¿½ï¿½Ç°Ò»ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ì¸ï¿½ï¿?
        }            
    }
}

//ï¿½×·ï¿½ï¿½ï¿½ï¿½ï¿½
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
            arrayforRegret2[i][j] = arrayforRegret1[i][j];  //ï¿½ï¿½Â¼ï¿½ï¿½ï¿½ï¿½Ç°ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ì¸ï¿½ï¿?
        }
        
    }
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            arrayforRegret1[i][j] = arrayForInnerBoardLayout[i][j]; //ï¿½ï¿½Â¼ï¿½ï¿½ï¿½ï¿½Ç°Ò»ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ì¸ï¿½ï¿?
        }            
    }
}
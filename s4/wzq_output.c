#include "gomoku.h"

void black();
void white();
int full(int array[SIZE][SIZE]);

extern char arrayForDisplayBoard[SIZE][SIZE*CHARSIZE+1];
extern int arrayForInnerBoardLayout[SIZE][SIZE];
extern int arrayforRegret[SIZE][SIZE];
extern char play1CurrentPic[];
extern char play2CurrentPic[];
extern struct Point point;

static int color=1; //Ö¸ï¿½ï¿½ï¿½ï¿½Ç°ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½É«

//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
void output(){
    extern int color;

    while (full(arrayForInnerBoardLayout) == 0){
        switch (color){
        case 1:
            printf("ÏÖÔÚÊÇºÚ·½ÐÐÆå£¬ÇëÊäÈëºÚÆåÂä×ÓÎ»ÖÃ£º");
            black();
            if (forbid(point.x, point.y, (-color+3)/2, 0) == 1)
            {
                printf("ºÚÆå´¥·¸½ûÊÖ£¬°×·½Ê¤Àû£¡");
                return;
            }
            if (judgeWin(point.x, point.y, (-color+3)/2) == 1)
            {
                printf("ºÚ·½Ê¤Àû£¡\n");
                return;
            }
            color=-1;
            break;
        case -1:
            printf("ÏÖÔÚÊÇ°×·½ÐÐÆå£¬ÇëÊäÈë°×ÆåÂä×ÓÎ»ÖÃ£º");
            white();
            if (judgeWin(point.x, point.y, (-color+3)/2) == 1)
            {
                printf("°×·½Ê¤Àû£¡\n");
                return;
            }
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
void black(){
    point=Input();
    
    innerLayoutToDisplayArray();
    arrayForDisplayBoard[point.x][point.y*2] = play1CurrentPic[0];
    arrayForDisplayBoard[point.x][point.y*2+1] = play1CurrentPic[1]; //ï¿½ï¿½ï¿½ï¿½ï¿½point.y*2+1ï¿½ï¿½ï¿½ï¿½Îªï¿½ï¿½ï¿½ï¿½ï¿½Ö·ï¿½Õ¼ï¿½ï¿½ï¿½ï¿½ï¿½Ö½ï¿½
    displayBoard();
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            arrayforRegret[i][j] = arrayForInnerBoardLayout[i][j];  //ï¿½ï¿½Â¼ï¿½ï¿½ï¿½ï¿½Ç°ï¿½ï¿½ï¿½ï¿½ï¿½Ì¸ï¿½ï¿?
        }            
    }        
    arrayForInnerBoardLayout[point.x][point.y] = 1;
    getchar();  
}
//ï¿½×·ï¿½ï¿½ï¿½ï¿½ï¿½
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


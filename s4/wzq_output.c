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

static int color=1; //ָ����ǰ������ɫ

//��������������������
void output(){
    extern int color;

    while (full(arrayForInnerBoardLayout) == 0){
        switch (color){
        case 1:
            printf("�����Ǻڷ����壬�������������λ�ã�");
            black();
            if (forbid(point.x, point.y, (-color+3)/2, 0) == 1)
            {
                printf("���崥�����֣��׷�ʤ����");
                return;
            }
            if (judgeWin(point.x, point.y, (-color+3)/2) == 1)
            {
                printf("�ڷ�ʤ����\n");
                return;
            }
            color=-1;
            break;
        case -1:
            printf("�����ǰ׷����壬�������������λ�ã�");
            white();
            if (judgeWin(point.x, point.y, (-color+3)/2) == 1)
            {
                printf("�׷�ʤ����\n");
                return;
            }
            color=1;
            break;
        default:
            break;
        }
    }
    printf("ƽ�֣�\n");
    return;
}

//�ڷ�����
void black(){
    point=Input();
    
    innerLayoutToDisplayArray();
    arrayForDisplayBoard[point.x][point.y*2] = play1CurrentPic[0];
    arrayForDisplayBoard[point.x][point.y*2+1] = play1CurrentPic[1]; //�����point.y*2+1����Ϊ�����ַ�ռ�����ֽ�
    displayBoard();
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            arrayforRegret[i][j] = arrayForInnerBoardLayout[i][j];  //��¼����ǰ�����̸��
        }            
    }        
    arrayForInnerBoardLayout[point.x][point.y] = 1;
    getchar();  
}
//�׷�����
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


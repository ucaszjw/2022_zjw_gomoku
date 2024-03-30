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
        switch (begin) //begin=1ʱ��������֣�begin=2ʱ����������
        {
        case 1:
            switch (color){
                case 1:
                    printf("�����Ǻڷ����壬�������������λ�ã�");
                    black_p();
                    if (forbid(point.x, point.y, (-color+3)/2, 0) == 1) //�ж��Ƿ񴥷�����
                    {
                        printf("���崥�����֣��׷�ʤ����\n");
                        return;
                    }
                    arrayForInnerBoardLayout[point.x][point.y] = 1;
                    if (judgeWin(point.x, point.y, (-color+3)/2) == 1)  //�ж��Ƿ�ʤ��
                    {
                        printf("�ڷ�ʤ����\n");
                        return;
                    }
                    color=-1;
                    break;
                case -1:
                    white_e();
                    printf("��������λ��Ϊ��%c%d\n",point.y+'A',point.x+1);
                    if (judgeWin(point.x, point.y, (-color+3)/2) == 1)  //�ж��Ƿ�ʤ��
                    {
                        printf("�׷�ʤ����\n");
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
                    printf("��������λ��Ϊ��%c%d\n",point.y+'A',point.x+1);
                    if (forbid(point.x, point.y, (-color+3)/2, 0) == 1) //�ж��Ƿ񴥷�����
                    {
                        printf("�׷�ʤ����\n");
                        return;
                    }
                    arrayForInnerBoardLayout[point.x][point.y] = 1;
                    if (judgeWin(point.x, point.y, (-color+3)/2))   //�ж��Ƿ�ʤ��
                    {
                        printf("�ڷ�ʤ����\n");
                        return;
                    }
                    color=-1;
                    break;
                case -1:
                    white_p();
                    if (judgeWin(point.x, point.y, (-color+3)/2) == 1)
                    {
                        printf("�׷�ʤ����\n");
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
    printf("ƽ�֣�\n");
    return;
}

void outputEVE(){
    extern int color;
    while (full(arrayForInnerBoardLayout) == 0){    //����δ��ʱѭ��
        switch (color)
        {
        case 1:
            black_e();
            printf("����λ��Ϊ��%c%d\n",point.y+'A',point.x+1);
            if (forbid(point.x, point.y, (-color+3)/2, 0) == 1)
            {
                printf("���崥�����֣��׷�ʤ����\n");
                return;
            }
            if (judgeWin(point.x, point.y, (-color+3)/2) == 1)
            {
                printf("�ڷ�ʤ����\n");
                return;
            }
            arrayForInnerBoardLayout[point.x][point.y] = 1;
            color=-1;
            break;
        case -1:
            white_e();
            printf("����λ��Ϊ��%c%d\n",point.y+'A',point.x+1);
            if (judgeWin(point.x, point.y, (-color+3)/2) == 1)
            {
                printf("�׷�ʤ����\n");
                return;
            }
            arrayForInnerBoardLayout[point.x][point.y] = 2;
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
            arrayforRegret2[i][j] = arrayforRegret1[i][j];  //��¼����ǰ���������̸��
        }
        
    }
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            arrayforRegret1[i][j] = arrayForInnerBoardLayout[i][j]; //��¼����ǰһ�������̸��
        }            
    }    
}

//�׷�����
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
            arrayforRegret2[i][j] = arrayforRegret1[i][j];  //��¼����ǰ���������̸��
        }
        
    }
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            arrayforRegret1[i][j] = arrayForInnerBoardLayout[i][j]; //��¼����ǰһ�������̸��
        }            
    }
}

//�ڷ�����
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
            arrayforRegret2[i][j] = arrayforRegret1[i][j];  //��¼����ǰ���������̸��
        }
    }
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            arrayforRegret1[i][j] = arrayForInnerBoardLayout[i][j]; //��¼����ǰһ�������̸��
        }            
    }
}

//�׷�����
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
            arrayforRegret2[i][j] = arrayforRegret1[i][j];  //��¼����ǰ���������̸��
        }
        
    }
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            arrayforRegret1[i][j] = arrayForInnerBoardLayout[i][j]; //��¼����ǰһ�������̸��
        }            
    }
}
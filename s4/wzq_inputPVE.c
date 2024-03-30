#include "gomoku.h"
int mygetline(char *line);
struct Point xyToBoard(char *line);

//InputPVE���������������������겢�ж��Ƿ�Ϸ�
struct Point InputPVE(int begin){
    char line[6];
    extern struct Point point;
    
    extern int color;
    extern int arrayForInnerBoardLayout[SIZE][SIZE];
    extern int arrayforRegret1[SIZE][SIZE]; 
    extern int arrayforRegret2[SIZE][SIZE]; 

    mygetline(line);
    if (line[0] == 'q' && line [1] == '\n') //����qʱ�˳�����
        exit(0);
    else if (line[0] == 'r' && line[1] == '\n'){    //����rʱ����
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                arrayForInnerBoardLayout[i][j] = arrayforRegret2[i][j]; //����ʱ������ǰ���̵ĸ�ָֻ�������ǰ��״̬
            }            
        }
        outputPVE(begin);
    }else{
        point=xyToBoard(line);
        if (point.x >= SIZE || point.y >= SIZE || point.x < 0 || point.y < 0)
        {
            printf("����������Ч��Χ�ڣ����������룺");
            return InputPVE(begin);     //�������ʱ�ݹ���ã�ֱ��������ȷ
        }else if (arrayForInnerBoardLayout[point.x][point.y] != 0)
        {
            printf("�ô��������ӣ����������룺");
            return InputPVE(begin);     //�������ʱ�ݹ���ã�ֱ��������ȷ
        }else{
            return point;
        }
    }
}        
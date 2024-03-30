#include "gomoku.h"
void initRecordBorard(void);
void innerLayoutToDisplayArray(void);
void displayBoard(void);

struct Point point;

//������ģ�� 
char arrayForEmptyBoard[SIZE][SIZE*CHARSIZE+1] = 
{
		"���өөөөөөөөөөөөө�",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"���۩۩۩۩۩۩۩۩۩۩۩۩۩�"
};
//������洢������ʾ������ 
char arrayForDisplayBoard[SIZE][SIZE*CHARSIZE+1];
 
char play1Pic[]="��";//������;
char play1CurrentPic[]="��"; 

char play2Pic[]="��";//������;
char play2CurrentPic[]="��";

//���������ڼ�¼��ǰ�����̵ĸ�� 
int arrayForInnerBoardLayout[SIZE][SIZE];

//���������ڼ�¼����ǰ�����̵ĸ��
int arrayforRegret[SIZE][SIZE];
int arrayforRegret1[SIZE][SIZE];
int arrayforRegret2[SIZE][SIZE];




//��ʼ��һ�������̸�� 
void initRecordBorard(void){
	//ͨ��˫��ѭ������arrayForInnerBoardLayout��0
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            arrayForInnerBoardLayout[i][j] = 0;
            arrayforRegret[i][j] = 0;
            arrayforRegret1[i][j] = 0;
            arrayforRegret2[i][j] = 0;
        }
        
    }   
}

//��arrayForInnerBoardLayout�м�¼������λ�ã�ת����arrayForDisplayBoard��
void innerLayoutToDisplayArray(void){
	//��һ������arrayForEmptyBoard�м�¼�Ŀ����̣����Ƶ�arrayForDisplayBoard��
        for (int i = 0; i < 15; i++)
        {
            for (int j = 0; j < 31; j++)
            {
                arrayForDisplayBoard[i][j] = arrayForEmptyBoard[i][j];
            }            
        }
        



	//�ڶ�����ɨ��arrayForInnerBoardLayout����������0��Ԫ�أ�������ߡ��Ƶ�arrayForDisplayBoard����Ӧλ����
	//ע�⣺arrayForDisplayBoard����¼���ַ��������ַ���ÿ���ַ�ռ2���ֽڡ���͡�Ҳ�������ַ���ÿ��Ҳռ2���ֽڡ�
        for (int i = 0; i < 15; i++)
        {
            for (int j = 0; j < 15; j++)
            {
                switch (arrayForInnerBoardLayout[i][j])
                {
                case 0:
                    arrayForDisplayBoard[i][j*2] = arrayForEmptyBoard[i][j*2];
                    arrayForDisplayBoard[i][j*2+1] = arrayForEmptyBoard[i][j*2+1];
                    break;
                case 1:
                    arrayForDisplayBoard[i][j*2] = play1Pic[0];
                    arrayForDisplayBoard[i][j*2+1] = play1Pic[1];
                    break;
                case 2:
                    arrayForDisplayBoard[i][j*2] = play2Pic[0];
                    arrayForDisplayBoard[i][j*2+1] = play2Pic[1];
                    break;
                default:
                    break;
                }
            }
            
        } 
}


//��ʾ���̸�� 
void displayBoard(void){
	int i;
	//��һ��������
	system("clear");   //����  
	//�ڶ�������arrayForDisplayBoard�������Ļ��
        for (i = 0; i < 15; i++)
        {
            printf("%2d %s\n",i+1,arrayForDisplayBoard[i]);
        }
	

	//������������������һ����ĸA B .... 
        printf("   A B C D E F G H I J K L M N O\n");

}

//�ж������Ƿ�����
int full(int array[SIZE][SIZE]){
    int flag = 1;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++){
            if (array[i][j] == 0)
            {
                flag = 0;
            }
        }
    }
    return flag;
}

//������ӣ�����ɾ��
struct Point randomgomoku(){
    struct Point point;
    int x, y;
    srand((unsigned)time(NULL));
    x = rand() % SIZE;
    y = rand() % SIZE;
    while (arrayForInnerBoardLayout[x][y] != 0)
    {
        x = rand() % SIZE;
        y = rand() % SIZE;
    }
    point.x = x;
    point.y = y;
    return point;
}

//�����������ת��Ϊ�����±�
struct Point xyToBoard(char *line){
    if (line[0] >= 'A' && line[0] <= 'O'){
        point.y = line[0] - 'A';
        if (line[2] != '\0' && line[2] != '\n'){
            point.x = 10 * (line[1] - '0') + (line[2] - '0') - 1;
        }else{
            point.x = line[1] - '1';
        }        
    }else if(line[0] >= '1' && line[0] <= '9'){
        if (line[2] != '\0' && line[2] != '\n'){
            if (line[2] >= 'A' && line[2] <= 'O'){
                point.x = 10 * (line[0] - '0') + (line[1] - '0') - 1;
                point.y = line[2] - 'A';
            }else{
                point.x = 10 * (line[0] - '0') + (line[1] - '0') - 1;
                point.y = line[2] - 'a';
            }
        }else{
            if (line[2] >= 'A' && line[2] <= 'O'){
                point.x = line[0] - '1';
                point.y = line[1] - 'A';
            }else{
                point.x = line[0] - '1';
                point.y = line[1] - 'a';
            }               
        }
    }else if (line[0] >= 'a' && line[0] <= 'o'){
            point.y = line[0] - 'a';
        if (line[2] != '\0' && line[2] != '\n'){
            point.x = 10 * (line[1] - '0') + (line[2] - '0') - 1;
        }else
            point.x = line[1] - '1';
    }else{
        printf("����������Ч��Χ�ڣ����������룺");
        return Input();
    }
    return point;
}

int mygetline(char *s){
    int c, i;
    i = 0;
    while((c = getchar()) != EOF && c != '\n'){
        s[i++] = c;
    }
    if(c == '\n'){
        s[i++] = c;
    }
    s[i] = '\0';
    return i;
}
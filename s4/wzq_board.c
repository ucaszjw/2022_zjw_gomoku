#include "gomoku.h"
void initRecordBorard(void);
void innerLayoutToDisplayArray(void);
void displayBoard(void);

//空棋盘模板 
char arrayForEmptyBoard[SIZE][SIZE*CHARSIZE+1] = 
{
		"┏┯┯┯┯┯┯┯┯┯┯┯┯┯┓",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┗┷┷┷┷┷┷┷┷┷┷┷┷┷┛"
};
//此数组存储用于显示的棋盘 
char arrayForDisplayBoard[SIZE][SIZE*CHARSIZE+1];
 
char play1Pic[]="●";//黑棋子;
char play1CurrentPic[]="▲"; 

char play2Pic[]="◎";//白棋子;
char play2CurrentPic[]="△";

//此数组用于记录当前的棋盘的格局 
int arrayForInnerBoardLayout[SIZE][SIZE];

//此数组用于记录悔棋前的棋盘的格局
int arrayforRegret[SIZE][SIZE];
int arrayforRegret1[SIZE][SIZE];
int arrayforRegret2[SIZE][SIZE];




//初始化一个空棋盘格局 
void initRecordBorard(void){
	//通过双重循环，将arrayForInnerBoardLayout清0
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

//将arrayForInnerBoardLayout中记录的棋子位置，转化到arrayForDisplayBoard中
void innerLayoutToDisplayArray(void){
	//第一步：将arrayForEmptyBoard中记录的空棋盘，复制到arrayForDisplayBoard中
        for (int i = 0; i < 15; i++)
        {
            for (int j = 0; j < 31; j++)
            {
                arrayForDisplayBoard[i][j] = arrayForEmptyBoard[i][j];
            }            
        }
        



	//第二步：扫描arrayForInnerBoardLayout，当遇到非0的元素，将●或者◎复制到arrayForDisplayBoard的相应位置上
	//注意：arrayForDisplayBoard所记录的字符是中文字符，每个字符占2个字节。●和◎也是中文字符，每个也占2个字节。
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


//显示棋盘格局 
void displayBoard(void){
	int i;
	//第一步：清屏
	system("clear");   //清屏  
	//第二步：将arrayForDisplayBoard输出到屏幕上
        for (i = 0; i < 15; i++)
        {
            printf("%2d %s\n",i+1,arrayForDisplayBoard[i]);
        }
	

	//第三步：输出最下面的一行字母A B .... 
        printf("   A B C D E F G H I J K L M N O\n");

}

//判断棋盘是否已满
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

//随机落子（懒得删了
struct point randomgomoku(){
    struct point point;
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

//将输入的坐标转化为数组下标
struct point xyToBoard(char *line){
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
        printf("不在棋盘有效范围内，请重新输入：");
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
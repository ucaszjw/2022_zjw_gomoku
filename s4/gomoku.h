#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>   //用于生成随机数

#define SIZE 15
#define CHARSIZE 2

#define huothree_1b  117  //011100
#define huothree_2b  39   //001110
#define huothree_3b  111  //011010
#define huothree_4b  93   //010110
#define chongfour_1b 112 //11011
#define chongfour_2b 94  //10111
#define chongfour_3b 118 //11101
#define chongthree_1b 91 //10101
#define chongthree_2b 111 //11010
#define chongthree_3b 93 //10110
#define chongthree_4b 85 //10011
#define chongthree_5b 109 //11001
#define chongthree_6b 37 //01101
#define chongthree_7b 31 //01011
#define huotwo_1b 108 //011000
#define huotwo_2b 12 //000110
#define huotwo_3b 30 //001010
#define huotwo_4b 90 //010100
#define huotwo_5b 84 //010010

#define huothree_1w 234 //022200
#define huothree_2w 78 //002220
#define huothree_3w 222 //022020
#define huothree_4w 186 //020220
#define chongfour_1w 224 //22022
#define chongfour_2w 188 //20222
#define chongfour_3w 236 //22202
#define chongthree_1w 183 //20202
#define chongthree_2w 222 //22020
#define chongthree_3w 186 //20220
#define chongthree_4w 170 //20022
#define chongthree_5w 218 //22002
#define chongthree_6w 74 //02202
#define chongthree_7w 62 //02022
#define huotwo_1w 216 //022000
#define huotwo_2w 24 //000220
#define huotwo_3w 60 //002020
#define huotwo_4w 180 //020200
#define huotwo_5w 168 //020020


struct Point
{
	int x;
	int y;
};

typedef struct {
    int i;
    int j;
    int score;
} PositionScore;

struct Point Input();
struct Point InputPVE(int begin);
int mygetline(char *s);
struct Point xyToBoard(char *line);
void output();
void outputPVE(int begin);
void outputEVE();


int full(int array[SIZE][SIZE]);

void initRecordBorard(void);
void innerLayoutToDisplayArray(void);
void displayBoard(void);
int judgeWin(int x, int y, int color);
int forbid(int x,int y,int color,int isRecursive);
int isHuoFour(int x, int y, int dx, int dy, int color);
int isChongFour1(int x, int y, int dx, int dy, int color);
int isChongFour2(int x, int y, int dx, int dy, int color);
int isHuoThree(int x, int y, int dx, int dy, int color);
int isChongThree(int x, int y, int dx, int dy, int color);
int isHuoTwo(int x, int y, int dx, int dy, int color);
int inRange(int x, int y);
struct Point position(int x, int y, int color);
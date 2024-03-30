#include "gomoku.h"
int mygetline(char *line);
struct Point xyToBoard(char *line);

//Inputï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ê²¢ï¿½Ð¶ï¿½ï¿½Ç·ï¿½Ï·ï¿?
struct Point Input(){
    char line[6];
    
    extern int color;
    extern int arrayForInnerBoardLayout[SIZE][SIZE];
    extern int arrayforRegret[SIZE][SIZE];
    extern struct Point point;

    mygetline(line);
    if (line[0] == 'q' && line [1] == '\n') //ï¿½ï¿½ï¿½ï¿½qÊ±ï¿½Ë³ï¿½ï¿½ï¿½ï¿½ï¿½
        exit(0);
    else if (line[0] == 'r' && line[1] == '\n'){    //ï¿½ï¿½ï¿½ï¿½rÊ±ï¿½ï¿½ï¿½ï¿½
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                arrayForInnerBoardLayout[i][j] = arrayforRegret[i][j];  //ï¿½ï¿½ï¿½ï¿½Ê±ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ç°ï¿½ï¿½ï¿½ÌµÄ¸ï¿½Ö»Ö¸ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ç°ï¿½ï¿½×´Ì?
            }            
        }
        color = -color;
        output();
    }else{
        point=xyToBoard(line);
        if (point.x >= SIZE || point.y >= SIZE || point.x < 0 || point.y < 0)
        {
            printf("²»ÔÚÆåÅÌÓÐÐ§·¶Î§ÄÚ£¬ÇëÖØÐÂÊäÈë£º£º");
            return Input();    //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ê±ï¿½Ý¹ï¿½ï¿½ï¿½Ã£ï¿½Ö±ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½È·
        }else if (arrayForInnerBoardLayout[point.x][point.y] != 0)
        {
            printf("¸Ã´¦ÒÑÓÐÆå×Ó£¬ÇëÖØÐÂÊäÈë£º");
            return Input();   //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ê±ï¿½Ý¹ï¿½ï¿½ï¿½Ã£ï¿½Ö±ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½È·
        }else{
            return point;
        }
    }
}
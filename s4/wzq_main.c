#include "gomoku.h"

void initRecordBorard(void);
void innerLayoutToDisplayArray(void);
void displayBoard(void);

int mode;
int color;
int begin;

int main(){
    printf("��ѡ����Ϸģʽ��\n 1. ���˶�ս\n 2. �˻���ս\n 3. ������ս\n");
    scanf("%d",&mode);

    if (mode==1)
    {
        getchar();
        printf("����������ʽ�磺A1,9g,12h,e4\n ����r���壨ÿ�غ����ɻ���һ�Σ�\n ����q�˳���Ϸ\n ���ڿ�ʼ��Ϸ�ɣ�\n");
        getchar();
        initRecordBorard();    //��ʼ��һ��������
        innerLayoutToDisplayArray();
        displayBoard();
        getchar();
        
        output();
    }else if (mode==2){
        getchar();
        printf("����������ʽ�磺A1,9g,12h,e4\n ����r���壨ÿ�غ����ɻ���һ�Σ�\n ����q�˳���Ϸ\n ���ڿ�ʼ��Ϸ�ɣ�\n");
        getchar();
        initRecordBorard();    //��ʼ��һ��������
        innerLayoutToDisplayArray();
        displayBoard();

        printf("��ѡ��ִ�������壺\n 1. ִ����\n 2. ִ����\n");
        scanf("%d",&begin);
        if (begin==1 || begin==2)
        {
            outputPVE(begin);
        }else{
            printf("�������");
        }
    }else if (mode==3)
    {
        initRecordBorard();    //��ʼ��һ��������
        innerLayoutToDisplayArray();
        displayBoard();
        getchar();

        outputEVE();
    }
    
    else{
        printf("�������");
    }    
    return 0;
}
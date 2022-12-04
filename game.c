#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")

#define UP 1
#define DOWN 2
#define ENT 3

#define WHITE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); //�ܼ� ��� �����
#define YELLOW SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
#define RED SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
#define GREEN SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);


void CursorView() //Ŀ�� �����
{
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
void cursor(int, int);
int menu();
int Key();
void stDown();
void title();
// int chosUser();
int blackjack();
void backPrt();
int cardPrt();
int qstRe(); //���� �̾��ϱ� ���� �����
int qstReSlot(); //���� �̾��ϱ� ���� ���Կ�
int slotGame();
int playSlot();
void slotPicPrt();
void slotrepeatprt();

int main()
{
    system("mode con:cols=60 ilnes=60 | title KWLand");
    CursorView();

    printf("     ��   A:����  Z:�Ʒ���  ENTER:����   ��\n     ������������������������������������������������������������������������\n");

    printf("               #  ##     #   # \n");
    printf("               # ##      # # # \n");
    printf("               ##        # # # \n");
    printf("               # ##       ###  \n");
    printf("               #  ##      # #  \n\n");
    printf("        #        ###    ####    ####      \n");
    printf("        #       #   #   #   #   #   #     \n");
    printf("        #       #####   #   #   #   #     \n");
    printf("        #       #   #   #   #   #   #     \n");
    printf("         ####   #   #   #   #   ####      \n\n\n");

    int menuNum = menu();
    if (menuNum==17){ //���� ����
        PlaySound(TEXT(".\\sound\\back.wav"), 0, SND_FILENAME | SND_ASYNC );
        stDown();
        return 0;
    }
    else if (menuNum==16){ //���Ըӽ�
        PlaySound(TEXT(".\\sound\\enter.wav"), 0, SND_FILENAME | SND_ASYNC );
        int bett = 10000;
        int m = playSlot(200000, &bett); //���ñݾ� ���� ���ӿ����� �����ϵ��� �������̿�
        while(1){
            int qcheck = qstReSlot(m);
            if (qcheck==0){
                return 0;
            }
            else if (qcheck==1){
                if (bett>m) bett=m; //���̳ʽ� �Ӵ� ������
                m = playSlot(m, &bett);
            }
        }


    }
    else if (menuNum==15){ //����
        //chosUser(); ������� �ʴ� �ڵ�
        PlaySound(TEXT(".\\sound\\enter.wav"), 0, SND_FILENAME | SND_ASYNC );
        backPrt();
        int m = blackjack(200000);

        while(1){
            int qcheck = qstRe(m);
            if (qcheck==0){
                stDown();
                return 0;
            }
            else if (qcheck==1){
                backPrt();
                m = blackjack(m);
            }
        }

    }
    system("pause");
    return 0;
}  


int qstReSlot(int m)
{
    YELLOW;
    if (m==0){
        cursor(3,11);
        printf(" ����Ʈ�� �����ϴ�.  ���� P : %d ", m);
        cursor(4,12);
        printf("   ������ 3�� �� ����˴ϴ�.    ");
        Sleep(3000);
        return 0;
    }
    cursor(3,11);
    printf(" ���� P : %d  �������� : A ", m);
    cursor(4,12);
    printf("            ���� ���� : Enter ");
    WHITE;
    while(1){
        int n = Key();
        switch(n){
            case UP:{
                PlaySound(TEXT(".\\sound\\back.wav"), 0, SND_FILENAME | SND_ASYNC );
                Sleep(300);
                return 0;
            }
            case ENT:{
                return 1;
            }
        }
    }

}


int qstRe(int m)
{
    YELLOW;
    if (m==0){
        cursor(4,11);
        printf("       ����Ʈ�� �����ϴ�.  ���� P : %d       ", m);
        cursor(4,12);
        printf("            ������ 3�� �� ����˴ϴ�.             ");
        Sleep(3000);
        return 0;
    }
    cursor(4,11);
    printf("               ���� P : %d              ", m);
    cursor(4,12);
    printf("     ���� ���� : A    ���� ���� : Enter      ");
    WHITE;
    while(1){
        int n = Key();
        switch(n){
            case UP:{
                PlaySound(TEXT(".\\sound\\back.wav"), 0, SND_FILENAME | SND_ASYNC );
                return 0;
            }
            case ENT:{
                return 1;
            }
        }
    }

}

/*
int chosUser() ??????? ??? ???
{
    int x=8, y=7;
    system("cls");
    cursor(6, 5);
    printf("?????? ??j? ????");
    cursor(8, 7);
    printf("> 1??");
    cursor(10, 8);
    printf("2??");

    while(1){
        int n = Key();
        switch(n){
            case UP:{
                if(y>7){
                    cursor(x, y);
                    printf(" ");
                    cursor(x, --y);
                    printf(">");
                    
                }
                break;
            }
            case DOWN:{
                if(y<8){
                    cursor(x, y);
                    printf(" ");
                    cursor(x, ++y);
                    printf(">");
                    
                }
                break;
            }
            case ENT:{
                return y;  //7(1??) ??? 8(2??) ???
            }
        }
    }
}
*/


int cardPrt(int cnum, int x, int y)
{
    PlaySound(TEXT(".\\sound\\card.wav"), 0, SND_FILENAME | SND_ASYNC );
    char *shape[2];
    if(cnum>0 && cnum<14){  //ī�� ����, �� ����
        shape[0] = "��";
        WHITE;
    }
    else if(cnum>13 && cnum<27){
        shape[0] = "��";
        WHITE;
    }
    else if(cnum>26 && cnum<40){
        shape[0] = "��";
        RED;
    }
    else{
        shape[0] = "��";
        RED;
    }

    if(cnum%13==0){  //ī�� ���� ���� A, 1~10, J, Q, K
        cnum=13;
    }
    else{
        cnum=cnum%13;
    }

    if (cnum==11){
        cursor(x,y);
        printf("%s J", shape[0]);
        return 10;
    }
    else if(cnum==12){
        cursor(x,y);
        printf("%s Q", shape[0]);
        return 10;
    }
    else if(cnum==13){
        cursor(x,y);
        printf("%s K", shape[0]);
        return 10;
    }
    // J Q K �� 10 ��ȯ, �������� ī�� ���� ��ȯ
    else{
        cursor(x,y);
        printf("%s %d", shape[0], cnum);
        return cnum;
    }

}

void hidedCardPrt(int cnum)  //���ϰ� ���� ���� ù��° ī�� ���� �Լ�
{
    char *shape[2];
    if(cnum>0 && cnum<14){
        shape[0] = "��";
        WHITE;
    }
    else if(cnum>13 && cnum<27){
        shape[0] = "��";
        WHITE;
    }
    else if(cnum>26 && cnum<40){
        shape[0] = "��";
        RED;
    }
    else{
        shape[0] = "��";
        RED;
    }

    if(cnum%13==0){
        cnum=13;
    }
    else{
        cnum=cnum%13;
    }

    cursor(7, 3);
    if (cnum==11){
        printf("%s J", shape[0]);
    }
    else if(cnum==12){
        printf("%s Q", shape[0]);
    }
    else if(cnum==13){
        printf("%s K", shape[0]);
    }
    else{
        printf("%s %d", shape[0], cnum);
    }

}



int blackjack(int money)
{
    int bet = 10000;
    cursor(42,1);
    printf("%d", money);
    cursor(5,11);
    printf("�����Ͻʽÿ�.          ���� �׼� ���� : A Z");
    cursor(32,12);
    printf("�����ϱ� : Enter");
    cursor(42,4);
    printf("%d", bet);

    int wnum=1;
    while(wnum==1){
        int n = Key();
        switch(n){
            case UP:{
                if(bet<money){
                    bet+=10000;
                    cursor(42, 4);
                    printf("%d ", bet);
                }
                break;
            }
            case DOWN:{
                if(bet>10000){
                    bet-=10000;
                    cursor(42, 4);
                    printf("%d ", bet);   
                }
                break;
            }
            case ENT:{
                wnum=0;
                cursor(35,4);
                printf("              ");
            }
        }
    }

    money-=bet;
    PlaySound(TEXT(".\\sound\\lever.wav"), 0, SND_FILENAME | SND_ASYNC );
    cursor(42,1);
    printf("%7d", money);
    cursor(42,2);
    RED;
    printf("-%d", bet);
    cursor(4,11);
    WHITE;
    printf("������ �Ϸ�Ǿ����ϴ�.");
    Sleep(1400);
    cursor(32,12);
    printf("                ");
    for(int i=3; i>0; i--){
        cursor(4,11);
        printf("         ������ �� ���۵˴ϴ�...%d           ", i);
        Sleep(1000);
    }
    cursor(42,2);
    printf("        ");
    cursor(4,11);
    printf("           ī�带 ����մϴ�...           ");
    Sleep(1000);



    srand((int)time(NULL));
    int cardNum;
    int save[53];   //�ߺ��˻�� �迭
    int saveArrNum=0;
    int dealSum=0, userSum=0;
    int userNum=1;
    int userY=3, dealY=3;
    int hidedCardNum;   //���� ù��° ī���ȣ �����
    
    int checkNum=1;
    while(checkNum==1){
        cardNum = rand()%52+1;
        for(int i=0; i<53; i++){
            if (cardNum==save[i]){
                break;
            }
            else if (i==52 && dealY==5){   // i=�ߺ��˻� ���, dealY=5 - ���� ī�� 2�� �޾��� ��
                cursor(4,11);
                WHITE;
                printf("           ���ĵ� : A   ��Ʈ : Z            ");
                wnum=1;
                while(wnum==1){
                    int n = Key();
                    switch(n){
                        case UP:{   //���� ���ĵ� ��
                            hidedCardPrt(hidedCardNum);
                            PlaySound(TEXT(".\\sound\\tik.wav"), 0, SND_FILENAME | SND_ASYNC );
                            Sleep(1300);
                            if(dealSum>16){  //���� ī�� �� 17�̻��� ��
                                if(dealSum<=userSum && userSum<22){
                                    cursor(4,11);
                                    WHITE;
                                    if (userSum==21){
                                        printf("       �¸�! �÷��̾�� �����Դϴ�.      ");
                                        money+=(bet*3);
                                        cursor(42,2);
                                        GREEN;
                                        printf("+%d", bet*3);
                                    }
                                    else{
                                        printf("        �¸�! �÷��̾�� %d �Դϴ�.     ", userSum);
                                        money+=(bet*2);
                                        cursor(42,2);
                                        GREEN;
                                        printf("+%d", bet*2);
                                    }
                                    WHITE;
                                    cursor(42,1);
                                    printf("%7d ", money);
                                    Sleep(2000);
                                    return money;
                                }
                                else if(dealSum>userSum){
                                    cursor(4,11);
                                    WHITE;
                                    printf("        �й�! �÷��̾�� %d �Դϴ�.     ", userSum);
                                    Sleep(2000);
                                    return money;
                                }
                            }
                            else if(dealSum<17){   //����ī���� 17������ �� ���� ī�� �� ����
                                while(dealSum<17){
                                    cardNum = rand()%52+1;
                                    for(int i=0; i<53; i++){
                                        if (cardNum==save[i]){
                                            break;
                                        }
                                        else if(i==52){
                                            save[saveArrNum] = cardNum;
                                            saveArrNum++;
                                            dealSum+=cardPrt(cardNum, 7, dealY);
                                            dealY++;
                                            Sleep(1100);
                                        }
                                    }
                                }
                                if((dealSum<=userSum && userSum<22) || dealSum>21){
                                    cursor(4,11);
                                    WHITE;
                                    if (userSum==21){
                                        printf("       �¸�! �÷��̾�� �����Դϴ�.      ");
                                        money+=(bet*3);
                                        cursor(42,2);
                                        GREEN;
                                        printf("+%d", bet*3);
                                    }
                                    else{
                                        printf("        �¸�! �÷��̾�� %d �Դϴ�.     ", userSum);
                                        money+=(bet*2);
                                        cursor(42,2);
                                        GREEN;
                                        printf("+%d", bet*2);
                                    }
                                    WHITE;
                                    cursor(42,1);
                                    printf("%7d ", money);
                                    Sleep(2000);
                                    return money;
                                }
                                else if(dealSum>userSum && dealSum<22){
                                    cursor(4,11);
                                    WHITE;
                                    printf("        �й�! �÷��̾�� %d �Դϴ�.        ", userSum);
                                    Sleep(2000);
                                    return money;
                                }
                            }
                        }

                        case DOWN:{   //���� ��Ʈ ��
                            userHit:
                            while(userSum<22){
                                cardNum = rand()%52+1;
                                for(int i=0; i<53; i++){
                                    if (cardNum==save[i]){
                                        break;
                                    }
                                    else if(i==52){
                                        save[saveArrNum] = cardNum;
                                        saveArrNum++;
                                        userSum+=cardPrt(cardNum, 23, userY);
                                        if (userSum>21){
                                            hidedCardPrt(hidedCardNum);
                                            Sleep(1300);
                                            cursor(4,11);
                                            WHITE;
                                            printf("       �й�! �÷��̾�� ����Ʈ�Դϴ�.     ");
                                            Sleep(2000);
                                            return money;
                                        }
                                        userY++;
                                        Sleep(1100);
                                    }
                                }
                                cursor(4,11);
                                WHITE;
                                printf("           ���ĵ� : A   ��Ʈ : Z            ");
                                int wnum=1;
                                while(wnum==1){
                                    int n = Key();
                                    switch(n){
                                        case UP:{
                                            PlaySound(TEXT(".\\sound\\tik.wav"), 0, SND_FILENAME | SND_ASYNC );
                                            if(dealSum>16){
                                                hidedCardPrt(hidedCardNum);
                                                Sleep(1300);
                                                if(dealSum<=userSum && userSum<22){
                                                    cursor(4,11);
                                                    WHITE;
                                                    if (userSum==21){
                                                        printf("       �¸�! �÷��̾�� �����Դϴ�.      ");
                                                        money+=(bet*3);
                                                        cursor(42,2);
                                                        GREEN;
                                                        printf("+%d", bet*3);
                                                    }
                                                    else{
                                                        printf("        �¸�! �÷��̾�� %d �Դϴ�.     ", userSum);
                                                        money+=(bet*2);
                                                        cursor(42,2);
                                                        GREEN;
                                                        printf("+%d", bet*2);
                                                    }
                                                    WHITE;
                                                    cursor(42,1);
                                                    printf("%7d ", money);
                                                    Sleep(2000);
                                                    return money;
                                                }
                                                else if(dealSum>userSum || userSum>21){
                                                    cursor(4,11);
                                                    WHITE;
                                                    printf("        �й�! �÷��̾�� %d �Դϴ�.     ", userSum);
                                                    Sleep(2000);
                                                    return money;
                                                }
                                            }
                                            else if(dealSum<17){
                                                hidedCardPrt(hidedCardNum);
                                                Sleep(1300);
                                                while(dealSum<17){
                                                    cardNum = rand()%52+1;
                                                    for(int i=0; i<53; i++){
                                                        if (cardNum==save[i]){
                                                            break;
                                                        }
                                                        else if(i==52){
                                                            save[saveArrNum] = cardNum;
                                                            saveArrNum++;
                                                            dealSum+=cardPrt(cardNum, 7, dealY);
                                                            dealY++;
                                                            Sleep(1100);
                                                        }
                                                    }
                                                }
                                                if((dealSum<=userSum && userSum<22) || (dealSum>21 && userSum<22) ){
                                                    cursor(4,11);
                                                    WHITE;
                                                    if (userSum==21){
                                                        printf("       �¸�! �÷��̾�� �����Դϴ�.      ");
                                                        money+=(bet*3);
                                                        cursor(42,2);
                                                        GREEN;
                                                        printf("+%d", bet*3);
                                                        
                                                    }
                                                    else{
                                                        printf("        �¸�! �÷��̾�� %d �Դϴ�.     ", userSum);
                                                        money+=(bet*2);
                                                        cursor(42,2);
                                                        GREEN;
                                                        printf("+%d", bet*2);
                                                    }
                                                    WHITE;
                                                    cursor(42,1);
                                                    printf("%7d ", money);
                                                    Sleep(2000);
                                                    return money;
                                                }
                                                else if(dealSum>userSum && dealSum<22){
                                                    cursor(4,11);
                                                    WHITE;
                                                    printf("        �й�! �÷��̾�� %d �Դϴ�.        ", userSum);
                                                    Sleep(2000);
                                                    return money;
                                                }
                                            }
                                        }
                                        case DOWN:{   //���� ����Ʈ ��
                                            goto userHit;  
                                        }
                                    }
                                }

                            }

                        }
                    }
                }
                
            }


            else if (i==52 && userNum==1){  //���� ī�� �ޱ�
                save[saveArrNum] = cardNum;
                saveArrNum++;
                userSum+=cardPrt(cardNum, 23, userY);
                userNum=0;
                userY++;
                Sleep(1100);
            }


            else if (i==52 && userNum==0 && dealY==3){  //���� ī�� �ޱ�(ù��°)
                save[saveArrNum] = cardNum;
                saveArrNum++;
                hidedCardNum = cardNum;
                dealSum+=cardPrt(cardNum, 7, dealY);
                cursor(7,3);
                YELLOW;
                printf(" ? ?");
                userNum=1;
                dealY++;
                Sleep(1100);
            }


            else if (i==52 && userNum==0&& dealY!=3){  //���� ī�� �ޱ�
                save[saveArrNum] = cardNum;
                saveArrNum++;
                dealSum+=cardPrt(cardNum, 7, dealY);
                userNum=1;
                dealY++;
                Sleep(1100);
            }
            
        }
    }

}

void backPrt()
{
    system("cls");
    printf("������������������������������������������������������������������������������������������������������\n"); //0
    printf("��     Dealer    ��      User      ��    P :         ��\n");
    printf("��               ��                ��                ��\n");
    printf("��               ��                ������������������������������������\n");
    printf("��               ��                   Bet :         ��\n");
    printf("��               ��                                 ��\n"); //5
    printf("��               ��                                 ��\n");
    printf("��               ��                                 ��\n");
    printf("��               ��                                 ��\n");
    printf("������������������������������������������������������������������������������������������������������\n");
    printf("��                                                 ��\n"); //10
    printf("��                                                 ��\n");
    printf("��                                                 ��\n");
    printf("��                                                 ��\n");
    printf("������������������������������������������������������������������������������������������������������\n"); //14
}


void slotPrt()
{
    system("cls");
    printf("��������������������������������������������������������������������������������������������������������\n"); //0
    printf("��     #####      ��     #####      ��     #####      ��\n");
    printf("��   ##     ##    ��   ##     ##    ��   ##     ##    ��\n");
    printf("��  ##       ##   ��  ##       ##   ��  ##       ##   ��\n");
    printf("��          ##    ��          ##    ��          ##    ��\n");
    printf("��        ##      ��        ##      ��        ##      ��\n"); //5
    printf("��       ##       ��       ##       ��       ##       ��\n");
    printf("��                ��                ��                ��\n");
    printf("��       ##       ��       ##       ��       ##       ��\n");
    printf("��������������������������������������������������������������������������������������������������������\n");
    printf("��                                      P :         ��\n"); //10
    printf("��                                                  ��\n");
    printf("��                                                  ��\n");
    printf("��                                    Bet :         ��\n");
    printf("��������������������������������������������������������������������������������������������������������\n"); //14


}

void slotrepeatprt(int x, int y)
{
    srand((int)time(NULL));
    int repeatnum = rand()%20+10;
    
    int k;
    for (int i=0; i<repeatnum; i++){
        k = i%7;
        if (i==4) PlaySound(TEXT(".\\sound\\spin.wav"), 0, SND_FILENAME | SND_ASYNC );
        switch(k){
            case 1:
                cursor(x,y);
                printf("    ########   ");
                cursor(x,y+1);
                printf("   #        #  ");
                cursor(x,y+2);
                printf("  ############ ");
                cursor(x,y+3);
                printf("   #        #  ");
                cursor(x,y+4);
                printf("    #      #   ");
                cursor(x,y+5);
                printf("     #    #    ");
                cursor(x,y+6);
                printf("      #  #     ");
                cursor(x,y+7);
                printf("       ##      ");
                break;

            case 2:
                cursor(x,y);
                printf("               ");
                cursor(x,y+1);
                printf("   ##########  ");
                cursor(x,y+2);
                printf("   #        #  ");
                cursor(x,y+3);
                printf("   #        #  ");
                cursor(x,y+4);
                printf("   #        #  ");
                cursor(x,y+5);
                printf("   #        #  ");
                cursor(x,y+6);
                printf("   ##########  ");
                cursor(x,y+7);
                printf("               ");
                break;

            case 3:
                cursor(x,y);
                printf("               ");
                cursor(x,y+1);
                printf("       ##      ");
                cursor(x,y+2);
                printf("      #  #     ");
                cursor(x,y+3);
                printf("     #    #    ");
                cursor(x,y+4);
                printf("    #      #   ");
                cursor(x,y+5);
                printf("   #        #  ");
                cursor(x,y+6);
                printf("  ############ ");
                cursor(x,y+7);
                printf("               ");
                break;

            case 4:
                cursor(x,y);
                printf("       ##      ");
                cursor(x,y+1);
                printf("       ##      ");
                cursor(x,y+2);
                printf("       ##      ");
                cursor(x,y+3);
                printf("       ##      ");
                cursor(x,y+4);
                printf("       ##      ");
                cursor(x,y+5);
                printf("       ##      ");
                cursor(x,y+6);
                printf("       ##      ");
                cursor(x,y+7);
                printf("       ##      ");
                break;

            case 5:
                cursor(x,y);
                printf("               ");
                cursor(x,y+1);
                printf("  ############ ");
                cursor(x,y+2);
                printf("  #          # ");
                cursor(x,y+3);
                printf("  ##        ## ");
                cursor(x,y+4);
                printf("   ##      ##  ");
                cursor(x,y+5);
                printf("    ###  ###   ");
                cursor(x,y+6);
                printf("      ####     ");
                cursor(x,y+7);
                printf("               ");
                break;

            case 6:
                cursor(x,y);
                printf("  ############ ");
                cursor(x,y+1);
                printf("            ## ");
                cursor(x,y+2);
                printf("           ##  ");
                cursor(x,y+3);
                printf("          ##   ");
                cursor(x,y+4);
                printf("         ##    ");
                cursor(x,y+5);
                printf("        ##     ");
                cursor(x,y+6);
                printf("       ##      ");
                cursor(x,y+7);
                printf("      ##       ");
                break;

            case 0:
                cursor(x,y);
                printf("      ####     ");
                cursor(x,y+1);
                printf("    ##    ##   ");
                cursor(x,y+2);
                printf("   ##     ###  ");
                cursor(x,y+3);
                printf("  ##    ##  ## ");
                cursor(x,y+4);
                printf("  ##  ##    ## ");
                cursor(x,y+5);
                printf("   ###     ##  ");
                cursor(x,y+6);
                printf("    ##    ##   ");
                cursor(x,y+7);
                printf("      ####     ");
                break;
        }
        Sleep(45); 
    }
}

void slotPicPrt(int picnum, int x, int y)
{
    slotrepeatprt(x, y);
    PlaySound(NULL, 0, 0);
    PlaySound(TEXT(".\\sound\\bam.wav"), 0, SND_FILENAME | SND_ASYNC );
    switch(picnum){
            case 1:
                cursor(x,y);
                printf("    ########   ");
                cursor(x,y+1);
                printf("   #        #  ");
                cursor(x,y+2);
                printf("  ############ ");
                cursor(x,y+3);
                printf("   #        #  ");
                cursor(x,y+4);
                printf("    #      #   ");
                cursor(x,y+5);
                printf("     #    #    ");
                cursor(x,y+6);
                printf("      #  #     ");
                cursor(x,y+7);
                printf("       ##      ");
                break;

            case 2:
                cursor(x,y);
                printf("               ");
                cursor(x,y+1);
                printf("   ##########  ");
                cursor(x,y+2);
                printf("   #        #  ");
                cursor(x,y+3);
                printf("   #        #  ");
                cursor(x,y+4);
                printf("   #        #  ");
                cursor(x,y+5);
                printf("   #        #  ");
                cursor(x,y+6);
                printf("   ##########  ");
                cursor(x,y+7);
                printf("               ");
                break;

            case 3:
                cursor(x,y);
                printf("               ");
                cursor(x,y+1);
                printf("       ##      ");
                cursor(x,y+2);
                printf("      #  #     ");
                cursor(x,y+3);
                printf("     #    #    ");
                cursor(x,y+4);
                printf("    #      #   ");
                cursor(x,y+5);
                printf("   #        #  ");
                cursor(x,y+6);
                printf("  ############ ");
                cursor(x,y+7);
                printf("               ");
                break;

            case 4:
                cursor(x,y);
                printf("       ##      ");
                cursor(x,y+1);
                printf("       ##      ");
                cursor(x,y+2);
                printf("       ##      ");
                cursor(x,y+3);
                printf("       ##      ");
                cursor(x,y+4);
                printf("       ##      ");
                cursor(x,y+5);
                printf("       ##      ");
                cursor(x,y+6);
                printf("       ##      ");
                cursor(x,y+7);
                printf("       ##      ");
                break;

            case 5:
                cursor(x,y);
                printf("               ");
                cursor(x,y+1);
                printf("  ############ ");
                cursor(x,y+2);
                printf("  #          # ");
                cursor(x,y+3);
                printf("  ##        ## ");
                cursor(x,y+4);
                printf("   ##      ##  ");
                cursor(x,y+5);
                printf("    ###  ###   ");
                cursor(x,y+6);
                printf("      ####     ");
                cursor(x,y+7);
                printf("               ");
                break;

            case 6:
                cursor(x,y);
                printf("  ############ ");
                cursor(x,y+1);
                printf("            ## ");
                cursor(x,y+2);
                printf("           ##  ");
                cursor(x,y+3);
                printf("          ##   ");
                cursor(x,y+4);
                printf("         ##    ");
                cursor(x,y+5);
                printf("        ##     ");
                cursor(x,y+6);
                printf("       ##      ");
                cursor(x,y+7);
                printf("      ##       ");
                break;

            case 0:
                cursor(x,y);
                printf("      ####     ");
                cursor(x,y+1);
                printf("    ##    ##   ");
                cursor(x,y+2);
                printf("   ##     ###  ");
                cursor(x,y+3);
                printf("  ##    ##  ## ");
                cursor(x,y+4);
                printf("  ##  ##    ## ");
                cursor(x,y+5);
                printf("   ###     ##  ");
                cursor(x,y+6);
                printf("    ##    ##   ");
                cursor(x,y+7);
                printf("      ####     ");
                break;
        }

}
// ���̾�1 �׸�2 ����3 �۴��4 �ݿ�(����)5   7   0

int slotGame(int x, int y)
{
    srand((int)time(NULL));
    int slotnum, retslotnum; //Ȯ������
    slotnum = rand()%20+1;
    if (slotnum==1) retslotnum=1; //���̾� 5%
    else if (slotnum>=2 && slotnum<6) retslotnum=2; //�׸� 20%
    else if (slotnum>=6 && slotnum<9) retslotnum=3; //���� 15%
    else if (slotnum>=9 && slotnum<11) retslotnum=4; //�۴�� 10%
    else if (slotnum>=11 && slotnum<17) retslotnum=5; //�� 30%
    else if (slotnum>=17 && slotnum<19) retslotnum=6; //7 10%
    else if (slotnum>=19 && slotnum<21) retslotnum=7; //0 10%
    
    
    slotPicPrt(retslotnum, x, y);

    return retslotnum;
}

int playSlot(int money, int *bett)
{
    int bet = *bett;
    slotPrt();

    cursor(62,1);
    printf("B E T");  //�׸��� ��� ���
    cursor(57,3);
    printf("�ߡߡ� : x50");
    cursor(57,4);
    printf("  �ߡ� : x4");
    cursor(57,5);
    printf("    �� : x2");
    cursor(57,6);
    printf("���� : x15");
    cursor(57,7);
    printf("���� : x25");
    cursor(57,8);
    printf("| | |  : x40");
    cursor(57,9);
    printf(" 7 7 7 : x50");
    cursor(57,10);
    printf(" 0 0 0 : x30");
    cursor(43, 10);
    printf("%d", money);
    cursor(3,11);
    printf("�����Ͻʽÿ�.  �����ϱ� : Enter");
    cursor(15,12);
    printf("���þ� ���� : A Z");
    cursor(43,13);
    printf("%d", bet);

    int wnum=1;
    while(wnum==1){
        int n = Key();
        switch(n){
            case UP:{
                if(bet<money){
                    bet+=10000;
                    cursor(43, 13);
                    printf("%d ", bet);
                }
                break;
            }
            case DOWN:{
                if(bet>10000){
                    bet-=10000;
                    cursor(43, 13);
                    printf("%d ", bet);   
                }
                break;
            }
            case ENT:{
                wnum=0;
                cursor(3,11);
                printf("                               ");
                cursor(4,11);
                printf("                               ");
            }
        }
    }
    *bett = bet;
    money-=bet;
    cursor(43,10);
    printf("%7d", money);
    cursor(43,11);
    RED;
    printf("-%d", bet);
    WHITE;
    cursor(6,12);
    printf("   ������ �� ���۵˴ϴ�.   ");
    PlaySound(TEXT(".\\sound\\lever.wav"), 0, SND_FILENAME | SND_ASYNC );
    Sleep(1000);
    cursor(43,11);
    printf("       ");

    wnum=1;

    int n1, n2, n3;
    //PlaySound(TEXT(".\\spin.wav"), 0, SND_FILENAME | SND_ASYNC );

    while(wnum==1){
        int n = ENT;
        switch(n){
            case ENT:{
                n1 = slotGame(2,1);
                n2 = slotGame(19,1);
                n3 = slotGame(36,1);
                //�������
                if (n1==1 && n2==1 && n3==1){
                    money+=(bet*50); // ���̾�*3 50��
                    cursor(43,10);
                    printf("%7d", money);
                    cursor(43,11);
                    GREEN;
                    printf("+%d", bet*50);
                }

                else if((n1==1 && n2==1) || (n1==1 && n3==1) || (n2==1 && n3==1)){
                    money+=(bet*4); // ���̾�*2 4��
                    cursor(43,10);
                    printf("%7d", money);
                    cursor(43,11);
                    GREEN;
                    printf("+%d", bet*4);
                }

                else if (n1==1 || n2==1 || n3==1){
                    money+=(bet*2); // ���̾�*1 2��
                    cursor(43,10);
                    printf("%7d", money);
                    cursor(43,11);
                    GREEN;
                    printf("+%d", bet*2);
                }

                else if (n1==5 || n2==5 || n3==5){ //���� �ϳ��� ������ �ƹ��͵� �������� ����

                }
                
                else if (n1==2 && n2==2 && n3==2){
                    money+=(bet*15); // �׸�*3 15��
                    cursor(43,10);
                    printf("%7d", money);
                    cursor(43,11);
                    GREEN;
                    printf("+%d", bet*15);
                }

                else if (n1==3 && n2==3 && n3==3){
                    money+=(bet*25); // ����*3 25��
                    cursor(43,10);
                    printf("%7d", money);
                    cursor(43,11);
                    GREEN;
                    printf("+%d", bet*25);
                }

                else if (n1==4 && n2==4 && n3==4){
                    money+=(bet*40); // �۴��*3 40��
                    cursor(43,10);
                    printf("%7d", money);
                    cursor(43,11);
                    GREEN;
                    printf("+%d", bet*40);
                }

                else if (n1==6 && n2==6 && n3==6){
                    money+=(bet*50); // 777 50��
                    cursor(43,10);
                    printf("%7d", money);
                    cursor(43,11);
                    GREEN;
                    printf("+%d", bet*50);
                }

                else if (n1==7 && n2==7 && n3==7){
                    money+=(bet*30); // 0*3 30��
                    cursor(43,10);
                    printf("%7d", money);
                    cursor(43,11);
                    GREEN;
                    printf("+%d", bet*30);
                }
                break;
            }
        }
        break;
    }
    return money;
}


void title()
{
    cursor(0,2);
    printf("     ####    #        ###     ####   #  ## \n");
    printf("     #   #   #       #   #   #       # ##  \n");
    printf("     ####    #       #####   #       ##    \n");
    printf("     #   #   #       #   #   #       # ##  \n");
    printf("     ####    #####   #   #    ####   #  ## \n\n");
    printf("            #    ###     ####   #  ##     \n");
    printf("            #   #   #   #       # ##      \n");
    printf("            #   #####   #       ##        \n");
    printf("            #   #   #   #       # ##      \n");
    printf("        ####    #   #    ####   #  ##     \n\n\n");
}

void stDown()
{
    cursor(1,0);
    printf("��                                              ��");
    cursor(1,1);
    printf("��              ������ �����մϴ�               ��");
    cursor(1,2);
    printf("������������������������������������������������������������������������������������������������");
    Sleep(250);
    cursor(1,1);
    printf("��              ������ �����մϴ�.              ��");
    Sleep(250);
    cursor(1,1);
    printf("��              ������ �����մϴ�..             ��");
    Sleep(250);
    cursor(1,1);
    printf("��              ������ �����մϴ�...            ��");
    Sleep(250);
}

int Key()
{
    char temp = getch();
    if(temp=='a'||temp=='A') return UP;
    else if(temp=='z'||temp=='Z') return DOWN;
    else if(temp==13) return ENT;
}


void cursor(int x, int y)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(consoleHandle, pos);
}

int menu()
{
    int x=18, y=15;
    cursor(18, 15);
    printf("> ����");
    cursor(20, 16);
    printf("���Ըӽ�");
    cursor(20, 17);
    printf("����");
    /*while(1){
        Sleep(600);
        cursor(18, 15);
        printf(" ");
        Sleep(600);
        cursor(18, 15);
        printf(">");
    }*/

    while(1){

        int n = Key();
        switch(n){
            case UP:{
                if(y>15){
                    PlaySound(TEXT(".\\sound\\select.wav"), 0, SND_FILENAME | SND_ASYNC );
                    cursor(x, y);
                    printf(" ");
                    cursor(x, --y);
                    printf(">");
                    
                }
                break;
            }
            case DOWN:{
                if(y<17){
                    PlaySound(TEXT(".\\sound\\select.wav"), 0, SND_FILENAME | SND_ASYNC );
                    cursor(x, y);
                    printf(" ");
                    cursor(x, ++y);
                    printf(">");
                    
                }
                break;
            }
            case ENT:{
                return y;
            }
        }
    }
}
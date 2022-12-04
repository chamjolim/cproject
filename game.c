#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")

#define UP 1
#define DOWN 2
#define ENT 3

#define WHITE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); //콘솔 출력 색상들
#define YELLOW SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
#define RED SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
#define GREEN SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);


void CursorView() //커서 숨기기
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
int qstRe(); //게임 이어하기 여부 블랙잭용
int qstReSlot(); //게임 이어하기 여부 슬롯용
int slotGame();
int playSlot();
void slotPicPrt();
void slotrepeatprt();

int main()
{
    system("mode con:cols=60 ilnes=60 | title KWLand");
    CursorView();

    printf("     │   A:위로  Z:아래로  ENTER:선택   │\n     └──────────────────────────────────┘\n");

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
    if (menuNum==17){ //게임 종료
        PlaySound(TEXT(".\\sound\\back.wav"), 0, SND_FILENAME | SND_ASYNC );
        stDown();
        return 0;
    }
    else if (menuNum==16){ //슬롯머신
        PlaySound(TEXT(".\\sound\\enter.wav"), 0, SND_FILENAME | SND_ASYNC );
        int bett = 10000;
        int m = playSlot(200000, &bett); //베팅금액 다음 게임에서도 유지하도록 포인터이용
        while(1){
            int qcheck = qstReSlot(m);
            if (qcheck==0){
                return 0;
            }
            else if (qcheck==1){
                if (bett>m) bett=m; //마이너스 머니 방지용
                m = playSlot(m, &bett);
            }
        }


    }
    else if (menuNum==15){ //블랙잭
        //chosUser(); 사용하지 않는 코드
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
        printf(" 포인트가 없습니다.  현재 P : %d ", m);
        cursor(4,12);
        printf("   게임이 3초 후 종료됩니다.    ");
        Sleep(3000);
        return 0;
    }
    cursor(3,11);
    printf(" 현재 P : %d  게임종료 : A ", m);
    cursor(4,12);
    printf("            게임 진행 : Enter ");
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
        printf("       포인트가 없습니다.  현재 P : %d       ", m);
        cursor(4,12);
        printf("            게임이 3초 후 종료됩니다.             ");
        Sleep(3000);
        return 0;
    }
    cursor(4,11);
    printf("               현재 P : %d              ", m);
    cursor(4,12);
    printf("     게임 종료 : A    게임 진행 : Enter      ");
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
    if(cnum>0 && cnum<14){  //카드 문양, 색 구별
        shape[0] = "♣";
        WHITE;
    }
    else if(cnum>13 && cnum<27){
        shape[0] = "♠";
        WHITE;
    }
    else if(cnum>26 && cnum<40){
        shape[0] = "♥";
        RED;
    }
    else{
        shape[0] = "◆";
        RED;
    }

    if(cnum%13==0){  //카드 숫자 구별 A, 1~10, J, Q, K
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
    // J Q K 는 10 반환, 나머지는 카드 숫자 반환
    else{
        cursor(x,y);
        printf("%s %d", shape[0], cnum);
        return cnum;
    }

}

void hidedCardPrt(int cnum)  //리턴값 없는 딜러 첫번째 카드 공개 함수
{
    char *shape[2];
    if(cnum>0 && cnum<14){
        shape[0] = "♣";
        WHITE;
    }
    else if(cnum>13 && cnum<27){
        shape[0] = "♠";
        WHITE;
    }
    else if(cnum>26 && cnum<40){
        shape[0] = "♥";
        RED;
    }
    else{
        shape[0] = "◆";
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
    printf("베팅하십시오.          베팅 액수 조정 : A Z");
    cursor(32,12);
    printf("베팅하기 : Enter");
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
    printf("베팅이 완료되었습니다.");
    Sleep(1400);
    cursor(32,12);
    printf("                ");
    for(int i=3; i>0; i--){
        cursor(4,11);
        printf("         게임이 곧 시작됩니다...%d           ", i);
        Sleep(1000);
    }
    cursor(42,2);
    printf("        ");
    cursor(4,11);
    printf("           카드를 배분합니다...           ");
    Sleep(1000);



    srand((int)time(NULL));
    int cardNum;
    int save[53];   //중복검사용 배열
    int saveArrNum=0;
    int dealSum=0, userSum=0;
    int userNum=1;
    int userY=3, dealY=3;
    int hidedCardNum;   //딜러 첫번째 카드번호 저장용
    
    int checkNum=1;
    while(checkNum==1){
        cardNum = rand()%52+1;
        for(int i=0; i<53; i++){
            if (cardNum==save[i]){
                break;
            }
            else if (i==52 && dealY==5){   // i=중복검사 통과, dealY=5 - 딜러 카드 2장 받았을 때
                cursor(4,11);
                WHITE;
                printf("           스탠드 : A   히트 : Z            ");
                wnum=1;
                while(wnum==1){
                    int n = Key();
                    switch(n){
                        case UP:{   //유저 스탠드 시
                            hidedCardPrt(hidedCardNum);
                            PlaySound(TEXT(".\\sound\\tik.wav"), 0, SND_FILENAME | SND_ASYNC );
                            Sleep(1300);
                            if(dealSum>16){  //딜러 카드 합 17이상일 떄
                                if(dealSum<=userSum && userSum<22){
                                    cursor(4,11);
                                    WHITE;
                                    if (userSum==21){
                                        printf("       승리! 플레이어는 블랙잭입니다.      ");
                                        money+=(bet*3);
                                        cursor(42,2);
                                        GREEN;
                                        printf("+%d", bet*3);
                                    }
                                    else{
                                        printf("        승리! 플레이어는 %d 입니다.     ", userSum);
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
                                    printf("        패배! 플레이어는 %d 입니다.     ", userSum);
                                    Sleep(2000);
                                    return money;
                                }
                            }
                            else if(dealSum<17){   //딜러카드합 17이하일 때 딜러 카드 더 받음
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
                                        printf("       승리! 플레이어는 블랙잭입니다.      ");
                                        money+=(bet*3);
                                        cursor(42,2);
                                        GREEN;
                                        printf("+%d", bet*3);
                                    }
                                    else{
                                        printf("        승리! 플레이어는 %d 입니다.     ", userSum);
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
                                    printf("        패배! 플레이어는 %d 입니다.        ", userSum);
                                    Sleep(2000);
                                    return money;
                                }
                            }
                        }

                        case DOWN:{   //유저 히트 시
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
                                            printf("       패배! 플레이어는 버스트입니다.     ");
                                            Sleep(2000);
                                            return money;
                                        }
                                        userY++;
                                        Sleep(1100);
                                    }
                                }
                                cursor(4,11);
                                WHITE;
                                printf("           스탠드 : A   히트 : Z            ");
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
                                                        printf("       승리! 플레이어는 블랙잭입니다.      ");
                                                        money+=(bet*3);
                                                        cursor(42,2);
                                                        GREEN;
                                                        printf("+%d", bet*3);
                                                    }
                                                    else{
                                                        printf("        승리! 플레이어는 %d 입니다.     ", userSum);
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
                                                    printf("        패배! 플레이어는 %d 입니다.     ", userSum);
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
                                                        printf("       승리! 플레이어는 블랙잭입니다.      ");
                                                        money+=(bet*3);
                                                        cursor(42,2);
                                                        GREEN;
                                                        printf("+%d", bet*3);
                                                        
                                                    }
                                                    else{
                                                        printf("        승리! 플레이어는 %d 입니다.     ", userSum);
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
                                                    printf("        패배! 플레이어는 %d 입니다.        ", userSum);
                                                    Sleep(2000);
                                                    return money;
                                                }
                                            }
                                        }
                                        case DOWN:{   //유저 재히트 시
                                            goto userHit;  
                                        }
                                    }
                                }

                            }

                        }
                    }
                }
                
            }


            else if (i==52 && userNum==1){  //유저 카드 받기
                save[saveArrNum] = cardNum;
                saveArrNum++;
                userSum+=cardPrt(cardNum, 23, userY);
                userNum=0;
                userY++;
                Sleep(1100);
            }


            else if (i==52 && userNum==0 && dealY==3){  //딜러 카드 받기(첫번째)
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


            else if (i==52 && userNum==0&& dealY!=3){  //딜러 카드 받기
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
    printf("┌───────────────┬────────────────┬────────────────┐\n"); //0
    printf("│     Dealer    │      User      │    P :         │\n");
    printf("│               │                │                │\n");
    printf("│               │                └────────────────┤\n");
    printf("│               │                   Bet :         │\n");
    printf("│               │                                 │\n"); //5
    printf("│               │                                 │\n");
    printf("│               │                                 │\n");
    printf("│               │                                 │\n");
    printf("├───────────────┴─────────────────────────────────┤\n");
    printf("│                                                 │\n"); //10
    printf("│                                                 │\n");
    printf("│                                                 │\n");
    printf("│                                                 │\n");
    printf("└─────────────────────────────────────────────────┘\n"); //14
}


void slotPrt()
{
    system("cls");
    printf("┌────────────────┬────────────────┬────────────────┐\n"); //0
    printf("│     #####      │     #####      │     #####      │\n");
    printf("│   ##     ##    │   ##     ##    │   ##     ##    │\n");
    printf("│  ##       ##   │  ##       ##   │  ##       ##   │\n");
    printf("│          ##    │          ##    │          ##    │\n");
    printf("│        ##      │        ##      │        ##      │\n"); //5
    printf("│       ##       │       ##       │       ##       │\n");
    printf("│                │                │                │\n");
    printf("│       ##       │       ##       │       ##       │\n");
    printf("├────────────────┴────────────────┴────────────────┤\n");
    printf("│                                      P :         │\n"); //10
    printf("│                                                  │\n");
    printf("│                                                  │\n");
    printf("│                                    Bet :         │\n");
    printf("└──────────────────────────────────────────────────┘\n"); //14


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
// 다이아1 네모2 세모3 작대기4 반원(꽝패)5   7   0

int slotGame(int x, int y)
{
    srand((int)time(NULL));
    int slotnum, retslotnum; //확률조정
    slotnum = rand()%20+1;
    if (slotnum==1) retslotnum=1; //다이아 5%
    else if (slotnum>=2 && slotnum<6) retslotnum=2; //네모 20%
    else if (slotnum>=6 && slotnum<9) retslotnum=3; //세모 15%
    else if (slotnum>=9 && slotnum<11) retslotnum=4; //작대기 10%
    else if (slotnum>=11 && slotnum<17) retslotnum=5; //꽝 30%
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
    printf("B E T");  //그림별 배수 출력
    cursor(57,3);
    printf("◆◆◆ : x50");
    cursor(57,4);
    printf("  ◆◆ : x4");
    cursor(57,5);
    printf("    ◆ : x2");
    cursor(57,6);
    printf("■■■ : x15");
    cursor(57,7);
    printf("▲▲▲ : x25");
    cursor(57,8);
    printf("| | |  : x40");
    cursor(57,9);
    printf(" 7 7 7 : x50");
    cursor(57,10);
    printf(" 0 0 0 : x30");
    cursor(43, 10);
    printf("%d", money);
    cursor(3,11);
    printf("베팅하십시오.  스핀하기 : Enter");
    cursor(15,12);
    printf("베팅액 조정 : A Z");
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
    printf("   게임이 곧 시작됩니다.   ");
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
                //배수조정
                if (n1==1 && n2==1 && n3==1){
                    money+=(bet*50); // 다이아*3 50배
                    cursor(43,10);
                    printf("%7d", money);
                    cursor(43,11);
                    GREEN;
                    printf("+%d", bet*50);
                }

                else if((n1==1 && n2==1) || (n1==1 && n3==1) || (n2==1 && n3==1)){
                    money+=(bet*4); // 다이아*2 4배
                    cursor(43,10);
                    printf("%7d", money);
                    cursor(43,11);
                    GREEN;
                    printf("+%d", bet*4);
                }

                else if (n1==1 || n2==1 || n3==1){
                    money+=(bet*2); // 다이아*1 2배
                    cursor(43,10);
                    printf("%7d", money);
                    cursor(43,11);
                    GREEN;
                    printf("+%d", bet*2);
                }

                else if (n1==5 || n2==5 || n3==5){ //꽝패 하나라도 있으면 아무것도 실행하지 않음

                }
                
                else if (n1==2 && n2==2 && n3==2){
                    money+=(bet*15); // 네모*3 15배
                    cursor(43,10);
                    printf("%7d", money);
                    cursor(43,11);
                    GREEN;
                    printf("+%d", bet*15);
                }

                else if (n1==3 && n2==3 && n3==3){
                    money+=(bet*25); // 세모*3 25배
                    cursor(43,10);
                    printf("%7d", money);
                    cursor(43,11);
                    GREEN;
                    printf("+%d", bet*25);
                }

                else if (n1==4 && n2==4 && n3==4){
                    money+=(bet*40); // 작대기*3 40배
                    cursor(43,10);
                    printf("%7d", money);
                    cursor(43,11);
                    GREEN;
                    printf("+%d", bet*40);
                }

                else if (n1==6 && n2==6 && n3==6){
                    money+=(bet*50); // 777 50배
                    cursor(43,10);
                    printf("%7d", money);
                    cursor(43,11);
                    GREEN;
                    printf("+%d", bet*50);
                }

                else if (n1==7 && n2==7 && n3==7){
                    money+=(bet*30); // 0*3 30배
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
    printf("│                                              │");
    cursor(1,1);
    printf("│              게임을 종료합니다               │");
    cursor(1,2);
    printf("└──────────────────────────────────────────────┘");
    Sleep(250);
    cursor(1,1);
    printf("│              게임을 종료합니다.              │");
    Sleep(250);
    cursor(1,1);
    printf("│              게임을 종료합니다..             │");
    Sleep(250);
    cursor(1,1);
    printf("│              게임을 종료합니다...            │");
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
    printf("> 블랙잭");
    cursor(20, 16);
    printf("슬롯머신");
    cursor(20, 17);
    printf("종료");
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
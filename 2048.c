#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

FILE *high;
int score = 0, num[4][4], if_move, high_score = 0;
void gotoxy(SHORT x, SHORT y);
void shift_merge(int *p, int length);
void display_box(void);
void display_number(void);
void random_number(void);
int operation(void);
int main(void)
{
    if(high = fopen("High Score", "rb"));
    {
        fread(&high_score, sizeof(int), 1, high);
        fclose(high);
    }
    int i, j, condition;
    for(i = 0; i < 4; i++)
        for(j = 0; j < 4; j++)
            num[i][j] = 0;
    random_number();
    random_number();
    display_box();
    display_number();
    condition = operation();
    if(condition)
    {
        high_score = score > high_score ? score : high_score;
        high = fopen("High Score", "wb");
        fwrite(&high_score, sizeof(int), 1, high);
        fclose(high);
        printf("\n\nGame Over!\n");
        printf("Your score is %d.\n", score);
        printf("Saving data", score);
        for(i = 0; i < 3; i++)
        {
            printf(".");
            Sleep(1000);
        }
        while(kbhit())
            _getch();
        printf("\rPress any key to quit.\n");
        _getch();
    }
    return 0;
}
void gotoxy(SHORT x, SHORT y)
{
    COORD pos = {x, y};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos);
}
void display_box(void)
{
    printf("%-18s", "Score: ");
    printf("High Score: %d\n", high_score);
    printf("Press ESC to quit.\n\n");
    printf("_____________________________________\n");
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
            printf("|        |        |        |        |\n");
        printf("|________|________|________|________|\n");
    }
}
void display_number(void)
{
    int i, j;
    for(i = 0; i < 4; i++)
        for(j = 0; j < 4; j++)
        {
            gotoxy(4 + 9 * j, 6 + 5 * i);
            printf("    \b\b\b\b");
            if(num[i][j])
                printf("%d", num[i][j]);
        }
    gotoxy(7, 0);
    printf("%d", score);
    gotoxy(0, 24);
}
void random_number(void)
{
    int position, number;
    srand((unsigned int)time(0));
    do{   
        position = rand() % 16;
        number = ((rand() % 2 & rand() % 2) + 1) * 2;
    }while(num[0][position]);
    num[0][position] = number;
}
int operation(void)
{
    int key, i, j;
    while(1)
    {
        if_move = 0;
        key = _getch();
        if(key == 27)
            return 0;
        else if(key == 72)//上
            for(i = 0; i < 4; i++)
                shift_merge(&num[0][i], 4);
        else if(key == 80)//下
            for(i = 0; i < 4; i++)
                shift_merge(&num[3][i], -4);
        else if(key == 75)//左
            for(i = 0; i < 4; i++)
                shift_merge(&num[i][0], 1);
        else if(key == 77)//右
            for(i = 0; i < 4; i++)
                shift_merge(&num[i][3], -1);
        else
            continue;
        if(if_move)
            random_number();
        else
        {
            for(i = 0; i < 16; i++)
                if(!num[0][i])
                    goto a;
            if(key == 72 || key == 80)
                for(i = 0; i < 4; i++)
                    for(j = 0; j < 3; j++)
                        if(num[i][j] == num[i][j + 1])
                            goto a;
            if(key == 75 || key == 77)
                for(i = 0; i < 4; i++)
                    for(j = 0; j < 3; j++)
                        if(num[j][i] == num[j + 1][i])
                            goto a;
            return 1;
        }
        display_number();
        a: continue;
    }
}
void shift_merge(int *p, int length)
{
    int i, j;
    for(i = 3; i > 0; i--)
        if(p[(i - 1) * length] == 0 && p[i * length] != 0)
        {    
            for(j = i; j < 4; j++)
                p[(j - 1) * length] = p[j * length];
            p[3 * length] = 0;
            if_move++;
        }
    for(i = 1; i < 4; i++)
        if(p[i * length] != 0 && p[(i - 1) * length] == p[i * length])
        {
            p[(i - 1) * length] = 2 * p[i * length];
            p[i * length] = 0;
            score += p[(i - 1) * length];
            if_move++;
        }
    for(i = 3; i > 0; i--)
        if(p[(i - 1) * length] == 0 && p[i * length] != 0)
        {    
            for(j = i; j < 4; j++)
                p[(j - 1) * length] = p[j * length];
            p[3 * length] = 0;
            if_move++;
        }
}
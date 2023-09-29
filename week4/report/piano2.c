#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>

void gotoxy(int x, int y);
void practice_piano(void);
int calc_frequency(int octave, int inx);
void print_piano(void);


int main(void)
{
	print_piano();
    practice_piano();
    return 0;
}

void print_piano(void) {
	printf("\n");
	printf("\n");
    printf("|  | | | |  |  | | | | | |  | | \n");
	printf("|  | | | |  |  | | | | | |  | | \n");
	printf("|  |w| |e|  |  |r| |t| |y|  | | \n");
	printf("|  | | | |  |  | | | | | |  | | \n");
	printf("|  ㅗㅗㅗㅗ |  ㅗㅗㅗㅗㅗㅗ |  ㅗ\n");
	printf("| a | s | d | f | g | h | j | k |\n");
	printf("_________________________________\n");
}



void practice_piano(void)
{
    int index[] = {0, 2, 4, 5, 7, 9, 11, 12};
    int freq[8];
    char code;
    int i;

    for (i = 0; i < 8; i++)
        freq[i] = calc_frequency(4, index[i]);

    do
    {
        code = getch();

        switch (code)
        {
        case 'a':
            Beep(freq[0], 300);
            break;
        case 's':
            Beep(freq[1], 300);
            break;
        case 'd':
            Beep(freq[2], 300);
            break;
        case 'f':
            Beep(freq[3], 300);
            break;
        case 'g':
            Beep(freq[4], 300);
            break;
        case 'h':
            Beep(freq[5], 300);
            break;
        case 'j':
            Beep(freq[6], 300);
            break;
        case 'k':
            Beep(freq[7], 300);
            break;
        case 'w':
            Beep(calc_frequency(4, 1), 300);
            break;
        case 'e':
            Beep(calc_frequency(4, 3), 300);
            break;
        case 'r':
            Beep(calc_frequency(4, 6), 300);
            break;
        case 't':
            Beep(calc_frequency(4, 8), 300);
            break;
        case 'y':
            Beep(calc_frequency(4, 10), 300);
            break;
        }
    } while (code != 27);
}

int calc_frequency(int octave, int inx)
{
    double do_scale = 32.7032;
    double ratio = pow(2., 1 / 12.), temp;
    int i;
    temp = do_scale * pow(2, octave - 1);
    for (i = 0; i < inx; i++)
    {
        temp = (int)(temp + 0.5);
        temp *= ratio;
    }
    return (int)temp;
}

void gotoxy(int x, int y)
{
    COORD Pos = {x - 1, y - 1};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

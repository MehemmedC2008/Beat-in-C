#include <stdio.h>
#include "CONSOLE_CONTROL.h"

typedef struct {
    int x, y;
} point;

int color[] = {39, 33};
int size = sizeof(color)/sizeof(color[0]);

void breathe(int radius, int row, int column, point middle, int speed){
    int color_num = 0;
    for (int r=0; r < radius; r++){
        move_cursor((COORD){0,0});
        for (int i=0; i<row; i++){
            for (int j=0; j<column; j++){
                point vector = {j-middle.x, i-middle.y};
                if (vector.x*vector.x + vector.y*vector.y < r*r)
                    printf("\33[%dm##\33[m", color[color_num%size]);
                else
                    printf("  ");
                color_num += 1;
            }
            printf("\n");
        }
        Sleep(speed);
        speed += 4;
    }
    Sleep(40);
    for (int r=radius-1; r >= 0; r--){
        move_cursor((COORD){0,0});
        for (int i=0; i<row; i++){
            for (int j=0; j<column; j++){
                point vector = {j-middle.x, i-middle.y};
                if (vector.x*vector.x + vector.y*vector.y < r*r)
                    printf("\33[%dm##\33[m", color[color_num%size]);
                else
                    printf("  ");
                color_num += 1;
            }
            printf("\n");
        }
        Sleep(speed);
        speed -= 4;
    }
    clear_screen();
}

int main(){
    atexit(show_cursor);
    hide_cursor();

    Coor screen = get_screen_size();
    int row = 40;
    int column = 70;
    int speed = 0;
    int radius = row/2 - 2;  
    point middle = {column/2 - 1, row/2};

    clear_screen();
    while (1)
        breathe(radius, row, column, middle, speed);
    //printf("%d %d", row, column, radius);
}
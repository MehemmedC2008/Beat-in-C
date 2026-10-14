#ifndef CONSOLE_CONTROL_H
#define CONSOLE_CONTROL_H
#include <windows.h>
#include <stdbool.h>
#include <stdio.h>

struct Coor{
    int width, height;
};
typedef struct Coor Coor;
Coor get_screen_size();
bool isChanged(Coor, Coor);
COORD get_middle(Coor);
void hide_cursor();
void show_cursor();
void move_cursor(COORD);
void clear_screen();
void draw_border(Coor);
void set_window_size(int, int);

#endif
        
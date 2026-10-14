#include "CONSOLE_CONTROL.h"


Coor get_screen_size(){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    return (Coor){width, height};
}

bool isChanged(Coor pre, Coor now){
    return (pre.height != now.height || pre.width != now.width);   
}

COORD get_middle(Coor screen_size){
    return (COORD){screen_size.width/2, screen_size.height/2};
}

void hide_cursor(){
    CONSOLE_CURSOR_INFO cursor;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
    cursor.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

void show_cursor(){
    CONSOLE_CURSOR_INFO cursor;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
    cursor.bVisible = true;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

void move_cursor(COORD position){
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void clear_screen(){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    COORD topLeft = {csbi.srWindow.Left, csbi.srWindow.Top};
    int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    DWORD size = width * height;
    DWORD written;

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    FillConsoleOutputCharacter(h, ' ', size, topLeft, &written);
    FillConsoleOutputAttribute(h, csbi.wAttributes, size, topLeft, &written);
    move_cursor(topLeft);
}

void draw_border(Coor size){
    for (int i = 0; i < size.width; i++){
        move_cursor((COORD){i, 0});
        printf("\33[33m-\33[m");
        move_cursor((COORD){i, size.height - 1});
        printf("\33[33m-\33[m");
    }
    for (int i = 1; i < size.height - 1; i++){
        move_cursor((COORD){0, i});
        printf("\33[33m|\33[m");
        move_cursor((COORD){size.width - 1, i});
        printf("\33[33m|\33[m");
    }
}    

void set_window_size(int width, int height){
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD bufferSize = {width, height};
    SetConsoleScreenBufferSize(h, bufferSize);

    SMALL_RECT windowSize = {0, 0, width-1, height-1};
    SetConsoleWindowInfo(h, TRUE, &windowSize);

    return;
}
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;
void clrscr();
void gotoxy(int x, int y);

// 화면을 모두 지운다.
void clrscr();

// 커서를 x,y좌표로 이동시킨다.
void gotoxy(int x, int y);
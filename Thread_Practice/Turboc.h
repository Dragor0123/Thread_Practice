#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;
void clrscr();
void gotoxy(int x, int y);

// ȭ���� ��� �����.
void clrscr();

// Ŀ���� x,y��ǥ�� �̵���Ų��.
void gotoxy(int x, int y);
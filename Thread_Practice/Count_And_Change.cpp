
#include <iostream>
#include <time.h>
#include <conio.h>
#include <process.h>
#include <windows.h>
#include "Turboc.h"
using namespace std;

// ������� �ϴ� ���α׷� 
//
//   Count�� ��� (�ſ� ������ �����Ѵ�)      <--- Thread_PrintCount ������
//  ------------------------------------------------------------------------
//   Main ������
//  // 5 * 5 �迭 ��� (1 ~ 25)
//  1  2  3  4   5
//  6  7  8  9  10
//  11 12 *  14 15
//  16 17 18 19 20
//  21 22 23 24 25
//
//  �� (*)�� ����ڷκ��� wasd�� �Է¹��� ������ �����¿� �����̸鼭 ������ ĭ��
//  ��ġ�� �ٲ۴�.
//

void Swap(int* _a, int* _b);
void PrintArr(int _arr[], int _colSize);
int FindPos(int _arr[], int _Size);
void MoveStar(int _arr[], char _dir, int* pos);

// Thread function
unsigned __stdcall Thread_PrintCount(void* pArguments)
{
	int iCount = 0;
	while (iCount < 1000) {
		// gotoxy(x, y) : �ܼ� Ŀ�� ��ġ�� x, y��ǥ�� �ٲ��ش�.
		gotoxy(0, 0);
		cout << iCount++ << '\n';
		Sleep(10);
	}

	_endthreadex(0);
	return 0;
}

int main()
{
	srand(unsigned(time(0)));

	int arr[25] = {};
	for (int i = 0; i < 25; ++i) {
		arr[i] = i + 1;
	}

	int pos = rand() % 25;
	arr[pos] = -1;

	HANDLE hThread;
	unsigned threadID;

	// Create the second thread.
	hThread = (HANDLE)_beginthreadex(NULL,
		0,
		&Thread_PrintCount,
		NULL,
		0,
		&threadID);

	while (true) {

		// hThread�� Suspend���·� �ٲ�
		system("cls");
		SuspendThread(hThread);
		// ���⼭ ����
		gotoxy(0, 1);
		cout << "----------------------------------------------------\n";
		PrintArr(arr, 5);
		cout << "----------------------------------------------------\n";
		cout << "�����¿� : WASD �Է�. q: ����\n";
		// ������� �������� ���� ���� �� ���� ����ؾ���
		ResumeThread(hThread); 		// hThread�� Resume���·� �ٲ�
		
		char chMove = rand() % 4;
		
		// Ű����� �ٷ� �Է� �޴´�. 
		/*char chMove = _getch();
		if (chMove == 'q' || chMove == 'Q')
			break;*/
		MoveStar(arr, chMove, &pos);
		Sleep(200);
	}
	system("cls");
	TerminateThread(hThread, 0);
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);

	cout << "���α׷��� ����Ǿ����ϴ�." << '\n';
	return 0;
}

void Swap(int* _a, int* _b)
{
	int temp = *_a;
	*_a = *_b;
	*_b = temp;
}

void PrintArr(int _arr[], int _colSize)
{
	for (int i = 0; i < _colSize; ++i) {
		for (int j = 0; j < _colSize; ++j) {
			if (_arr[_colSize * i + j] == -1)
				cout << "* \t";
			else
				cout << _arr[_colSize * i + j] << '\t';
		}
		cout << '\n';
	}
}

int FindPos(int _arr[], int _Size)
{
	for (int i = 0; i < _Size; ++i) {
		if (_arr[i] == -1)
			return i;
	}
	return -1;
}

void MoveStar(int _arr[], char _dir, int* pos)
{
	switch (_dir)
	{
	case 'W':
	case 'w':
	case 0:
		if (*pos >= 5) {
			Swap(&_arr[*pos], &_arr[*pos - 5]);
			*pos = *pos - 5;
		}
		break;
	case 'A':
	case 'a':
	case 1:
		if (*pos % 5) {
			Swap(&_arr[*pos], &_arr[*pos - 1]);
			*pos = *pos - 1;
		}
		break;
	case 'S':
	case 's':
	case 2:
		if (*pos < 20) {
			Swap(&_arr[*pos], &_arr[*pos + 5]);
			*pos = *pos + 5;
		}
		break;
	case 'D':
	case 'd':
	case 3:
		if (4 != *pos % 5) {
			Swap(&_arr[*pos], &_arr[*pos + 1]);
			*pos = *pos + 1;
		}
		break;
	default:
		break;
	}
}

//
//const std::string CurrentDateTime() {
//	time_t     now = time(0); //���� �ð��� time_t Ÿ������ ����
//	struct tm  tstruct;
//	char       buf[80];
//	localtime_s(&tstruct, &now);
//	strftime(buf, sizeof(buf), "%r", &tstruct); // YYYY-MM-DD.HH:mm:ss ������ ��Ʈ��
//
//	return buf;
//}

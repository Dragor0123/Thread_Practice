
#include <iostream>
#include <time.h>
#include <conio.h>
#include <process.h>
#include <windows.h>
#include <string>
#include "Turboc.h"
using namespace std;

// ������� �ϴ� ���α׷� (���ѷ��� ���� ���α׷�. ������ ���� ������)
//
//  Thread_curTime ������
//  ���� �ð� ���     
//  ------------------------------------------------------------------------
//   Main ������
//     * �� �����¿�� ������� �����δ�.
//
//
//


const std::string CurrentDateTime();

// Thread function
unsigned __stdcall Thread_PrintCount(void* pArguments)
{

	while (true)
	{
		// gotoxy(x, y) : �ܼ� Ŀ�� ��ġ�� x, y��ǥ�� �ٲ��ش�.
		gotoxy(0, 0);
		cout << " ���� �ð��� " << CurrentDateTime() << " �Դϴ�." << endl;
		Sleep(1000);
	}
	_endthreadex(0);
	return 0;
}

int main()
{
	srand(unsigned(time(0)));

	HANDLE hThread;
	unsigned threadID;

	// Create the second thread.
	hThread = (HANDLE)_beginthreadex(NULL,
		0,
		&Thread_PrintCount,
		NULL,
		0,
		&threadID);

	int x, y;
	x = rand() % 41;
	y = rand() % 19 + 2;
	int oldx = 0;
	int oldy = 2;
	while (true) {

		// hThread�� Suspend���·� �ٲ�
		SuspendThread(hThread);
		// ���⼭ ����
		// ���� ��ġ�� �ִ� * �� �����ش�.
		gotoxy(oldx, oldy);
		cout << ' ';

		// 0, 1��ǥ�� ��輱�� �׾��ش�.
		gotoxy(0, 1);
		cout << "---------------------------------------------------------\n";

		// �� ��ǥ�� *�� ��´�.
		gotoxy(x, y);
		cout << '*';
		oldx = x;
		oldy = y;

		// ���⿡ ���� �����¿� �����ϰ� �����δ�.
		int dir = rand() % 4;
		switch (dir)
		{
		case 0: // ��
			y--;
			y = (y < 2) ? 2 : y;
			break;
		case 1: // �Ʒ�
			y++;
			y = (y > 20) ? 20 : y;
			break;
		case 2: // ����
			x--;
			x = (x < 0) ? 0 : x;
			break;
		case 3: // ������
			x++;
			x = (x > 80) ? 80 : x;
			break;
		}
		// ������� �������� ���� ���� �� ���� ����ؾ���
		gotoxy(0, 0);
		ResumeThread(hThread); 		// hThread�� Resume���·� �ٲ�
		Sleep(500);
	}
	system("cls");
	WaitForSingleObject(hThread, 1000);
	CloseHandle(hThread);

	cout << "���α׷��� ����Ǿ����ϴ�." << '\n';
	return 0;
}

const std::string CurrentDateTime() {
	time_t     now = time(0); //���� �ð��� time_t Ÿ������ ����
	struct tm  tstruct;
	char       buf[80];
	localtime_s(&tstruct, &now);
	strftime(buf, sizeof(buf), "%r", &tstruct); // YYYY-MM-DD.HH:mm:ss ������ ��Ʈ��

	return buf;
}

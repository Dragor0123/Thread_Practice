
#include <iostream>
#include <time.h>
#include <conio.h>
#include <process.h>
#include <windows.h>
#include <string>
#include "Turboc.h"
using namespace std;

// 만들고자 하는 프로그램 (무한루프 도는 프로그램. 강제로 꺼야 꺼진다)
//
//  Thread_curTime 쓰레드
//  현재 시간 출력     
//  ------------------------------------------------------------------------
//   Main 쓰레드
//     * 이 상하좌우로 마음대로 움직인다.
//
//
//


const std::string CurrentDateTime();

// Thread function
unsigned __stdcall Thread_PrintCount(void* pArguments)
{

	while (true)
	{
		// gotoxy(x, y) : 콘솔 커서 위치를 x, y좌표로 바꿔준다.
		gotoxy(0, 0);
		cout << " 현재 시간은 " << CurrentDateTime() << " 입니다." << endl;
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

		// hThread를 Suspend상태로 바꿈
		SuspendThread(hThread);
		// 여기서 부터
		// 이전 위치에 있는 * 을 지워준다.
		gotoxy(oldx, oldy);
		cout << ' ';

		// 0, 1좌표에 경계선을 그어준다.
		gotoxy(0, 1);
		cout << "---------------------------------------------------------\n";

		// 새 좌표에 *을 찍는다.
		gotoxy(x, y);
		cout << '*';
		oldx = x;
		oldy = y;

		// 방향에 따라 상하좌우 랜덤하게 움직인다.
		int dir = rand() % 4;
		switch (dir)
		{
		case 0: // 위
			y--;
			y = (y < 2) ? 2 : y;
			break;
		case 1: // 아래
			y++;
			y = (y > 20) ? 20 : y;
			break;
		case 2: // 왼쪽
			x--;
			x = (x < 0) ? 0 : x;
			break;
		case 3: // 오른쪽
			x++;
			x = (x > 80) ? 80 : x;
			break;
		}
		// 여기까지 쓰레드의 끊김 없이 한 번에 출력해야함
		gotoxy(0, 0);
		ResumeThread(hThread); 		// hThread를 Resume상태로 바꿈
		Sleep(500);
	}
	system("cls");
	WaitForSingleObject(hThread, 1000);
	CloseHandle(hThread);

	cout << "프로그램이 종료되었습니다." << '\n';
	return 0;
}

const std::string CurrentDateTime() {
	time_t     now = time(0); //현재 시간을 time_t 타입으로 저장
	struct tm  tstruct;
	char       buf[80];
	localtime_s(&tstruct, &now);
	strftime(buf, sizeof(buf), "%r", &tstruct); // YYYY-MM-DD.HH:mm:ss 형태의 스트링

	return buf;
}
